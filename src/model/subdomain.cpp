#include <iostream>

#include "../model.h"
#include "domain.h"
#include "subdomain.h"

void subdomain::save()
{
	try{
		cppdb::statement stat;

		if (_vhost_id != -1 ) {
			stat = db.session() << 
				"INSERT INTO subdomain (name, domain_name, vhost_id) "
				"VALUES (?, ?, ?)" << name << _domain->get_domain_name() << _vhost_id;
		} else {
			stat = db.session() << 
				"INSERT INTO subdomain (name, domain_name) "
				"VALUES (?, ?)" << name << _domain->get_domain_name();
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

void subdomain::load()
{
	try{
		cppdb::statement stat;
		std::string domain_name;

		stat = db.session() << 
				"SELECT * FROM subdomain WHERE name = ?" << name;
		cppdb::result r = stat.query();

		while(r.next()) {
			r >> this->name >> this->_created;
	  		if( r.fetch(2,domain_name) != false){
				if ( !domain_name.empty() ) {
	  				set_domain(std::shared_ptr<domain>(new domain(db,domain_name)));
	  			}
	  		}
	  		else{
	  			std::cout << "Failed to load domain " << std::endl;
	  		}
	  		if(r.fetch(3,this->_vhost_id) == false){ /* TODO replace with vhost object) */
	  			this->_vhost_id = -1;
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

bool subdomain::update(std::string field)
{
	/* TODO */
	(std::string)field;
	return true;
}

bool subdomain::m_delete()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"DELETE FROM subdomain WHERE name = ? and domain_name = ?" << name << _domain->get_domain_name();
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

void subdomain::set_name(std::string name)
{
	this->name = name;
}

void subdomain::set_domain(std::shared_ptr<domain> domain)
{
	this->_domain.swap(domain);
}

void subdomain::set_vhost_id(int vhost_id)
{
	this->_vhost_id = vhost_id;
}

std::string subdomain::get_name()
{
	return this->name;
}

std::string subdomain::get_created()
{
	return this->_created;
}

domain subdomain::get_domain()
{
	return *this->_domain;
}

std::shared_ptr<domain> subdomain::get_domain_ptr()
{
	return this->_domain;
}

int subdomain::get_vhost_id()
{
	return this->_vhost_id;
}
