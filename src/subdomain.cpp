#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "subdomain.h"
#include "domain.h"

using namespace std;

void subdomain::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO subdomain (name, domain_name) "
			"VALUES (?, ?)" << _name << _domain->get_domain_name();

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

void subdomain::load()
{
	try{
		cppdb::statement stat;
		string domain_name;

		stat = db.session() << 
				"SELECT * FROM subdomain WHERE id = ?" << id;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r.fetch(0,this->id);
	  		r.fetch(1,this->_name);
	  		r.fetch(2,this->_created);
	  		r.fetch(3,domain_name);
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

void subdomain::set_name(string name)
{
	this->_name = name;
}

void subdomain::set_domain(std::shared_ptr<domain> domain)
{
	this->_domain.swap(domain);
}

int subdomain::get_id()
{
	return this->id;
}

string subdomain::get_name()
{
	return this->_name;
}

string subdomain::get_created()
{
	return this->_created;
}

domain subdomain::get_domain()
{
	return *this->_domain;
}
