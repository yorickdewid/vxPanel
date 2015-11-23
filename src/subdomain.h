#ifndef SUBDOMAIN_H
#define SUBDOMAIN_H
#include "domain.h"

class subdomain : public model {

public:
	subdomain(backend& db, int id) :
		model(db),
		id(id)
	{};
	
	void save();
	void load();

	void set_name(std::string name);
	void set_domain(std::shared_ptr<domain> domain);

	int get_id();
	std::string get_name();
	std::string get_created();
	domain get_domain();

private:
	int id;
	std::string _name;
	std::string _created; 
	std::shared_ptr<domain> _domain; /* auto_ptr deprecated */

};

#endif /* SUBDOMAIN_H */

