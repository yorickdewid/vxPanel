#ifndef USER_H
#define USER_H

class user: public model {

public:
	user(backend& db, std::string username) : model(db), name(username) {};
	void email(std::string email);
	void password(std::string password);
	void save();
	void load();
	std::string get_username();
	std::string get_email();

private:
	int uid;
	std::string name;
	std::string _email;
	std::string _password;

};

#endif /* USER_H */

