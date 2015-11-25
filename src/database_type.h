#ifndef DATABASE_TYPE_H
#define DATABASE_TYPE_H
#include <vector>

class database_type : public model {

public:
	database_type(backend& db, std::string name) :
		model(db),
		name(name)
	{ this->load(); };
	
	void save();
	void load();
	std::vector<database_type> load_all();

	void set_name(std::string name);

	std::string get_name();

private:
	std::string name;

};

#endif /* DATABASE_TYPE_H */

