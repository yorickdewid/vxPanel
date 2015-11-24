#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "database_type.h"

using namespace std;

void database_type::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO database_type (name) "
			"VALUES (?)" << name;

		stat.exec();
		stat.reset();

		this->saved = true;

		cout << "Saved" << endl;
	}
	catch(exception &e)
	{
		cout << "Exception occured " << e.what() << endl;
	}
}

void database_type::load()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"SELECT * FROM database_type WHERE name = ?" << name;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r.fetch(0,this->name);
	    }

	    stat.reset();

    	this->saved = true;

		cout << "Entity loaded " << endl;
	}
	catch(exception &e)
	{
		cout << "Exception occured " << e.what() << endl;
	}
}

string database_type::get_name()
{
	return this->name;
}

