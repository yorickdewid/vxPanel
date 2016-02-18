#include <booster/log.h>
#include <cppcms/json.h>
#include <cppcms/session_interface.h>
#include <cppcms/url_mapper.h>
#include <cppcms/http_request.h>
#include <iostream>
#include <fstream>
#include <typeinfo>

#include "master.h"
#include "config.h"
#include "exceptions.h"
#include "model.h"
#include "any.h"
#include "model/models.h"
#include "constants.h"
#include "validation/domain_validator.h"
#include "function/create.h"
#include "function/get.h"
#include "function/get_multiple.h"
#include "function/update.h"
#include "function/delete_m.h"

/*
 * Bind JSON RPC calls to class methods
 */
master::master(cppcms::service &srv) : cppcms::rpc::json_rpc_server(srv)
{
	init_backend();

#ifdef SAMPLE
	bind("sum", cppcms::rpc::json_method(&master::sum, this), method_role);
	bind("div", cppcms::rpc::json_method(&master::div, this), method_role);
	bind("notify", cppcms::rpc::json_method(&master::notify, this), notification_role);
	bind("both", cppcms::rpc::json_method(&master::both, this));
#endif
	bind("header", cppcms::rpc::json_method(&master::header, this), method_role);
	bind("authenticate", cppcms::rpc::json_method(&master::authenticate, this), method_role);
	// bind("logged_in", cppcms::rpc::json_method(&master::check_authenticated, this), method_role);
	bind("uptime", cppcms::rpc::json_method(&master::system_uptime, this), method_role);
	bind("version", cppcms::rpc::json_method(&master::version, this), method_role);
	bind("db_version", cppcms::rpc::json_method(&master::db_version, this), method_role);
	bind("get_ip", cppcms::rpc::json_method(&master::get_ip, this), method_role);

	create_obj = new create( get_database(), this);
	bind("create_user", cppcms::rpc::json_method(&create::create_user, create_obj), method_role);
	bind("create_domain", cppcms::rpc::json_method(&create::create_domain, create_obj), method_role);
	bind("create_dns", cppcms::rpc::json_method(&create::create_dns, create_obj), method_role);
	bind("create_ftp_account",cppcms::rpc::json_method(&create::create_ftp_account, create_obj), method_role);
	bind("create_vhost",cppcms::rpc::json_method(&create::create_vhost, create_obj), method_role);
	bind("create_mailbox",cppcms::rpc::json_method(&create::create_mailbox, create_obj), method_role);
	bind("create_shell",cppcms::rpc::json_method(&create::create_shell, create_obj), method_role);
	bind("create_subdomain",cppcms::rpc::json_method(&create::create_subdomain, create_obj), method_role);
	bind("create_setting",cppcms::rpc::json_method(&create::create_setting, create_obj), method_role);
	bind("create_database_user", cppcms::rpc::json_method(&create::create_database_user, create_obj), method_role);
	bind("create_database", cppcms::rpc::json_method(&create::create_database, create_obj), method_role);
	bind("create_queue", cppcms::rpc::json_method(&create::create_queue, create_obj), method_role);
	bind("create_domain_alias", cppcms::rpc::json_method(&create::create_domain_alias, create_obj), method_role);

	get_obj = new get( get_database(), this);
	bind("get_user", cppcms::rpc::json_method(&get::get_user, get_obj), method_role);
	bind("get_domain", cppcms::rpc::json_method(&get::get_domain, get_obj), method_role);
	bind("get_dns", cppcms::rpc::json_method(&get::get_dns, get_obj), method_role);
	bind("get_ftp_account", cppcms::rpc::json_method(&get::get_ftp_account, get_obj), method_role);
	bind("get_vhost", cppcms::rpc::json_method(&get::get_vhost, get_obj), method_role);
	bind("get_mailbox", cppcms::rpc::json_method(&get::get_mailbox, get_obj), method_role);
	bind("get_shell", cppcms::rpc::json_method(&get::get_shell, get_obj), method_role);
	bind("get_subdomain", cppcms::rpc::json_method(&get::get_subdomain, get_obj), method_role);
	bind("get_setting", cppcms::rpc::json_method(&get::get_setting, get_obj), method_role);
	bind("get_database_user", cppcms::rpc::json_method(&get::get_database_user, get_obj), method_role);
	bind("get_database", cppcms::rpc::json_method(&get::get_database, get_obj), method_role);
	bind("get_queue", cppcms::rpc::json_method(&get::get_queue, get_obj), method_role);
	bind("get_domain_alias", cppcms::rpc::json_method(&get::get_domain_alias, get_obj), method_role);

	get_multiple_obj = new get_multiple( get_database(), this);
	bind("get_users", cppcms::rpc::json_method(&get_multiple::get_users, get_multiple_obj), method_role);
	bind("get_domains", cppcms::rpc::json_method(&get_multiple::get_domains, get_multiple_obj), method_role);
	bind("get_dns_records", cppcms::rpc::json_method(&get_multiple::get_dns_records, get_multiple_obj), method_role);
	bind("get_ftp_accounts", cppcms::rpc::json_method(&get_multiple::get_ftp_accounts, get_multiple_obj), method_role);
	bind("get_vhosts", cppcms::rpc::json_method(&get_multiple::get_vhosts, get_multiple_obj), method_role);
	bind("get_mailboxes", cppcms::rpc::json_method(&get_multiple::get_mailboxes, get_multiple_obj), method_role);
	bind("get_shells", cppcms::rpc::json_method(&get_multiple::get_shells, get_multiple_obj), method_role);
	bind("get_subdomains", cppcms::rpc::json_method(&get_multiple::get_subdomains, get_multiple_obj), method_role);
	bind("get_settings", cppcms::rpc::json_method(&get_multiple::get_settings, get_multiple_obj), method_role);
	bind("get_database_types", cppcms::rpc::json_method(&get_multiple::get_database_types, get_multiple_obj), method_role);
	bind("get_database_users", cppcms::rpc::json_method(&get_multiple::get_database_users, get_multiple_obj), method_role);
	bind("get_databases", cppcms::rpc::json_method(&get_multiple::get_databases, get_multiple_obj), method_role);
	bind("get_queues", cppcms::rpc::json_method(&get_multiple::get_queues, get_multiple_obj), method_role);

 	update_obj = new update( get_database(), this);
	bind("update_user", cppcms::rpc::json_method(&update::update_user, update_obj), method_role);
	bind("update_domain", cppcms::rpc::json_method(&update::update_domain, update_obj), method_role);
	bind("update_dns", cppcms::rpc::json_method(&update::update_dns, update_obj), method_role);
	bind("update_ftp_account", cppcms::rpc::json_method(&update::update_ftp_account, update_obj), method_role);
	bind("update_vhost", cppcms::rpc::json_method(&update::update_vhost, update_obj), method_role);
	bind("update_mailbox", cppcms::rpc::json_method(&update::update_mailbox, update_obj), method_role);
	bind("update_subdomain", cppcms::rpc::json_method(&update::update_subdomain, update_obj), method_role);
	bind("update_setting", cppcms::rpc::json_method(&update::update_setting, update_obj), method_role);
	bind("update_database_user", cppcms::rpc::json_method(&update::update_database_user, update_obj), method_role);
	bind("update_database", cppcms::rpc::json_method(&update::update_database, update_obj), method_role);
	bind("update_domain_alias", cppcms::rpc::json_method(&update::update_domain_alias, update_obj), method_role);

	delete_m_obj = new delete_m( get_database(), this);
	bind("delete_user", cppcms::rpc::json_method(&delete_m::delete_user, delete_m_obj), method_role);
	bind("delete_domain", cppcms::rpc::json_method(&delete_m::delete_domain, delete_m_obj), method_role);
	bind("delete_dns", cppcms::rpc::json_method(&delete_m::delete_dns, delete_m_obj), method_role);
	bind("delete_ftp_account", cppcms::rpc::json_method(&delete_m::delete_ftp_account, delete_m_obj), method_role);
	bind("delete_vhost", cppcms::rpc::json_method(&delete_m::delete_vhost, delete_m_obj), method_role);
	bind("delete_mailbox", cppcms::rpc::json_method(&delete_m::delete_mailbox, delete_m_obj), method_role);
	bind("delete_shell", cppcms::rpc::json_method(&delete_m::delete_shell, delete_m_obj), method_role);
	bind("delete_subdomain", cppcms::rpc::json_method(&delete_m::delete_subdomain, delete_m_obj), method_role);
	bind("delete_setting", cppcms::rpc::json_method(&delete_m::delete_setting, delete_m_obj), method_role);
	bind("delete_database_type", cppcms::rpc::json_method(&delete_m::delete_database_type, delete_m_obj), method_role);
	bind("delete_database_user", cppcms::rpc::json_method(&delete_m::delete_database_user, delete_m_obj), method_role);
	bind("delete_database", cppcms::rpc::json_method(&delete_m::delete_database, delete_m_obj), method_role);
	bind("delete_domain_alias", cppcms::rpc::json_method(&delete_m::delete_domain_alias, delete_m_obj), method_role);
}

master::~master()
{
	delete db; // must exist otherwise we cannot function
	delete create_obj;
	delete get_obj;
	delete get_multiple_obj;
	delete update_obj;
	delete delete_m_obj;
}

void master::init_backend()
{
	std::string user = settings().get<std::string>("db.user");
	std::string password = settings().get<std::string>("db.password");
	std::string database = settings().get<std::string>("db.database");
	db = new backend(user, password, database);
}

backend& master::get_database()
{
	return *db;
}

#ifdef SAMPLE
void master::sum(int x, int y)
{
	BOOSTER_DEBUG("master") << "Sum Called" << std::endl;
	return_result(x + y);
}
#endif

void master::div(int x, int y)
{
	BOOSTER_DEBUG("master") << "Div Called" << std::endl;
	if (y == 0) {
		return_error("Division by zero");
	} else {
		return_result(x / y);
	}
}

void master::notify(std::string msg)
{
	BOOSTER_DEBUG("master") << "We got notification " << msg << std::endl;
}

void master::both(std::string msg)
{
	if (notification()) {
		BOOSTER_DEBUG("master") << "We got notification " << msg << std::endl;
	} else {
		return_result("call:" + msg);
	}
}

void master::header()
{
	std::map<std::string,std::string> env = cppcms::application::request().getenv();
	std::string env2 = cppcms::application::request().getenv("HTTP_X_AUTH_TOKEN");
	BOOSTER_INFO("master") << env2 << std::endl;

	for (auto p=env.begin(); p!=env.end(); ++p) {
		BOOSTER_INFO("master") << "Key " << p->first << " Value " << p->second << std::endl;
	}
	return_result("OK");
}

std::string master::format_uptime(std::string sec){
	std::ostringstream os;

	long seconds = atol(sec.c_str());
	unsigned int days = seconds / 86400;
	seconds = seconds % 86400;
	unsigned int hours = seconds / 3600;
	seconds = seconds % 3600;
	unsigned int mins = seconds / 60;
	seconds = seconds % 60;
	unsigned int secs = seconds;

	os << days << " days " << ", " << hours << ":" << mins << ":" << secs << std::endl;
	std::string s = os.str();
	return s;
}

void master::system_uptime()
{
	std::ifstream uptime;
	std::string result;
	uptime.open("/proc/uptime");

	if (uptime.is_open()) { 
		for(
			std::string line;
			getline( uptime, line );
		)
		{
			std::size_t pos = line.find(" ");
			std::string s = line.substr(0, pos);
			result = format_uptime(s);
		}
	}

	uptime.close();
	return_result(result);
}

void master::version()
{
	std::ostringstream os;

	os << "VxPanel version " << VERSION;
	return_result(os.str());
}

void master::db_version()
{
	return_result(db->version().c_str());
}

void master::authenticate(std::string username, std::string password)
{
	try{
		cppdb::statement stat;
		std::ostringstream query;

		// check if already authenticated

		query << "SELECT uid FROM user WHERE username = ? AND password = encrypt(?,password)";
		stat = get_database().session() << query.str() << username << password;
		cppdb::result r = stat.query();
		bool error;

		if(r.next())
		{
			int uid = -1;
			r.fetch(0, uid);
			BOOSTER_INFO("master") << "UID == " << uid << std::endl;
			if( uid != -1 ) {
				std::string remote_address = cppcms::application::request().remote_addr();
				/*  check if already authenticated */
				stat.reset();
				stat = get_database().session() << 
				"SELECT * FROM auth_token WHERE uid = ? and remote = inet6_aton(?) and valid > now()" << uid << remote_address;
				cppdb::result r = stat.query();
				if ( r.next() ) {
					cppcms::json::value json;
					std::string token,refresh,valid;

					r.fetch(0,token);
					r.fetch(3,refresh);
					r.fetch(5,valid);

					json["auth"]["token"] = token;
					json["auth"]["refresh_token"] = refresh;
					json["auth"]["valid"] = valid;

					return_result(json);
				} else {
					std::string token;
					token = this->create_auth_token(uid);
					if ( !token.empty() ){
						cppcms::json::value json;
						
						auth_token auth_token(get_database(),token,remote_address);
						auth_token.load();

						json["auth"]["token"] = auth_token.session_id;
						json["auth"]["refresh_token"] = auth_token._refresh;
						json["auth"]["valid"] = auth_token._valid;

						return_result(json);
					} else {
						error = true;
					}
				}
			} else {
				error = true;
			}
			if( error ) {
				return_error("Failed to create token");
			}
		} else {
			return_error("Incorrect credentials");
		}
	}
	catch (std::exception &e)
	{
		return_error(e.what());
	}
}

bool master::check_authenticated(std::vector<std::string> role_types)
{
	cppdb::statement stat;

	std::string remote = cppcms::application::request().remote_addr();
	std::string token = cppcms::application::request().getenv("HTTP_X_AUTH_TOKEN"); // dont supply the http part in js or python

	BOOSTER_INFO("master") << remote << std::endl;
	BOOSTER_INFO("master") << token << std::endl;

	if( token.empty() ) {
		throw no_token_ex();
	}

	if(token.size() != 40) {
		return_error("invalid token supplied");
	} else {
		stat = get_database().session() << 
			"SELECT * FROM auth_token WHERE sessionid = ? and remote = inet6_aton(?) and valid > now()" << token << remote;
		cppdb::result r = stat.query();

		if(r.next()){
			int uid = -1;
			r.fetch(2, uid);
			if ( uid != -1 ) {
				if ( this->is_role_allowed(role_types, uid) ) {
					return true;
				} else {
					throw auth_ex();
				}
			}
			return false;
		} else {
			throw token_not_valid_ex();
		}
	}
	return false;
}

bool master::is_role_allowed(std::vector<std::string> role_types, int uid)
{
	user user(get_database(),uid);
	user.load();

	if ( user.model::get_saved() ) {
		for ( auto it = role_types.begin(); it != role_types.end(); ++it ) {
			if ( (*it).compare(user._user_type) == 0 )
			{
				return true;
			}
		}
	}
	return false;
}

int master::get_uid_from_token()
{
	cppdb::statement stat;

	std::string remote = cppcms::application::request().remote_addr();
	std::string token = cppcms::application::request().getenv("HTTP_X_AUTH_TOKEN"); // dont supply the http part in js or python

	stat = get_database().session() << 
			"SELECT * FROM auth_token WHERE sessionid = ? and remote = inet6_aton(?) and valid > now()" << token << remote;
	cppdb::result r = stat.query();

	if ( r.next() ) {
		int uid = -1;
		r.fetch(2, uid);
		return uid;
	}
	return -1;
}


std::string master::create_auth_token(int uid)
{
	try{
		std::string remote_address = cppcms::application::request().remote_addr();

		auth_token auth_token(get_database());

		auth_token.remote = remote_address;
		auth_token.set_user(std::shared_ptr<user>(new user(get_database(),uid)));

		auth_token.save();

		if( auth_token.model::get_saved() ) {
			return auth_token.session_id;
		} else {
			return "";
		}
	} catch(std::exception &e) {
		return "";
	}
}

void master::get_ip()
{
	std::string remote_address = cppcms::application::request().remote_addr();
	return_result(remote_address);
}

/* Helper methods */

/* Dump map contents */
void dump_map(const std::map<std::string,any>& map) {
	for (std::map<std::string, any>::const_iterator it = map.begin(); it != map.end(); it++) {
		BOOSTER_DEBUG("master") << "Key: " << it->first << std::endl;
		BOOSTER_DEBUG("master") << "Value: " << std::endl;
		switch (it->second.tag) {
			case any::CHAR:
				puts(it->second.string);
				break;
			case any::LONG_INT:
				printf("%ld\n", it->second.long_integer);
				break;
			case any::LL_INT:
				printf("%lld\n", it->second.ll_integer);
				break;
			case any::INT:
				printf("%d\n", it->second.integer);
				break;
			case any::BOOL:
				printf("%d\n", it->second.boolean);
				break;
		}
	}
}

bool master::check_primary_field(std::vector<any> primary_list, std::string field)
{
	for ( auto it = primary_list.begin(); it != primary_list.end(); ++it ) {
		if ( field.compare((*it).string) == 0 ) {
			return true;
		}
	}
	return false;
}

