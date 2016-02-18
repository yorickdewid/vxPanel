#include <iostream>

#include "../model.h"
#include "mailbox.h"
#include "domain.h"

void mailbox::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO mailbox (email, password, maildir, quota, domain_name) "
			"VALUES (?, ?, ?, ?, ?)" << _email << this->_password << this->_maildir << this->_quota << _domain->name;
		stat.exec();
		stat.reset();

		this->saved = true;

		BOOSTER_INFO("mailbox") << "Saved" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

void mailbox::load()
{
	try{
		cppdb::statement stat;
		std::string domain_name;

		stat = db.session() << 
				"SELECT * FROM mailbox WHERE id = ?" << id;
		cppdb::result r = stat.query();

		while(r.next()) {
			int tmp_active;
			r >> this->id >> this->_email >> this->_password >> this->_maildir >> this->_quota >> this->_created >> domain_name >> tmp_active;
			if ( !domain_name.empty() ) {
	  			set_domain(std::shared_ptr<domain>(new domain(db,domain_name)));
	  		}
	  		if ( tmp_active == 1 ) {
	  			this->_active = true;
	  		} else {
	  			this->_active = false;
	  		}
	    }

	    stat.reset();

    	this->saved = true;

		BOOSTER_INFO("mailbox") << "Entity loaded " << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

void mailbox::load(std::string domain_name)
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"SELECT * FROM mailbox WHERE domain_name = ?" << domain_name;
		cppdb::result r = stat.query();

		while(r.next()) {
			int tmp_active;
			r >> this->id >> this->_email >> this->_password >> this->_maildir >> this->_quota >> this->_created >> domain_name >> tmp_active;
			if ( !domain_name.empty() ) {
	  			set_domain(std::shared_ptr<domain>(new domain(db,domain_name)));
	  		}
	  		if ( tmp_active == 1 ) {
	  			this->_active = true;
	  		} else {
	  			this->_active = false;
	  		}
	    }

	    stat.reset();

    	this->saved = true;

		BOOSTER_INFO("mailbox") << "Entity loaded " << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

bool mailbox::m_delete()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"DELETE FROM mailbox WHERE id = ?" << id;
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


void mailbox::set_email(std::string email)
{
	this->_email = email;
}

void mailbox::set_password(std::string password)
{
	this->_password = password;
}

void mailbox::set_maildir(std::string maildir)
{
	this->_maildir = maildir;
}

void mailbox::set_quota(long long int quota)
{
	this->_quota = quota;
}

void mailbox::set_domain(std::shared_ptr<domain> domain)
{
	this->_domain.swap(domain);
}

void mailbox::set_active(bool active)
{
	this->_active = active;
}

int mailbox::get_id()
{
	return this->id;
}

std::string mailbox::get_email()
{
	return this->_email;
}

std::string mailbox::get_password()
{
	return this->_password;
}

std::string mailbox::get_created()
{
	return this->_created;
}

std::string mailbox::get_maildir()
{
	return this->_maildir;
}

long long int mailbox::get_quota()
{
	return this->_quota;
}

domain mailbox::get_domain()
{
	return *this->_domain;
}

bool mailbox::get_active()
{
	return this->_active;
}

