#include <cppcms/json.h>
#include <cppcms/session_interface.h>
#include <cppcms/url_mapper.h>
#include <iostream>
#include <fstream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "user.h"
#include "domain.h"
#include "master.h"

/*
 * Bind JSON RPC calls to class methods
 */
master::master(cppcms::service &srv) : cppcms::rpc::json_rpc_server(srv)
{
	std::string conn = settings().get<std::string>("db.connection_string");
	db = new backend(conn);

	bind("sum", cppcms::rpc::json_method(&master::sum, this), method_role);
	bind("div", cppcms::rpc::json_method(&master::div, this), method_role);
	bind("notify", cppcms::rpc::json_method(&master::notify, this), notification_role);
	bind("both", cppcms::rpc::json_method(&master::both, this));
	bind("uptime", cppcms::rpc::json_method(&master::system_uptime, this), method_role);
	bind("version", cppcms::rpc::json_method(&master::version, this), method_role);
	bind("db_version", cppcms::rpc::json_method(&master::db_version, this), method_role);
	bind("new_user", cppcms::rpc::json_method(&master::new_user, this), method_role);
	bind("get_user", cppcms::rpc::json_method(&master::get_user, this), method_role);
	bind("new_domain", cppcms::rpc::json_method(&master::new_domain, this), method_role);
	bind("get_domain", cppcms::rpc::json_method(&master::get_domain, this), method_role);
}

master::~master()
{
	if (db)
		delete db;
}

backend& master::database()
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

void master::new_user(std::string name)
{
	user user(database(), name);

	user.password("kaas");
	user.email("info@kaas.nl");

	user.save();
	return_result("OK");
}

void master::get_user(std::string username)
{
	cppcms::json::value json;

	user user(database(), username);

	user.load();

	json["user"]["username"] = user.get_username();
	json["user"]["email"] =  user.get_email();

	return_result(json);
}

void master::new_domain(std::string domain_name)
{
	domain domain(database(), domain_name);

	domain.status("inactive");
	domain.registrar("transip");
	domain.user_id(1);

	domain.save();
	return_result("OK");
}

void master::get_domain(std::string domain_name)
{
	cppcms::json::value json;

	domain domain(database(), domain_name);

	domain.load();

	json["domain"]["domainname"] = domain.get_domain_name();
	json["domain"]["status"] = domain.get_status();
	json["domain"]["registrar"] =  domain.get_registrar();

	return_result(json);
}

