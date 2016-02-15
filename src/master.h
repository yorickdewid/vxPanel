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
class get_multiple;
class update;
class delete_m;
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

	bool check_primary_field(std::vector<any> primary_list, std::string field);
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
	get_multiple* get_multiple_obj = NULL;
	update* update_obj = NULL;
	delete_m* delete_m_obj = NULL;

};

#endif /* MASTER_H */

