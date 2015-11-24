#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "database_user.h"
#include "user.h"

void database_user::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO database_user (name, password, permissions, uid) "
			"VALUES (?, ?, ?, ?)" << name << _password << _permissions << _user->get_uid();

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

void database_user::load()
{
	try{
		cppdb::statement stat;
		int uid;

		stat = db.session() << 
				"SELECT * FROM database_user WHERE name = ?" << name;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r.fetch(0,this->name);
	  		r.fetch(1,this->_password);
	  		r.fetch(2,this->_permissions);
	  		r.fetch(3,this->_created);
	  		r.fetch(4,uid);
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

