#include "model.h"

void model::add_to_statement(cppdb::statement& stat, boost::any value)
{
	std::string string = "PKc"; /* occurs when directly adding string to boost::any e.g = "example" */
	std::string string2 = "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE";
	std::string boolean = "b";
	std::string integer = "i";

	std::cout << "Called add to statement" << std::endl;

	const std::type_info &ti = value.type();
	if (string.compare(ti.name()) == 0 || string2.compare(ti.name()) == 0 ) {
		std::string s = boost::any_cast<std::string>(value);
		std::cout << "string " << s << std::endl;
		stat << s;
	} else if (boolean.compare(ti.name()) == 0 ) {
		bool b = boost::any_cast<bool>(value);
		std::cout << "boolean " << b << std::endl;
		stat << b;
	} else if (integer.compare(ti.name()) == 0 ) {
		int i = boost::any_cast<int>(value);
		std::cout << "Integer " << i << std::endl;
		stat << i;
	}
	else {
		std::cout << "Failed to identify type.." << std::endl;
		std::cout << "Type was " << ti.name() << std::endl;
	}
}

// TODO SANITIZE VALUE
bool model::update(std::unique_ptr<update_interface> update)
{
	try{
		cppdb::statement stat;

		std::ostringstream query;
		query << "UPDATE "<< this->table_name << " set `" << update->get_field() << "` = ? WHERE "<< this->primary << " = ?";

		std::cout << query.str() << std::endl;

		stat = db.session() << query.str();
		
		this->add_to_statement(stat, update->get_value());

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
		std::cout << "Exception occured in update " << e.what() << std::endl;
		return false;
	}
	return false;
}

// TODO SANITIZE VALUE
bool model::update(std::vector<std::unique_ptr<update_interface>> update_list)
{
	try{
		cppdb::statement stat;

		std::ostringstream query;
		query << "UPDATE "<< this->table_name;

		std::cout << "Table name " << this->table_name << std::endl;

		/* First generate the entire query .. */
		int count = 0;
		for(std::vector<std::unique_ptr<update_interface>>::iterator it = update_list.begin(); it != update_list.end(); ++it) {
			if ( count == 0) {
				query << " set `" << (*it)->get_field() << "` = ?";
			} else {
				query << ", `" << (*it)->get_field() << "` = ?";
			}
			count++;
		}

		query << " WHERE " << this->primary << " = ?";
		stat = db.session() << query.str();

		/* Now add the values .. */
		for(std::vector<std::unique_ptr<update_interface>>::iterator it = update_list.begin(); it != update_list.end(); ++it) {
			this->add_to_statement(stat, (*it)->get_value());
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
		std::cout << "Exception occured in update (vector) " << e.what() << std::endl;
		return false;
	}
	return false;
}

bool model::compare_field(std::string field)
{
	std::cout << "Size " << this->field_list.size() << std::endl;
	if ( this->field_list.size() > 1 ) {
		for(std::vector<std::string>::iterator it = this->field_list.begin(); it != this->field_list.end(); ++it) {
	    	if((*it).compare(field) == 0)
	    	{
	    		return true;
	    	}
		}
		return false;
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

