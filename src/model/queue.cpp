#include "../model.h"
#include "queue.h"
#include "user.h"

void queue::save()
{
	try{
		cppdb::statement stat;

		std::ostringstream query;
		query << "INSERT INTO queue (action, uid ";

		if ( !_params.empty() ) {
			query << ", params";
		}
		if ( !_started.empty() ) {
			query << ", started";
		}
		if ( !_finished.empty() ) {
			query << ", finished";
		}
		if ( !_status.empty() ) {
			query << ", status";
		}

		query << ")";
	    query << " VALUES (?, ?";

	    if ( !_params.empty() ) {
			query << ", ?";
		}
		if ( !_started.empty() ) {
			query << ", ?";
		}
		if ( !_finished.empty() ) {
			query << ", ?";
		}
		if ( !_status.empty() ) {
			query << ", ?";
		}

		query << ")";

		stat = db.session() << query.str();

		stat << _action << this->get_user().get_uid();

		if ( !_params.empty() ) {
			stat << _params;
		}
		if ( !_started.empty() ) {
			stat << _started;
		}
		if ( !_finished.empty() ) {
			stat << _finished;
		}
		if ( !_status.empty() ) {
			stat << _status;
		}

		stat.exec();
		stat.reset();

		this->saved = true;

		BOOSTER_INFO("queue") << "Saved" << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

void queue::load()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"SELECT * FROM queue WHERE qid = ?" << qid;
		cppdb::result r = stat.query();

		while(r.next()) {
			int uid = -1;
	  		r >> this->qid >> this->_action >> this->_params >> this->_created >> this->_started >> this->_finished >> uid >> this->_status >> this->_result;
	  		if ( uid != -1 ) {
	  			this->set_user(std::shared_ptr<user>(new user(db,uid)));
	  		}
	    }

	    stat.reset();

    	this->saved = true;

		BOOSTER_INFO("queue") << "Entity loaded " << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured vhost load " << e.what() << std::endl;
	}
}

bool queue::m_delete()
{
	try{
		cppdb::statement stat;

		stat = db.session() << 
				"DELETE FROM queue WHERE qid = ?" << qid;
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

void queue::set_user(std::shared_ptr<user> user)
{
	this->_user.swap(user);
}

std::string queue::get_created()
{
	return this->_created;
}

std::string queue::get_result()
{
	return this->_result;
}

user queue::get_user()
{
	return *this->_user;
}

