#ifndef MODEL_H
#define MODEL_H

#include "exceptions.h"
#include "backend.h"
#include <vector>

class model {

public:
	model(backend& db) :
		db(db),
		saved(false)
	{};
	virtual void save() = 0;
	virtual void load() = 0;
	virtual bool update(std::string field) = 0;
	// virtual bool update(std::vector<std::string,)
	virtual bool m_delete() = 0;

	bool is_empty(std::string var){
		if ( !var.empty() ) {
			return false;
		} else {
			return true;
		}
	}

	bool get_saved(){ return this->saved; };

protected:
	backend& db;
	bool saved;
	std::vector<std::string> field_list;

};

#endif /* MODEL_H */

