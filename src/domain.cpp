#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "domain.h"

void domain::status(std::string status)
{
	this->_status = status;
}

void domain::registrar(std::string registrar)
{
	this->_registrar = registrar;
}

std::string domain::get_status()
{
	return this->_status;
}

std::string domain::get_registrar()
{
	return this->_registrar;
}

std::string domain::get_domain_name()
{
	return this->name;
}

void domain::save()
{
	cppdb::statement stat;

	stat = db.session() << 
			"INSERT INTO domain (name, status, registrar) "
			"VALUES (?, ?, ?)" << name << _status << _registrar;

	stat.exec();
	stat.reset();

	std::cout << "Saved" << std::endl;
}

void domain::load()
{
	cppdb::statement stat;

	stat = db.session() << 
			"SELECT * FROM domain WHERE name = ?" << name;
	cppdb::result r = stat.query();

	while(r.next()) {
  		r.fetch(0,this->name);
  		r.fetch(1,this->_status);
  		r.fetch(2,this->_registrar);
  		r.fetch(3,this->_created);
    }

    stat.reset();

	std::cout << "Entity loaded " << std::endl;
}

