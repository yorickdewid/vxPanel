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
	void create_domain(std::string domain_name, int uid);
	void create_dns(std::string name, std::string domain_name);
	void create_ftp_account(std::string ftp_account,std::string password,std::string permissions, int uid);
	void create_vhost(std::string domain_name, std::string custom_config, int uid);
	void create_mailbox(std::string address, std::string domain_name, int uid);
	void create_shell(int uid);
	void create_subdomain(std::string subdomain_name, std::string domain_name, int uid);
	void create_setting(std::string key, std::string value, bool default_, std::string description);
	void create_database_user(std::string name, std::string password, std::string permissions, int uid);
	void create_database(std::string db_name, std::string db_type, std::string db_username, int uid);

	void get_user(int uid);
	void get_domain(std::string domain_name, int uid);
	void get_dns(std::string domain_name, int uid);
	void get_ftp_account(std::string ftp_account, int uid);
	void get_vhost(std::string domain_name, int uid);
	void get_mailbox(std::string domain_name, int uid);
	void get_shell(int id, int uid);
	void get_subdomain(std::string subdomain_name, std::string domain_name, int uid);
	void get_setting(std::string key);
	void get_database_types();
	void get_database_user(std::string username, int uid);
	void get_database(std::string db_name, int uid);
	void get_ip();

	void update_user(int uid, std::vector<std::string> update_list); /* password,email,fname,lname,country,city,address,postal,note,user_type,active */
	void update_domain(int uid, std::string domain_name, std::vector<std::string> update_list); /* status, registrar, vhost_id */
	void update_dns(int uid, int dns_id, std::vector<std::string> update_list); /* address */
	void update_ftp_account(int uid, std::string ftp_account, std::vector<std::string> update_list); /* password, permissions */
	void update_vhost(int uid, std::string domain_name, std::vector<std::string> update_list); /* name ?, custom_config */ 
	void update_mailbox(int uid, std::string domain_name, std::vector<std::string> update_list); /* address */
	void update_subdomain(int uid, std::string subdomain_name, std::vector<std::string> update_list); /* subdomain name , vhost_id */
	void update_setting(std::string key); /* value, default, description */
	void update_database_user(int uid, std::string username); /* password, permissions */
	void update_database(int uid, std::string db_name, std::vector<std::string> update_list); /* database_type */

	void delete_user(std::string username, int uid);
	void delete_domain(std::string domain_name, int uid);
	void delete_dns(int dns_id, int uid);
	void delete_ftp_account(std::string ftp_username, int uid);
	void delete_vhost(int vhost_id, int uid);
	void delete_mailbox(int mailbox_id, int uid);
	void delete_shell(int id, int uid);
	void delete_subdomain(std::string subdomain_name, std::string domain_name, int uid);
	void delete_setting(std::string key);
	void delete_database_type(std::string name);
	void delete_database_user(std::string username, int uid);
	void delete_database(std::string db_name, std::string username, int uid);

	void write_ip_to_db(); /* both ivp4 and ipv6 */

protected:
	std::string format_uptime(std::string sec);

private:
	backend *db = NULL;
	void init_backend();

};

#endif /* MASTER_H */

