#ifndef APP_SETTINGS_H
#define APP_SETTINGS_H

class app_settings : public model {

public:
	app_settings(backend& db) :
		model(db)
	{
		this->table_name = "`settings`";
		this->primary_info["key"] = "";
		this->field_list["key"] = true;
		this->field_list["value"] = true; 
		this->field_list["default"] = true; 
		this->field_list["description"] = true;
		this->field_list["updated"] = false;
		this->field_list["created"] = false;
	};
	app_settings(backend& db, std::string key) :
		model(db),
		key(key)
	{
		this->table_name = "`settings`";
		this->primary_info["key"] = key;
		this->field_list["key"] = true;
		this->field_list["value"] = true; 
		this->field_list["default"] = true; 
		this->field_list["description"] = true;
		this->field_list["updated"] = false;
		this->field_list["created"] = false;
	};
	
	void save();
	void load();
	bool m_delete();

	void set_key(std::string key);
	void set_value(std::string value);
    void set_default(bool default_);
	void set_description(std::string description);

	std::string get_key();
	std::string get_value();
	bool get_default();
	std::string get_description();
	std::string get_updated();
	std::string get_created();

private:
	std::string key;
	std::string _value;
	bool _default;
	std::string _description;
	std::string _updated;
	std::string _created;

};

#endif /* APP_SETTINGS_H */

