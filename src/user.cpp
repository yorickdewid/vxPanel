#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "sha1.h"
#include "backend.h"
#include "model.h"
#include "user.h"

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

std::string user::get_username()
{
	return this->name;
}

std::string user::get_email()
{
	return this->_email;
}

void user::save()
{
	try{

		cppdb::statement stat;

		stat = db.session() << 
				"INSERT INTO user (username, password, email) "
				"VALUES (?, ?, ?)" << name << _password << _email;

		stat.exec();
		uid = stat.last_insert_id();
		stat.reset();
	}
	catch(std::exception &e)
	{
		std::cout << "exception occured " << e.what();
	}
}

void user::load()
{
	try{

		cppdb::statement stat;

		stat = db.session() << 
			"SELECT uid,password,email FROM user WHERE username = ?" << name;
		cppdb::result r = stat.query();

		while(r.next()) {
  			r.fetch(0,this->uid);
  			r.fetch(1,this->_password);
  			r.fetch(2,this->_email);
    	}
    
    	stat.reset();

		std::cout << "Entity loaded " << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "exception occured " << e.what();
	}
}

