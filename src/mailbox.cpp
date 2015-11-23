#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "mailbox.h"
#include "domain.h"

using namespace std;

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

		cout << "Saved" << endl;
	}
	catch(exception &e)
	{
		cout << "Exception occured " << e.what() << endl;
	}
}

void mailbox::load()
{
	try{
		cppdb::statement stat;
		string domain_name;

		stat = db.session() << 
				"SELECT * FROM mailbox WHERE id = ?" << id;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r.fetch(0,this->id);
	  		r.fetch(1,this->_name);
	  		r.fetch(2,this->_address);
	  		r.fetch(3,this->_created);
	  		r.fetch(4,domain_name);
			if ( !domain_name.empty() ) {
	  			set_domain(std::shared_ptr<domain>(new domain(db,domain_name)));
	  		}
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

void mailbox::set_name(string name)
{
	this->_name = name;
}

void mailbox::set_address(string address)
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

string mailbox::get_address()
{
	return this->_address;
}

string mailbox::get_created()
{
	return this->_created;
}

domain mailbox::get_domain()
{
	return *this->_domain;
}
