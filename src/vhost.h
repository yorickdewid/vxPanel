#ifndef VHOST_H
#define VHOST_H

class vhost : public model {

public:
	vhost(backend& db, int id) :
		model(db),
		id(id)
	{};
	
	void save();
	void load();
	void load(std::string domain_name);
	bool update(std::string field);
	bool m_delete();
	
	void set_name(std::string name);
	void set_custom_config(std::string custom_config);

	int get_id();
	std::string get_name();
	std::string get_custom_config();
	std::string get_created();

private:
	int id;
	std::string _name;
	std::string _custom_config;
	std::string _created; 

};

#endif /* VHOST_H */

