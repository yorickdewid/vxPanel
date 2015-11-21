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

void user::save()
{
	cppdb::statement stat;

	stat = db.session() << 
			"INSERT INTO user (username, password, email) "
			"VALUES (?, ?, ?)" << name << _password << _email;

	stat.exec();
	uid = stat.last_insert_id();
	stat.reset();
}
