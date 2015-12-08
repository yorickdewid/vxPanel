#include <iostream>

#include "../config.h"
#include "../model.h"
#include <typeinfo>
#include "user.h"

void user::save()
{
	try{
		cppdb::statement stat;

		if ( _note.empty() ) {
			stat = db.session() << 
				"INSERT INTO user (username, password, email, firstname, lastname, country, city, address, address_number, postal, remote, user_type, active, lastlogin) "
				"VALUES (?, encrypt(?), ?, ?, ?, ?, ?, ?, ?, ?, inet6_aton(?), ?, ?, ?)" << username << _password << _email << _firstname << _lastname << _country << _city << _address << _address_number << _postal << _remote << _active << _lastlogin;
		}
		else{
			stat = db.session() << 
				"INSERT INTO user (username, password, email, firstname, lastname, country, city, address, address_number, postal, note, remote, user_type, active, lastlogin) "
				"VALUES (?, encrypt(?), ?, ?, ?, ?, ?, ?, ?, ?, ?, inet6_aton(?), ?, ?, ?)" << username << _password << _email << _firstname << _lastname << _country << _city << _address << _address_number << _postal << _note << _remote << _user_type << _active << _lastlogin;
		}

		stat.exec();
		uid = stat.last_insert_id();
		stat.reset();

		this->saved = true;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

void user::load()
{
	try{
		int tmp_active;
		cppdb::statement stat;

		stat = db.session() << 
			"SELECT * FROM user WHERE uid = ?" << uid;
		cppdb::result r = stat.query();

		while(r.next()) {
  			r >> this->uid >> this->username >> this->_password >> this->_email >> this->_firstname >> this->_lastname >> this->_country >> this->_city >> this->_address >> this->_address_number >> this->_postal >> this->_note >> this->_remote >> this->_user_type >> tmp_active >> this->_lastlogin;

  			if ( tmp_active == 0 ){
  				this->_active = false;
  			}
  			else if ( tmp_active == 1 ){
  				this->_active = true;
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

bool user::update(std::vector<update_obj> list)
{
	/* TODO */
	(std::vector<update_obj>)list;
	return true;
}

/* TODO Handle foreign key block correctly */
bool user::m_delete()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"DELETE FROM user WHERE uid = ?" << uid;
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

void user::set_username(std::string username)
{
	this->username = username;
}

void user::set_email(std::string email)
{
	this->_email = email;
}

void user::set_password(std::string password)
{
	this->_password = password;
}

void user::set_firstname(std::string firstname)
{
	this->_firstname = firstname;
}

void user::set_lastname(std::string lastname)
{
	this->_lastname = lastname;
}

void user::set_country(std::string country)
{
	this->_country = country;
}

void user::set_city(std::string city)
{
	this->_city = city;
}

void user::set_address(std::string address)
{
	this->_address = address;
}

void user::set_address_number(int address_number)
{
	this->_address_number = address_number;
}

void user::set_postal(std::string postal)
{
	this->_postal = postal;
}

void user::set_note(std::string note)
{
	this->_note = note;
}

void user::set_remote(std::string remote)
{
	this->_remote = remote;
}

void user::set_user_type(std::string user_type)
{
	this->_user_type = user_type;
}

void user::set_active(bool active)
{
	this->_active = active;
}

void user::set_lastlogin(std::string lastlogin)
{
	this->_lastlogin = lastlogin;
}

int user::get_uid()
{
	return uid;
}

std::string user::get_username()
{
	return this->username;
}

std::string user::get_password()
{
	return this->_password;
}

std::string user::get_email()
{
	return this->_email;
}

std::string user::get_firstname()
{
	return this->_firstname;
}

std::string user::get_lastname()
{
	return this->_lastname;
}

std::string user::get_country()
{
	return this->_country;
}

std::string user::get_city()
{
	return this->_city;
}

std::string user::get_address()
{
	return this->_address;
}

int user::get_address_number()
{
	return this->_address_number;
}

std::string user::get_postal()
{
	return this->_postal;
}

std::string user::get_note()
{
	return this->_note;
}

std::string user::get_user_type()
{
	return this->_user_type;
}

std::string user::get_remote()
{
	return this->_remote;
}

bool user::get_active()
{
	return this->_active;
}

std::string user::get_created()
{
	return this->_created;
}

std::string user::get_lastlogin()
{
	return this->_lastlogin;
}

