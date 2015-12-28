#ifndef MAILBOX_H
#define MAILBOX_H
#include "domain.h"

class mailbox : public model {

public:
	mailbox(backend& db) :
		model(db)
	{
		this->table_name = "mailbox";
		this->primary_info["id"] = -1; 
		this->field_list["id"] = true;
		this->field_list["email"] = true; 
		this->field_list["password"] = true; 
		this->field_list["maildir"] = true; 
		this->field_list["quota"] = true;
		this->field_list["created"] = false;
		this->field_list["domain_name"] = true;
		this->field_list["bytes"]= true;
		this->field_list["messages"] = true;
		this->field_list["active"] = false;
	};
	mailbox(backend& db, int id) :
		model(db),
		id(id)
	{
		this->table_name = "mailbox";
		this->primary_info["id"] = id; 
		this->field_list["id"] = true;
		this->field_list["email"] = true; 
		this->field_list["password"] = true; 
		this->field_list["maildir"] = true; 
		this->field_list["quota"] = true;
		this->field_list["created"] = false;
		this->field_list["domain_name"] = true;
		this->field_list["bytes"]= true;
		this->field_list["messages"] = true;
		this->field_list["active"] = false;
	};
	
	void save();
	void load();
	void load(std::string domain_name);
	bool m_delete();
	
	void set_email(std::string email);
	void set_password(std::string password);
	void set_maildir(std::string maildir);
	void set_quota(long long int quota);
	void set_domain(std::shared_ptr<domain> domain);
	void set_active(bool active);

	int get_id();
	std::string get_email();
	std::string get_password();
	std::string get_created();
	std::string get_maildir();
	long long int get_quota();
	domain get_domain();
	bool get_active();

private:
	int id;
	std::string _email;
	std::string _password;
	std::string _maildir;
	long long int _quota;
	std::string _created;
	std::shared_ptr<domain> _domain; /* auto_ptr deprecated */
	long long int bytes;
	std::string messages; 
	bool _active;

};

#endif /* MAILBOX_H */

