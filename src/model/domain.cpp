#include <iostream>

#include "../model.h"
#include "domain.h"
#include "user.h"
#include "vhost.h"

void domain::save()
{
	cppdb::statement stat;

	if ( _vhost ) {
		stat = db.session() << 
			"INSERT INTO domain (name, status, registrar, uid, vhost_id) "
			"VALUES (?, ?, ?, ?, ?)" << name << _status << _registrar << get_user().get_uid() << _vhost->get_id();
	}else	{
		stat = db.session() << 
			"INSERT INTO domain (name, status, registrar, uid) "
			"VALUES (?, ?, ?, ?)" << name << _status << _registrar << get_user().get_uid();
	}

	stat.exec();
	stat.reset();

	this->saved = true;

	BOOSTER_INFO("domain") << "Saved" << std::endl;
}

void domain::load()
{
	cppdb::statement stat;
	int uid;

	stat = db.session() << 
			"SELECT * FROM domain WHERE name = ?" << name;
	cppdb::result r = stat.query();

	while(r.next()) {
		int tmp_vhost_id = -1;
		int tmp_active;
		r >> this->name >> this->_status >> this->_registrar >> this->_created >> uid >> tmp_vhost_id >> tmp_active;
  		this->set_user(std::shared_ptr<user>(new user(db,uid)));
  		if ( tmp_vhost_id != -1 ) { /* TODO replace with vhost object) */
  			set_vhost(std::shared_ptr<vhost>(new vhost(db,tmp_vhost_id)));
  		}
  		if ( tmp_active == 1 ) {
  			this->_active = true;
  		} else {
  			this->_active = false;
  		}
    }

    stat.reset();

	this->saved = true;

	BOOSTER_INFO("domain") << "Entity loaded domain " << std::endl;
}

/* TODO Handle foreign key block correctly */
bool domain::m_delete()
{
	cppdb::statement stat;

	stat = db.session() << 
			"DELETE FROM domain WHERE name = ?" << name;
	stat.exec();

	if ( stat.affected() == 1 ) {
		stat.reset();
		return true;
	} else {
		stat.reset();
		return false;
	}
}

bool domain::compare_owner(int uid)
{
	if ( !this->saved ) {
		if ( !name.empty() ) {
			this->load();
		} else {
			throw primary_key_ex();
			return false;
		}
	}
	if( this->get_user().get_uid() ==  uid ) {
		return true;
	}
	return false;
}

void domain::set_user(std::shared_ptr<user> user)
{
	this->_user.swap(user);
}

void domain::set_vhost(std::shared_ptr<vhost> vhost)
{
	this->_vhost.swap(vhost);
}

std::string domain::get_created()
{
	return this->_registrar;
}

user domain::get_user()
{
	return *this->_user;
}

vhost domain::get_vhost()
{
	return *this->_vhost;
}

std::shared_ptr<vhost> domain::get_vhost_ptr()
{
	return this->_vhost;
}

