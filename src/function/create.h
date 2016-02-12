#ifndef CREATE_H
#define CREATE_H

#include <cppcms/application.h>
#include <cppcms/rpc_json.h>
#include "functions.h"

class create: public functions {

public:
	create(backend& db, master* main) : 
		functions(db,main){};

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
	void create_domain_alias(cppcms::json::value object);

	/*helper*/

	std::map<std::string, any> create_generic(cppcms::json::value object, ModelFactory::ModelType type);
	bool convert(std::unique_ptr<model> tmp, cppcms::string_key first, cppcms::json::value second, std::map<std::string,any> &update_list);

};

#endif /* CREATE_H */

