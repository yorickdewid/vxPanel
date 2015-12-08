#ifndef USER_H
#define USER_H

#include <iostream>

class user: public model {

public:
	user(backend& db) : model(db) { 
		this->table_name = "user";
		this->primary = "uid"; 
		this->field_list.push_back("uid");
		this->field_list.push_back("username"); 
		this->field_list.push_back("password"); 
		this->field_list.push_back("email"); 
		this->field_list.push_back("firstname"); 
		this->field_list.push_back("lastname"); 
		this->field_list.push_back("country");
		this->field_list.push_back("city");
		this->field_list.push_back("address");
		this->field_list.push_back("address_number");
		this->field_list.push_back("postal");
		this->field_list.push_back("note");
		this->field_list.push_back("remote");
		this->field_list.push_back("user_type");
		this->field_list.push_back("active");
		this->field_list.push_back("created");
		this->field_list.push_back("last_login");
	};
	user(backend& db, int uid) : model(db), uid(uid) { 
		this->table_name = "user";
		this->primary = "uid"; 
		this->primary_value = uid;
		this->field_list.push_back("uid");
		this->field_list.push_back("username"); 
		this->field_list.push_back("password"); 
		this->field_list.push_back("email"); 
		this->field_list.push_back("firstname"); 
		this->field_list.push_back("lastname"); 
		this->field_list.push_back("country");
		this->field_list.push_back("city");
		this->field_list.push_back("address");
		this->field_list.push_back("address_number");
		this->field_list.push_back("postal");
		this->field_list.push_back("note");
		this->field_list.push_back("remote");
		this->field_list.push_back("user_type");
		this->field_list.push_back("active");
		this->field_list.push_back("created");
		this->field_list.push_back("last_login");
		this->load(); 
	};

	
	void save();
	void load();
	bool update(update_obj update);
	bool update(std::vector<update_obj> list);
	bool m_delete();

	/* Setters */
	void set_username(std::string username);
	void set_email(std::string email);
	void set_password(std::string password);
	void set_firstname(std::string firstname);
	void set_lastname(std::string lastname);
	void set_country(std::string country);
	void set_city(std::string city);
	void set_address(std::string address);
	void set_address_number(int address_number);
	void set_postal(std::string postal);
	void set_remote(std::string remote);
	void set_note(std::string note);
	void set_user_type(std::string user_type);
	void set_active(bool active);
	void set_lastlogin(std::string lastlogin);

	int get_uid();
	std::string get_username();
	std::string get_password();
	std::string get_email();
	std::string get_firstname();
	std::string get_lastname();
	std::string get_country();
	std::string get_city();
	std::string get_address();
	int get_address_number();
	std::string get_postal();
	std::string get_note();
	std::string get_remote();
	std::string get_user_type();
	bool get_active();
	std::string get_created(); /* no altering */
	std::string get_lastlogin();

	friend std::ostream &operator<<(std::ostream &output, const user &u)
	{ 
		output << u.username;
		return output;
	}

private:
	int uid;
	std::string username;
	std::string _password;
	std::string _email;
	std::string _firstname;
	std::string _lastname;
	std::string _country;
	std::string _city;
	std::string _address;
	int _address_number;
	std::string _postal;
	std::string _note;
	std::string _remote; // ip_address on save
	std::string _user_type;
	bool _active;
	std::string _created;
	std::string _lastlogin;

};

#endif /* USER_H */

