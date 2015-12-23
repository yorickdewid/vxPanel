#include <iostream>

#include "../model.h"
#include "auth_token.h"
#include "user.h"

void auth_token::save()
{
	try{
		cppdb::statement stat;

		if ( _valid.empty() ) {
			stat = db.session() << 
				"INSERT INTO auth_token (name, status, uid, refresh, created, valid) "
				"VALUES (?, ?, ?, ?, ?, ?)" << session_id << _remote << get_user().get_uid() << _refresh << _created << _valid; 
		} else {
				stat = db.session() << 
				"INSERT INTO auth_token (name, status, uid, refresh, created) "
				"VALUES (?, ?, ?, ?, ?)" << session_id << _remote << get_user().get_uid() << _refresh << _created; 
		}

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

void auth_token::load()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"SELECT * FROM auth_token WHERE session_id = ? AND remote = ?" << session_id << _remote;
		cppdb::result r = stat.query();

		while(r.next()) {
			int uid;
			r >> this->session_id >> this->_remote >> uid >> this->_refresh >> this->_created >> this->_valid;
	  		this->set_user(std::shared_ptr<user>(new user(db,uid)));
	    }

	    stat.reset();

    	this->saved = true;

		std::cout << "Entity loaded domain " << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured domain load " << e.what() << std::endl;
	}
}

/* TODO Handle foreign key block correctly */
bool auth_token::m_delete()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"DELETE FROM auth_token WHERE session_id = ? AND remote = ?" << session_id << _remote;
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

void auth_token::set_user(std::shared_ptr<user> user)
{
	this->_user.swap(user);
}

user auth_token::get_user()
{
	return *this->_user;
}

