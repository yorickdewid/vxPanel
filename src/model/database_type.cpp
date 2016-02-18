#include <iostream>
#include <vector>

#include "../model.h"
#include "database_type.h"

void database_type::save()
{
	cppdb::statement stat;

	stat = db.session() << 
		"INSERT INTO user_db_type (name) "
		"VALUES (?)" << name;

	stat.exec();
	stat.reset();

	this->saved = true;

	BOOSTER_INFO("database_type") << "Saved" << std::endl;
}

void database_type::load()
{
	cppdb::statement stat;

	stat = db.session() << 
			"SELECT * FROM user_db_type WHERE name = ?" << name;
	cppdb::result r = stat.query();

	while(r.next()) {
  		r >> this->name;
    }

    stat.reset();

	this->saved = true;

	BOOSTER_INFO("database_type") << "Entity loaded " << std::endl;
}

/* TODO Handle foreign key block correctly */
bool database_type::m_delete()
{
	cppdb::statement stat;

	stat = db.session() << 
			"DELETE FROM user_db_type WHERE name = ?" << name;
	stat.exec();

	if ( stat.affected() == 1 ) {
		stat.reset();
		return true;
	} else {
		stat.reset();
		return false;
	}
}


std::vector<database_type> database_type::load_all()
{
	cppdb::statement stat;
	std::vector<database_type> database_types; 

	stat = db.session() << 
			"SELECT * FROM user_db_type";
	cppdb::result r = stat.query();

	while(r.next()) {
		std::string tmp_name;
  		r >> tmp_name;
  		database_type obj = database_type(db,tmp_name);
  		database_types.push_back(obj);
    }

    stat.reset();

	BOOSTER_INFO("database_type") << "All data loaded" << std::endl;

	return database_types;
}

std::string database_type::get_name()
{
	return this->name;
}

