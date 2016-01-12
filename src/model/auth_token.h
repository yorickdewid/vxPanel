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
		this->primary_info["remote"] = "";
		this->field_list["session_id"] = true;
		this->field_list["remote"] = true; 
		this->field_list["uid"] = true; 
		this->field_list["refresh"] = true;
		this->field_list["created"] = false;
		this->field_list["valid"] = true;
	};
	auth_token(backend& db, std::string session_id, std::string remote) :
		model(db),
		session_id(session_id),
		remote(remote)
	{
		this->table_name = "auth_token";
		this->primary_info["session_id"] = session_id;
		this->primary_info["remote"] = remote;
		this->field_list["session_id"] = true;
		this->field_list["remote"] = true; 
		this->field_list["uid"] = true; 
		this->field_list["refresh"] = true;
		this->field_list["created"] = false;
		this->field_list["valid"] = true;
	};
	
	void save();
	void load();
	bool m_delete();

	/* Setters */
	void set_user(std::shared_ptr<user> user);

	user get_user();

	std::string session_id;
	std::string remote;
	std::string _refresh;
	std::string _created;
    std::string _valid;

private:
	void check_if_token_exists();

	std::shared_ptr<user> _user;
};

#endif /* AUTH_TOKEN_H */

