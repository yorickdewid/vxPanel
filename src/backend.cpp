#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"

backend::backend(std::string &conn) : conn_str_(conn)
{
	backend::init();

	if (!backend::is_active()) {
		throw backend_ex();
	}
}

backend::~backend()
{
	backend::kill();
}

void backend::init()
{
	sql.open(conn_str_);
}

void backend::kill()
{
	sql.close();
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
		std::cerr << "ERROR: " << e.what() << std::endl;
		return false;
	}
	return true;
}