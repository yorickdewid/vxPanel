#ifndef SETTINGS_H
#define SETTINGS_H

class settings : public model {

public:
	settings(backend& db, std::string key) :
		model(db),
		key(key)
	{};
	
	void save();
	void load();

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

#endif /* SETTINGS_H */

