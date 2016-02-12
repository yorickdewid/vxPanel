#include "functions.h"

backend& functions::get_database()
{
	return db;
}

master* functions::get_main()
{
	return main;
}

