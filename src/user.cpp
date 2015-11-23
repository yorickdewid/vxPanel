#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "sha1.h"
#include "backend.h"
#include "model.h"
#include "user.h"

void user::save()
{
	try{

		cppdb::statement stat;

		if ( _note.empty() ) {
			stat = db.session() << 
				"INSERT INTO user (username, password, email, firstname, lastname, country, city, address, postal, active, lastlogin) "
				"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)" << username << _password << _email << _firstname << _lastname << _country << _city << _address << _postal << _active << _lastlogin;
		}
		else{
			stat = db.session() << 
				"INSERT INTO user (username, password, email, firstname, lastname, country, city, address, postal, note, active, lastlogin) "
				"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)" << username << _password << _email << _firstname << _lastname << _country << _city << _address << _postal << _note << _active << _lastlogin;
		}

		stat.exec();
		uid = stat.last_insert_id();
		stat.reset();

		this->saved = true;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what();
	}
}

void user::load()
{
	try{
		int tmp_active;
		cppdb::statement stat;

		stat = db.session() << 
			"SELECT * FROM user WHERE username = ?" << username;
		cppdb::result r = stat.query();

		while(r.next()) {
  			r.fetch(0,this->uid);
  			r.fetch(1,this->_password);
  			r.fetch(2,this->_email);
  			r.fetch(3,this->_firstname);
  			r.fetch(4,this->_lastname);
  			r.fetch(5,this->_country);
  			r.fetch(6,this->_city);
  			r.fetch(7,this->_address);
  			r.fetch(8,this->_postal);
  			r.fetch(9,this->_note);
  			r.fetch(10,tmp_active);
  			if ( tmp_active == 0 ){
  				this->_active = false;
  			}
  			else if ( tmp_active == 1 ){
  				this->_active = true;
  			}
  			r.fetch(11,this->_lastlogin);
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

void user::email(std::string email)
{
	this->_email = email;
}

void user::password(std::string password)
{
	unsigned char hash[20];
	char hexstring[41];

	sha1::calc(password.c_str(), password.size(), hash);
	sha1::toHexString(hash, hexstring);

	this->_password = std::string(hexstring);
}

void user::firstname(std::string firstname)
{
	this->_firstname = firstname;
}

void user::lastname(std::string lastname)
{
	this->_lastname = lastname;
}

void user::country(std::string country)
{
	this->_country = country;
}

void user::city(std::string city)
{
	this->_city = city;
}

void user::address(std::string address)
{
	this->_address = address;
}

void user::postal(std::string postal)
{
	this->_postal = postal;
}

void user::note(std::string note)
{
	this->_note = note;
}

void user::active(bool active)
{
	this->_active = active;
}

void user::lastlogin(std::string lastlogin)
{
	this->_lastlogin = lastlogin;
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

std::string user::get_postal()
{
	return this->_postal;
}

std::string user::get_note()
{
	return this->_note;
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

