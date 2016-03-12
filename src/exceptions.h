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

class empty_result_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Result was empty";
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

class not_auth_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Not authenticated";
  }
};

class no_token_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "No token supplied";
  }
};

class token_not_valid_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Token not valid";
  }
};

/* Domain exceptions */

class invalid_domain_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Domain is invalid";
  }
};

class domain_length_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Domain length exceeds 253";
  }
};

class invalid_queue_action_ex: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Queue action invalid";
  }
};

#endif /* EXCEPTIONS_H */

