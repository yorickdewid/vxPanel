#ifndef SUBDOMAIN_H
#define SUBDOMAIN_H
#include "domain.h"

class subdomain : public model {

public:
	subdomain(backend& db, std::string name, std::string domain_name) :
		model(db),
		name(name),
		_domain(new domain(db,domain_name)),
		_vhost_id(-1)
	{};
	
	void save();
	void load();
	bool update(std::string field);
	bool m_delete();

	void set_name(std::string name);
	void set_domain(std::shared_ptr<domain> domain);
	void set_vhost_id(int vhost_id);

	std::string get_name();
	std::string get_created();
	domain get_domain();
	std::shared_ptr<domain> get_domain_ptr();
	int get_vhost_id();

private:
	std::string name;
	std::string _created; 
	std::shared_ptr<domain> _domain; /* auto_ptr deprecated */
	int _vhost_id; /* todo vhost object */

};

#endif /* SUBDOMAIN_H */

