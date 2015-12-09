#include <iostream>

#include "../model.h"
#include "dns.h"
#include "domain.h"

void dns::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO dns (name, domain_name) "
			"VALUES (?, ?)" << _name << _domain->get_domain_name();

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
		int tmp_active;

		stat = db.session() << 
				"SELECT * FROM dns WHERE id = ?" << id;
		cppdb::result r = stat.query();

		while(r.next()) {
			r >> this->id >> this->_name >> this->_created >> domain_name >> tmp_active;
	  		if ( !domain_name.empty() ) {
	  			set_domain(std::shared_ptr<domain>(new domain(db,domain_name)));
	  		}
	  		if ( tmp_active == 0 ){
  				this->_active = false;
  			}
  			else if ( tmp_active == 1 ){
  				this->_active = true;
  			}
	    }

	    stat.reset();

    	this->saved = true;

		std::cout << "Entity loaded dns " << std::endl;
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
		int tmp_active;

		stat = db.session() << 
				"SELECT * FROM dns WHERE domain_name = ?" << domain_name;
		cppdb::result r = stat.query();

		while(r.next()) {
			r >> this->id >> this->_name >> this->_created >> domain_name >> tmp_active;
	  		if ( !domain_name.empty() ) {
	  			set_domain(std::shared_ptr<domain>(new domain(db,domain_name)));
	  		}
	  		if ( tmp_active == 0 ){
  				this->_active = false;
  			}
  			else if ( tmp_active == 1 ){
  				this->_active = true;
  			}
	    }

	    stat.reset();

    	this->saved = true;

		std::cout << "Entity loaded dns (domain_name) " << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

bool dns::update(std::string field)
{
	/* TODO */
	(std::string)field;
	return true;
}

bool dns::update(std::vector<update_obj> list)
{
	/* TODO */
	(std::vector<update_obj>)list;
	return true;
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

void dns::set_name(std::string name)
{
	this->_name = name;
}

void dns::set_domain(std::shared_ptr<domain> domain)
{
	this->_domain.swap(domain);
}

void dns::set_active(bool active)
{
	this->_active = active;
}

int dns::get_id()
{
	return this->id;
}

std::string dns::get_name()
{
	return this->_name;
}

std::string dns::get_created()
{
	return this->_created;
}

domain dns::get_domain()
{
	return *this->_domain;
}

bool dns::get_active()
{
	return this->_active;
}

