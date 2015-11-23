#ifndef DNS_H
#define DNS_H
#include "domain.h"

class dns : public model {

public:
	dns(backend& db, int id) :
		model(db),
		id(id)
	{};
	
	void save();
	void load();

	void set_address(std::string address);
	void set_domain(std::unique_ptr<domain> domain);

	int get_id();
	std::string get_address();
	std::string get_created();
	domain get_domain();

private:
	int id;
	std::string _address;
	std::string _created;
	std::unique_ptr<domain> _domain; /* auto_ptr deprecated */

};

#endif /* DNS_H */

