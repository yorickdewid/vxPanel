#include <iostream>

#include "../model.h"
#include "dns.h"
#include "domain.h"

void dns::save()
{
	cppdb::statement stat;

	stat = db.session() << 
		"INSERT INTO dns (name, domain_name) "
		"VALUES (?, ?)" << _name << _domain->name;

	stat.exec();
	stat.reset();

	this->saved = true;

	BOOSTER_INFO("dns") << "Saved" << std::endl;
}

void dns::load()
{
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

	BOOSTER_INFO("dns") << "Entity loaded dns " << std::endl;
}

void dns::load(std::string domain_name)
{
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

	BOOSTER_INFO("dns") << "Entity loaded dns (domain_name) " << std::endl;
}

bool dns::m_delete()
{
	cppdb::statement stat;

	stat = db.session() << 
			"DELETE FROM dns WHERE domain_name = ?" << _domain->name;
	stat.exec();

	if ( stat.affected() == 1 ) {
		stat.reset();
		return true;
	} else {
		stat.reset();
		return false;
	}
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

