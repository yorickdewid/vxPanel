#ifndef APPS_MASTER_H
#define APPS_MASTER_H

#include <cppcms/application.h>
#include <cppdb/frontend.h>

class master: public cppcms::application {
public:

	master(cppcms::service &w);
	virtual void init();
	virtual void clear();

protected:
	cppdb::session sql;

private:
	std::string conn_str_;
};

#endif

