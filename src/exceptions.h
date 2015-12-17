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

class unrecognized_field_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Unrecognized db field";
  }
};

#endif /* EXCEPTIONS_H */

