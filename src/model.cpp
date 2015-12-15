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

		query << " WHERE ";
		for ( auto it =this->primary_info.begin(); it != this->primary_info.end(); ++it ) {
			query << (*it).first << " = ? ";
		}

		stat = db.session() << query.str();

		/* Now add the values .. */
		for ( auto it = update_list.begin(); it != update_list.end(); ++it ) {
			this->add_to_statement(stat, (*it).second);
		}

		std::cout << query.str() << std::endl;

		/* Now add the values .. */
		for ( auto it = this->primary_info.begin(); it != this->primary_info.end(); ++it ) {
			this->add_to_statement(stat, (*it).second);
		}

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
		for(auto it = this->field_list.begin(); it != this->field_list.end(); ++it) {
	    	if((*it).compare(field) == 0)
	    	{
	    		return true;
	    	}
		}
		return false;
	}
	return false;
}

bool model::compare_primary_field(std::string field)
{
	std::cout << " Primary Size " << this->primary_info.size() << std::endl;
	if ( this->primary_info.size() > 1 ) {
		for(auto it = this->primary_info.begin(); it != this->primary_info.end(); ++it) {
	    	if(it->first.compare(field) == 0)
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

