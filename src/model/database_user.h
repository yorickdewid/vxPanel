#ifndef DATABASE_USER_H
#define DATABASE_USER_H
#include "user.h"

class database_user : public model {

public:
	database_user(backend& db) :
		model(db)
	{
		this->table_name = "user_db_user";
		this->primary_info["name"] = "";
		this->field_list["name"] = true;
		this->field_list["password"] = true;
		this->field_list["permissions"] = true; 
		this->field_list["created"] = false;
		this->field_list["uid"] = true;
	};
	database_user(backend& db, std::string name) :
		model(db),
		name(name)
	{
		this->table_name = "user_db_user";
		this->primary_info["name"] = name;
		this->field_list["name"] = true;
		this->field_list["password"] = true;
		this->field_list["permissions"] = true; 
		this->field_list["created"] = false;
		this->field_list["uid"] = true;
	};
	
	void save();
	void load();
	bool m_delete();

	void set_name(std::string name);
	void set_password(std::string address);
	void set_permissions(std::string _permissions);
	void set_user(std::shared_ptr<user> user);

	std::string get_name();
	std::string get_password();
	std::string get_permissions();
	std::string get_created();
	user get_user();

private:
	std::string name;
	std::string _password;
	std::string _permissions;
	std::string _created;
	std::shared_ptr<user> _user;

};

#endif /* DATABASE_USER_H */

