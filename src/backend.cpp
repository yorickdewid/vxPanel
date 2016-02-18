#include <iostream>
#include <sstream>
#include <fstream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"

backend::backend(std::string& user, std::string& password, std::string& database) : 
	user(user),
	password(password),
	database(database)
{
	std::ostringstream poolsize;
	poolsize << DB_POOLSZ;

	this->conn_str_ = DB_DRIVER ":database=" + database + ";user=" + user + ";password=" + password + ";@pool_size=" + poolsize.str() + "\n"	;

	sql.open(conn_str_);

	if (!is_active()) {
		throw backend_ex();
	}
}

backend::~backend()
{
	sql.close();
}

void backend::drop()
{
#if 0
	sql << "DROP DATABASE IF EXISTS " + database << cppdb::exec;
#endif
}

void backend::create()
{
#if 0
	std::string transaction;
	std::ifstream scheme("scheme/create.sql");
	std::string line;

	if (scheme.is_open()) {
		while ( getline(scheme, line) )
		{
			transaction.append(line);
			transaction.append("\n");
		}
		std::cout << transaction;

		sql << transaction << cppdb::exec;
		scheme.close();
	}
#endif
}

bool backend::is_active()
{
	try {
		cppdb::result res = sql << "SELECT VERSION()";
		if (!res.next() || res.empty()) {
			return false;
		}
	}
	catch(std::exception const &e) {
		BOOSTER_ERROR("master") << "ERROR: " << e.what() << std::endl;
		return false;
	}
	return true;
}

std::string backend::version()
{
	std::string version;
	try {
		cppdb::result res = sql << "SELECT VERSION()";
		if (!res.next()) {
			//TODO err
		}
		res >> version;
	}
	catch(std::exception const &e) {
		BOOSTER_ERROR("master") << "ERROR: " << e.what() << std::endl;
	}
	return version;
}
