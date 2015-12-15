#ifndef DNS_H
#define DNS_H
#include "domain.h"

class dns : public model {

public:
	dns(backend& db) :
		model(db)
	{};
	dns(backend& db, int id) :
		model(db),
		id(id)
	{
		this->table_name = "dns";
		this->primary_info["id"] = id; 
		this->field_list.push_back("id");
		this->field_list.push_back("name"); 
		this->field_list.push_back("created"); 
		this->field_list.push_back("domain_name"); 
		this->field_list.push_back("active");
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

private:
	int id;
	std::string _name;
	std::string _created;
	std::shared_ptr<domain> _domain; /* auto_ptr deprecated */
	bool _active;

};

#endif /* DNS_H */

