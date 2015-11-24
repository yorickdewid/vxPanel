#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
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
	  		r.fetch(0,this->id);
	  		r.fetch(1,this->_name);
	  		r.fetch(2,this->_custom_config);
	  		r.fetch(3,this->_created);
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

void vhost::set_name(std::string name)
{
	this->_name = name;
}

void vhost::set_custom_config(std::string custom_config)
{
	this->_custom_config = custom_config;
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

