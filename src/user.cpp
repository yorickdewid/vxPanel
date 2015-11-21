#include <iostream>

#include "config.h"
#include "exceptions.h"
#include "backend.h"
#include "model.h"
#include "user.h"

void user::email(std::string email)
{
	this->_email = email;
}

void user::password(std::string password)
{
	this->_password = password;
}

void user::save()
{
	cppdb::statement stat;

	stat = db.session() << 
			"INSERT INTO user (username, password, email) "
			"VALUES (?, ?, ?)" << name << _password << _email;

	stat.exec();
	uid = stat.last_insert_id();
	stat.reset();

	std::cout << "Saved" << std::endl;
}
