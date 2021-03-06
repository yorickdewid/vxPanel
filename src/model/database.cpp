#include <iostream>

#include "../model.h"
#include "database.h"
#include "user.h"
#include "database_type.h"

void database::save()
{
	cppdb::statement stat;

	stat = db.session() << 
		"INSERT INTO user_db (name, db_type, uid) "
		"VALUES (?, ?, ?)" << name << _database_type->get_name() << _user->get_uid();

	stat.exec();
	stat.reset();

	this->saved = true;

	BOOSTER_INFO("database") << "Saved" << std::endl;
}

void database::load()
{
	cppdb::statement stat;
	std::string type;
	int uid;

	stat = db.session() << 
			"SELECT * FROM user_db WHERE name = ?" << name;
	cppdb::result r = stat.query();

	while(r.next()) {
  		r >> this->name	>> this->_created >> uid >> type;
  		set_database_type(std::shared_ptr<database_type>(new database_type(db,type)));
  		set_user(std::shared_ptr<user>(new user(db,uid)));
    }

    stat.reset();

	this->saved = true;

	BOOSTER_INFO("database") << "Entity loaded " << std::endl;
}

bool database::m_delete()
{
	cppdb::statement stat;

	stat = db.session() << 
			"DELETE FROM user_db WHERE name = ?" << name;
	stat.exec();

	if ( stat.affected() == 1 ) {
		stat.reset();
		return true;
	} else {
		stat.reset();
		return false;
	}
}


void database::set_name(std::string name)
{
	this->name = name;
}

void database::set_database_type(std::shared_ptr<database_type> database_type)
{
	this->_database_type.swap(database_type);
}

void database::set_user(std::shared_ptr<user> user)
{
	this->_user.swap(user);
}

std::string database::get_name()
{
	return this->name;
}

database_type database::get_database_type()
{
	return *this->_database_type;
}

std::string database::get_created()
{
	return this->_created;
}

user database::get_user()
{
	return *this->_user;
}

