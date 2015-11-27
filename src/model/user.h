#ifndef USER_H
#define USER_H

#include <iostream>

class user: public model {

public:
	user(backend& db, int uid) : model(db), uid(uid) { /*this->load(); */ };
	user(backend& db) : model(db) {};
	
	void save();
	void load();
	bool update(std::string field);
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
	void set_postal(std::string postal);
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
	std::string get_postal();
	std::string get_note();
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
	std::string _postal;
	std::string _note;
	std::string _user_type;
	bool _active;
	std::string _created;
	std::string _lastlogin;

};

#endif /* USER_H */
