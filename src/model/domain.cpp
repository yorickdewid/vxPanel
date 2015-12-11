#include <iostream>

#include "../model.h"
#include "domain.h"
#include "user.h"
#include "vhost.h"

void domain::save()
{
	try{
		cppdb::statement stat;

		if ( _vhost ) {
			stat = db.session() << 
				"INSERT INTO domain (name, status, registrar, uid, vhost_id) "
				"VALUES (?, ?, ?, ?, ?)" << name << _status << _registrar << get_user().get_uid() << _vhost->get_id();
		}else	{
			stat = db.session() << 
				"INSERT INTO domain (name, status, registrar, uid) "
				"VALUES (?, ?, ?, ?)" << name << _status << _registrar << get_user().get_uid();
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

void domain::load()
{
	try{
		cppdb::statement stat;
		int uid;

		stat = db.session() << 
				"SELECT * FROM domain WHERE name = ?" << name;
		cppdb::result r = stat.query();

		while(r.next()) {
			int tmp_vhost_id = -1;
			int tmp_active;
			r >> this->name >> this->_status >> this->_registrar >> this->_created >> uid >> tmp_vhost_id >> tmp_active;
	  		this->set_user(std::shared_ptr<user>(new user(db,uid)));
	  		if ( tmp_vhost_id != -1 ) { /* TODO replace with vhost object) */
	  			set_vhost(std::shared_ptr<vhost>(new vhost(db,tmp_vhost_id)));
	  		}
	  		if ( tmp_active == 1 ) {
	  			this->_active = true;
	  		} else {
	  			this->_active = false;
	  		}
	    }

	    stat.reset();

    	this->saved = true;

		std::cout << "Entity loaded domain " << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured domain load " << e.what() << std::endl;
	}
}

/* TODO Handle foreign key block correctly */
bool domain::m_delete()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"DELETE FROM domain WHERE name = ?" << name;
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

void domain::status(std::string status)
{
	this->_status = status;
}

void domain::registrar(std::string registrar)
{
	this->_registrar = registrar;
}

void domain::set_user(std::shared_ptr<user> user)
{
	this->_user.swap(user);
}

void domain::set_vhost(std::shared_ptr<vhost> vhost)
{
	this->_vhost.swap(vhost);
}

void domain::set_active(bool active)
{
	this->_active = active;
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

user domain::get_user()
{
	return *this->_user;
}

vhost domain::get_vhost()
{
	return *this->_vhost;
}

bool domain::get_active()
{
	return this->_active;
}

