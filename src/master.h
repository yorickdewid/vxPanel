#ifndef MASTER_H
#define MASTER_H

#include <cppcms/application.h>
#include <cppcms/rpc_json.h>
#include <cppdb/frontend.h>

class master: public cppcms::rpc::json_rpc_server {
public:

	master(cppcms::service &srv);
	void sum(int x, int y);
	void div(int x, int y);
	void notify(std::string msg);
	void both(std::string msg);
	void system_uptime();
	void version();
	virtual void init();
	virtual void clear();

protected:
	cppdb::session sql;
	std::string format_uptime(std::string sec);

private:
	std::string conn_str_;
};

#endif /* MASTER_H */

