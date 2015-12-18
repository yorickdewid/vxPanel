#ifndef SUBDOMAIN_H
#define SUBDOMAIN_H

#include "domain.h"
#include "vhost.h"

class subdomain : public model {

public:
	subdomain(backend& db) :
		model(db)
	{
		this->table_name = "subdomain";
		this->primary_info["name"] = "";
		this->primary_info["domain_name"] = "";
		this->field_list.push_back("name");
		this->field_list.push_back("created"); 
		this->field_list.push_back("domain_name"); 
		this->field_list.push_back("vhost_id");
		this->field_list.push_back("active");
	};
	subdomain(backend& db, std::string name, std::string domain_name) :
		model(db),
		name(name),
		_domain(new domain(db,domain_name))
	{
		this->table_name = "subdomain";
		this->primary_info["name"] = name;
		this->primary_info["domain_name"] = domain_name;
		this->field_list.push_back("name");
		this->field_list.push_back("created"); 
		this->field_list.push_back("domain_name"); 
		this->field_list.push_back("vhost_id");
		this->field_list.push_back("active");
	};
	
	void save();
	void load();
	bool m_delete();

	void set_name(std::string name);
	void set_domain(std::shared_ptr<domain> domain);
	void set_vhost(std::shared_ptr<vhost> vhost);

	std::string get_name();
	std::string get_created();
	domain get_domain();
	std::shared_ptr<domain> get_domain_ptr();
	vhost get_vhost();

private:
	std::string name;
	std::string _created; 
	std::shared_ptr<domain> _domain;
	std::shared_ptr<vhost> _vhost;

};

#endif /* SUBDOMAIN_H */

