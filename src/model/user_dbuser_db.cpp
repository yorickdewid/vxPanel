#include <iostream>

#include "../model.h"
#include "user_dbuser_db.h"

void user_dbuser_db::save()
{
	cppdb::statement stat;

	stat = db.session() << 
		"INSERT INTO user_dbuser_db (db_username, db_name) "
		"VALUES (?, ?)" << db_username << db_name;

	stat.exec();
	stat.reset();

	this->saved = true;

	BOOSTER_INFO("user_db_user") << "Saved" << std::endl;
}

void user_dbuser_db::load()
{
	BOOSTER_DEBUG("user_db_user") << "trick" << std::endl;
}

void user_dbuser_db::load(std::string db_username, std::string db_name = "false")
{
	cppdb::statement stat;
	if (db_name.compare("false") == 0) {
		stat = db.session() << 
		"SELECT * FROM user_dbuser_db WHERE db_username = ?" << db_username;
	} else {
		stat = db.session() << 
		"SELECT * FROM user_dbuser_db WHERE db_name= ?" << db_name;
	}

	cppdb::result r = stat.query();

	while(r.next()) {
		r >> this->db_username >> this->db_name;
    }

    stat.reset();

	this->saved = true;

	BOOSTER_INFO("user_db_user") << "Entity loaded " << std::endl;
}

bool user_dbuser_db::m_delete()
{
	cppdb::statement stat;

	stat = db.session() << 
			"DELETE FROM user_dbuser_db WHERE db_username = ? and db_name = ?" << db_username << db_name;
	stat.exec();

	if ( stat.affected() == 1 ) {
		stat.reset();
		return true;
	} else {
		stat.reset();
		return false;
	}
}

void user_dbuser_db::set_db_username(std::string db_username)
{
	this->db_username = db_username;
}

void user_dbuser_db::set_db_name(std::string db_name)
{
	this->db_name = db_name;
}

std::string user_dbuser_db::get_db_username()
{
	return this->db_username;
}

std::string user_dbuser_db::get_db_name()
{
	return this->db_name;
}

