#ifndef DNS_H
#define DNS_H
#include "domain.h"

class dns : public model {

public:
	dns(backend& db) :
		model(db)
	{
		this->table_name = "dns";
		this->primary_info["id"] = -1; 
		this->field_list["id"] = false;
		this->field_list["name"] = true;
		this->field_list["created"] = false;
		this->field_list["domain_name"] = true;
		this->field_list["active"] = false;
	};
	dns(backend& db, int id) :
		model(db),
		id(id)
	{
		this->table_name = "dns";
		this->primary_info["id"] = id; 
		this->field_list["id"] = false;
		this->field_list["name"] = true;
		this->field_list["created"] = false;
		this->field_list["domain_name"] = true;
		this->field_list["active"] = false;
	};
	
	void save();
	void load();
	void load(std::string domain_name);
	bool m_delete();
	
	void set_name(std::string name);
	void set_domain(std::shared_ptr<domain> domain);
	void set_active(bool active);

	int get_id();
	std::string get_name();
	std::string get_created();
	domain get_domain();
	bool get_active();

	std::string _name;
	bool _active;

private:
	int id;
	std::string _created;
	std::shared_ptr<domain> _domain; /* auto_ptr deprecated */

};

#endif /* DNS_H */

