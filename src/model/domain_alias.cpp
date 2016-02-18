#include <iostream>

#include "../model.h"
#include "domain_alias.h"
#include "domain.h"

void domain_alias::save()
{
	cppdb::statement stat;

	stat = db.session() << 
		"INSERT INTO domain_alias (domain_name, source, destination) "
		"VALUES (?, ?, ?)" << _domain->name <<  _source << _destination;

	stat.exec();
	stat.reset();

	this->saved = true;

	BOOSTER_INFO("domain_alias") << "Saved" << std::endl;
}

void domain_alias::load()
{
	cppdb::statement stat;
	std::string domain_name;
	int tmp_active;

	stat = db.session() << 
			"SELECT * FROM domain_alias WHERE id = ?" << id;
	cppdb::result r = stat.query();

	while(r.next()) {
		r >> this->id >> domain_name >> this->_source >> this->_destination >> this->_created >> tmp_active;
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

	BOOSTER_INFO("domain_alias") << "Entity loaded domain_alias " << std::endl;
}

bool domain_alias::m_delete()
{
	cppdb::statement stat;

	stat = db.session() << 
			"DELETE FROM domain_alias WHERE id = ?" << this->id;
	stat.exec();

	if ( stat.affected() == 1 ) {
		stat.reset();
		return true;
	} else {
		stat.reset();
		return false;
	}
}

void domain_alias::set_domain(std::shared_ptr<domain> domain)
{
	this->_domain.swap(domain);
}

int domain_alias::get_id()
{
	return this->id;
}

std::string domain_alias::get_created()
{
	return this->_created;
}

domain domain_alias::get_domain()
{
	return *this->_domain;
}

