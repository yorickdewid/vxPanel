#include <iostream>

#include "../model.h"
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
			int tmp_active;
			r >> this->id >> this->_created >> uid >> tmp_active;
	  		set_user(std::shared_ptr<user>(new user(db,uid)));
	  		if ( tmp_active == 1 ) {
	  			this->_active = true;
	  		} else {
	  			this->_active = false;
	  		}
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

bool shell::update(std::string field)
{
	/* TODO */
	(std::string)field;
	return true;
}

bool shell::m_delete()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"DELETE FROM shell WHERE id = ?" << id;
		stat.exec();

		if ( stat.affected() == 1 ) {
			stat.reset();
			return true;
		} else {
			stat.reset();
			return false;
		}
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
	return false;
}

void shell::set_user(std::shared_ptr<user> user)
{
	this->_user.swap(user);
}

void shell::set_active(bool active)
{
	this->_active = active;
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

bool shell::get_active()
{
	return this->_active;
}

