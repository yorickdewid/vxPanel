#ifndef DATABASE_H
#define DATABASE_H
#include "user.h"
#include "database_type.h"

class database : public model {

public:
	database(backend& db, std::string name) :
		model(db),
		name(name)
	{};
	
	void save();
	void load();

	void set_name(std::string name);
	void set_database_type(std::shared_ptr<database_type> database_type);
	void set_user(std::shared_ptr<user> user);

	std::string get_name();
	database_type get_database_type();
	std::string get_created();
	user get_user();

private:
	std::string name;
	std::string _created;
	std::shared_ptr<database_type> _database_type;
	std::shared_ptr<user> _user;

};

#endif /* DATABASE_H */
