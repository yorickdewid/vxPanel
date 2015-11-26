#include <iostream>

#include "../model.h"
#include "dns.h"
#include "domain.h"

void dns::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO dns (address, domain_name) "
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

void dns::load()
{
	try{
		cppdb::statement stat;
		std::string domain_name;

		stat = db.session() << 
				"SELECT * FROM dns WHERE id = ?" << id;
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

void dns::load(std::string domain_name)
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"SELECT * FROM dns WHERE domain_name = ?" << domain_name;
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

bool dns::update(std::string field)
{

}

bool dns::m_delete()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"DELETE FROM dns WHERE domain_name = ?" << _domain->get_domain_name();
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

void dns::set_address(std::string address)
{
	this->_address = address;
}

void dns::set_domain(std::shared_ptr<domain> domain)
{
	this->_domain.swap(domain);
}

int dns::get_id()
{
	return this->id;
}

std::string dns::get_address()
{
	return this->_address;
}

std::string dns::get_created()
{
	return this->_created;
}

domain dns::get_domain()
{
	return *this->_domain;
}

