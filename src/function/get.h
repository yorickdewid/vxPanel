#ifndef GET_H
#define GET_H

#include <cppcms/application.h>
#include <cppcms/rpc_json.h>
#include "functions.h"

class get : public functions {

public:
	get(backend& db, master* main) : 
		functions(db,main){};

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
	void get_domain_alias(int id);

};

#endif /* GET_H */

