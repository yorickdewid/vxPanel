#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "domain.h"

void domain::save()
{
	try{
		cppdb::statement stat;

		if ( this->_vhost_id != -1 ) {
			stat = db.session() << 
				"INSERT INTO domain (name, status, registrar, uid) "
				"VALUES (?, ?, ?, ?, ?)" << name << _status << _registrar << _uid << _vhost_id;
		}else	{
			stat = db.session() << 
				"INSERT INTO domain (name, status, registrar, uid) "
				"VALUES (?, ?, ?, ?)" << name << _status << _registrar << _uid;
		}

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

void domain::load()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"SELECT * FROM domain WHERE name = ?" << name;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r.fetch(0,this->name);
	  		r.fetch(1,this->_status);
	  		r.fetch(2,this->_registrar);
	  		r.fetch(3,this->_created);
	  		r.fetch(4,this->_uid);
	  		if(r.fetch(5,this->_vhost_id) == false){
	  			this->_vhost_id = -1;
	  		}
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

void domain::status(std::string status)
{
	this->_status = status;
}

void domain::registrar(std::string registrar)
{
	this->_registrar = registrar;
}

void domain::user_id(int uid)
{
	this->_uid = uid;
}

void domain::vhost_id(int vhost_id)
{
	this->_vhost_id = vhost_id;
}

std::string domain::get_domain_name()
{
	return this->name;
}

std::string domain::get_status()
{
	return this->_status;
}

std::string domain::get_registrar()
{
	return this->_registrar;
}

std::string domain::get_created()
{
	return this->_registrar;
}

int domain::get_user_id()
{
	return this->_uid;
}

int domain::get_vhost_id()
{
	return this->_vhost_id;
}

