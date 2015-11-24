#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "database_user.h"
#include "user.h"

using namespace std;

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

		cout << "Saved" << endl;
	}
	catch(exception &e)
	{
		cout << "Exception occured " << e.what() << endl;
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
	  		r.fetch(0,this->name);
	  		r.fetch(1,this->_password);
	  		r.fetch(2,this->_permissions);
	  		r.fetch(3,this->_created);
	  		r.fetch(4,uid);
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

void database_user::set_name(string name)
{
	this->name = name;
}

void database_user::set_password(string password)
{
	this->_password = password;
}

void database_user::set_permissions(string permissions)
{
	this->_permissions = permissions;
}

void database_user::set_user(shared_ptr<user> user)
{
	this->_user.swap(user);
}

string database_user::get_name()
{
	return this->name;
}

string database_user::get_password()
{
	return this->_password;
}

string database_user::get_permissions()
{
	return this->_permissions;
}

string database_user::get_created()
{
	return this->_created;
}

user database_user::get_user()
{
	return *this->_user;
}

