#ifndef USER_H
#define USER_H

#include <iostream>
#include "../constants.h"

class user : public model {

public:
	user(backend& db) : model(db), _address_number(-1){ 
		this->table_name = "user";
		this->primary_info["uid"] = -1; 
		this->field_list["uid"] = false;
		this->field_list["username"] = true; 
		this->field_list["password"] = true; 
		this->field_list["email"] = true; 
		this->field_list["firstname"] = false; 
		this->field_list["lastname"] = false; 
		this->field_list["country"] = false;
		this->field_list["city"] = false;
		this->field_list["address"] = false;
		this->field_list["address_number"] = false;
		this->field_list["postal"] = false;
		this->field_list["note"] = false;
		this->field_list["remote"] = false;
		this->field_list["user_type"] = false;
		this->field_list["active"] = false;
		this->field_list["created"] = false;
		this->field_list["last_login"] = false;
	};
	user(backend& db, int uid) : model(db), uid(uid), _address_number(-1) { 
		this->table_name = "user";
		this->primary_info["uid"] = uid;
		this->field_list["uid"] = false;
		this->field_list["username"] = true; 
		this->field_list["password"] = true; 
		this->field_list["email"] = true; 
		this->field_list["firstname"] = false; 
		this->field_list["lastname"] = false; 
		this->field_list["country"] = false;
		this->field_list["city"] = false;
		this->field_list["address"] = false;
		this->field_list["address_number"] = false;
		this->field_list["postal"] = false;
		this->field_list["note"] = false;
		this->field_list["remote"] = false;
		this->field_list["user_type"] = false;
		this->field_list["active"] = false;
		this->field_list["created"] = false;
		this->field_list["last_login"] = false;
		this->load(); 
	};

	
	void save();
	void load();
	bool m_delete();

	/* Setters */
	void set_uid(int uid);
	void set_username(std::string username);
	void set_password(std::string password);
	void set_email(std::string email);
	void set_user_type(std::string user_type);
	void set_active(bool active);
	void set_lastlogin(std::string lastlogin);

	int get_uid();
	std::string get_username();
	std::string get_password();
	std::string get_email();
	std::string get_user_type();
	bool get_active();
	std::string get_created(); /* no altering */
	std::string get_lastlogin();

	friend std::ostream &operator<<(std::ostream &output, const user &u)
	{ 
		output << u.username;
		return output;
	}

	std::string _firstname;
	std::string _lastname;
	std::string _country;
	std::string _city;
	std::string _address;
	int _address_number;
	std::string _postal;
	std::string _note;
	std::string _remote; // ip_address on save
	std::string _user_type = USER_TYPE_USER; // SAME DEFAULT AS DB
	bool _active;

private:
	int uid;
	std::string username;
	std::string _password;
	std::string _email;
	std::string _created;
	std::string _lastlogin;

};

#endif /* USER_H */

