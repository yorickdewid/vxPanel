#ifndef BACKEND_H
#define BACKEND_H

#include <cppdb/frontend.h>

class backend {

public:
	backend(std::string& user, std::string& password, std::string& database);
	virtual ~backend();
	virtual bool is_active();
	void drop();
	void create();
	std::string version();
	cppdb::session session()
	{
		return sql;
	}

protected:
	cppdb::session sql;

private:
	std::string conn_str_;
	std::string user;
	std::string password;
	std::string database;

};

#endif /* BACKEND_H */

