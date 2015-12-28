#ifndef MODEL_H
#define MODEL_H

#include "exceptions.h"
#include "backend.h"
#include "any.h"
#include "config.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <map>

class model {

public:
	model(backend& db) :
		db(db),
		saved(false)
	{};
	virtual void save() = 0;
	virtual void load() = 0;

	void add_to_statement(cppdb::statement& stat, any value);
	bool update(std::map<std::string, any> update_list);

	bool compare_field(std::string field);
	bool compare_primary_field(std::string field);

	virtual bool m_delete() = 0;

	bool is_empty(std::string var);
	bool get_saved(){ return this->saved; };
	std::map<std::string,any> get_primary_info(){ return this->primary_info; };
	std::map<std::string,bool> get_fields() { return this->field_list; };

protected:
	backend& db;
	bool saved;
	std::map<std::string,bool> field_list; // field name, required (true/false)
	std::string table_name;
    std::map<std::string,any> primary_info;

};

#endif /* MODEL_H */

