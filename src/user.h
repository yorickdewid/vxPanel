#ifndef USER_H
#define USER_H

#include <iostream>

class user: public model {

public:
	user(backend& db, std::string username) : model(db), username(username) {};
	
	void save();
	void load();

	/* Setters */
	void email(std::string email);
	void password(std::string password);
	void firstname(std::string firstname);
	void lastname(std::string lastname);
	void country(std::string country);
	void city(std::string city);
	void address(std::string address);
	void postal(std::string postal);
	void note(std::string note);
	void active(bool active);
	void lastlogin(std::string lastlogin);

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
	bool _active;
	std::string _created;
	std::string _lastlogin;

};

#endif /* USER_H */

