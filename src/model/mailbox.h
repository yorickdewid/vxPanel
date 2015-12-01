#ifndef MAILBOX_H
#define MAILBOX_H
#include "domain.h"

class mailbox : public model {

public:
	mailbox(backend& db, int id) :
		model(db),
		id(id)
	{};
	
	void save();
	void load();
	void load(std::string domain_name);
	bool update(std::string field);
	bool m_delete();
	
	void set_address(std::string address);
	void set_password(std::string password);
	void set_maildir(std::string maildir);
	void set_quota(long long int quota);
	void set_domain(std::shared_ptr<domain> domain);
	void set_active(bool active);

	int get_id();
	std::string get_address();
	std::string get_password();
	std::string get_created();
	std::string get_maildir();
	long long int get_quota();
	domain get_domain();
	bool get_active();

private:
	int id;
	std::string _address;
	std::string _password;
	std::string _created;
	std::string _maildir;
	long long int _quota;
	std::shared_ptr<domain> _domain; /* auto_ptr deprecated */
	bool _active;

};

#endif /* MAILBOX_H */

