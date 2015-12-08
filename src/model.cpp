#include "model.h"

void model::add_to_statement(cppdb::statement& stat, boost::any& value)
{
	std::string string = "PKc";
	std::string boolean = "b";
	std::string integer = "i";

	const std::type_info &ti = value.type();
	if (string.compare(ti.name()) == 0 ) {
		stat << boost::any_cast<std::string>(value);
	} else if (boolean.compare(ti.name()) == 0 ) {
		stat << boost::any_cast<bool>(value);
	} else if (integer.compare(ti.name()) == 0 ) {
		stat << boost::any_cast<int>(value);
	}
}

// TODO SANITIZE VALUE
bool model::update(update_obj update)
{
	try{
		cppdb::statement stat;

		std::ostringstream query;
		query << "UPDATE "<< this->table_name << " set `" << update.field << "` = ? WHERE "<< this->primary << " = ?";

		std::cout << query.str() << std::endl;

		stat = db.session() << query.str();
		if (!update.value.empty())
		{
			this->add_to_statement(stat, update.value);
		}

		this->add_to_statement(stat, this->primary_value);

		stat.exec();

		if ( stat.affected() == 1 ) {
			stat.reset();
			return true;
		} else {
			stat.reset();
			return false;
		}
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
		return false;
	}
	return false;
}

// TODO SANITIZE VALUE
bool model::update(std::vector<update_obj> update_list)
{
	try{
		cppdb::statement stat;

		std::ostringstream query;
		query << "UPDATE "<< this->table_name;

		/* First generate the entire query .. */
		for(std::vector<update_obj>::iterator it = update_list.begin(); it != update_list.end(); ++it) {
			if (!(*it).value.empty()) {
				query << " set `" << (*it).field << "` = ?";
			}
		}

		query << " WHERE " << this->primary << " = ?";
		stat = db.session() << query.str();

		/* Now add the values .. */
		for(std::vector<update_obj>::iterator it = update_list.begin(); it != update_list.end(); ++it) {
			if (!(*it).value.empty()) {
				this->add_to_statement(stat, (*it).value);
			}
		}

		std::cout << query.str() << std::endl;

		this->add_to_statement(stat, this->primary_value);

		stat.exec();

		std::cout << "Affected "<< stat.affected() << std::endl;

		if ( stat.affected() == 1 ) {
			stat.reset();
			return true;
		} else {
			stat.reset();
			return false;
		}
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
		return false;
	}
	return false;
}

bool model::compare_field(std::string field)
{
	std::cout << "Size " << this->field_list.size() << std::endl;
	for(std::vector<std::string>::iterator it = this->field_list.begin(); it != this->field_list.end(); ++it) {
    	if((*it).compare(field) == 0)
    	{
    		return true;
    	}
	}
	return false;
}

bool model::is_empty(std::string var)
{
	if ( !var.empty() ) {
		return false;
	} else {
		return true;
	}
}

