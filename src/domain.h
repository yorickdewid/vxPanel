#ifndef DOMAIN_H
#define DOMAIN_H
#include "user.h"

class domain: public model {

public:
	domain(backend& db, std::string domain_name) :
		model(db),
		name(domain_name),
		_vhost_id(-1)
	{ this->load(); };
	
	void save();
	void load();

	/* Setters */
	void status(std::string status);
	void registrar(std::string registrar);
	void set_user(std::shared_ptr<user> user);
	void vhost_id(int vhost_id);

	std::string get_domain_name();
	std::string get_status();
	std::string get_registrar();
	std::string get_created();
	user get_user();
	int get_vhost_id();

private:
	std::string name;
	std::string _status;
	std::string _registrar;
	std::string _created;
	std::shared_ptr<user> _user;
	int _vhost_id; /* todo vhost object */

};

#endif /* DOMAIN_H */

