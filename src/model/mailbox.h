#ifndef MAILBOX_H
#define MAILBOX_H
#include "domain.h"

class mailbox : public model {

public:
	mailbox(backend& db) :
		model(db)
	{};
	mailbox(backend& db, int id) :
		model(db),
		id(id)
	{
		this->table_name = "mailbox";
		this->primary_info["id"] = id; 
		this->field_list.push_back("id");
		this->field_list.push_back("email"); 
		this->field_list.push_back("password"); 
		this->field_list.push_back("maildir"); 
		this->field_list.push_back("quota");
		this->field_list.push_back("created");
		this->field_list.push_back("domain_name");
		this->field_list.push_back("bytes");
		this->field_list.push_back("messages");
		this->field_list.push_back("active");
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

