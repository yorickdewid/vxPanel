#include <iostream>

#include "../model.h"
#include "auth_token.h"
#include "user.h"

void auth_token::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << "SELECT sha1(concat(now(), RAND()))";
		cppdb::result r = stat.query();
		r.fetch(0, session_id);

		stat.reset();

		stat = db.session() << 
			"INSERT INTO auth_token (session_id, remote, uid, refresh, valid) "
			"VALUES (?, inet6_aton(?), ?, sha1(concat(now(), RAND())), now()+" << TOKEN_VALID << ")" << session_id << remote << get_user().get_uid(); 

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
				"SELECT session_id, INET6_NTOA(remote), uid, refresh, created, valid FROM auth_token WHERE session_id = ? AND remote = inet6_aton(?)" << session_id << remote;
		cppdb::result r = stat.query();

		while(r.next()) {
			int uid;
			r >> this->session_id >> this->remote >> uid >> this->_refresh >> this->_created >> this->_valid;
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
				"DELETE FROM auth_token WHERE session_id = ? AND remote = inet6_aton(?)" << session_id << remote;
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

