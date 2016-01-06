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
	void create_vhost(std::string domain_name, std::string custom_config, int uid);
	void create_mailbox(std::vector<std::string> required_fields, std::string domain_name, int uid);
	void create_shell(int uid);
	void create_subdomain(std::string subdomain_name, std::string domain_name, int uid);
	void create_setting(std::string key, std::string value, bool default_, std::string description);
	void create_database_user(std::string name, std::string password, std::string permissions, int uid);
	void create_database(std::string db_name, std::string db_type, std::string db_username, int uid);
	void create_queue(cppcms::json::value object);

	std::map<std::string, any> create_generic(cppcms::json::value object, ModelFactory::ModelType type);

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
	void get_queue(int qid);
	void get_ip();

	bool check_default(any value);
	bool check_default(std::map<std::string,any> primary_list);
	bool check_primary_field(std::vector<any> primary_list, std::string field);
	void update_generic(cppcms::json::value object, std::unique_ptr<model> tmp, ModelFactory::ModelType type);
	bool convert(std::unique_ptr<model> tmp, cppcms::string_key first, cppcms::json::value second, std::map<std::string,any> &update_list);
	any get_identifier(std::string primary_field, cppcms::string_key first, cppcms::json::value second);

	void update_user(cppcms::json::value object); /* password,email,fname,lname,country,city,address,postal,note,user_type,active */
	void update_domain(cppcms::json::value object); /* status, registrar, vhost_id */
	void update_dns( cppcms::json::value object); /* address */
	void update_ftp_account(cppcms::json::value object); /* password, permissions */
	void update_vhost(cppcms::json::value object); /* name ?, custom_config */ 
	void update_mailbox(cppcms::json::value object); /* address */
	void update_subdomain(cppcms::json::value object); /* subdomain name , vhost_id */
	void update_setting(cppcms::json::value object); /* value, default, description */
	void update_database_user(cppcms::json::value object); /* password, permissions */
	void update_database(cppcms::json::value object); /* database_type */

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
	std::string create_auth_token(int uid);
	bool check_authenticated();
	backend *db = NULL;
	void init_backend();

};

#endif /* MASTER_H */

