#include <iostream>
#include <vector>

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
	  		r >> this->name;
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

bool database_type::update(std::string field)
{

}

bool database_type::m_delete()
{
	
}


std::vector<database_type> database_type::load_all()
{
	try{
		cppdb::statement stat;
		std::vector<database_type> database_types; 

		stat = db.session() << 
				"SELECT * FROM user_db_type";
		cppdb::result r = stat.query();

		while(r.next()) {
			std::string tmp_name;
	  		r >> tmp_name;
	  		database_type obj = database_type(db,tmp_name);
	  		database_types.push_back(obj);
	    }

	    stat.reset();


		std::cout << "All data loaded" << std::endl;
		return database_types;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
		std::vector<database_type> k;
		return k;
	}
}

std::string database_type::get_name()
{
	return this->name;
}

