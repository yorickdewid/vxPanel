#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../exceptions.h"
#include "../backend.h"
#include "../master.h"

class functions {

public:
	functions(backend& db, master* main) : db(db), main(main){};

protected:
	backend& db;
	master* main = NULL;
	backend& get_database();
	master* get_main();

};

#endif /* FUNCTIONS_H */

