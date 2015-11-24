#include <cppcms/json.h>
#include <cppcms/session_interface.h>
#include <cppcms/url_mapper.h>
#include <iostream>
#include <fstream>

#include "master.h"
#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"

#include "user.h"
#include "domain.h"
#include "dns.h"
#include "ftp_account.h"
#include "vhost.h"
#include "mailbox.h"
#include "shell.h"
#include "subdomain.h"
#include "settings.h"
#include "database.h"
#include "database_user.h"
#include "database_type.h"

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
	bind("get_settings", cppcms::rpc::json_method(&master::get_settings, this), method_role);
	bind("get_database_types", cppcms::rpc::json_method(&master::get_database_types, this), method_role);
	bind("get_database_user", cppcms::rpc::json_method(&master::get_database_user, this), method_role);
	bind("get_database", cppcms::rpc::json_method(&master::get_database, this), method_role);
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
	ftp_account.set_user(std::shared_ptr<user>(new user(get_database(),uid)));

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

void master::create_mailbox(std::string name, std::string address, std::string domain_name, int uid)
{
	mailbox mailbox(get_database(),0);

	mailbox.set_name(name);
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
	subdomain subdomain(get_database(),0);

	subdomain.set_name(subdomain_name);
	subdomain.set_domain(std::shared_ptr<domain>(new domain(get_database(),domain_name)));

	subdomain.save();

	return_result("OK");
}

void master::create_setting(std::string key, std::string value, bool default_, std::string description)
{
	settings settings(get_database(),key);

	settings.set_value(value);
    settings.set_default(default_);
	settings.set_description(description);

	settings.save();

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

void master::create_database(std::string db_name, std::string db_type, int uid)
{
	try{
		database database(get_database(),db_name);

		database.set_database_type(std::shared_ptr<database_type>(new database_type(get_database(),db_type)));
		database.set_user(std::shared_ptr<user>(new user(get_database(),uid)));

		database.save();

		return_result("OK");
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

void master::get_ftp_account(std::string ftp_account, int uid)
{

}

void master::get_vhost(std::string domain_name, int uid)
{

}

void master::get_mailbox(std::string domain_name, int uid)
{

}

void master::get_shell(int uid)
{

}

void master::get_subdomain(std::string subdomain, int uid)
{

}

void master::get_settings(std::string key)
{

}

void master::get_database_types()
{

}

void master::get_database_user(int uid)
{

}

void master::get_database(int uid)
{

}


