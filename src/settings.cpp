#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "settings.h"

void settings::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO settings (key,value,default,description) "
			"VALUES (?, ?, ?)" << key << _value << _default << _description;

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

void settings::load()
{
	try{
		cppdb::statement stat;
		int tmp_default;

		stat = db.session() << 
				"SELECT * FROM settings WHERE key = ?" << key;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r.fetch(0,this->key);
	  		r.fetch(1,this->_value);
	  		r.fetch(2,tmp_default);
	  		if ( tmp_default == 0 ){
  				this->_default = false;
  			}
  			else if ( tmp_default == 1 ){
  				this->_default = true;
  			}
	  		r.fetch(3,this->_description);
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

void settings::set_key(std::string key)
{
	this->key = key;
}

void settings::set_value(std::string value)
{
	this->_value = value;
}

void settings::set_default(bool default_)
{
	this->_default = default_;
}

void settings::set_description(std::string description)
{
	this->_description = description;
}

std::string settings::get_key()
{
	return this->key;
}

std::string settings::get_value()
{
	return this->_value;
}

bool settings::get_default()
{
	return this->_default;
}

std::string settings::get_description()
{
	return this->_description;
}

std::string settings::get_updated()
{
	return this->_updated;
}

std::string settings::get_created()
{
	return this->_created;
}

