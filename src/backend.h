#ifndef BACKEND_H
#define BACKEND_H

#include <cppdb/frontend.h>

class backend {
public:

	backend(std::string &conn);
	virtual ~backend();
	virtual bool is_active();
	virtual void init();
	virtual void kill();
	std::string version();

protected:
	cppdb::session sql;

private:
	std::string conn_str_;

};

#endif /* BACKEND_H */

