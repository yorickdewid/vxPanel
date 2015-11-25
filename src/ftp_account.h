#ifndef FTP_ACCOUNT_H
#define FTP_ACCOUNT_H
#include "domain.h"
#include "user.h"

class ftp_account : public model {

public:
	ftp_account(backend& db, std::string username) :
		model(db),
		username(username),
		_user(NULL)
	{};
	
	void save();
	void load();

	void set_password(std::string address);
	void set_permissions(std::string _permissions);
	void set_domain(std::shared_ptr<domain> domain);
	void set_user(std::shared_ptr<user> user);

	std::string get_username();
	std::string get_password();
	std::string get_permissions();
	std::string get_created();
	domain get_domain();
	std::shared_ptr<domain> get_domain_ptr();
	user get_user();

private:
	std::string username;
	std::string _password;
	std::string _permissions; /* e.g WO, RO */
	std::string _created;
	std::shared_ptr<domain> _domain; /* auto_ptr deprecated */
	std::shared_ptr<user> _user;

};

#endif /* FTP_ACCOUNT_H */

