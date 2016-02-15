#ifndef HELPER_H
#define HELPER_H

#include <cppcms/json.h>
#include "../any.h"
#include "../model.h"

class helper {

public:
	bool static convert(std::unique_ptr<model> tmp, cppcms::string_key first, cppcms::json::value second, std::map<std::string,any> &update_list); // TODO MOVE TO OWN CLASS
};

#endif /* HELPER_H */

