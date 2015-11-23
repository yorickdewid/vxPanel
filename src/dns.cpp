#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "dns.h"
#include "domain.h"

void dns::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO dns (id, address, domain_name) "
			"VALUES (?, ?, ?)" << id << _address << _domain->get_domain_name();

		stat.exec();
		stat.reset();

		this->saved = true;

		std::cout << "Saved" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what();
	}
}

void dns::load()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"SELECT * FROM dns WHERE id = ?" << id;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r.fetch(0,this->id);
	  		r.fetch(1,this->_address);
	  		r.fetch(2,this->_created);
	    }

	    stat.reset();

    	this->saved = true;

		std::cout << "Entity loaded " << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what();
	}
}

void dns::set_address(std::string address)
{
	this->_address = address;
}

void dns::set_domain(std::unique_ptr<domain> domain)
{
	this->_domain.swap(domain);
}

