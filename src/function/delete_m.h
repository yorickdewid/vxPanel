#ifndef DELETE_M_H
#define DELETE_M_H

#include <cppcms/application.h>
#include <cppcms/rpc_json.h>
#include "functions.h"

class delete_m: public functions {

public:
	delete_m(backend& db, master* main) : 
		functions(db,main){};

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

};

#endif /* DELETE_M_H */

