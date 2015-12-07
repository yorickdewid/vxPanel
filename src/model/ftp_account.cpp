#include <iostream>

#include "../model.h"
#include "ftp_account.h"
#include "domain.h"
#include "user.h"

void ftp_account::save()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
		"INSERT INTO ftpuser (name, password, homedir, userid) "
		"VALUES (?, encrypt(?), ?, ?)" << _name << _password << _homedir << _user->get_uid();
		stat.exec();
		stat.reset();

		this->saved = true;

		std::cout << "Saved" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

void ftp_account::load()
{
	try{
		cppdb::statement stat;
		int userid;

		stat = db.session() << 
				"SELECT * FROM ftpuser WHERE name = ?" << _name;
		cppdb::result r = stat.query();

		while(r.next()) {
			r >> this->id >> this->_name >> this->_password >> this->_uid >> this->_gid >> this->_homedir >> this->_shell >> this->_count >> userid >> this->_created >> this->_accessed >> this ->_modified;
	  		set_user(std::shared_ptr<user>(new user(db,userid)));
	    }

	    stat.reset();

    	this->saved = true;

		std::cout << "Entity loaded " << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

bool ftp_account::update(std::string field)
{
	/* TODO */
	(std::string)field;
	return true;
}

bool ftp_account::update(std::vector<update_obj> list)
{
	/* TODO */
	(std::vector<update_obj>)list;
	return true;
}

bool ftp_account::m_delete()
{
	try{
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
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
	return false;
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

