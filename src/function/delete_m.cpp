#include "delete_m.h"
#include "../model/models.h"
#include "../validation/domain_validator.h"

/* delete */

void delete_m::delete_user(std::string username)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			user user(get_database(), get_main()->get_uid_from_token());

			user.load();

			if ( user.m_delete() ) {
				get_main()->return_result("OK");
			} else {
				get_main()->return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void delete_m::delete_domain(std::string domain_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			domain domain(get_database(),domain_name);

			domain.load();

			if ( domain.get_user().get_uid() != get_main()->get_uid_from_token() ){
				throw auth_ex();
			}

			if ( domain.m_delete() ) {
				get_main()->return_result("OK");
			} else {
				get_main()->return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void delete_m::delete_dns(int dns_id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			dns dns(get_database(),dns_id);

			dns.load();

			if ( dns.get_domain().get_user().get_uid() != get_main()->get_uid_from_token() ){
				throw auth_ex();
			}

			if ( dns.m_delete() ) {
				get_main()->return_result("OK");
			} else {
				get_main()->return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void delete_m::delete_ftp_account(std::string ftp_username)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			ftp_account ftp_account(get_database(),ftp_username);

			ftp_account.load();

			if ( ftp_account.get_user().get_uid() != get_main()->get_uid_from_token() ){
				throw auth_ex();
			}

			if ( ftp_account.m_delete() ) {
				get_main()->return_result("OK");
			} else {
				get_main()->return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* possible problem with authorization */
void delete_m::delete_vhost(int vhost_id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			vhost vhost(get_database(),vhost_id);

			vhost.load();

			if ( vhost.m_delete() ) {
				get_main()->return_result("OK");
			} else {
				get_main()->return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void delete_m::delete_mailbox(int mailbox_id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			mailbox mailbox(get_database(),mailbox_id);

			mailbox.load();

			if ( mailbox.get_domain().get_user().get_uid() != get_main()->get_uid_from_token() ){
				throw auth_ex();
			}

			if ( mailbox.m_delete() ) {
				get_main()->return_result("OK");
			} else {
				get_main()->return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void delete_m::delete_shell(int id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			shell shell(get_database(),id);

			shell.load();

			if ( shell.get_user().get_uid() != get_main()->get_uid_from_token() ){
				throw auth_ex();
			}

			if ( shell.m_delete() ) {
				get_main()->return_result("OK");
			} else {
				get_main()->return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void delete_m::delete_subdomain(std::string subdomain_name, std::string domain_name)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			subdomain subdomain(get_database(),subdomain_name,domain_name);

			subdomain.load();

			if ( subdomain.get_domain().get_user().get_uid() != get_main()->get_uid_from_token() ){
				throw auth_ex();
			}

			if ( subdomain.m_delete() ) {
				get_main()->return_result("OK");
			} else {
				get_main()->return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void delete_m::delete_setting(std::string key)
{
	app_settings app_settings(get_database(),key);

	app_settings.load();
	if ( app_settings.m_delete() ) {
		get_main()->return_result("OK");
	} else {
		get_main()->return_error("Delete failed");
	}
}

void delete_m::delete_database_type(std::string name)
{
	database_type database_type(get_database(),name);

	database_type.load();

	if ( database_type.m_delete() ) {
		get_main()->return_result("OK");
	} else {
		get_main()->return_error("Delete failed");
	}
}

void delete_m::delete_database_user(std::string username)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			database_user database_user(get_database(),username);

			database_user.load();
			if ( database_user.get_user().get_uid() != get_main()->get_uid_from_token() ){
				throw auth_ex();
			}

			if ( database_user.m_delete() ) {
				get_main()->return_result("OK");
			} else {
				get_main()->return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void delete_m::delete_database(std::string db_name, std::string db_username)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			database database(get_database(),db_name);

			database.load();
			user_dbuser_db connect(get_database(),db_username,db_name);

			if ( database.get_user().get_uid() != get_main()->get_uid_from_token() ){
				throw auth_ex();
			}

			if ( connect.m_delete() ) {
				if ( database.m_delete() ) {
					get_main()->return_result("OK");
				} else {
					get_main()->return_error("Failed to delete database, and remove connection with username");
				}
			} else {
				get_main()->return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void delete_m::delete_domain_alias(int id)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			domain_alias domain_alias(get_database(), id);

			domain_alias.load();
			if ( domain_alias.get_domain().get_user().get_uid() != get_main()->get_uid_from_token() ){
				throw auth_ex();
			}
			if ( domain_alias.m_delete() ) {
				get_main()->return_result("OK");
			} else {
				get_main()->return_error("Delete failed");
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

