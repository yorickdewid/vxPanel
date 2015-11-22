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

		stat = db.session() << 
				"INSERT INTO user (username, password, email) "
				"VALUES (?, ?, ?)" << username << _password << _email;

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

		cppdb::statement stat;

		stat = db.session() << 
			"SELECT uid,password,email FROM user WHERE username = ?" << username;
		cppdb::result r = stat.query();

		while(r.next()) {
  			r.fetch(0,this->uid);
  			r.fetch(1,this->_password);
  			r.fetch(2,this->_email);
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

