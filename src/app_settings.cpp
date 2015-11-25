#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "app_settings.h"

void app_settings::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
			"INSERT INTO settings (`key`,value,`default`,description) "
			"VALUES (?, ?, ?, ?)" << key << _value << _default << _description;
			
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

void app_settings::load()
{
	try{
		cppdb::statement stat;
		int tmp_default;

		stat = db.session() << 
				"SELECT * FROM settings WHERE `key` = ?" << key;
		cppdb::result r = stat.query();

		while(r.next()) {
	  		r >> this->key >> this->_value >> tmp_default >> this->_description >> this->_updated >> this->_created;
	  		if ( tmp_default == 0 ){
  				this->_default = false;
  			}
  			else if ( tmp_default == 1 ){
  				this->_default = true;
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

void app_settings::set_key(std::string key)
{
	this->key = key;
}

void app_settings::set_value(std::string value)
{
	this->_value = value;
}

void app_settings::set_default(bool default_)
{
	this->_default = default_;
}

void app_settings::set_description(std::string description)
{
	this->_description = description;
}

std::string app_settings::get_key()
{
	return this->key;
}

std::string app_settings::get_value()
{
	return this->_value;
}

bool app_settings::get_default()
{
	return this->_default;
}

std::string app_settings::get_description()
{
	return this->_description;
}

std::string app_settings::get_updated()
{
	return this->_updated;
}

std::string app_settings::get_created()
{
	return this->_created;
}

