#ifndef DOMAIN_H
#define DOMAIN_H

#include "user.h"
#include "vhost.h"

class domain: public model {

public:
	domain(backend& db) :
		model(db),
		_active(false)
	{
		this->table_name = "domain";
		this->primary_info["name"] = "";
		this->field_list["name"] = true;
		this->field_list["status"] = true; 
		this->field_list["registrar"] = true; 
		this->field_list["created"] = false; 
		this->field_list["uid"] = true; 
		this->field_list["vhost_id"] = false;
		this->field_list["active"] = false;
	};
	domain(backend& db, std::string domain_name) :
		model(db),
		name(domain_name),
		_active(false)
	{
		this->table_name = "domain";
		this->primary_info["name"] = domain_name;
		this->field_list["name"] = true;
		this->field_list["status"] = true; 
		this->field_list["registrar"] = true; 
		this->field_list["created"] = false; 
		this->field_list["uid"] = true; 
		this->field_list["vhost_id"] = false;
		this->field_list["active"] = false;
		this->load();
	};
	
	void save();
	void load();
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

