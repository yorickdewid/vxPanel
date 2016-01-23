#ifndef DOMAIN_VALIDATOR_H
#define DOMAIN_VALIDATOR_H

#include <fstream>
#include <vector>

class domain_validator {

public:
	domain_validator();
	void static validate_domain(std::string domain_name);
	void static validate_subdomain();

private:

};


#endif /* DOMAIN_VALIDATOR_H */

