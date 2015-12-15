#include "model.h"

void model::add_to_statement(cppdb::statement& stat, any value)
{
	switch (value.tag) {
		case any::CHAR:
			stat << value.string;
			break;
		case any::INT:
			stat << value.integer;
			break;
		case any::BOOL:
			stat << value.boolean;
			break;
	}
}

// TODO SANITIZE VALUE
bool model::update(std::string field, any value)
{
	try{
		cppdb::statement stat;

		std::ostringstream query;
		query << "UPDATE "<< this->table_name << " set `" << field << "` = ? WHERE "<< this->primary << " = ?";

		std::cout << query.str() << std::endl;

		stat = db.session() << query.str();
		
		this->add_to_statement(stat, value);

		this->add_to_statement(stat, this->primary_value);

		stat.exec();

		return true;
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured in update " << e.what() << std::endl;
		return false;
	}
	return false;
}

// TODO SANITIZE VALUE
bool model::update(std::map<std::string,any> update_list)
{
	try{
		cppdb::statement stat;

		std::ostringstream query;
		query << "UPDATE "<< this->table_name;

		std::cout << "Table name " << this->table_name << std::endl;

		/* First generate the entire query .. */
		int count = 0;
		for ( auto it = update_list.begin(); it != update_list.end(); ++it ) {
			if ( count == 0) {
				query << " set `" << (*it).first << "` = ?";
			} else {
				query << ", `" << (*it).first << "` = ?";
			}
			count++;
		}

		query << " WHERE " << this->primary << " = ?";
		stat = db.session() << query.str();

		/* Now add the values .. */
		for ( auto it = update_list.begin(); it != update_list.end(); ++it ) {
			this->add_to_statement(stat, (*it).second);
		}

		std::cout << query.str() << std::endl;

		this->add_to_statement(stat, this->primary_value);

		stat.exec();

		std::cout << "Affected "<< stat.affected() << std::endl;

		return true;
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

