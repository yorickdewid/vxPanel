#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "mailbox.h"
#include "domain.h"

void mailbox::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO mailbox (address, domain_name) "
			"VALUES (?, ?)" << _address << _domain->get_domain_name();
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

void mailbox::load()
{
	try{
		cppdb::statement stat;
		std::string domain_name;

		stat = db.session() << 
				"SELECT * FROM mailbox WHERE id = ?" << id;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r.fetch(0,this->id);
	  		r.fetch(1,this->_address);
	  		r.fetch(2,this->_created);
	  		r.fetch(3,domain_name);
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

void mailbox::load(std::string domain_name)
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"SELECT * FROM mailbox WHERE domain_name = ?" << domain_name;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r.fetch(0,this->id);
	  		r.fetch(1,this->_address);
	  		r.fetch(2,this->_created);
	  		r.fetch(3,domain_name);
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

bool mailbox::update(std::string field)
{

}

bool mailbox::m_delete()
{
	
}


void mailbox::set_address(std::string address)
{
	this->_address = address;
}

void mailbox::set_domain(std::shared_ptr<domain> domain)
{
	this->_domain.swap(domain);
}

int mailbox::get_id()
{
	return this->id;
}

std::string mailbox::get_address()
{
	return this->_address;
}

std::string mailbox::get_created()
{
	return this->_created;
}

domain mailbox::get_domain()
{
	return *this->_domain;
}

