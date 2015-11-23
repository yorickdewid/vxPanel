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

	void set_name(std::string name);
	void set_address(std::string custom_config);
	void set_domain(std::shared_ptr<domain> domain);

	int get_id();
	std::string get_name();
	std::string get_address();
	std::string get_created();
	domain get_domain();

private:
	int id;
	std::string _name;
	std::string _address;
	std::string _created; 
	std::shared_ptr<domain> _domain; /* auto_ptr deprecated */

};

#endif /* MAILBOX_H */

