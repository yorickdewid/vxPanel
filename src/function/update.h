#ifndef UPDATE_H
#define UPDATE_H

#include <cppcms/application.h>
#include <cppcms/rpc_json.h>
#include "functions.h"

class update : public functions {

public:
	update(backend& db, master* main) : 
		functions(db,main){};

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

	/* helper */
	void update_generic(cppcms::json::value object, std::unique_ptr<model> tmp, ModelFactory::ModelType type);
	any get_identifier(std::string primary_field, cppcms::string_key first, cppcms::json::value second);
	bool check_default(std::map<std::string,any> primary_list);
	bool check_default(any value);
 
};

#endif /* UPDATE_H */