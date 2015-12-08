#ifndef MODEL_H
#define MODEL_H

#include "exceptions.h"
#include "backend.h"
#include <boost/any.hpp>
#include <iostream>
#include <sstream>
#include <vector>

struct update_obj{
public:
    std::string field;
    boost::any value;
    std::string primary;
    boost::any primary_value;
};

class model {

public:
	model(backend& db) :
		db(db),
		saved(false)
	{};
	virtual void save() = 0;
	virtual void load() = 0;
	// virtual bool update(std::string field) = 0;

	void add_to_statement(cppdb::statement& stat, boost::any& value);
	bool update(update_obj update);

	//virtual bool update(std::vector<update_obj> list) = 0;
	virtual bool m_delete() = 0;

	bool is_empty(std::string var);
	bool get_saved(){ return this->saved; };

protected:
	backend& db;
	bool saved;
	std::vector<std::string> field_list;
	std::string table_name;

};

#endif /* MODEL_H */

