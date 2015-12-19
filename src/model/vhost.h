#ifndef VHOST_H
#define VHOST_H

class vhost : public model {

public:
	vhost(backend& db) :
		model(db)
	{
		this->table_name = "vhost";
		this->primary_info["id"] = -1; 
		this->field_list.push_back("id");
		this->field_list.push_back("name"); 
		this->field_list.push_back("custom_config"); 
		this->field_list.push_back("created"); 
		this->field_list.push_back("active");
	};
	vhost(backend& db, int id) :
		model(db),
		id(id)
	{
		this->table_name = "vhost";
		this->primary_info["id"] = id; 
		this->field_list.push_back("id");
		this->field_list.push_back("name"); 
		this->field_list.push_back("custom_config"); 
		this->field_list.push_back("created"); 
		this->field_list.push_back("active");
	};
	
	void save();
	void load();
	void load(std::string domain_name);
	bool m_delete();
	
	void set_name(std::string name);
	void set_custom_config(std::string custom_config);
	void set_active(bool active);

	int get_id();
	std::string get_name();
	std::string get_custom_config();
	std::string get_created();
	bool get_active();

private:
	int id;
	std::string _name;
	std::string _custom_config;
	std::string _created; 
	bool _active;
	
};

#endif /* VHOST_H */

