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
	void set_domain(std::shared_ptr<domain> domain);

	int get_id();
	std::string get_address();
	std::string get_created();
	domain get_domain();

private:
	int id;
	std::string _address;
	std::string _created; 
	std::shared_ptr<domain> _domain; /* auto_ptr deprecated */

};

#endif /* MAILBOX_H */

