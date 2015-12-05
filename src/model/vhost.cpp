#include <iostream>

#include "../model.h"
#include "vhost.h"

void vhost::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO vhost (name, custom_config) "
			"VALUES (?, ?)" << _name << _custom_config;

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

void vhost::load()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"SELECT * FROM vhost WHERE id = ?" << id;
		cppdb::result r = stat.query();

		while(r.next()) {
			int tmp_active;
	  		r >> this->id >> this->_name >> this->_custom_config >> this->_created >> tmp_active;
	  		if ( tmp_active == 1 ) {
	  			this->_active = true;
	  		} else {
	  			this->_active = false;
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

void vhost::load(std::string domain_name)
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"SELECT * FROM vhost WHERE name = ?" << domain_name;
		cppdb::result r = stat.query();

		while(r.next()) {
			int tmp_active;
	  		r >> this->id >> this->_name >> this->_custom_config >> this->_created >> tmp_active;
	  		if ( tmp_active == 1 ) {
	  			this->_active = true;
	  		} else {
	  			this->_active = false;
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

bool vhost::update(std::string field)
{
	/* TODO */
	(std::string)field;
	return true;
}

bool vhost::update(std::vector<update_obj> list)
{
	/* TODO */
	(std::vector<update_obj>)list;
	return true;
}

bool vhost::m_delete()
{
	/* TODO */
	return true;	
}

void vhost::set_name(std::string name)
{
	this->_name = name;
}

void vhost::set_custom_config(std::string custom_config)
{
	this->_custom_config = custom_config;
}

void vhost::set_active(bool active)
{
	this->_active = active;
}

int vhost::get_id()
{
	return this->id;
}

std::string vhost::get_name()
{
	return this->_name;
}

std::string vhost::get_custom_config()
{
	return this->_custom_config;
}

std::string vhost::get_created()
{
	return this->_created;
}

bool vhost::get_active()
{
	return this->_active;
}

