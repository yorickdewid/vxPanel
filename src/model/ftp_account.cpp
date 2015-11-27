#include <iostream>

#include "../model.h"
#include "ftp_account.h"
#include "domain.h"
#include "user.h"

void ftp_account::save()
{
	try{
		cppdb::statement stat;

		if ( _domain ) {
			stat = db.session() << 
			"INSERT INTO ftp_account (username, password, permissions, domain_name , uid) "
			"VALUES (?, ?, ?, ?, ?)" << username << _password << _permissions << _domain->get_domain_name() << _user->get_uid();
		}else{
			stat = db.session() << 
			"INSERT INTO ftp_account (username, password, permissions, uid) "
			"VALUES (?, ?, ?, ?)" << username << _password << _permissions << _user->get_uid();
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

void ftp_account::load()
{
	try{
		cppdb::statement stat;
		std::string domain_name;
		int uid;

		stat = db.session() << 
				"SELECT * FROM ftp_account WHERE username = ?" << username;
		cppdb::result r = stat.query();

		while(r.next()) {
			r >> this->username >> this->_password >> this->_permissions >> this->_created >> domain_name;
	  		if ( !domain_name.empty() ) {
	  			set_domain(std::shared_ptr<domain>(new domain(db,domain_name)));
	  		}
	  		r.fetch(5,uid);
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

bool ftp_account::update(std::string field)
{
	/* TODO */
	(std::string)field;
	return true;
}

bool ftp_account::m_delete()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"DELETE FROM ftp_account WHERE username = ?" << username;
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

void ftp_account::set_password(std::string password)
{
	this->_password = password;
}

void ftp_account::set_permissions(std::string permissions)
{
	this->_permissions = permissions;
}

void ftp_account::set_domain(std::shared_ptr<domain> domain)
{
	this->_domain.swap(domain);
}

void ftp_account::set_user(std::shared_ptr<user> user)
{
	this->_user.swap(user);
}

std::string ftp_account::get_username()
{
	return this->username;
}

std::string ftp_account::get_password()
{
	return this->_password;
}

std::string ftp_account::get_permissions()
{
	return this->_permissions;
}

std::string ftp_account::get_created()
{
	return this->_created;
}

domain ftp_account::get_domain()
{
	return *this->_domain;
}

std::shared_ptr<domain> ftp_account::get_domain_ptr()
{
	return this->_domain;
}

user ftp_account::get_user()
{
	return *this->_user;
}

