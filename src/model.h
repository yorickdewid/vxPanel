#ifndef MODEL_H
#define MODEL_H

#include "exceptions.h"
#include "backend.h"
#include "any.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <map>

class model {

public:
	model(backend& db) :
		db(db),
		saved(false),
		primary_value(0)
	{};
	virtual void save() = 0;
	virtual void load() = 0;

	void add_to_statement(cppdb::statement& stat, any value);
	bool update(std::string field, any value);
	bool update(std::map<std::string, any> update_list);
	bool compare_field(std::string field); /* TODO move to validate class ? */

	virtual bool m_delete() = 0;

	bool is_empty(std::string var);
	bool get_saved(){ return this->saved; };
	std::vector<std::string> get_fields() { return this->field_list; };

protected:
	backend& db;
	bool saved;
	std::vector<std::string> field_list;
	std::string table_name;
	std::string primary;
    any primary_value;

};

#endif /* MODEL_H */

