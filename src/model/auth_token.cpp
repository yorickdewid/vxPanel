#include <iostream>

#include "../model.h"
#include "auth_token.h"
#include "user.h"

void auth_token::save()
{
	cppdb::statement stat;

	this->check_if_token_exists();

	stat = db.session() << "DROP TEMPORARY TABLE IF EXISTS `token_gen`";
	stat.exec();
	stat.reset();

	stat = db.session() << "CREATE TEMPORARY TABLE `token_gen`(`token` char(40) NOT NULL)";
	stat.exec();
	stat.reset();

	stat = db.session() << "INSERT INTO token_gen (`token`) VALUES(sha1(concat(now(), RAND())))";
	stat.exec();
	stat.reset();

	stat = db.session() << "SELECT * FROM token_gen";
	cppdb::result r = stat.query();

	if( r.next() ) {
		r >> session_id;
	}
	stat.reset();

	std::ostringstream query;

	query << "INSERT INTO auth_token (sessionid, remote, uid, refresh, valid) ";
	query << "VALUES (?, inet6_aton(?), ?, sha1(concat(now(), RAND())), now()+ INTERVAL " << TOKEN_VALID << " MINUTE )";
	stat = db.session() << query.str() << session_id << remote << get_user().get_uid(); 

	stat.exec();

	this->saved = true;

	BOOSTER_INFO("auth_token") << "Saved" << std::endl;
}

void auth_token::load()
{
	cppdb::statement stat;

	stat = db.session() << 
			"SELECT sessionid, INET6_NTOA(remote), uid, refresh, created, valid FROM auth_token WHERE sessionid = ? AND remote = inet6_aton(?)" << session_id << remote;
	cppdb::result r = stat.query();

	while(r.next()) {
		int uid;
		r >> this->session_id >> this->remote >> uid >> this->_refresh >> this->_created >> this->_valid;
  		this->set_user(std::shared_ptr<user>(new user(db,uid)));
    }

    stat.reset();

	this->saved = true;

	BOOSTER_INFO("auth_token") << "Entity loaded auth_token " << std::endl;
}

/* TODO Handle foreign key block correctly */
bool auth_token::m_delete()
{
	cppdb::statement stat;

	stat = db.session() << 
			"DELETE FROM auth_token WHERE sessionid = ? AND remote = inet6_aton(?)" << this->session_id << remote;
	stat.exec();

	if ( stat.affected() == 1 ) {
		stat.reset();
		return true;
	} else {
		stat.reset();
		return false;
	}
}

void auth_token::set_user(std::shared_ptr<user> user)
{
	this->_user.swap(user);
}

user auth_token::get_user()
{
	return *this->_user;
}

void auth_token::check_if_token_exists()
{
	cppdb::statement stat;

	stat = db.session() << 
	"SELECT * FROM auth_token WHERE uid = ? and valid <= now()" << get_user().get_uid();
	cppdb::result r = stat.query();

	std::string token;

	if( r.next() ) {
		r >> token;
	}

	stat.reset();

	stat = db.session() << 
	"DELETE FROM auth_token WHERE uid = ? and sessionid = ? and remote = inet6_aton(?)" << get_user().get_uid() << token << remote;
	stat.exec();
}
