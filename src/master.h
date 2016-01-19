#ifndef MASTER_H
#define MASTER_H

#include <cppcms/application.h>
#include <cppcms/rpc_json.h>

#include "backend.h"
#include "any.h"
#include "model.h"
#include "ModelFactory.h"

class master: public cppcms::rpc::json_rpc_server {

public:
	master(cppcms::service &srv);
	~master();
	backend& get_database();
	void sum(int x, int y);
	void div(int x, int y);
	void notify(std::string msg);
	void both(std::string msg);
	void header();
	void system_uptime();
	void version();
	void db_version();

	void authenticate(std::string username, std::string password);

	void create_user(cppcms::json::value object);
	void create_domain(cppcms::json::value object);
	void create_dns(cppcms::json::value object);
	void create_ftp_account(cppcms::json::value object);
	void create_vhost(cppcms::json::value object);
	void create_mailbox(cppcms::json::value object);
	void create_shell(cppcms::json::value object);
	void create_subdomain(cppcms::json::value object);
	void create_setting(cppcms::json::value object);
	void create_database_user(cppcms::json::value object);
	void create_database(cppcms::json::value object);
	void create_queue(cppcms::json::value object);

	void get_user();
	void get_domain(std::string domain_name);
	void get_dns(std::string domain_name);
	void get_ftp_account(std::string ftp_account);
	void get_vhost(std::string domain_name, int vhost_id);
	void get_mailbox(std::string domain_name);
	void get_shell(int id);
	void get_subdomain(std::string subdomain_name, std::string domain_name);
	void get_setting(std::string key);
	void get_database_user(std::string username);
	void get_database(std::string db_name);
	void get_queue(int qid);
	void get_ip();

	/* LISTS */
	void get_users(cppcms::json::value object); // admin only for now
	void get_domains(); // get domains for 1 user
	void get_dns_records(std::string domain_name); // get all dns records for 1 domain
	void get_ftp_accounts(std::string ftp_account); // get all ftp accounts for 1 user
	void get_vhosts(std::string domain_name); // get all vhosts for 1 domain
	void get_mailboxes(std::string domain_name); // get all mailboxes for 1 domain
	void get_shells(); // get all shells for 1 domain 
	void get_subdomains(); // get all subdomains for 1 user
	void get_settings(std::string key); // get all settings (admin only)
	void get_database_types(); // get all subdomains for 1 user
	void get_database_users(); // get all database users for 1 user
	void get_databases(); // get all databases for 1 user
	void get_queues(); // get all queues for 1 user

	void update_user(cppcms::json::value object);
	void update_domain(cppcms::json::value object);
	void update_dns( cppcms::json::value object);
	void update_ftp_account(cppcms::json::value object);
	void update_vhost(cppcms::json::value object);
	void update_mailbox(cppcms::json::value object);
	void update_subdomain(cppcms::json::value object);
	void update_setting(cppcms::json::value object);
	void update_database_user(cppcms::json::value object);
	void update_database(cppcms::json::value object);

	void delete_user(std::string username);
	void delete_domain(std::string domain_name);
	void delete_dns(int dns_id);
	void delete_ftp_account(std::string ftp_username);
	void delete_vhost(int vhost_id);
	void delete_mailbox(int mailbox_id);
	void delete_shell(int id);
	void delete_subdomain(std::string subdomain_name, std::string domain_name);
	void delete_setting(std::string key);
	void delete_database_type(std::string name);
	void delete_database_user(std::string username);
	void delete_database(std::string db_name, std::string username);

	cppdb::result get_result(std::ostringstream query);
	std::map<std::string, any> create_generic(cppcms::json::value object, ModelFactory::ModelType type);
	bool check_default(any value);
	bool check_default(std::map<std::string,any> primary_list);
	bool check_primary_field(std::vector<any> primary_list, std::string field);
	void update_generic(cppcms::json::value object, std::unique_ptr<model> tmp, ModelFactory::ModelType type);
	bool convert(std::unique_ptr<model> tmp, cppcms::string_key first, cppcms::json::value second, std::map<std::string,any> &update_list);
	any get_identifier(std::string primary_field, cppcms::string_key first, cppcms::json::value second);

protected:
	std::string format_uptime(std::string sec);

private:
	std::string create_auth_token(int uid);
	bool check_authenticated(std::vector<std::string> role_types);
	bool is_role_allowed(std::vector<std::string> role_types, int uid);
	int get_uid_from_token();
	void init_backend();

	backend *db = NULL;

};

#endif /* MASTER_H */

