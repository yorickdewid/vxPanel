#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class backend_ex: public std::exception
{
	virtual const char *what() const throw()
	{
		return "Cannot connect to database";
	}
};

#endif /* EXCEPTIONS_H */

