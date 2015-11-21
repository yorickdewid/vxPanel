#ifndef BACKEND_H
#define BACKEND_H

#include <cppdb/frontend.h>

class backend {
public:

	backend(std::string &conn);
	~backend();
	bool is_active();
	virtual void init();
	virtual void kill();

protected:
	cppdb::session sql;

private:
	std::string conn_str_;

};

#endif /* BACKEND_H */

