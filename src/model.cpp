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
		case any::LONG_INT:
			stat << value.long_integer;
			break;
		case any::BOOL:
			stat << value.boolean;
			break;
	}
}

// TODO SANITIZE VALUE
bool model::update(std::map<std::string, any> update_list)
{
	try{
		cppdb::statement stat;

		std::ostringstream query;
		query << "UPDATE "<< this->table_name;

		std::cout << "Table name " << this->table_name << std::endl;

		std::cout << "update_list.size() is " << update_list.size() << '\n';

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
		count = 0;
		for ( auto it =this->primary_info.begin(); it != this->primary_info.end(); ++it,count++) {
			if(count > 0) {
				query << "AND `" <<  (*it).first << "` = ? ";
			} else {
				query << "`" << (*it).first << "` = ? ";
			}
		}
		std::cout << query.str() << std::endl;

		stat = db.session() << query.str();

		/* Now add the values .. */
		for ( auto it = update_list.begin(); it != update_list.end(); ++it ) {
			this->add_to_statement(stat, (*it).second);
		}

		/* Now add the primary values .. */
		for ( auto it = this->primary_info.begin(); it != this->primary_info.end(); ++it ) {
			this->add_to_statement(stat, (*it).second);
		}

		stat.exec();

		std::cout << "Affected "<< stat.affected() << std::endl;

		return true;
	} catch (std::exception &e) {
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
	    	if( it->first.compare(field) == 0)
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
	if ( this->primary_info.size() > 0 ) {
		for(auto it = this->primary_info.begin(); it != this->primary_info.end(); ++it) {
	    	if(it->first.compare(field) == 0)
	    	{
	    		std::cout << "Primary field matches" << std::endl;
	    		return true;
	    	}
		}
		std::cout << "Primary field matches" << std::endl;
		return false;
	}
	std::cout << "Primary fields == 0" << std::endl;
	return false;
}

bool model::check_required_fields(std::map<std::string,any> list)
{
	int countRequired = 0;
	int countValuesOfRequired = 0;
	if ( this->field_list.size() > 1 ) {
		for(auto fields = this->field_list.begin(); fields != this->field_list.end(); ++fields) {
	    	for(auto values = list.begin(); values != list.end(); ++values) {
	    		if(fields->second) 
	    		{
 		    		countRequired++;
	    		}
		    	if( fields->first.compare(values->first) == 0)
		    	{
		    		countValuesOfRequired++;
		    	}
			}
		}
	}
	if(countValuesOfRequired == countRequired)
	{
		return true;
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

