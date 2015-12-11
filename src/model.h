#ifndef MODEL_H
#define MODEL_H

#include "exceptions.h"
#include "backend.h"
#include "update_obj.h"
#include <boost/any.hpp>
#include <iostream>
#include <sstream>
#include <vector>

class model {

public:
	model(backend& db) :
		db(db),
		saved(false)
	{};
	virtual void save() = 0;
	virtual void load() = 0;

	void add_to_statement(cppdb::statement& stat, boost::any value);
	bool update(std::unique_ptr<update_interface> update);
	bool update(std::vector<std::unique_ptr<update_interface>> update_list);
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
    boost::any primary_value;

};

#endif /* MODEL_H */

