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

class missing_params_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Missing params";
  }
};

class entity_save_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Entity not saved";
  }
};

class primary_key_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Empty primary key";
  }
};

class missing_required_field_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Missing required fields";
  }
};

class invalid_value_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Received unexpected value";
  }
};

class auth_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Invalid authorization";
  }
};

#endif /* EXCEPTIONS_H */

