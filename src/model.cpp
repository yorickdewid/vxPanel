#include "model.h"
#include <booster/log.h>

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
		case any::LL_INT:
			stat << value.ll_integer;
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

		BOOSTER_DEBUG("model") << "Table name " << this->table_name << std::endl;
    	BOOSTER_DEBUG("model") << "update_list.size() is " << update_list.size() << '\n';

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
		BOOSTER_DEBUG("model") << "Query is " << query.str() << std::endl;

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

		BOOSTER_DEBUG("model") << "Affected "<< stat.affected() << std::endl;

		return true;
	} catch (std::exception &e) {
		BOOSTER_DEBUG("model") << "Exception occured in update (vector) " << e.what() << std::endl;
		return false;
	}
	return false;
}


/* Debug for fields */
void dump_map(const std::map<std::string,bool>& map) {
	for (std::map<std::string, bool>::const_iterator it = map.begin(); it != map.end(); it++) {
		BOOSTER_DEBUG("model") << "Key: " << it->first << std::endl;
	}
}

bool model::compare_field(std::string field)
{
	// dump_map(this->field_list);
	BOOSTER_DEBUG("model") << "Size " << this->field_list.size() << std::endl;
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
	BOOSTER_DEBUG("model") << " Primary Size " << this->primary_info.size() << std::endl;
	if ( this->primary_info.size() > 0 ) {
		for(auto it = this->primary_info.begin(); it != this->primary_info.end(); ++it) {
	    	if(it->first.compare(field) == 0)
	    	{
	    		BOOSTER_DEBUG("model") << "Primary field matches" << std::endl;
	    		return true;
	    	}
		}
		return false;
	}
	BOOSTER_DEBUG("model") << "Primary fields == 0" << std::endl;
	return false;
}

bool model::check_required_fields(std::map<std::string,any> list)
{
	int countRequired = 0;
	int countValuesOfRequired = 0;
	if ( this->field_list.size() > 1 ) {
		for(auto fields = this->field_list.begin(); fields != this->field_list.end(); ++fields) {
			if(fields->second) 
	    	{
	    		BOOSTER_DEBUG("model") <<  "Found a required field" << std::endl;
 		    	countRequired++;
 		    	for(auto values = list.begin(); values != list.end(); ++values) {
			    	if( fields->first.compare(values->first) == 0)
			    	{
			    		BOOSTER_DEBUG("model") <<  "Matched required field" << std::endl;
			    		countValuesOfRequired++;
			    		break;
			    	}
				}
	    	}
		}
	}
	if(countValuesOfRequired == countRequired)
	{
		BOOSTER_DEBUG("model") << "all required fields are there" << std::endl;
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

