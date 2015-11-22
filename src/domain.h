#ifndef DOMAIN_H
#define DOMAIN_H

class domain: public model {

public:
	domain(backend& db, std::string domain_name) : model(db), name(domain_name) {};
	
	void save();
	void load();

	/* Setters */
	void status(std::string status);
	void registrar(std::string registrar);
	void user_id(int uid);
	void vhost_id(int vhost_id);

	std::string get_domain_name();
	std::string get_status();
	std::string get_registrar();
	std::string get_created();
	int get_user_id();
	int get_vhost_id();

private:
	std::string name;
	std::string _status;
	std::string _registrar;
	std::string _created;
	int _uid;
	int _vhost_id = -1;

};

#endif /* DOMAIN_H */

