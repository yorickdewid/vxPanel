#include <cppcms/application.h>
#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <string>

#include "config.h"
#include "master.h"

bool check_secret(cppcms::service &srv )
{
	std::string secret = srv.settings().get<std::string>("secret");
	if ( secret.length() != 40) {
		return false;
	} else {
		return true;
	}
}

/*
 * Initialize the application pool and pass control to master
 */
int main(int argc, char *argv[])
{
	try {
		std::cout << "Starting vxPanel " << VERSION << std::endl;
		cppcms::service srv(argc,argv);

		srv.applications_pool().mount(cppcms::applications_factory<master>());
		if( !check_secret(srv) ) {
			std::cout << "Secret key badly formed, exiting..." << std::endl;
			exit (EXIT_FAILURE);
		}
		srv.run();
		std::cout << "Stopping vxPanel " << std::endl;
	}
	catch(std::exception const &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}


