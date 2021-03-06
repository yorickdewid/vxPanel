#include <iostream>

#include "../model.h"
#include "../config.h"
#include "ftp_account.h"
#include "domain.h"
#include "user.h"

void ftp_account::save()
{
	cppdb::statement stat;

	std::ostringstream query;
	
	query << "INSERT INTO ftpuser (name, password, homedir, userid) ";
	query << "VALUES (?, encrypt(?,'"<< FTP_SALT <<"'), ?, ?)";

	stat = db.session() << query.str() << _name << _password << _homedir << _user->get_uid(); 
	stat.exec();
	stat.reset();

	this->saved = true;

	BOOSTER_INFO("ftp_account") << "Saved" << std::endl;
}

void ftp_account::load()
{
	cppdb::statement stat;
	int userid;

	stat = db.session() << 
			"SELECT * FROM ftpuser WHERE name = ?" << _name;
	cppdb::result r = stat.query();

	while(r.next()) {
		BOOSTER_DEBUG("ftp_account") << "before " << std::endl;
		r >> this->id >> this->_name >> this->_password >> this->_uid >> this->_gid >> this->_homedir >> this->_shell >> this->_count >> userid >> this->_created >> this->_accessed >> this ->_modified;
  		BOOSTER_DEBUG("ftp_account") << "after " << std::endl;
  		set_user(std::shared_ptr<user>(new user(db,userid)));
    }

    stat.reset();

	this->saved = true;

	BOOSTER_INFO("ftp_account") << "Entity loaded " << std::endl;
}


void ftp_account::load_id()
{
	cppdb::statement stat;
	int userid;

	stat = db.session() << 
			"SELECT * FROM ftpuser WHERE id = ?" << id;
	cppdb::result r = stat.query();

	while(r.next()) {
		BOOSTER_DEBUG("ftp_account") << "before " << std::endl;
		r >> this->id >> this->_name >> this->_password >> this->_uid >> this->_gid >> this->_homedir >> this->_shell >> this->_count >> userid >> this->_created >> this->_accessed >> this ->_modified;
  		BOOSTER_DEBUG("ftp_account") << "before " << std::endl;
  		set_user(std::shared_ptr<user>(new user(db,userid)));
    }

    stat.reset();

	this->saved = true;

	BOOSTER_INFO("ftp_account") << "Entity loaded " << std::endl;
}

bool ftp_account::m_delete()
{
	cppdb::statement stat;

	stat = db.session() << 
			"DELETE FROM ftpuser WHERE name = ?" << _name;
	stat.exec();

	if ( stat.affected() == 1 ) {
		stat.reset();
		return true;
	} else {
		stat.reset();
		return false;
	}
}

void ftp_account::set_username(std::string username)
{
	this->_name = username;
}

void ftp_account::set_password(std::string password)
{
	this->_password = password;
}

void ftp_account::set_uid(int uid)
{
	this->_uid = uid;
}

void ftp_account::set_gid(int gid)
{
	this->_gid = gid;
}

void ftp_account::set_homedir(std::string homedir)
{
	this->_homedir = homedir;
}

void ftp_account::set_shell(std::string shell)
{
	this->_shell = shell;
}

void ftp_account::set_count(int count)
{
	this->_count = count;
}

void ftp_account::set_user(std::shared_ptr<user> user)
{
	this->_user.swap(user);
}

void ftp_account::set_accessed(std::string accessed)
{
	this->_accessed = accessed;
}

void ftp_account::set_modified(std::string modified)
{
	this->_modified = modified;
}

int ftp_account::get_id()
{
	return this->id;
}

std::string ftp_account::get_username()
{
	return this->_name;
}

std::string ftp_account::get_password()
{
	return this->_password;
}

int ftp_account::get_uid()
{
	return this->_uid;
}

int ftp_account::get_gid()
{
	return this->_gid;
}

std::string ftp_account::get_homedir()
{
	return this->_homedir;
}

std::string ftp_account::get_shell()
{
	return this->_shell;
}

int ftp_account::get_count()
{
	return this->_count;
}

user ftp_account::get_user()
{
	return *this->_user;
}

std::string ftp_account::get_created()
{
	return this->_created;
}

std::string ftp_account::get_accessed()
{
	return this->_accessed;
}

std::string ftp_account::get_modified()
{
	return this->_modified;
}

