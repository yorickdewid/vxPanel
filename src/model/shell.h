#ifndef SHELL_H
#define SHELL_H
#include "user.h"

class shell : public model {

public:
	shell(backend& db) :
		model(db)
	{
		this->table_name = "shell";
		this->primary_info["id"] = -1; 
		this->field_list["id"] = false;
		this->field_list["created"] = false;
		this->field_list["uid"] = true; 
		this->field_list["active"] = false;
	};
	shell(backend& db, int id) :
		model(db),
		id(id)
	{
		this->table_name = "shell";
		this->primary_info["id"] = id; 
		this->field_list["id"] = false;
		this->field_list["created"] = false;
		this->field_list["uid"] = true; 
		this->field_list["active"] = false;
	};
	
	void save();
	void load();
	bool m_delete();
	
	void set_user(std::shared_ptr<user> user);
	void set_active(bool active);

	int get_id();
	std::string get_created();
	user get_user();
	bool get_active();

	bool _active;

private:
	int id;
	std::string _created;
	std::shared_ptr<user> _user;


};

#endif /* SHELL_H */

