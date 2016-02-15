#include "get_multiple.h"
#include "../model/models.h"
#include "../validation/domain_validator.h"

void get_multiple::get_users(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value json;
			std::ostringstream query;
			int count = 0;

			query << "SELECT * FROM user LIMIT ";

			this->create_get_all_query(object,query);

			cppdb::result r = this->get_result(query);

			while ( r.next() ) {
				int uid;
				r >> uid;
	  			std::map<std::string,any> primary_list;
				primary_list["uid"] = uid;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::User, get_database(), primary_list);		
	  			user* tmp = dynamic_cast<user*>(model_obj.get());
				std::unique_ptr<user> user_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    user_obj.reset(tmp);
				}

				json["users"][count]["uid"] = user_obj->get_uid();
				json["users"][count]["username"] = user_obj->get_username();
				json["users"][count]["email"] = user_obj->get_email();
				json["users"][count]["firstname"] = user_obj->_firstname;
				json["users"][count]["lastname"] = user_obj->_lastname;
				json["users"][count]["country"] = user_obj->_country;
				json["users"][count]["city"] = user_obj->_city;
				json["users"][count]["address"] = user_obj->_address;
				json["users"][count]["address_number"] = user_obj->_address_number;
				json["users"][count]["postal"] = user_obj->_postal;
				json["users"][count]["note"] = user_obj->_note;
				json["users"][count]["remote"] = user_obj->_remote;
				json["users"][count]["user_type"] = user_obj->_user_type;
				json["users"][count]["active"] = user_obj->_active;
				json["users"][count]["created"] = user_obj->get_created();
				json["users"][count]["last_login"] = user_obj->get_lastlogin();

				count++;
			}
			if(!json.is_undefined())
			{
				get_main()->return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get_multiple::get_domains(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppdb::statement stat;
			cppcms::json::value json;
			std::ostringstream query;
			int count = 0;

			query << "SELECT name FROM domain WHERE uid = ? LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();
			stat << get_main()->get_uid_from_token();

			std::cout << query.str() << std::endl;

			cppdb::result r = stat.query();

			while ( r.next() ) {
				std::string domain_name;
				r >> domain_name;
	  			std::map<std::string,any> primary_list;
				primary_list["name"] = domain_name;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Domain, get_database(), primary_list);		
	  			domain* tmp = dynamic_cast<domain*>(model_obj.get());
				std::unique_ptr<domain> domain_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    domain_obj.reset(tmp);
				}

				json["domains"][count]["domain_name"] = domain_obj->name;
				json["domains"][count]["status"] = domain_obj->_status;
				json["domains"][count]["registrar"] = domain_obj->_registrar;
				json["domains"][count]["created"] = domain_obj->get_created();
				json["domains"][count]["uid"] = domain_obj->get_user().get_uid();
				if( domain_obj->get_vhost_ptr() )
				{
					json["domains"][count]["vhost_id"] = domain_obj->get_vhost().get_id();
				}
				json["domains"][count]["active"] = domain_obj->_active;

				count++;
			}
			if(!json.is_undefined())
			{
				get_main()->return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get_multiple::get_dns_records(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppdb::statement stat;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			int count = 0;

			query << "SELECT id FROM dns WHERE domain_name = ? LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();

			cppcms::json::value options;
			try {
				options = object["options"];
				domain_name = options.get<std::string>("domain_name");
			}	catch(std::exception &e) {
				throw missing_params_ex();
			}

			stat << domain_name;
			std::cout << query.str() << std::endl;
			cppdb::result r = stat.query();

			while ( r.next() ) {
				int dns_id;
				r >> dns_id;
	  			std::map<std::string,any> primary_list;
				primary_list["id"] = dns_id;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Dns, get_database(), primary_list);		
	  			dns* tmp = dynamic_cast<dns*>(model_obj.get());
				std::unique_ptr<dns> dns_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    dns_obj.reset(tmp);
				}

				dns_obj->load(); //sigsev

				json["dns_records"][count]["id"] = dns_obj->get_id();
				json["dns_records"][count]["name"] = dns_obj->_name;
				json["dns_records"][count]["created"] = dns_obj->get_created();
				json["dns_records"][count]["domain_name"] = dns_obj->get_domain().name;
				json["dns_records"][count]["active"] = dns_obj->_active;

				count++;
			}
			if(!json.is_undefined())
			{
				get_main()->return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get_multiple::get_ftp_accounts(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppdb::statement stat;
			cppcms::json::value json;
			std::ostringstream query;
			int count = 0;

			query << "SELECT id FROM ftpuser WHERE userid = ? LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();

			stat << get_main()->get_uid_from_token();
			std::cout << query.str() << std::endl;
			cppdb::result r = stat.query();

			while ( r.next() ) {
				int id;
				r >> id;
	  			std::map<std::string,any> primary_list;
				primary_list["id"] = id;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::FtpAccount, get_database(), primary_list);
	  			ftp_account* tmp = dynamic_cast<ftp_account*>(model_obj.get());
				std::unique_ptr<ftp_account> ftp_account_obj;


				if(tmp != nullptr)
				{
					model_obj.release();
				    ftp_account_obj.reset(tmp);
				}

				ftp_account_obj->load_id(); //sigsev


				json["ftp_accounts"][count]["id"] = ftp_account_obj->get_id();
				json["ftp_accounts"][count]["name"] = ftp_account_obj->_name;
				json["ftp_accounts"][count]["uid"] = ftp_account_obj->_uid;
				json["ftp_accounts"][count]["gid"] = ftp_account_obj->_gid;
				json["ftp_accounts"][count]["homedir"] = ftp_account_obj->_homedir;
				json["ftp_accounts"][count]["shell"] = ftp_account_obj->_shell;
				json["ftp_accounts"][count]["count"] = ftp_account_obj->get_count();
				json["ftp_accounts"][count]["userid"] = ftp_account_obj->get_user().get_uid();
				json["ftp_accounts"][count]["created"] = ftp_account_obj->get_created();
				json["ftp_accounts"][count]["accessed"] = ftp_account_obj->get_accessed();
				json["ftp_accounts"][count]["modified"] = ftp_account_obj->get_modified();

				count++;
			}
			if(!json.is_undefined())
			{
				get_main()->return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get_multiple::get_vhosts(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT id FROM vhost WHERE name = ? LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();

			try {
				options = object["options"];
				domain_name = options.get<std::string>("domain_name");
			}	catch(std::exception &e) {
				throw missing_params_ex();
			}

			stat << domain_name;
			cppdb::result r = stat.query();

			while ( r.next() ) {
				int id;
				r >> id;
	  			std::map<std::string,any> primary_list;
				primary_list["id"] = id;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Vhost, get_database(), primary_list);
	  			vhost* tmp = dynamic_cast<vhost*>(model_obj.get());
				std::unique_ptr<vhost> vhost_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    vhost_obj.reset(tmp);
				}

				vhost_obj->load(); //sigsev

				json["vhosts"][count]["id"] = vhost_obj->get_id();
				json["vhosts"][count]["name"] = vhost_obj->_name;
				json["vhosts"][count]["custom_config"] = vhost_obj->_custom_config;
				json["vhosts"][count]["created"] = vhost_obj->get_created();
				json["vhosts"][count]["active"] = vhost_obj->get_active();

				count++;
			}
			if(!json.is_undefined())
			{
				get_main()->return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* NOTE this method could be more efficient:
	If the mailbox table includes an uid.
*/
void get_multiple::get_mailboxes(cppcms::json::value object) 
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;

			query << "SELECT name FROM domain WHERE uid = ?"; /* first get the domains from the logged in user */

			stat = get_database().session() << query.str();
			stat << get_main()->get_uid_from_token();

			cppdb::result result_domain = stat.query(); /* its a reference to stat->result so if stat.reset() is called result points to empty memory */

			while ( result_domain.next() ) {
				std::string domain_name;
				int count_mailboxes = 0;
				result_domain >> domain_name;

				query.str("");
				query << "SELECT id FROM mailbox WHERE domain_name = ? LIMIT "; /* now get the mailboxes from the domains */
				this->create_get_all_query(object,query);
				stat = get_database().session() << query.str();
				stat << domain_name;

				cppdb::result result_mailbox = stat.query();
				
				while ( result_mailbox.next() ) {
					int id;
					result_mailbox >> id;
		  			std::map<std::string,any> primary_list;
					primary_list["id"] = id;

		  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Mailbox, get_database(), primary_list);
		  			mailbox* tmp = dynamic_cast<mailbox*>(model_obj.get());
					std::unique_ptr<mailbox> mailbox_obj;

					if(tmp != nullptr)
					{
						model_obj.release();
					    mailbox_obj.reset(tmp);
					}

					mailbox_obj->load(); //sigsev

					json["mailboxes"][count_mailboxes]["id"] = mailbox_obj->get_id();
					json["mailboxes"][count_mailboxes]["email"] = mailbox_obj->_email;
					json["mailboxes"][count_mailboxes]["maildir"] = mailbox_obj->_maildir;
					json["mailboxes"][count_mailboxes]["quota"] = mailbox_obj->_quota;
					json["mailboxes"][count_mailboxes]["created"] = mailbox_obj->get_created();
					json["mailboxes"][count_mailboxes]["domain_name"] = mailbox_obj->get_domain().name;
					json["mailboxes"][count_mailboxes]["bytes"] = mailbox_obj->_bytes;
					json["mailboxes"][count_mailboxes]["messages"] = mailbox_obj->_messages;
					json["mailboxes"][count_mailboxes]["active"] = mailbox_obj->_active;

					count_mailboxes++;
				}
			}
			if(!json.is_undefined())
			{
				get_main()->return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get_multiple::get_shells(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT id FROM shell WHERE uid = ? LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();

			stat << get_main()->get_uid_from_token();
			cppdb::result r = stat.query();

			while ( r.next() ) {
				int id;
				r >> id;
	  			std::map<std::string,any> primary_list;
				primary_list["id"] = id;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Shell, get_database(), primary_list);
	  			shell* tmp = dynamic_cast<shell*>(model_obj.get());
				std::unique_ptr<shell> shell_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    shell_obj.reset(tmp);
				}

				shell_obj->load(); //sigsev

				json["shells"][count]["id"] = shell_obj->get_id();
				json["shells"][count]["uid"] = shell_obj->get_user().get_uid();
				json["shells"][count]["created"] = shell_obj->get_created();
				json["shells"][count]["active"] = shell_obj->get_active();

				count++;
			}
			if(!json.is_undefined())
			{
				get_main()->return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get_multiple::get_subdomains(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT name FROM subdomain WHERE domain_name = ? LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();

			try {
				options = object["options"];
				domain_name = options.get<std::string>("domain_name");
			}	catch(std::exception &e) {
				throw missing_params_ex();
			}

			stat << domain_name;
			cppdb::result r = stat.query();

			while ( r.next() ) {
				std::string name;
				r >> name;
	  			std::map<std::string,any> primary_list;
				primary_list["name"] = name;
				primary_list["domain_name"] = domain_name;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Subdomain, get_database(), primary_list);
	  			subdomain* tmp = dynamic_cast<subdomain*>(model_obj.get());
				std::unique_ptr<subdomain> subdomain_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    subdomain_obj.reset(tmp);
				}

				subdomain_obj->load(); //sigsev

				json["subdomains"][count]["name"] = subdomain_obj->get_name();
				json["subdomains"][count]["domain_name"] = subdomain_obj->get_domain().name;
				if( subdomain_obj->get_vhost_ptr() )
				{
					json["subdomains"][count]["vhost_id"] = subdomain_obj->get_vhost().get_id();
				}
				json["subdomains"][count]["created"] = subdomain_obj->get_created();
				json["subdomains"][count]["active"] = subdomain_obj->_active;

				count++;
			}
			if(!json.is_undefined())
			{
				get_main()->return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get_multiple::get_settings(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT `key` FROM settings LIMIT ";

			this->create_get_all_query(object,query);

			stat = get_database().session() << query.str();

			cppdb::result r = stat.query();

			while ( r.next() ) {
				std::string key;
				r >> key;
	  			std::map<std::string,any> primary_list;
				primary_list["key"] = key;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::AppSettings, get_database(), primary_list);
	  			app_settings* tmp = dynamic_cast<app_settings*>(model_obj.get());
				std::unique_ptr<app_settings> app_settings_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    app_settings_obj.reset(tmp);
				}

				app_settings_obj->load(); //sigsev

				json["app_settings"][count]["key"] = app_settings_obj->get_key();
				json["app_settings"][count]["value"] = app_settings_obj->get_value();
				json["app_settings"][count]["description"] = app_settings_obj->get_description();
				json["app_settings"][count]["updated"] = app_settings_obj->get_updated();
				json["app_settings"][count]["created"] = app_settings_obj->get_created();

				count++;
			}
			if(!json.is_undefined())
			{
				get_main()->return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* TODO Inspect for memory leakage */
void get_multiple::get_database_types()
{
	cppcms::json::value json;

	database_type tmp_object(get_database(),"");

	std::vector<database_type> v = tmp_object.load_all();

	int count = 0;
	for(std::vector<database_type>::iterator it = v.begin(); it != v.end(); ++it) {
    	json["database_types"][count] = it->get_name();
    	count++;
	}
	v.clear();
	get_main()->return_result(json);
}

void get_multiple::get_database_users(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT name FROM user_db_user WHERE uid = ? LIMIT ";

			this->create_get_all_query(object,query);
			stat = get_database().session() << query.str();
			stat << get_main()->get_uid_from_token();

			cppdb::result r = stat.query();

			while ( r.next() ) {
				std::string name;
				r >> name;
	  			std::map<std::string,any> primary_list;
				primary_list["name"] = name;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::DatabaseUser, get_database(), primary_list);
	  			database_user* tmp = dynamic_cast<database_user*>(model_obj.get());
				std::unique_ptr<database_user> database_user_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    database_user_obj.reset(tmp);
				}

				database_user_obj->load(); //sigsev

				json["database_users"][count]["name"] = database_user_obj->get_name();
				json["database_users"][count]["permissions"] = database_user_obj->get_permissions();
				json["database_users"][count]["created"] = database_user_obj->get_created();
				json["database_users"][count]["uid"] = database_user_obj->get_user().get_uid();

				count++;
			}
			if(!json.is_undefined())
			{
				get_main()->return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get_multiple::get_databases(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT name FROM user_db WHERE uid = ? LIMIT ";

			this->create_get_all_query(object,query);
			stat = get_database().session() << query.str();
			stat << get_main()->get_uid_from_token();

			cppdb::result r = stat.query();

			while ( r.next() ) {
				std::string name;
				r >> name;
	  			std::map<std::string,any> primary_list;
				primary_list["name"] = name;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Database, get_database(), primary_list);
	  			database* tmp = dynamic_cast<database*>(model_obj.get());
				std::unique_ptr<database> database_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    database_obj.reset(tmp);
				}

				database_obj->load(); //sigsev

				json["databases"][count]["name"] = database_obj->get_name();
				json["databases"][count]["created"] = database_obj->get_created();
				json["databases"][count]["type"] = database_obj->get_database_type().get_name();
				json["databases"][count]["uid"] = database_obj->get_user().get_uid();

				count++;
			}
			if(!json.is_undefined())
			{
				get_main()->return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/*
 base on uid?
 */
void get_multiple::get_queues(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			cppcms::json::value options;
			cppcms::json::value json;
			std::ostringstream query;
			std::string domain_name;
			cppdb::statement stat;
			
			int count = 0;

			query << "SELECT qid FROM queue WHERE uid = ? LIMIT ";

			this->create_get_all_query(object,query);
			stat = get_database().session() << query.str();
			stat << get_main()->get_uid_from_token();

			cppdb::result r = stat.query();

			while ( r.next() ) {
				int qid;
				r >> qid;
	  			std::map<std::string,any> primary_list;
				primary_list["qid"] = qid;

	  			std::unique_ptr<model> model_obj = ModelFactory::createModel(ModelFactory::ModelType::Queue, get_database(), primary_list);
	  			queue* tmp = dynamic_cast<queue*>(model_obj.get());
				std::unique_ptr<queue> queue_obj;

				if(tmp != nullptr)
				{
					model_obj.release();
				    queue_obj.reset(tmp);
				}

				queue_obj->load(); //sigsev

				json["queues"][count]["qid"] = queue_obj->qid;
				json["queues"][count]["action"] = queue_obj->_action;
				json["queues"][count]["params"] = queue_obj->_params;
				json["queues"][count]["created"] = queue_obj->get_created();
				json["queues"][count]["started"] = queue_obj->_started;
				json["queues"][count]["finished"] = queue_obj->_finished;
				json["queues"][count]["uid"] = queue_obj->get_user().get_uid();
				json["queues"][count]["status"] = queue_obj->_status;
				json["queues"][count]["result"] = queue_obj->get_result();

				count++;
			}
			if(!json.is_undefined())
			{
				get_main()->return_result(json);
			} else {
				throw empty_result_ex();
			}
		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void get_multiple::create_get_all_query(cppcms::json::value object, std::ostringstream& query)
{
	cppcms::json::value options;

	try {
		options = object["options"];
	}	catch(std::exception &e) {
		throw missing_params_ex();
	}

	cppcms::json::value start_point = options.find("start_point");
	if( !start_point.is_undefined() ) {
		query << start_point.number();
	} else {
		query << DEFAULT_START_POINT;
	}

	query << ",";

	cppcms::json::value size = options.find("size");
	if( !size.is_undefined() ) {
		query << size.number();
	} else {
		query << DEFAULT_LIMIT;
	}
}


cppdb::result get_multiple::get_result(std::ostringstream& query)
{
	cppdb::statement stat;

	stat = get_database().session() << query.str();
	std::cout << query.str() << std::endl;

	// dont reset the statement here clears the result..
	return stat.query();
}

