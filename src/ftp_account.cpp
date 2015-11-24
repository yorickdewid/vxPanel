#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "ftp_account.h"
#include "domain.h"

void ftp_account::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO ftp_account (username, password, permissions, domain_name) "
			"VALUES (?, ?, ?, ?)" << username << _password << _permissions << _domain->get_domain_name();

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

		stat = db.session() << 
				"SELECT * FROM ftp_account WHERE username = ?" << username;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r.fetch(0,this->username);
	  		r.fetch(1,this->_password);
	  		r.fetch(2,this->_permissions);
	  		r.fetch(3,this->_created);
	  		r.fetch(4,domain_name);
	  		if ( !domain_name.empty() ) {
	  			set_domain(std::shared_ptr<domain>(new domain(db,domain_name)));
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

