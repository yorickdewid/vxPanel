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

bool model::update(update_obj update)
{
	try{
		cppdb::statement stat;

		std::ostringstream query;
		query << "UPDATE "<< this->table_name << " set `" << update.field << "` = ? WHERE "<< update.primary << " = ?";

		std::cout << query.str() << std::endl;

		stat = db.session() << query.str();
		if (!update.value.empty())
		{
			this->add_to_statement(stat, update.value);
		}

		this->add_to_statement(stat, update.primary_value);

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

bool model::is_empty(std::string var){
	if ( !var.empty() ) {
		return false;
	} else {
		return true;
	}
}

