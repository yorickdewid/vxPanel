#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <string>

#include "master.h"

/*
 * Initialize the application pool and pass control to master
 */
int main(int argc, char *argv[])
{
    try {
        std::cout << "Starting vxPanel" << std::endl;
    	cppcms::service srv(argc,argv);
    	srv.applications_pool().mount(cppcms::applications_factory<master>());
    	srv.run();
    }
    catch(std::exception const &e) {
    	std::cerr << e.what() << std::endl;
    	return 1;
    }
    return 0;
}
