#include "get.h"
#include "../model/models.h"
#include "../validation/domain_validator.h"

/* get */

void get::get_user()
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;

			user user(this->functions::get_database(), get_main()->get_uid_from_token());

			user.load();

			json["user"]["uid"] = user.get_uid();
			json["user"]["username"] = user.get_username();
			json["user"]["email"] = user.get_email();
			json["user"]["firstname"] = user._firstname;
			json["user"]["lastname"] = user._lastname;
			json["user"]["country"] = user._country;
			json["user"]["city"] = user._city;
			json["user"]["address"] = user._address;
			json["user"]["address_number"] = user._address_number;
			json["user"]["postal"] = user._postal;
			json["user"]["note"] = user._note;
			json["user"]["remote"] = user._remote;
			json["user"]["user_type"] = user._user_type;
			json["user"]["active"] = user._active;
			json["user"]["created"] = user.get_created();
			json["user"]["last_login"] = user.get_lastlogin();

			get_main()->return_result(json);
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get::get_domain(std::string domain_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;

			domain domain(this->functions::get_database(), domain_name);

			domain.load();

			if (domain.get_user().get_uid() == get_main()->get_uid_from_token() ) {

				json["domain"]["domainname"] = domain.name;
				json["domain"]["status"] = domain._status;
				json["domain"]["registrar"] =  domain._registrar;

				get_main()->return_result(json);
			} else {
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}


void get::get_dns(std::string domain_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;

			dns dns(this->functions::get_database(), 0);
			dns.load(domain_name);

			if (dns.get_domain().get_user().get_uid() == get_main()->get_uid_from_token() ) {

				json["dns"]["address"] = dns.get_name();
				json["dns"]["created"] = dns.get_created();
				json["dns"]["domain_name"] = domain_name;

				get_main()->return_result(json);
			} else {
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

// TODO add missing fields
void get::get_ftp_account(std::string ftp_username)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;

			ftp_account ftp_account(this->functions::get_database(), ftp_username);
			ftp_account.load();

			if (ftp_account.get_user().get_uid() == get_main()->get_uid_from_token() ){

				json["ftp_account"]["username"] = ftp_account.get_username();
				json["ftp_account"]["password"] = ftp_account.get_password();
				json["ftp_account"]["created"] = ftp_account.get_created();

				get_main()->return_result(json);
			}
			else{
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get::get_vhost(std::string domain_name, int vhost_id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;

			vhost vhost(this->functions::get_database(),vhost_id);
			vhost.load(domain_name);

			json["vhost"]["id"] = vhost.get_id();
			json["vhost"]["name"] = vhost.get_name();
			json["vhost"]["custom_config"] = vhost.get_custom_config();
			json["vhost"]["created"] = vhost.get_created();
			json["vhost"]["active"] = vhost.get_active();

			get_main()->return_result(json);
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get::get_mailbox(std::string domain_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;

			mailbox mailbox(this->functions::get_database(),0);
			mailbox.load(domain_name);

			if ( mailbox.get_domain().name.compare(domain_name) == 0) {
				json["mailbox"]["id"] = mailbox.get_id();
				json["mailbox"]["email"] = mailbox.get_email();
				json["mailbox"]["password"] = mailbox.get_password();
				json["mailbox"]["maildir"] = mailbox.get_maildir();
				json["mailbox"]["quota"] = mailbox.get_quota();
				json["mailbox"]["created"] = mailbox.get_created();
				if ( !mailbox.get_domain().name.compare("") ) { /* good enough? */
					json["mailbox"]["domain"] = mailbox.get_domain().name;
				}

				get_main()->return_result(json);
			} else{
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get::get_shell(int id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;

			shell shell(this->functions::get_database(),id);
			shell.load();

			if ( shell.get_user().get_uid() == get_main()->get_uid_from_token() ) {
				json["shell"]["created"] = shell.get_created();

				get_main()->return_result(json);
			}
			else{
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* todo check if domain belongs to logged in user */
void get::get_subdomain(std::string subdomain_name, std::string domain_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;

			subdomain subdomain(this->functions::get_database(),subdomain_name, domain_name);
			subdomain.load();

			json["subdomain"]["name"] = subdomain.get_name();	
			json["subdomain"]["created"] = subdomain.get_created();
			if ( subdomain.get_domain_ptr() !=  NULL ) { /* good enough? */
				json["subdomain"]["domain"] = subdomain.get_domain().name;
			}

			get_main()->return_result(json);
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get::get_setting(std::string key)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;

			app_settings app_settings(this->functions::get_database(),key);
			app_settings.load();

			json["app_settings"]["key"] = app_settings.get_key();
			json["app_settings"]["value"] = app_settings.get_value();
			json["app_settings"]["default"] = app_settings.get_default();
			json["app_settings"]["description"] = app_settings.get_description();
			json["app_settings"]["updated"] = app_settings.get_updated();	
			json["app_settings"]["created"] = app_settings.get_created();

			get_main()->return_result(json);
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get::get_database_user(std::string username)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;

			database_user database_user(this->functions::get_database(),username);
			database_user.load();

			if ( database_user.get_user().get_uid() == get_main()->get_uid_from_token() ) {
				json["db_user"]["username"] = database_user.get_name();
				json["db_user"]["password"] = database_user.get_password();
				json["db_user"]["permissions"] = database_user.get_permissions();
				json["db_user"]["created"] = database_user.get_created();

				get_main()->return_result(json);
			}
			else {
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get::get_database(std::string db_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;

			database database(this->functions::get_database(),db_name);
			database.load();

			if ( database.get_user().get_uid() == get_main()->get_uid_from_token()) {
				json["db"]["name"] = database.get_name();
				json["db"]["created"] = database.get_created();
				json["db"]["db_type"] = database.get_database_type().get_name();

				get_main()->return_result(json);
			} else {
				throw auth_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get::get_queue(int qid)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;

			queue queue(this->functions::get_database(),qid);
			queue.load();

			json["queue"]["id"] = queue.qid; // TODO read only
			json["queue"]["action"] = queue._action;
			json["queue"]["params"] = queue._params;
			json["queue"]["created"] = queue.get_created();
			json["queue"]["started"] = queue._started;
			json["queue"]["finished"] = queue._finished;
			json["queue"]["uid"] = queue.get_user().get_uid();
			json["queue"]["status"] = queue._status;
			json["queue"]["result"] = queue.get_result();

			get_main()->return_result(json);
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get::get_domain_alias(int id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;

			domain_alias domain_alias(this->functions::get_database(),id);
			domain_alias.load();

			json["domain_alias"]["id"] = domain_alias.get_id();
			json["domain_alias"]["domain_name"] = domain_alias.get_domain().name;
			json["domain_alias"]["source"] = domain_alias._source;
			json["domain_alias"]["destination"] = domain_alias._destination;
			json["domain_alias"]["created"] = domain_alias.get_created();
			json["domain_alias"]["active"] = domain_alias._active;

			get_main()->return_result(json);
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

