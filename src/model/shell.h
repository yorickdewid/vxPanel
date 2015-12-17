#ifndef SHELL_H
#define SHELL_H
#include "user.h"

class shell : public model {

public:
	shell(backend& db) :
		model(db)
	{};
	shell(backend& db, int id) :
		model(db),
		id(id)
	{};
	
	void save();
	void load();
	bool m_delete();
	
	void set_user(std::shared_ptr<user> user);
	void set_active(bool active);

	int get_id();
	std::string get_created();
	user get_user();
	bool get_active();

private:
	int id;
	std::string _created;
	std::shared_ptr<user> _user;
	bool _active;

};

#endif /* SHELL_H */

