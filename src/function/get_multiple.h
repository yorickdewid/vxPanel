#ifndef GET_MULTIPLE_H
#define GET_MULTIPLE_H

#include <cppcms/application.h>
#include <cppcms/rpc_json.h>
#include "functions.h"

class get_multiple : public functions {

public:
	get_multiple(backend& db, master* main) : 
		functions(db,main){};

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

	cppdb::result get_result(std::ostringstream& query);
	void create_get_all_query(cppcms::json::value object, std::ostringstream& query);

};

#endif /* GET_MULTIPLE_H */

