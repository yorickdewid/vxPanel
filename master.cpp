#include "master.h"

#include <cppcms/json.h>
#include <cppcms/session_interface.h>
#include <cppcms/url_mapper.h>
#include <iostream>

master::master(cppcms::service &srv) : cppcms::application(srv)
{
	conn_str_ = settings().get<std::string>("db.connection_string");
}

void master::init()
{
	sql.open(conn_str_);
}
void master::clear()
{
	sql.close();
}
