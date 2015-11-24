#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "database_type.h"

void database_type::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO user_db_type (name) "
			"VALUES (?)" << name;

		stat.exec();
		stat.reset();

		this->saved = true;

		std::cout << "Saved" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

void database_type::load()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"SELECT * FROM user_db_type WHERE name = ?" << name;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r.fetch(0,this->name);
	    }

	    stat.reset();

    	this->saved = true;

		std::cout << "Entity loaded " << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

std::string database_type::get_name()
{
	return this->name;
}

