#ifndef DOMAIN_H
#define DOMAIN_H

#include "user.h"
#include "vhost.h"

class domain: public model {

public:
	domain(backend& db, std::string domain_name) :
		model(db),
		name(domain_name)
	{
		this->load();
	};
	
	void save();
	void load();
	bool update(std::string field);
	bool update(std::vector<update_obj> list);
	bool m_delete();

	/* Setters */
	void status(std::string status);
	void registrar(std::string registrar);
	void set_user(std::shared_ptr<user> user);
	void set_vhost(std::shared_ptr<vhost> vhost);
	void set_active(bool active);

	std::string get_domain_name();
	std::string get_status();
	std::string get_registrar();
	std::string get_created();
	user get_user();
	vhost get_vhost();
	bool get_active();

private:
	std::string name;
	std::string _status;
	std::string _registrar;
	std::string _created;
	std::shared_ptr<user> _user;
	std::shared_ptr<vhost> _vhost;
	bool _active;

};

#endif /* DOMAIN_H */

