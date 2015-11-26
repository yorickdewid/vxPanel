#include <cppcms/json.h>
#include <cppcms/session_interface.h>
#include <cppcms/url_mapper.h>
#include <iostream>
#include <fstream>

#include "master.h"
#include "config.h"
#include "exceptions.h"
#include "model.h"

#include "model/user.h"
#include "model/domain.h"
#include "model/dns.h"
#include "model/ftp_account.h"
#include "model/vhost.h"
#include "model/mailbox.h"
#include "model/shell.h"
#include "model/subdomain.h"
#include "model/app_settings.h"
#include "model/database.h"
#include "model/database_user.h"
#include "model/database_type.h"
#include "model/user_dbuser_db.h"

/*
 * Bind JSON RPC calls to class methods
 */
master::master(cppcms::service &srv) : cppcms::rpc::json_rpc_server(srv)
{
	init_backend();

	bind("sum", cppcms::rpc::json_method(&master::sum, this), method_role);
	bind("div", cppcms::rpc::json_method(&master::div, this), method_role);
	bind("notify", cppcms::rpc::json_method(&master::notify, this), notification_role);
	bind("both", cppcms::rpc::json_method(&master::both, this));
	bind("uptime", cppcms::rpc::json_method(&master::system_uptime, this), method_role);
	bind("version", cppcms::rpc::json_method(&master::version, this), method_role);
	bind("db_version", cppcms::rpc::json_method(&master::db_version, this), method_role);

	bind("create_user", cppcms::rpc::json_method(&master::create_user, this), method_role);
	bind("create_domain", cppcms::rpc::json_method(&master::create_domain, this), method_role);
	bind("create_dns", cppcms::rpc::json_method(&master::create_dns, this), method_role);
	bind("create_ftp_account",cppcms::rpc::json_method(&master::create_ftp_account, this), method_role);
	bind("create_vhost",cppcms::rpc::json_method(&master::create_vhost, this), method_role);
	bind("create_mailbox",cppcms::rpc::json_method(&master::create_mailbox, this), method_role);
	bind("create_shell",cppcms::rpc::json_method(&master::create_shell, this), method_role);
	bind("create_subdomain",cppcms::rpc::json_method(&master::create_subdomain, this), method_role);
	bind("create_setting",cppcms::rpc::json_method(&master::create_setting, this), method_role);
	bind("create_database_user", cppcms::rpc::json_method(&master::create_database_user, this), method_role);
	bind("create_database", cppcms::rpc::json_method(&master::create_database, this), method_role);

	bind("get_user", cppcms::rpc::json_method(&master::get_user, this), method_role);
	bind("get_domain", cppcms::rpc::json_method(&master::get_domain, this), method_role);
	bind("get_dns", cppcms::rpc::json_method(&master::get_dns, this), method_role);
	bind("get_ftp_account", cppcms::rpc::json_method(&master::get_ftp_account, this), method_role);
	bind("get_vhost", cppcms::rpc::json_method(&master::get_vhost, this), method_role);
	bind("get_mailbox", cppcms::rpc::json_method(&master::get_mailbox, this), method_role);
	bind("get_shell", cppcms::rpc::json_method(&master::get_shell, this), method_role);
	bind("get_subdomain", cppcms::rpc::json_method(&master::get_subdomain, this), method_role);
	bind("get_setting", cppcms::rpc::json_method(&master::get_setting, this), method_role);
	bind("get_database_types", cppcms::rpc::json_method(&master::get_database_types, this), method_role);
	bind("get_database_user", cppcms::rpc::json_method(&master::get_database_user, this), method_role);
	bind("get_database", cppcms::rpc::json_method(&master::get_database, this), method_role);

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
	bind("delete_database_user", cppcms::rpc::json_method(&master::delete_database_user, this), method_role);
	bind("delete_database", cppcms::rpc::json_method(&master::delete_database, this), method_role);
}

master::~master()
{
	if (db)
		delete db;
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

void master::sum(int x, int y)
{
	std::cout << "Sum Called" << std::endl;
	return_result(x + y);
}

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

void master::create_user(std::string username)
{
	user user(get_database());

	user.set_username(username);
	user.set_password("kaas");
	user.set_email("info@kaas.nl");

	user.save();

	return_result("OK");
}

void master::create_domain(std::string domain_name, int uid)
{
	domain domain(get_database(), domain_name);

	domain.status("inactive");
	domain.registrar("transip");
	domain.set_user(std::shared_ptr<user>(new user(get_database(),uid)));

	domain.save();

	return_result("OK");
}

void master::create_dns(std::string address, std::string domain_name)
{
	dns dns(get_database(),0);

	dns.set_address(address);
	dns.set_domain(std::shared_ptr<domain>(new domain(get_database(),domain_name)));

	dns.save();

	return_result("OK");
}

void master::create_ftp_account(std::string ftp_username, std::string password, std::string permissions, int uid)
{
	ftp_account ftp_account(get_database(),ftp_username);

	ftp_account.set_password(password);
	ftp_account.set_permissions(permissions);

	std::shared_ptr<user> point(new user(get_database(),uid));
	ftp_account.set_user(point);

	ftp_account.save();

	return_result("OK");
}

void master::create_vhost(std::string name, std::string custom_config, int uid)
{
	vhost vhost(get_database(),0);

	vhost.set_name(name); /* either domain or subdomain */
	vhost.set_custom_config(custom_config);

	vhost.save();

	return_result("OK");
}

void master::create_mailbox(std::string address, std::string domain_name, int uid)
{
	mailbox mailbox(get_database(),0);

	mailbox.set_address(address);
	mailbox.set_domain(std::shared_ptr<domain>(new domain(get_database(),domain_name)));

	mailbox.save();

	return_result("OK");
}

void master::create_shell(int uid)
{
	shell shell(get_database(),0);

	shell.set_user(std::shared_ptr<user>(new user(get_database(),uid)));

	shell.save();

	return_result("OK");
}

void master::create_subdomain(std::string subdomain_name, std::string domain_name, int uid)
{
	subdomain subdomain(get_database(),subdomain_name, domain_name);

	subdomain.save();

	return_result("OK");
}

void master::create_setting(std::string key, std::string value, bool default_, std::string description)
{
	app_settings app_settings(get_database(),key);

	app_settings.set_value(value);
    app_settings.set_default(default_);
	app_settings.set_description(description);

	app_settings.save();

	return_result("OK");
}

void master::create_database_user(std::string name, std::string password, std::string permissions, int uid)
{
	database_user database_user(get_database(),name);

	database_user.set_password(password);
	database_user.set_permissions(permissions);
	database_user.set_user(std::shared_ptr<user>(new user(get_database(),uid)));

	database_user.save();

	return_result("OK");
}

void master::create_database(std::string db_name, std::string db_type, std::string db_username, int uid)
{
	try{
		database database(get_database(),db_name);

		database.set_database_type(std::shared_ptr<database_type>(new database_type(get_database(),db_type)));
		database.set_user(std::shared_ptr<user>(new user(get_database(),uid)));

		database.save();

		/* now connect the db_username and db_name */
		user_dbuser_db connect(get_database(),db_username,db_name);
		connect.save();

		if ( connect.get_saved() ) {
			return_result("OK");
		}
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

/* get */

void master::get_user(int uid)
{
	cppcms::json::value json;

	user user(get_database(), uid);

	user.load();

	json["user"]["username"] = user.get_username();
	json["user"]["password"] = user.get_password();
	json["user"]["email"] =  user.get_email();

	return_result(json);
}

void master::get_domain(std::string domain_name, int uid)
{
	cppcms::json::value json;

	domain domain(get_database(), domain_name);

	domain.load();

	json["domain"]["domainname"] = domain.get_domain_name();
	json["domain"]["status"] = domain.get_status();
	json["domain"]["registrar"] =  domain.get_registrar();

	return_result(json);
}

void master::get_dns(std::string domain_name, int uid)
{
	cppcms::json::value json;

	dns dns(get_database(), 0);
	dns.load(domain_name);

	json["dns"]["address"] = dns.get_address();
	json["dns"]["created"] = dns.get_created();
	json["dns"]["domain_name"] = domain_name;

	return_result(json);
}

void master::get_ftp_account(std::string ftp_username, int uid)
{
	cppcms::json::value json;

	ftp_account ftp_account(get_database(), ftp_username);
	ftp_account.load();

	if (ftp_account.get_user().get_uid() == uid){

		json["ftp_account"]["username"] = ftp_account.get_username();
		json["ftp_account"]["password"] = ftp_account.get_password();
		json["ftp_account"]["permissions"] = ftp_account.get_permissions();
		json["ftp_account"]["created"] = ftp_account.get_created();
		if ( ftp_account.get_domain_ptr() !=  NULL ) { /* good enough? */
			json["ftp_account"]["domain"] = ftp_account.get_domain().get_domain_name();
		}

		return_result(json);
	}
	else{
		return_error("Unauthorized");
	}
}

void master::get_vhost(std::string domain_name, int uid)
{
	cppcms::json::value json;

	vhost vhost(get_database(),0);
	vhost.load(domain_name);

	json["vhost"]["id"] = vhost.get_id();
	json["vhost"]["name"] = vhost.get_name();
	json["vhost"]["custom_config"] = vhost.get_custom_config();
	json["vhost"]["created"] = vhost.get_created();

	return_result(json);
}

void master::get_mailbox(std::string domain_name, int uid)
{
	cppcms::json::value json;

	mailbox mailbox(get_database(),0);
	mailbox.load(domain_name);

	if ( mailbox.get_domain().get_domain_name().compare(domain_name) == 0) {
		json["mailbox"]["id"] = mailbox.get_id();
		json["mailbox"]["address"] = mailbox.get_address();
		json["mailbox"]["created"] = mailbox.get_created();
		if ( !mailbox.get_domain().get_domain_name().compare("") ) { /* good enough? */
			json["mailbox"]["domain"] = mailbox.get_domain().get_domain_name();
		}

		return_result(json);
	}
	else{
		return_error("Unauthorized");
	}
}

void master::get_shell(int id,int uid)
{
	cppcms::json::value json;

	shell shell(get_database(),uid);
	shell.load();

	if ( shell.get_user().get_uid() == uid) {
		json["shell"]["created"] = shell.get_created();

		return_result(json);
	}
	else{
		return_error("Unauthorized");
	}
}

/* todo check if domain belongs to logged in user */
void master::get_subdomain(std::string subdomain_name, std::string domain_name, int uid)
{
	cppcms::json::value json;

	subdomain subdomain(get_database(),subdomain_name, domain_name);
	subdomain.load();

	json["subdomain"]["name"] = subdomain.get_name();	
	json["subdomain"]["created"] = subdomain.get_created();
	if ( subdomain.get_domain_ptr() !=  NULL ) { /* good enough? */
			json["subdomain"]["domain"] = subdomain.get_domain().get_domain_name();
	}

	return_result(json);
}

void master::get_setting(std::string key)
{
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

void master::get_database_user(std::string username, int uid)
{

	cppcms::json::value json;

	database_user database_user(get_database(),username);
	database_user.load();

	if ( database_user.get_user().get_uid() == uid ) {
		json["db_user"]["username"] = database_user.get_name();
		json["db_user"]["password"] = database_user.get_password();
		json["db_user"]["permissions"] = database_user.get_permissions();
		json["db_user"]["created"] = database_user.get_created();

		return_result(json);
	}
	else {
		return_error("Unauthorized");
	}
}

void master::get_database(std::string db_name, int uid)
{
	cppcms::json::value json;

	database database(get_database(),db_name);
	database.load();

	if ( database.get_user().get_uid() == uid ) {
		json["db"]["name"] = database.get_name();
		json["db"]["created"] = database.get_created();
		json["db"]["db_type"] = database.get_database_type().get_name();

		return_result(json);
	}
	else {
		return_error("Unauthorized");
	}
}

/* Update */

/* password,email,fname,lname,country,city,address,postal,note,user_type,active */
void master::update_user(int uid, std::vector<std::string> update_list)
{

}

/* status, registrar, vhost_id */
void master::update_domain(int uid, std::string domain_name, std::vector<std::string> update_list)
{

}

/* address */
void master::update_dns(int uid, int dns_id, std::vector<std::string> update_list)
{

}

/* password, permissions */
void master::update_ftp_account(int uid, std::string ftp_account, std::vector<std::string> update_list)
{

}

/* name ?, custom_config */ 
void master::update_vhost(int uid, std::string domain_name, std::vector<std::string> update_list)
{

}

/* address */
void master::update_mailbox(int uid, std::string domain_name, std::vector<std::string> update_list)
{

}

/* subdomain name , vhost_id */
void master::update_subdomain(int uid, std::string subdomain_name, std::vector<std::string> update_list)
{

}

/* value, default, description */
void master::update_setting(std::string key)
{

}

/* password, permissions */
void master::update_database_user(int uid, std::string username)
{

}

/* database_type */
void master::update_database(int uid, std::string db_name, std::vector<std::string> update_list)
{

}

/* delete */

void master::delete_user(std::string username, int uid)
{
	user user(get_database(),uid);

	user.load();

	if ( user.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_domain(std::string domain_name, int uid)
{
	domain domain(get_database(),domain_name);

	domain.load();

	if ( domain.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_dns(int dns_id, int uid)
{
	dns dns(get_database(),dns_id);

	dns.load();

	if ( dns.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_ftp_account(std::string ftp_username, int uid)
{
	ftp_account ftp_account(get_database(),ftp_username);

	ftp_account.load();

	if ( ftp_account.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_vhost(int vhost_id, int uid)
{
	vhost vhost(get_database(),vhost_id);

	vhost.load();

	if ( vhost.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_mailbox(int mailbox_id, int uid)
{
	mailbox mailbox(get_database(),mailbox_id);

	mailbox.load();

	if ( mailbox.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_shell(int id, int uid)
{
	shell shell(get_database(),id);

	shell.load();

	if ( shell.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_subdomain(std::string subdomain_name, std::string domain_name, int uid)
{
	subdomain subdomain(get_database(),subdomain_name,domain_name);

	subdomain.load();

	if ( subdomain.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
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

void master::delete_database_user(std::string username, int uid)
{
	database_user database_user(get_database(),username);

	database_user.load();
	if ( database_user.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_database(std::string db_name, std::string db_username, int uid)
{
	database database(get_database(),db_name);

	database.load();
	if ( database.m_delete() ) {
		user_dbuser_db connect(get_database(),db_username,db_name);
		if ( connect.m_delete() ) {
			return_result("OK");
		}
		else {
			return_error("Failed to delete database, and remove connection with username");
		}
	} else {
		return_error("Delete failed");
	}
}

