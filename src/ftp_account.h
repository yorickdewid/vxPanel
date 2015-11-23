#ifndef FTP_ACCOUNT_H
#define FTP_ACCOUNT_H
#include "domain.h"

class ftp_account : public model {

public:
	ftp_account(backend& db, std::string username) :
		model(db),
		username(username)
	{};
	
	void save();
	void load();

	void set_password(std::string address);
	void set_permissions(std::string _permissions);
	void set_domain(std::shared_ptr<domain> domain);

	std::string get_username();
	std::string get_password();
	std::string get_permissions();
	std::string get_created();
	domain get_domain();

private:
	std::string username;
	std::string _password;
	std::string _permissions; /* e.g WO, RO */
	std::string _created;
	std::shared_ptr<domain> _domain; /* auto_ptr deprecated */

};

#endif /* FTP_ACCOUNT_H */

