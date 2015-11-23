#ifndef MASTER_H
#define MASTER_H

#include <cppcms/application.h>
#include <cppcms/rpc_json.h>

#include "backend.h"

class master: public cppcms::rpc::json_rpc_server {

public:
	master(cppcms::service &srv);
	~master();
	backend& database();
	void sum(int x, int y);
	void div(int x, int y);
	void notify(std::string msg);
	void both(std::string msg);
	void system_uptime();
	void version();
	void db_version();
	void new_user(std::string name);
	void get_user(std::string name);
	void new_domain(std::string domain_name);
	void get_domain(std::string domain_name);
	void create_dns(std::string address, std::string domain_name);

protected:
	std::string format_uptime(std::string sec);

private:
	backend *db = NULL;
	void init_backend();

};

#endif /* MASTER_H */

