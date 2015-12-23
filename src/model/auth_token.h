#ifndef AUTH_TOKEN_H
#define AUTH_TOKEN_H

#include "user.h"

class auth_token : public model {

public:
	auth_token(backend& db) :
		model(db)
	{
		this->table_name = "auth_token";
		this->primary_info["session_id"] = "";
		this->primary_info["remote"] = 0;
		this->field_list.push_back("session_id");
		this->field_list.push_back("remote"); 
		this->field_list.push_back("uid"); 
		this->field_list.push_back("refresh");
		this->field_list.push_back("created");
		this->field_list.push_back("valid");
	};
	auth_token(backend& db, std::string session_id, long int remote) :
		model(db),
		session_id(session_id),
		_remote(remote)
	{
		this->table_name = "auth_token";
		this->primary_info["session_id"] = session_id;
		this->primary_info["remote"] = remote;
		this->field_list.push_back("session_id");
		this->field_list.push_back("remote"); 
		this->field_list.push_back("uid"); 
		this->field_list.push_back("refresh");
		this->field_list.push_back("created");
		this->field_list.push_back("valid");
	};
	
	void save();
	void load();
	bool m_delete();

	/* Setters */
	void set_user(std::shared_ptr<user> user);

	user get_user();

	std::string session_id;
	long int _remote;
	std::string _refresh;
	std::string _created;
    std::string _valid;

private:
	std::shared_ptr<user> _user;

};

#endif /* AUTH_TOKEN_H */

