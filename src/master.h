#ifndef MASTER_H
#define MASTER_H

#include <cppcms/application.h>
#include <cppcms/rpc_json.h>

#include "backend.h"
#include "any.h"
#include "model.h"
#include "ModelFactory.h"

class create;
class get;
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

	void get_ip();

	/* LISTS */
	void get_users(cppcms::json::value object); // admin only for now
	void get_domains(cppcms::json::value object); // get domains for 1 user
	void get_dns_records(cppcms::json::value object); // get all dns records for 1 domain
	void get_ftp_accounts(cppcms::json::value object); // get all ftp accounts for 1 user
	void get_vhosts(cppcms::json::value object); // get all vhosts for 1 domain
	void get_mailboxes(cppcms::json::value object); // get all mailboxes for 1 domain
	void get_shells(cppcms::json::value object); // get all shells for 1 domain 
	void get_subdomains(cppcms::json::value object); // get all subdomains for 1 user
	void get_settings(cppcms::json::value object); // get all settings (admin only)
	void get_database_types(); 
	void get_database_users(cppcms::json::value object); // get all database users for 1 user
	void get_databases(cppcms::json::value object); // get all databases for 1 user
	void get_queues(cppcms::json::value object); // get all queues for 1 user

	void update_user(cppcms::json::value object);
	void update_domain(cppcms::json::value object);
	void update_dns(cppcms::json::value object);
	void update_ftp_account(cppcms::json::value object);
	void update_vhost(cppcms::json::value object);
	void update_mailbox(cppcms::json::value object);
	void update_subdomain(cppcms::json::value object);
	void update_setting(cppcms::json::value object);
	void update_database_user(cppcms::json::value object);
	void update_database(cppcms::json::value object);
	void update_domain_alias(cppcms::json::value object);

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
	void delete_domain_alias(int id);

	/* used for get_all functions */
	cppdb::result get_result(std::ostringstream& query);
	void create_get_all_query(cppcms::json::value object, std::ostringstream& query);

	/* used mainly in update (create) functions */
	std::map<std::string, any> create_generic(cppcms::json::value object, ModelFactory::ModelType type);
	bool check_default(any value);
	bool check_default(std::map<std::string,any> primary_list);
	bool check_primary_field(std::vector<any> primary_list, std::string field);
	void update_generic(cppcms::json::value object, std::unique_ptr<model> tmp, ModelFactory::ModelType type);
	bool convert(std::unique_ptr<model> tmp, cppcms::string_key first, cppcms::json::value second, std::map<std::string,any> &update_list);
	any get_identifier(std::string primary_field, cppcms::string_key first, cppcms::json::value second);

	bool check_authenticated(std::vector<std::string> role_types); // usage in functions
	int get_uid_from_token();

protected:
	std::string format_uptime(std::string sec);

private:
	std::string create_auth_token(int uid);
	bool is_role_allowed(std::vector<std::string> role_types, int uid);
	void init_backend();

	backend *db = NULL;
	create* create_obj = NULL;
	get* get_obj = NULL;

};

#endif /* MASTER_H */

