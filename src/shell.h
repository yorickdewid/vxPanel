#ifndef SHELL_H
#define SHELL_H
#include "user.h"

class shell : public model {

public:
	shell(backend& db, int id) :
		model(db),
		id(id)
	{};
	
	void save();
	void load();
	bool update(std::string field);
	bool m_delete();
	
	void set_user(std::shared_ptr<user> user);

	int get_id();
	std::string get_created();
	user get_user();

private:
	int id;
	std::string _created;
	std::shared_ptr<user> _user;

};

#endif /* SHELL_H */

