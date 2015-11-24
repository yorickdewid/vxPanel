#ifndef MASTER_H
#define MASTER_H

#include <cppcms/application.h>
#include <cppcms/rpc_json.h>

#include "backend.h"

class master: public cppcms::rpc::json_rpc_server {

public:
	master(cppcms::service &srv);
	~master();
	backend& get_database();
	void sum(int x, int y);
	void div(int x, int y);
	void notify(std::string msg);
	void both(std::string msg);
	void system_uptime();
	void version();
	void db_version();

	void create_user(std::string username);
	void create_domain(std::string domain_name,int uid);
	void create_dns(std::string address, std::string domain_name);
	void create_ftp_account(std::string ftp_account,std::string password,std::string permissions, int uid);
	void create_vhost(std::string domain_name, std::string custom_config, int uid);
	void create_mailbox(std::string name, std::string address, std::string domain_name, int uid);
	void create_shell(int uid);
	void create_subdomain(std::string subdomain_name, std::string domain_name, int uid);
	void create_setting(std::string key, std::string value, bool default_, std::string description);
	void create_database_user(std::string name, std::string password, std::string permissions, int uid);
	void create_database(std::string db_name, std::string db_type, std::string db_username, int uid);

	void get_user(int uid);
	void get_domain(std::string domain_name,int uid);
	void get_dns(std::string domain_name,int uid);
	void get_ftp_account(std::string ftp_account, int uid);
	void get_vhost(std::string domain_name, int uid);
	void get_mailbox(std::string domain_name, int uid);
	void get_shell(int uid);
	void get_subdomain(std::string subdomain, int uid);
	void get_settings(std::string key);
	void get_database_types();
	void get_database_user(int uid);
	void get_database(int uid);

protected:
	std::string format_uptime(std::string sec);

private:
	backend *db = NULL;
	void init_backend();

};

#endif /* MASTER_H */

