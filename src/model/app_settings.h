#ifndef APP_SETTINGS_H
#define APP_SETTINGS_H

class app_settings : public model {

public:
	app_settings(backend& db) :
		model(db)
	{};
	app_settings(backend& db, std::string key) :
		model(db),
		key(key)
	{
		this->table_name = "`settings`";
		this->primary_info["key"] = key;
		this->field_list.push_back("key");
		this->field_list.push_back("value"); 
		this->field_list.push_back("default"); 
		this->field_list.push_back("description"); //linux
		this->field_list.push_back("updated");
		this->field_list.push_back("created");
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

