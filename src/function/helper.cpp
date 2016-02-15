#include "helper.h"

bool helper::convert(std::unique_ptr<model> tmp, cppcms::string_key first, cppcms::json::value second, std::map<std::string,any> &update_list)
{
	if ( tmp->model::compare_field(first.str()) ) {
		switch(second.type()) {
			case cppcms::json::json_type::is_number: 
			{
				update_list[first.str()] = any((int)second.number());
				break;
			}
			case cppcms::json::json_type::is_string: 
			{
				std::string val = (std::string)second.str();
				update_list[first.str()] = any(val);
				break;
			}
			case cppcms::json::json_type::is_boolean:
			{
				update_list[first.str()] = any((bool)second.boolean());
				break;
			}
			default:
				break;
		}
		// dump_map(update_list);
		return true;
	}
	std::cout << "field " << first.str() << std::endl;
	throw unrecognized_field_ex();
}

