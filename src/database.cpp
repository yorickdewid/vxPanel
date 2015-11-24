#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "database.h"
#include "user.h"

using namespace std;

void database::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO database (name, type, uid) "
			"VALUES (?, ?, ?)" << name << _database_type->get_name() << _user->get_uid();

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

void database::load()
{
	try{
		cppdb::statement stat;
		string type;
		int uid;

		stat = db.session() << 
				"SELECT * FROM database WHERE name = ?" << name;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r.fetch(0,this->name);
	  		r.fetch(1,type);
	  		set_database_type(shared_ptr<database_type>(new database_type(db,type)));
	  		r.fetch(2,this->_created);
	  		r.fetch(3,uid);
	  		set_user(shared_ptr<user>(new user(db,uid)));
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

void database::set_name(string name)
{
	this->name = name;
}

void database::set_database_type(shared_ptr<database_type> database_type)
{
	this->_database_type.swap(database_type);
}

void database::set_user(shared_ptr<user> user)
{
	this->_user.swap(user);
}

string database::get_name()
{
	return this->name;
}

database_type database::get_database_type()
{
	return *this->_database_type;
}

string database::get_created()
{
	return this->_created;
}

user database::get_user()
{
	return *this->_user;
}

