#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "shell.h"
#include "user.h"

void shell::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO shell (uid) "
			"VALUES (?)" << _user->get_uid();

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

void shell::load()
{
	try{
		cppdb::statement stat;
		int uid;

		stat = db.session() << 
				"SELECT * FROM shell WHERE id = ? " << id;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r.fetch(0,this->id);
	  		r.fetch(1,this->_created);
	  		r.fetch(2,uid);
	  		set_user(std::shared_ptr<user>(new user(db,uid)));
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

void shell::set_user(std::shared_ptr<user> user)
{
	this->_user.swap(user);
}

int shell::get_id()
{
	return this->id;
}

std::string shell::get_created()
{
	return this->_created;
}

user shell::get_user()
{
	return *this->_user;
}

