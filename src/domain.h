#ifndef DOMAIN_H
#define DOMAIN_H

class domain: public model {

public:
	domain(backend& db, std::string domain_name) : model(db), name(domain_name) {};
	void status(std::string status);
	void registrar(std::string registrar);
	void save();
	void load();
	std::string get_registrar();
	std::string get_status();
	std::string get_domain_name();

private:
	std::string name;
	std::string _status;
	std::string _registrar;
	std::string _created;

};

#endif /* DOMAIN_H */

