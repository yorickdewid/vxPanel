#ifndef DOMAIN_ALIAS_H
#define DOMAIN_ALIAS_H
#include "domain.h"

class domain_alias : public model {

public:
	domain_alias(backend& db) :
		model(db)
	{
		this->table_name = "domain_alias";
		this->primary_info["id"] = -1; 
		this->field_list["id"] = false;
		this->field_list["domain_name"] = true;
		this->field_list["source"] = true;
		this->field_list["destination"] = true;
		this->field_list["created"] = false;
		this->field_list["active"] = false;
	};
	domain_alias(backend& db, int id) :
		model(db),
		id(id)
	{
		this->table_name = "domain_alias";
		this->primary_info["id"] = id; 
		this->field_list["id"] = false;
		this->field_list["domain_name"] = true;
		this->field_list["source"] = true;
		this->field_list["destination"] = true;
		this->field_list["created"] = false;
		this->field_list["active"] = false;
	};
	
	void save();
	void load();
	void load(std::string domain_name);
	bool m_delete();
	
	void set_domain(std::shared_ptr<domain> domain);

	int get_id();
	std::string get_created();
	domain get_domain();

	std::string _source;
	std::string _destination;
	bool _active;

private:
	int id;
	std::string _created;
	std::shared_ptr<domain> _domain;

};

#endif /* DOMAIN_ALIAS_H */

