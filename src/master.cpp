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

	bind("get_user", cppcms::rpc::json_method(&master::get_user, this), method_role);
	bind("get_domain", cppcms::rpc::json_method(&master::get_domain, this), method_role);
	bind("get_dns", cppcms::rpc::json_method(&master::get_dns, this), method_role);
	bind("get_ftp_account", cppcms::rpc::json_method(&master::get_ftp_account, this), method_role);
	bind("get_vhost", cppcms::rpc::json_method(&master::get_vhost, this), method_role);
	bind("get_mailbox", cppcms::rpc::json_method(&master::get_mailbox, this), method_role);
	bind("get_shell", cppcms::rpc::json_method(&master::get_shell, this), method_role);
	bind("get_subdomain", cppcms::rpc::json_method(&master::get_subdomain, this), method_role);
	bind("get_setting", cppcms::rpc::json_method(&master::get_setting, this), method_role);
	bind("get_database_user", cppcms::rpc::json_method(&master::get_database_user, this), method_role);
	bind("get_database", cppcms::rpc::json_method(&master::get_database, this), method_role);
	bind("get_queue", cppcms::rpc::json_method(&master::get_queue, this), method_role);
	bind("get_domain_alias", cppcms::rpc::json_method(&master::get_domain_alias, this), method_role);

	bind("get_ip", cppcms::rpc::json_method(&master::get_ip, this), method_role);

	bind("get_users", cppcms::rpc::json_method(&master::get_users, this), method_role);
	bind("get_domains", cppcms::rpc::json_method(&master::get_domains, this), method_role);
	bind("get_dns_records", cppcms::rpc::json_method(&master::get_dns_records, this), method_role);
	bind("get_ftp_accounts", cppcms::rpc::json_method(&master::get_ftp_accounts, this), method_role);
	bind("get_vhosts", cppcms::rpc::json_method(&master::get_vhosts, this), method_role);
	bind("get_mailboxes", cppcms::rpc::json_method(&master::get_mailboxes, this), method_role);
	bind("get_shells", cppcms::rpc::json_method(&master::get_shells, this), method_role);
	bind("get_subdomains", cppcms::rpc::json_method(&master::get_subdomains, this), method_role);
	bind("get_settings", cppcms::rpc::json_method(&master::get_settings, this), method_role);
	bind("get_database_types", cppcms::rpc::json_method(&master::get_database_types, this), method_role);
	bind("get_database_users", cppcms::rpc::json_method(&master::get_database_users, this), method_role);
	bind("get_databases", cppcms::rpc::json_method(&master::get_databases, this), method_role);
	bind("get_queues", cppcms::rpc::json_method(&master::get_queues, this), method_role);

	bind("update_user", cppcms::rpc::json_method(&master::update_user, this), method_role);
	bind("update_domain", cppcms::rpc::json_method(&master::update_domain, this), method_role);
	bind("update_dns", cppcms::rpc::json_method(&master::update_dns, this), method_role);
	bind("update_ftp_account", cppcms::rpc::json_method(&master::update_ftp_account, this), method_role);
	bind("update_vhost", cppcms::rpc::json_method(&master::update_vhost, this), method_role);
	bind("update_mailbox", cppcms::rpc::json_method(&master::update_mailbox, this), method_role);
	bind("update_subdomain", cppcms::rpc::json_method(&master::update_subdomain, this), method_role);
	bind("update_setting", cppcms::rpc::json_method(&master::update_setting, this), method_role);
	bind("update_database_user", cppcms::rpc::json_method(&master::update_database_user, this), method_role);
	bind("update_database", cppcms::rpc::json_method(&master::update_database, this), method_role);
	bind("update_domain_alias", cppcms::rpc::json_method(&master::update_domain_alias, this), method_role);

	/* TODO update */

	bind("delete_user", cppcms::rpc::json_method(&master::delete_user, this), method_role);
	bind("delete_domain", cppcms::rpc::json_method(&master::delete_domain, this), method_role);
	bind("delete_dns", cppcms::rpc::json_method(&master::delete_dns, this), method_role);
	bind("delete_ftp_account", cppcms::rpc::json_method(&master::delete_ftp_account, this), method_role);
	bind("delete_vhost", cppcms::rpc::json_method(&master::delete_vhost, this), method_role);
	bind("delete_mailbox", cppcms::rpc::json_method(&master::delete_mailbox, this), method_role);
	bind("delete_shell", cppcms::rpc::json_method(&master::delete_shell, this), method_role);
	bind("delete_subdomain", cppcms::rpc::json_method(&master::delete_subdomain, this), method_role);
	bind("delete_setting", cppcms::rpc::json_method(&master::delete_setting, this), method_role);
	bind("delete_database_type", cppcms::rpc::json_method(&master::delete_database_type, this), method_role);
	bind("delete_database_user", cppcms::rpc::json_method(&master::delete_database_user, this), method_role);
	bind("delete_database", cppcms::rpc::json_method(&master::delete_database, this), method_role);
	bind("delete_domain_alias", cppcms::rpc::json_method(&master::delete_domain_alias, this), method_role);
}

master::~master()
{
	if (db)	{
		delete db;
	}

	if (create_obj) {
		delete create_obj;
	}
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
	std::cout << "Sum Called" << std::endl;
	return_result(x + y);
}
#endif

void master::div(int x, int y)
{
	std::cout << "Div Called" << std::endl;
	if (y == 0) {
		return_error("Division by zero");
	} else {
		return_result(x / y);
	}
}

void master::notify(std::string msg)
{
	std::cout << "We got notification " << msg << std::endl;
}

void master::both(std::string msg)
{
	if (notification()) {
		std::cout << "We got notification " << msg << std::endl;
	} else {
		return_result("call:" + msg);
	}
}

void master::header()
{
	std::map<std::string,std::string> env = cppcms::application::request().getenv();
	std::string env2 = cppcms::application::request().getenv("HTTP_X_AUTH_TOKEN");
	std::cout << env2 << std::endl;

	for (auto p=env.begin(); p!=env.end(); ++p) {
		std::cout << "Key " << p->first << " Value " << p->second << std::endl;
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
			std::cout << "UID == " << uid << std::endl;
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

	}
}

bool master::check_authenticated(std::vector<std::string> role_types)
{
	cppdb::statement stat;

	std::string remote = cppcms::application::request().remote_addr();
	std::string token = cppcms::application::request().getenv("HTTP_X_AUTH_TOKEN"); // dont supply the http part in js or python

	std::cout << remote << std::endl;
	std::cout << token << std::endl;

	if( token.empty() )
	{
		throw no_token_ex();
		return false;
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
			return false;
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

	if(r.next()){
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

/* get */

void master::get_user()
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;

			user user(get_database(), this->get_uid_from_token());

			user.load();

			json["user"]["uid"] = user.get_uid();
			json["user"]["username"] = user.get_username();
			json["user"]["email"] = user.get_email();
			json["user"]["firstname"] = user._firstname;
			json["user"]["lastname"] = user._lastname;
			json["user"]["country"] = user._country;
			json["user"]["city"] = user._city;
			json["user"]["address"] = user._address;
			json["user"]["address_number"] = user._address_number;
			json["user"]["postal"] = user._postal;
			json["user"]["note"] = user._note;
			json["user"]["remote"] = user._remote;
			json["user"]["user_type"] = user._user_type;
			json["user"]["active"] = user._active;
			json["user"]["created"] = user.get_created();
			json["user"]["last_login"] = user.get_lastlogin();

			return_result(json);
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_domain(std::string domain_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;

			domain domain(get_database(), domain_name);

			domain.load();

			if (domain.get_user().get_uid() == this->get_uid_from_token() ) {

				json["domain"]["domainname"] = domain.name;
				json["domain"]["status"] = domain._status;
				json["domain"]["registrar"] =  domain._registrar;

				return_result(json);
			} else {
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}


void master::get_dns(std::string domain_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;

			dns dns(get_database(), 0);
			dns.load(domain_name);

			if (dns.get_domain().get_user().get_uid() == this->get_uid_from_token() ) {

				json["dns"]["address"] = dns.get_name();
				json["dns"]["created"] = dns.get_created();
				json["dns"]["domain_name"] = domain_name;

				return_result(json);
			} else {
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

// TODO add missing fields
void master::get_ftp_account(std::string ftp_username)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;

			ftp_account ftp_account(get_database(), ftp_username);
			ftp_account.load();

			if (ftp_account.get_user().get_uid() == this->get_uid_from_token() ){

				json["ftp_account"]["username"] = ftp_account.get_username();
				json["ftp_account"]["password"] = ftp_account.get_password();
				json["ftp_account"]["created"] = ftp_account.get_created();

				return_result(json);
			}
			else{
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_vhost(std::string domain_name, int vhost_id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;

			vhost vhost(get_database(),vhost_id);
			vhost.load(domain_name);

			json["vhost"]["id"] = vhost.get_id();
			json["vhost"]["name"] = vhost.get_name();
			json["vhost"]["custom_config"] = vhost.get_custom_config();
			json["vhost"]["created"] = vhost.get_created();
			json["vhost"]["active"] = vhost.get_active();

			return_result(json);
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_mailbox(std::string domain_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;

			mailbox mailbox(get_database(),0);
			mailbox.load(domain_name);

			if ( mailbox.get_domain().name.compare(domain_name) == 0) {
				json["mailbox"]["id"] = mailbox.get_id();
				json["mailbox"]["email"] = mailbox.get_email();
				json["mailbox"]["password"] = mailbox.get_password();
				json["mailbox"]["maildir"] = mailbox.get_maildir();
				json["mailbox"]["quota"] = mailbox.get_quota();
				json["mailbox"]["created"] = mailbox.get_created();
				if ( !mailbox.get_domain().name.compare("") ) { /* good enough? */
					json["mailbox"]["domain"] = mailbox.get_domain().name;
				}

				return_result(json);
			} else{
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_shell(int id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;

			shell shell(get_database(),id);
			shell.load();

			if ( shell.get_user().get_uid() == this->get_uid_from_token() ) {
				json["shell"]["created"] = shell.get_created();

				return_result(json);
			}
			else{
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* todo check if domain belongs to logged in user */
void master::get_subdomain(std::string subdomain_name, std::string domain_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;

			subdomain subdomain(get_database(),subdomain_name, domain_name);
			subdomain.load();

			json["subdomain"]["name"] = subdomain.get_name();	
			json["subdomain"]["created"] = subdomain.get_created();
			if ( subdomain.get_domain_ptr() !=  NULL ) { /* good enough? */
				json["subdomain"]["domain"] = subdomain.get_domain().name;
			}

			return_result(json);
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_setting(std::string key)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;

			app_settings app_settings(get_database(),key);
			app_settings.load();

			json["app_settings"]["key"] = app_settings.get_key();
			json["app_settings"]["value"] = app_settings.get_value();
			json["app_settings"]["default"] = app_settings.get_default();
			json["app_settings"]["description"] = app_settings.get_description();
			json["app_settings"]["updated"] = app_settings.get_updated();	
			json["app_settings"]["created"] = app_settings.get_created();

			return_result(json);
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* TODO Inspect for memory leakage */
void master::get_database_types()
{
	cppcms::json::value json;

	database_type tmp_object(get_database(),"");

	std::vector<database_type> v = tmp_object.load_all();

	int count = 0;
	for(std::vector<database_type>::iterator it = v.begin(); it != v.end(); ++it) {
    	json["database_types"][count] = it->get_name();
    	count++;
	}
	v.clear();
	return_result(json);
}

void master::get_database_user(std::string username)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;

			database_user database_user(get_database(),username);
			database_user.load();

			if ( database_user.get_user().get_uid() == this->get_uid_from_token() ) {
				json["db_user"]["username"] = database_user.get_name();
				json["db_user"]["password"] = database_user.get_password();
				json["db_user"]["permissions"] = database_user.get_permissions();
				json["db_user"]["created"] = database_user.get_created();

				return_result(json);
			}
			else {
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_database(std::string db_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;

			database database(get_database(),db_name);
			database.load();

			if ( database.get_user().get_uid() == this->get_uid_from_token()) {
				json["db"]["name"] = database.get_name();
				json["db"]["created"] = database.get_created();
				json["db"]["db_type"] = database.get_database_type().get_name();

				return_result(json);
			} else {
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_queue(int qid)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;

			queue queue(get_database(),qid);
			queue.load();

			json["queue"]["id"] = queue.qid; // TODO read only
			json["queue"]["action"] = queue._action;
			json["queue"]["params"] = queue._params;
			json["queue"]["created"] = queue.get_created();
			json["queue"]["started"] = queue._started;
			json["queue"]["finished"] = queue._finished;
			json["queue"]["uid"] = queue.get_user().get_uid();
			json["queue"]["status"] = queue._status;
			json["queue"]["result"] = queue.get_result();

			return_result(json);
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_domain_alias(int id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;

			domain_alias domain_alias(get_database(),id);
			domain_alias.load();

			json["domain_alias"]["id"] = domain_alias.get_id();
			json["domain_alias"]["domain_name"] = domain_alias.get_domain().name;
			json["domain_alias"]["source"] = domain_alias._source;
			json["domain_alias"]["destination"] = domain_alias._destination;
			json["domain_alias"]["created"] = domain_alias.get_created();
			json["domain_alias"]["active"] = domain_alias._active;

			return_result(json);
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_ip()
{
	std::string remote_address = cppcms::application::request().remote_addr();
	return_result(remote_address);
}

/* Get all */

//helper

cppdb::result master::get_result(std::ostringstream& query)
{
	cppdb::statement stat;

	stat = get_database().session() << query.str();
	std::cout << query.str() << std::endl;

	// dont reset the statement here clears the result..
	return stat.query();
}

void master::create_get_all_query(cppcms::json::value object, std::ostringstream& query)
{
	cppcms::json::value options;

	try {
		options = object["options"];
	}	catch(std::exception &e) {
		throw missing_params_ex();
	}

	cppcms::json::value start_point = options.find("start_point");
	if( !start_point.is_undefined() ) {
		query << start_point.number();
	} else {
		query << DEFAULT_START_POINT;
	}

	query << ",";

	cppcms::json::value size = options.find("size");
	if( !size.is_undefined() ) {
		query << size.number();
	} else {
		query << DEFAULT_LIMIT;
	}
}

void master::get_users(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value json;
			std::ostringstream query;
			int count = 0;

			query << "SELECT * FROM user LIMIT ";

			this->create_get_all_query(object,query);

			cppdb::result r = this->get_result(query);

			while ( r.next() ) {
				int uid;
				r >> uid;
	  			std::map<std::string,any> primary_list;
				primary_list["uid"] = uid;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::User, get_database(), primary_list);		
	  			user* tmp = dynamic_cast<user*>(model_obj.get());
				std::unique_ptr<user> user_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    user_obj.reset(tmp);
				}

				json["users"][count]["uid"] = user_obj->get_uid();
				json["users"][count]["username"] = user_obj->get_username();
				json["users"][count]["email"] = user_obj->get_email();
				json["users"][count]["firstname"] = user_obj->_firstname;
				json["users"][count]["lastname"] = user_obj->_lastname;
				json["users"][count]["country"] = user_obj->_country;
				json["users"][count]["city"] = user_obj->_city;
				json["users"][count]["address"] = user_obj->_address;
				json["users"][count]["address_number"] = user_obj->_address_number;
				json["users"][count]["postal"] = user_obj->_postal;
				json["users"][count]["note"] = user_obj->_note;
				json["users"][count]["remote"] = user_obj->_remote;
				json["users"][count]["user_type"] = user_obj->_user_type;
				json["users"][count]["active"] = user_obj->_active;
				json["users"][count]["created"] = user_obj->get_created();
				json["users"][count]["last_login"] = user_obj->get_lastlogin();

				count++;
			}
			if(!json.is_undefined())
			{
				return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_domains(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppdb::statement stat;
			cppcms::json::value json;
			std::ostringstream query;
			int count = 0;

			query << "SELECT name FROM domain WHERE uid = ? LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();
			stat << this->get_uid_from_token();

			std::cout << query.str() << std::endl;

			cppdb::result r = stat.query();

			while ( r.next() ) {
				std::string domain_name;
				r >> domain_name;
	  			std::map<std::string,any> primary_list;
				primary_list["name"] = domain_name;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Domain, get_database(), primary_list);		
	  			domain* tmp = dynamic_cast<domain*>(model_obj.get());
				std::unique_ptr<domain> domain_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    domain_obj.reset(tmp);
				}

				json["domains"][count]["domain_name"] = domain_obj->name;
				json["domains"][count]["status"] = domain_obj->_status;
				json["domains"][count]["registrar"] = domain_obj->_registrar;
				json["domains"][count]["created"] = domain_obj->get_created();
				json["domains"][count]["uid"] = domain_obj->get_user().get_uid();
				if( domain_obj->get_vhost_ptr() )
				{
					json["domains"][count]["vhost_id"] = domain_obj->get_vhost().get_id();
				}
				json["domains"][count]["active"] = domain_obj->_active;

				count++;
			}
			if(!json.is_undefined())
			{
				return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_dns_records(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppdb::statement stat;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			int count = 0;

			query << "SELECT id FROM dns WHERE domain_name = ? LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();

			cppcms::json::value options;
			try {
				options = object["options"];
				domain_name = options.get<std::string>("domain_name");
			}	catch(std::exception &e) {
				throw missing_params_ex();
			}

			stat << domain_name;
			std::cout << query.str() << std::endl;
			cppdb::result r = stat.query();

			while ( r.next() ) {
				int dns_id;
				r >> dns_id;
	  			std::map<std::string,any> primary_list;
				primary_list["id"] = dns_id;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Dns, get_database(), primary_list);		
	  			dns* tmp = dynamic_cast<dns*>(model_obj.get());
				std::unique_ptr<dns> dns_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    dns_obj.reset(tmp);
				}

				dns_obj->load(); //sigsev

				json["dns_records"][count]["id"] = dns_obj->get_id();
				json["dns_records"][count]["name"] = dns_obj->_name;
				json["dns_records"][count]["created"] = dns_obj->get_created();
				json["dns_records"][count]["domain_name"] = dns_obj->get_domain().name;
				json["dns_records"][count]["active"] = dns_obj->_active;

				count++;
			}
			if(!json.is_undefined())
			{
				return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_ftp_accounts(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppdb::statement stat;
			cppcms::json::value json;
			std::ostringstream query;
			int count = 0;

			query << "SELECT id FROM ftpuser WHERE userid = ? LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();

			stat << this->get_uid_from_token();
			std::cout << query.str() << std::endl;
			cppdb::result r = stat.query();

			while ( r.next() ) {
				int id;
				r >> id;
	  			std::map<std::string,any> primary_list;
				primary_list["id"] = id;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::FtpAccount, get_database(), primary_list);
	  			ftp_account* tmp = dynamic_cast<ftp_account*>(model_obj.get());
				std::unique_ptr<ftp_account> ftp_account_obj;


				if(tmp != nullptr)
				{
					model_obj.release();
				    ftp_account_obj.reset(tmp);
				}

				ftp_account_obj->load_id(); //sigsev


				json["ftp_accounts"][count]["id"] = ftp_account_obj->get_id();
				json["ftp_accounts"][count]["name"] = ftp_account_obj->_name;
				json["ftp_accounts"][count]["uid"] = ftp_account_obj->_uid;
				json["ftp_accounts"][count]["gid"] = ftp_account_obj->_gid;
				json["ftp_accounts"][count]["homedir"] = ftp_account_obj->_homedir;
				json["ftp_accounts"][count]["shell"] = ftp_account_obj->_shell;
				json["ftp_accounts"][count]["count"] = ftp_account_obj->get_count();
				json["ftp_accounts"][count]["userid"] = ftp_account_obj->get_user().get_uid();
				json["ftp_accounts"][count]["created"] = ftp_account_obj->get_created();
				json["ftp_accounts"][count]["accessed"] = ftp_account_obj->get_accessed();
				json["ftp_accounts"][count]["modified"] = ftp_account_obj->get_modified();

				count++;
			}
			if(!json.is_undefined())
			{
				return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_vhosts(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT id FROM vhost WHERE name = ? LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();

			try {
				options = object["options"];
				domain_name = options.get<std::string>("domain_name");
			}	catch(std::exception &e) {
				throw missing_params_ex();
			}

			stat << domain_name;
			cppdb::result r = stat.query();

			while ( r.next() ) {
				int id;
				r >> id;
	  			std::map<std::string,any> primary_list;
				primary_list["id"] = id;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Vhost, get_database(), primary_list);
	  			vhost* tmp = dynamic_cast<vhost*>(model_obj.get());
				std::unique_ptr<vhost> vhost_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    vhost_obj.reset(tmp);
				}

				vhost_obj->load(); //sigsev

				json["vhosts"][count]["id"] = vhost_obj->get_id();
				json["vhosts"][count]["name"] = vhost_obj->_name;
				json["vhosts"][count]["custom_config"] = vhost_obj->_custom_config;
				json["vhosts"][count]["created"] = vhost_obj->get_created();
				json["vhosts"][count]["active"] = vhost_obj->get_active();

				count++;
			}
			if(!json.is_undefined())
			{
				return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* NOTE this method could be more efficient:
	If the mailbox table includes an uid.
*/
void master::get_mailboxes(cppcms::json::value object) 
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;

			query << "SELECT name FROM domain WHERE uid = ?"; /* first get the domains from the logged in user */

			stat = get_database().session() << query.str();
			stat << this->get_uid_from_token();

			cppdb::result result_domain = stat.query(); /* its a reference to stat->result so if stat.reset() is called result points to empty memory */

			while ( result_domain.next() ) {
				std::string domain_name;
				int count_mailboxes = 0;
				result_domain >> domain_name;

				query.str("");
				query << "SELECT id FROM mailbox WHERE domain_name = ? LIMIT "; /* now get the mailboxes from the domains */
				this->create_get_all_query(object,query);
				stat = get_database().session() << query.str();
				stat << domain_name;

				cppdb::result result_mailbox = stat.query();
				
				while ( result_mailbox.next() ) {
					int id;
					result_mailbox >> id;
		  			std::map<std::string,any> primary_list;
					primary_list["id"] = id;

		  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Mailbox, get_database(), primary_list);
		  			mailbox* tmp = dynamic_cast<mailbox*>(model_obj.get());
					std::unique_ptr<mailbox> mailbox_obj;

					if(tmp != nullptr)
					{
						model_obj.release();
					    mailbox_obj.reset(tmp);
					}

					mailbox_obj->load(); //sigsev

					json["mailboxes"][count_mailboxes]["id"] = mailbox_obj->get_id();
					json["mailboxes"][count_mailboxes]["email"] = mailbox_obj->_email;
					json["mailboxes"][count_mailboxes]["maildir"] = mailbox_obj->_maildir;
					json["mailboxes"][count_mailboxes]["quota"] = mailbox_obj->_quota;
					json["mailboxes"][count_mailboxes]["created"] = mailbox_obj->get_created();
					json["mailboxes"][count_mailboxes]["domain_name"] = mailbox_obj->get_domain().name;
					json["mailboxes"][count_mailboxes]["bytes"] = mailbox_obj->_bytes;
					json["mailboxes"][count_mailboxes]["messages"] = mailbox_obj->_messages;
					json["mailboxes"][count_mailboxes]["active"] = mailbox_obj->_active;

					count_mailboxes++;
				}
			}
			if(!json.is_undefined())
			{
				return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_shells(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT id FROM shell WHERE uid = ? LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();

			stat << this->get_uid_from_token();
			cppdb::result r = stat.query();

			while ( r.next() ) {
				int id;
				r >> id;
	  			std::map<std::string,any> primary_list;
				primary_list["id"] = id;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Shell, get_database(), primary_list);
	  			shell* tmp = dynamic_cast<shell*>(model_obj.get());
				std::unique_ptr<shell> shell_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    shell_obj.reset(tmp);
				}

				shell_obj->load(); //sigsev

				json["shells"][count]["id"] = shell_obj->get_id();
				json["shells"][count]["uid"] = shell_obj->get_user().get_uid();
				json["shells"][count]["created"] = shell_obj->get_created();
				json["shells"][count]["active"] = shell_obj->get_active();

				count++;
			}
			if(!json.is_undefined())
			{
				return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_subdomains(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT name FROM subdomain WHERE domain_name = ? LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();

			try {
				options = object["options"];
				domain_name = options.get<std::string>("domain_name");
			}	catch(std::exception &e) {
				throw missing_params_ex();
			}

			stat << domain_name;
			cppdb::result r = stat.query();

			while ( r.next() ) {
				std::string name;
				r >> name;
	  			std::map<std::string,any> primary_list;
				primary_list["name"] = name;
				primary_list["domain_name"] = domain_name;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Subdomain, get_database(), primary_list);
	  			subdomain* tmp = dynamic_cast<subdomain*>(model_obj.get());
				std::unique_ptr<subdomain> subdomain_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    subdomain_obj.reset(tmp);
				}

				subdomain_obj->load(); //sigsev

				json["subdomains"][count]["name"] = subdomain_obj->get_name();
				json["subdomains"][count]["domain_name"] = subdomain_obj->get_domain().name;
				if( subdomain_obj->get_vhost_ptr() )
				{
					json["subdomains"][count]["vhost_id"] = subdomain_obj->get_vhost().get_id();
				}
				json["subdomains"][count]["created"] = subdomain_obj->get_created();
				json["subdomains"][count]["active"] = subdomain_obj->_active;

				count++;
			}
			if(!json.is_undefined())
			{
				return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_settings(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT `key` FROM settings LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();

			cppdb::result r = stat.query();

			while ( r.next() ) {
				std::string key;
				r >> key;
	  			std::map<std::string,any> primary_list;
				primary_list["key"] = key;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::AppSettings, get_database(), primary_list);
	  			app_settings* tmp = dynamic_cast<app_settings*>(model_obj.get());
				std::unique_ptr<app_settings> app_settings_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    app_settings_obj.reset(tmp);
				}

				app_settings_obj->load(); //sigsev

				json["app_settings"][count]["key"] = app_settings_obj->get_key();
				json["app_settings"][count]["value"] = app_settings_obj->get_value();
				json["app_settings"][count]["description"] = app_settings_obj->get_description();
				json["app_settings"][count]["updated"] = app_settings_obj->get_updated();
				json["app_settings"][count]["created"] = app_settings_obj->get_created();

				count++;
			}
			if(!json.is_undefined())
			{
				return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_database_users(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT name FROM user_db_user WHERE uid = ? LIMIT ";

			this->create_get_all_query(object,query);
			stat = get_database().session() << query.str();
			stat << this->get_uid_from_token();

			cppdb::result r = stat.query();

			while ( r.next() ) {
				std::string name;
				r >> name;
	  			std::map<std::string,any> primary_list;
				primary_list["name"] = name;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::DatabaseUser, get_database(), primary_list);
	  			database_user* tmp = dynamic_cast<database_user*>(model_obj.get());
				std::unique_ptr<database_user> database_user_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    database_user_obj.reset(tmp);
				}

				database_user_obj->load(); //sigsev

				json["database_users"][count]["name"] = database_user_obj->get_name();
				json["database_users"][count]["permissions"] = database_user_obj->get_permissions();
				json["database_users"][count]["created"] = database_user_obj->get_created();
				json["database_users"][count]["uid"] = database_user_obj->get_user().get_uid();

				count++;
			}
			if(!json.is_undefined())
			{
				return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::get_databases(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT name FROM user_db WHERE uid = ? LIMIT ";

			this->create_get_all_query(object,query);
			stat = get_database().session() << query.str();
			stat << this->get_uid_from_token();

			cppdb::result r = stat.query();

			while ( r.next() ) {
				std::string name;
				r >> name;
	  			std::map<std::string,any> primary_list;
				primary_list["name"] = name;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Database, get_database(), primary_list);
	  			database* tmp = dynamic_cast<database*>(model_obj.get());
				std::unique_ptr<database> database_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    database_obj.reset(tmp);
				}

				database_obj->load(); //sigsev

				json["databases"][count]["name"] = database_obj->get_name();
				json["databases"][count]["created"] = database_obj->get_created();
				json["databases"][count]["type"] = database_obj->get_database_type().get_name();
				json["databases"][count]["uid"] = database_obj->get_user().get_uid();

				count++;
			}
			if(!json.is_undefined())
			{
				return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/*
 base on uid?
 */
void master::get_queues(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT qid FROM queue WHERE uid = ? LIMIT ";

			this->create_get_all_query(object,query);
			stat = get_database().session() << query.str();
			stat << this->get_uid_from_token();

			cppdb::result r = stat.query();

			while ( r.next() ) {
				int qid;
				r >> qid;
	  			std::map<std::string,any> primary_list;
				primary_list["qid"] = qid;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Queue, get_database(), primary_list);
	  			queue* tmp = dynamic_cast<queue*>(model_obj.get());
				std::unique_ptr<queue> queue_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    queue_obj.reset(tmp);
				}

				queue_obj->load(); //sigsev

				json["queues"][count]["qid"] = queue_obj->qid;
				json["queues"][count]["action"] = queue_obj->_action;
				json["queues"][count]["params"] = queue_obj->_params;
				json["queues"][count]["created"] = queue_obj->get_created();
				json["queues"][count]["started"] = queue_obj->_started;
				json["queues"][count]["finished"] = queue_obj->_finished;
				json["queues"][count]["uid"] = queue_obj->get_user().get_uid();
				json["queues"][count]["status"] = queue_obj->_status;
				json["queues"][count]["result"] = queue_obj->get_result();

				count++;
			}
			if(!json.is_undefined())
			{
				return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* Update */

/* password,email,fname,lname,country,city,address,postal,note,user_type,active */
void master::update_user(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {

			int uid = -1;
			std::map<std::string,any> primary_list;
			primary_list["uid"] = uid;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::User, get_database(), primary_list), ModelFactory::ModelType::User);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* status, registrar, vhost_id */
void master::update_domain(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			
			std::string domain_name = "";
			std::map<std::string,any> primary_list;
			primary_list["name"] = domain_name;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Domain, get_database(), primary_list), ModelFactory::ModelType::Domain);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* address */
void master::update_dns(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			
			int dns_id = -1;
			std::map<std::string,any> primary_list;
			primary_list["id"] = dns_id;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Dns, get_database(), primary_list), ModelFactory::ModelType::Dns);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* password, permissions */
void master::update_ftp_account(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			
			std::string ftp_account = "";
			std::map<std::string,any> primary_list;
			primary_list["name"] = ftp_account;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::FtpAccount, get_database(), primary_list), ModelFactory::ModelType::FtpAccount);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* name ?, custom_config */ 
void master::update_vhost(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {

			int vhost_id = -1;
			std::map<std::string,any> primary_list;
			primary_list["id"] = vhost_id;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Vhost, get_database(), primary_list), ModelFactory::ModelType::Vhost);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* address */
void master::update_mailbox(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {

			int mailbox_id = -1;
			std::map<std::string,any> primary_list;
			primary_list["id"] = mailbox_id;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Mailbox, get_database(), primary_list), ModelFactory::ModelType::Mailbox);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* subdomain name , vhost_id */
void master::update_subdomain(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {

			std::string domain_name = "";
			std::string subdomain_name = "";
			std::map<std::string,any> primary_list;
			primary_list["name"] = subdomain_name;
			primary_list["domain_name"] = domain_name;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Subdomain, get_database(), primary_list), ModelFactory::ModelType::Subdomain);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* value, default, description */
void master::update_setting(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		if ( this->check_authenticated(role_types) ) {

			std::string key = "";
			std::map<std::string,any> primary_list;
			primary_list["key"] = key;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::AppSettings, get_database(), primary_list), ModelFactory::ModelType::AppSettings);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* password, permissions */
void master::update_database_user(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {

			std::string username = "";
			std::map<std::string,any> primary_list;
			primary_list["name"] = username;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::DatabaseUser, get_database(), primary_list), ModelFactory::ModelType::DatabaseUser);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* database_type */
void master::update_database(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {

			std::string name = "";
			std::map<std::string,any> primary_list;
			primary_list["name"] = name;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Database, get_database(), primary_list), ModelFactory::ModelType::Database);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}


void master::update_domain_alias(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {

			int id = -1;
			std::map<std::string,any> primary_list;
			primary_list["id"] = id;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::DomainAlias, get_database(), primary_list), ModelFactory::ModelType::DomainAlias);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

/* delete */

void master::delete_user(std::string username)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			user user(get_database(), this->get_uid_from_token());

			user.load();

			if ( user.m_delete() ) {
				return_result("OK");
			} else {
				return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::delete_domain(std::string domain_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			domain domain(get_database(),domain_name);

			domain.load();

			if ( domain.m_delete() ) {
				return_result("OK");
			} else {
				return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::delete_dns(int dns_id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			dns dns(get_database(),dns_id);

			dns.load();

			if ( dns.m_delete() ) {
				return_result("OK");
			} else {
				return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::delete_ftp_account(std::string ftp_username)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			ftp_account ftp_account(get_database(),ftp_username);

			ftp_account.load();

			if ( ftp_account.m_delete() ) {
				return_result("OK");
			} else {
				return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::delete_vhost(int vhost_id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			vhost vhost(get_database(),vhost_id);

			vhost.load();

			if ( vhost.m_delete() ) {
				return_result("OK");
			} else {
				return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::delete_mailbox(int mailbox_id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			mailbox mailbox(get_database(),mailbox_id);

			mailbox.load();

			if ( mailbox.m_delete() ) {
				return_result("OK");
			} else {
				return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::delete_shell(int id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			shell shell(get_database(),id);

			shell.load();

			if ( shell.m_delete() ) {
				return_result("OK");
			} else {
				return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::delete_subdomain(std::string subdomain_name, std::string domain_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			subdomain subdomain(get_database(),subdomain_name,domain_name);

			subdomain.load();

			if ( subdomain.m_delete() ) {
				return_result("OK");
			} else {
				return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::delete_setting(std::string key)
{
	app_settings app_settings(get_database(),key);

	app_settings.load();
	if ( app_settings.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_database_type(std::string name)
{
	database_type database_type(get_database(),name);

	database_type.load();

	if ( database_type.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_database_user(std::string username)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			database_user database_user(get_database(),username);

			database_user.load();
			if ( database_user.m_delete() ) {
				return_result("OK");
			} else {
				return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::delete_database(std::string db_name, std::string db_username)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			database database(get_database(),db_name);

			database.load();
			user_dbuser_db connect(get_database(),db_username,db_name);
			if ( connect.m_delete() ) {
				if ( database.m_delete() ) {
					return_result("OK");
				}
				else {
					return_error("Failed to delete database, and remove connection with username");
				}
			} else {
				return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::delete_domain_alias(int id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( this->check_authenticated(role_types) ) {
			domain_alias domain_alias(get_database(), id);

			domain_alias.load();
			if ( domain_alias.get_domain().get_user().get_uid() == this->get_uid_from_token() ){
				if ( domain_alias.m_delete() ) {
					return_result("OK");
				} else {
					return_error("Delete failed");
				}
			} else {
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		return_error(e.what());
	}
}


/* Helper methods */

std::map<std::string, any> master::create_generic(cppcms::json::value object, ModelFactory::ModelType type)
{
	cppcms::json::object ob_req;
	cppcms::json::object ob_opt;
	try {
		ob_req = object.get<cppcms::json::object>("required_list");
		ob_opt = object.get<cppcms::json::object>("optional_list");
	}	catch(std::exception &e) {
		throw missing_params_ex();
	}
	std::map<std::string, any> list;
	std::map<std::string, any> primary_list_empty;

	for (cppcms::json::object::const_iterator p=ob_req.begin(); p!=ob_req.end(); ++p) {
		this->convert(ModelFactory::createModel(type, get_database(), primary_list_empty), p->first, p->second, list);
	}

	for (cppcms::json::object::const_iterator p=ob_opt.begin(); p!=ob_opt.end(); ++p) {
		this->convert(ModelFactory::createModel(type, get_database(), primary_list_empty), p->first, p->second, list);
	}
	return list;
}

/* Dump map contents */
void dump_map(const std::map<std::string,any>& map) {
	for (std::map<std::string, any>::const_iterator it = map.begin(); it != map.end(); it++) {
		std::cout << "Key: " << it->first << std::endl;
		std::cout << "Value: " << std::endl;
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

bool master::convert(std::unique_ptr<model> tmp, cppcms::string_key first, cppcms::json::value second, std::map<std::string,any> &update_list)
{
	// std::cout << "convert" << std::endl;
	// std::cout << "Field " << first.str() << std::endl;
	if ( tmp->model::compare_field(first.str()) ) {
		switch(second.type()) {
			case cppcms::json::json_type::is_number: 
			{
				update_list[first.str()] = any((int)second.number());
				break;
			}
			case cppcms::json::json_type::is_string: 
			{
				std::string val = (std::string)second.str();
				update_list[first.str()] = any(val);
				break;
			}
			case cppcms::json::json_type::is_boolean:
			{
				update_list[first.str()] = any((bool)second.boolean());
				break;
			}
			default:
				break;
		}
		// dump_map(update_list);
		return true;
	}
	std::cout << "field " << first.str() << std::endl;
	throw unrecognized_field_ex();
	return false;
}

any master::get_identifier(std::string primary_field, cppcms::string_key first, cppcms::json::value second)
{
	std::cout << "Called get get_identifier" << std::endl;
	std::cout << first.str() << primary_field << std::endl;
	if( primary_field.compare(first.str()) == 0){
		switch(second.type())
		{
			case cppcms::json::json_type::is_number: 
			{
				return (int)second.number();
				break;
			}
			case cppcms::json::json_type::is_string: 
			{
				std::string val = (std::string)second.str();
				return val;
				break;
			}
			case cppcms::json::json_type::is_boolean:
			{
				return (bool)second.boolean();
				break;
			}
			case cppcms::json::json_type::is_undefined:
			{
				std::cout << "Undefined type detected, trying to convert to string" << std::endl;
				std::string val = (std::string)second.str();
				return val;
				break;
			}
			default:
			{
				return -1;
				break;
			}
		}
	}
	std::cout << " Primary field doesnt match " << std::endl;
	return -1;
}

bool master::check_default(any value)
{
	switch (value.tag) {
		case any::CHAR:
			std::cout << " String " << std::endl;
			if( ((std::string)value.string).empty() )
			{
				return true;
			}
			return false;
			break;
		case any::INT:
			std::cout << " Integer " << std::endl;
			if( value.integer == -1 )
			{
				return true;
			}
			return false;
			break;
		default: 
			std::cout << "Default case" << std::endl;
			return true;
	}
}

bool master::check_default(std::map<std::string,any> primary_list)
{
	int count_defaults = 0;
	for ( auto it = primary_list.begin(); it != primary_list.end(); ++it ) {
		switch ((*it).second.tag) {
			case any::CHAR:
				if( ((std::string)(*it).second.string).empty() )
				{
					count_defaults++;
				}
				break;
			case any::INT:
				if( (*it).second.integer == -1 )
				{
					count_defaults++;
				}
				break;
			default: 
				count_defaults++;
				break;
		}
	}
	if(count_defaults == 0 )
	{
		return false;
	} else {
		return true;
	}
}

bool master::check_primary_field(std::vector<any> primary_list, std::string field)
{
	for ( auto it = primary_list.begin(); it != primary_list.end(); ++it ) {
		if(field.compare((*it).string) == 0)
		{
			return true;
		}
	}
	return false;
}

// TODO check if primary fields are supplied
void master::update_generic(cppcms::json::value object, std::unique_ptr<model> tmp, ModelFactory::ModelType type)
{
	try{
		std::map<std::string, any> update_list;
		cppcms::json::object ob = object.get<cppcms::json::object>("update_list");
		std::map<std::string, any> primary_list;
		std::map<std::string, any> primary_list_empty;
		std::map<std::string, any> primary_info = tmp->get_primary_info();

		for (cppcms::json::object::const_iterator p=ob.begin(); p!=ob.end(); ++p) {
			bool primary = false;
			for ( auto it = primary_info.begin(); it != primary_info.end(); ++it ) {
				if( this->check_default( (*it).second) && tmp->model::compare_primary_field(p->first) && (it->first.compare(p->first) == 0) ) {
					primary_list[it->first] = this->get_identifier( (*it).first, p->first.str(), p->second);
					primary = true;
				} 
			}
			if ( primary ) {
				continue; // skip primary value
			}
			this->convert(ModelFactory::createModel(type, get_database(), primary_list_empty), p->first, p->second, update_list);
		}
		dump_map(primary_list);
		if ( !this->check_default(primary_list) ) {
			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, get_database(), primary_list);
			if (model_obj->model::update(update_list)) {
				return_result("OK");
			} else { 
				return_error("Failed to update model");
			}
		}
	} catch(std::exception &e) {
		std::cout << "User update Exception : " << e.what() << std::endl;
		return_error(e.what());
	}
}

