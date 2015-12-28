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
	void set_user(std::shared_ptr<user> user);
	void set_vhost(std::shared_ptr<vhost> vhost);

	std::string get_created();
	user get_user();
	vhost get_vhost();

	std::string name;
	std::string _status;
	std::string _registrar;
	bool _active;

private:
	std::string _created;
	std::shared_ptr<user> _user;
	std::shared_ptr<vhost> _vhost;

};

#endif /* DOMAIN_H */

