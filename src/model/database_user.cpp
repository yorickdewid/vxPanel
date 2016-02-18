#include <iostream>

#include "../model.h"
#include "database_user.h"
#include "user.h"

void database_user::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO user_db_user (name, password, permissions, uid) "
			"VALUES (?, ?, ?, ?)" << name << _password << _permissions << _user->get_uid();

		stat.exec();
		stat.reset();

		this->saved = true;

		BOOSTER_INFO("database_user") << "Saved" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

void database_user::load()
{
	try{
		cppdb::statement stat;
		int uid;

		stat = db.session() << 
				"SELECT * FROM user_db_user WHERE name = ?" << name;
		cppdb::result r = stat.query();

		while(r.next()) {
			r >> this->name >> this->_password >> this->_permissions >> this->_created >> uid;
	  		set_user(std::shared_ptr<user>(new user(db,uid)));
	    }

	    stat.reset();

    	this->saved = true;

		BOOSTER_INFO("database_user") <<  "Entity loaded " << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

/* TODO Handle foreign key block correctly */
bool database_user::m_delete()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"DELETE FROM user_db_user WHERE name = ?" << name;
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


void database_user::set_name(std::string name)
{
	this->name = name;
}

void database_user::set_password(std::string password)
{
	this->_password = password;
}

void database_user::set_permissions(std::string permissions)
{
	this->_permissions = permissions;
}

void database_user::set_user(std::shared_ptr<user> user)
{
	this->_user.swap(user);
}

std::string database_user::get_name()
{
	return this->name;
}

std::string database_user::get_password()
{
	return this->_password;
}

std::string database_user::get_permissions()
{
	return this->_permissions;
}

std::string database_user::get_created()
{
	return this->_created;
}

user database_user::get_user()
{
	return *this->_user;
}

