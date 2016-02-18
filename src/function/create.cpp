#include "create.h"
#include "../model/models.h"
#include "../validation/domain_validator.h"
#include "helper.h"

/*
	Create
*/

void create::create_user(cppcms::json::value object)
{
	std::map<std::string,any> primary_list;

	try{
		ModelFactory::ModelType type = ModelFactory::ModelType::User;
		std::map<std::string, any> list = this->create_generic(object, type);

		std::unique_ptr<model> model_obj = ModelFactory::createModel(type, this->functions::get_database(), primary_list);		
		user* tmp = dynamic_cast<user*>(model_obj.get());
		std::unique_ptr<user> user_obj;
		if ( tmp != nullptr ) {
		    model_obj.release();
		    user_obj.reset(tmp);
		}

		if ( !user_obj->model::check_required_fields(list) ) {
			throw missing_required_field_ex();
		}
		
		user_obj->set_username(list["username"].string);
		user_obj->set_password(list["password"].string);
		user_obj->set_email(list["email"].string);

		// optional
		if ( list.count("firstname") == 1 ) {
			user_obj->_firstname = list.at("firstname").string;
		}
		if ( list.count("lastname") == 1 ) {
	    	user_obj->_lastname = list.at("lastname").string;
	    }
	    if ( list.count("country") == 1 ) {
	    	user_obj->_country = list.at("country").string;
		}
		if ( list.count("city") == 1 ) {
    		user_obj->_city = list.at("city").string;
    	}
    	if ( list.count("address") == 1 ) {
    		user_obj->_address = list.at("address").string;
    	}
    	if ( list.count("address_number") == 1 ) {
    		user_obj->_address_number = list.at("address_number").integer;
    	}
    	if ( list.count("postal") == 1 ) {
    		user_obj->_postal = list.at("postal").string;
    	}
    	if ( list.count("note") == 1 ) {
    		user_obj->_note = list.at("note").string;
    	}
    	if ( list.count("remote") == 1 ) {
    		user_obj->_remote = list.at("remote").string;
    	}
    	if ( list.count("user_type") == 1 ) {
    		user_obj->_user_type = list.at("user_type").string;
    	}
    	if ( list.count("active") == 1 ) {
    		user_obj->_active = list.at("active").boolean;
    	}

		user_obj->save();

		std::cout << "After saving called" << std::endl;

		if( user_obj->model::get_saved() ) {
			get_main()->return_result("OK");
		} else {
			throw entity_save_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void create::create_domain(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			std::map<std::string,any> primary_list;

			ModelFactory::ModelType type = ModelFactory::ModelType::Domain;
			std::map<std::string, any> list = this->create_generic(object, type);

			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, this->functions::get_database(), primary_list);		
			domain* tmp = dynamic_cast<domain*>(model_obj.get());
			std::unique_ptr<domain> domain_obj;
			if(tmp != nullptr)
			{
			    model_obj.release();
			    domain_obj.reset(tmp);
			}

			if(!domain_obj->model::check_required_fields(list))
			{
				throw missing_required_field_ex();
			}
			
			domain_validator::validate_domain(list["name"].string);

			domain_obj->name = list["name"].string;
			domain_obj->_status = list["status"].string;
			domain_obj->_registrar = list["registrar"].string;
			domain_obj->set_user(std::shared_ptr<user>(new user(this->functions::get_database(),list["uid"].integer)));

			// optional
	    	if ( list.count("vhost_id") == 1 ) {
	    		domain_obj->set_vhost(std::shared_ptr<vhost>(new vhost(this->functions::get_database(),list.at("vhost_id").integer)));
	    	}
	    	if ( list.count("active") == 1 ) {
	    		domain_obj->_active = list.at("active").boolean;
	    	}

			domain_obj->save();

			std::cout << "After saving called" << std::endl;

			if( domain_obj->model::get_saved() ) {
				get_main()->return_result("OK");
			} else {
				throw entity_save_ex();
			}
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void create::create_dns(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			std::map<std::string,any> primary_list;
			ModelFactory::ModelType type = ModelFactory::ModelType::Dns;
			std::map<std::string, any> list = this->create_generic(object, type);

			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, this->functions::get_database(), primary_list);		
			dns* tmp = dynamic_cast<dns*>(model_obj.get());
			std::unique_ptr<dns> dns_obj;
			if(tmp != nullptr)
			{
			    model_obj.release();
			    dns_obj.reset(tmp);
			}

			if(!dns_obj->model::check_required_fields(list))
			{
				throw missing_required_field_ex();
			}
			
			dns_obj->_name = list["name"].string;
			dns_obj->set_domain(std::shared_ptr<domain>(new domain(this->functions::get_database(),list["domain_name"].string)));

			/* check if domain is actually of user */
			if ( dns_obj->get_domain().get_user().get_uid() != get_main()->get_uid_from_token() ){
				throw auth_ex();
			}

			// optional
	    	if ( list.count("active") == 1 ) {
	    		dns_obj->_active = list.at("active").boolean;
	    	}

			dns_obj->save();

			std::cout << "After saving called" << std::endl;

			if( dns_obj->model::get_saved() ) {
				get_main()->return_result("OK");
			} else {
				throw entity_save_ex();
			}
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void create::create_ftp_account(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			std::map<std::string,any> primary_list;
			ModelFactory::ModelType type = ModelFactory::ModelType::FtpAccount;
			std::map<std::string, any> list = this->create_generic(object, type);

			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, this->functions::get_database(), primary_list);		
			ftp_account* tmp = dynamic_cast<ftp_account*>(model_obj.get());
			std::unique_ptr<ftp_account> ftp_account_obj;
			if(tmp != nullptr)
			{
			    model_obj.release();
			    ftp_account_obj.reset(tmp);
			}

			if(!ftp_account_obj->model::check_required_fields(list))
			{
				throw missing_required_field_ex();
			}

			ftp_account_obj->_name = list["name"].string;
			ftp_account_obj->_password = list["password"].string;
			ftp_account_obj->_homedir= list["homedir"].string;
			ftp_account_obj->set_user(std::shared_ptr<user>(new user(this->functions::get_database(),get_main()->get_uid_from_token())));

			// optional
	    	if ( list.count("shell") == 1 ) {
	    		ftp_account_obj->_shell = list.at("shell").string;
	    	}
	    	if ( list.count("uid") == 1 ) {
	    		ftp_account_obj->_uid = list["uid"].integer;
	    	}
	    	if ( list.count("gid") == 1 ) {
	    		ftp_account_obj->_gid = list["gid"].integer;
	    	}

			ftp_account_obj->save();

			std::cout << "After saving called" << std::endl;

			if( ftp_account_obj->model::get_saved() ) {
				get_main()->return_result("OK");
			} else {
				throw entity_save_ex();
			}
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void create::create_vhost(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			std::map<std::string,any> primary_list;
			ModelFactory::ModelType type = ModelFactory::ModelType::Vhost;
			std::map<std::string, any> list = this->create_generic(object, type);

			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, this->functions::get_database(), primary_list);		
			vhost* tmp = dynamic_cast<vhost*>(model_obj.get());
			std::unique_ptr<vhost> vhost_obj;
			if(tmp != nullptr)
			{
			    model_obj.release();
			    vhost_obj.reset(tmp);
			}

			if(!vhost_obj->model::check_required_fields(list))
			{
				throw missing_required_field_ex();
			}

			vhost_obj->_name = list["name"].string; // validate?
			vhost_obj->_custom_config = list["custom_config"].string;

			// optional
	    	if ( list.count("active") == 1 ) {
	    		vhost_obj->_active = list["active"].boolean;
	    	}

			vhost_obj->save();

			std::cout << "After saving called" << std::endl;

			if( vhost_obj->model::get_saved() ) {
				get_main()->return_result("OK");
			} else {
				throw entity_save_ex();
			}
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void create::create_mailbox(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			std::map<std::string,any> primary_list;
			ModelFactory::ModelType type = ModelFactory::ModelType::Mailbox;
			std::map<std::string, any> list = this->create_generic(object, type);

			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, this->functions::get_database(), primary_list);		
			mailbox* tmp = dynamic_cast<mailbox*>(model_obj.get());
			std::unique_ptr<mailbox> mailbox_obj;
			if(tmp != nullptr)
			{
			    model_obj.release();
			    mailbox_obj.reset(tmp);
			}

			if(!mailbox_obj->model::check_required_fields(list))
			{
				throw missing_required_field_ex();
			}

			mailbox_obj->_email = list["email"].string; // validate?
			mailbox_obj->_password = list["password"].string;
			mailbox_obj->_maildir = list["maildir"].string;
			mailbox_obj->set_domain(std::shared_ptr<domain>(new domain(this->functions::get_database(),list["domain_name"].string)));

			if ( mailbox_obj->get_domain().get_user().get_uid() != get_main()->get_uid_from_token() ){
				throw auth_ex();
			}

			// optional
	    	if ( list.count("quota") == 1 ) {
	    		mailbox_obj->_quota = list["quota"].ll_integer;
	    	}
	    	if ( list.count("bytes") == 1 ) {
	    		mailbox_obj->_bytes = list["bytes"].ll_integer;
	    	}
	    	if ( list.count("messages") == 1 ) {
	    		mailbox_obj->_messages = list["messages"].string;
	    	}
	    	if ( list.count("active") == 1 ) {
	    		mailbox_obj->_active = list["active"].boolean;
	    	}

			mailbox_obj->save();

			std::cout << "After saving called" << std::endl;

			if( mailbox_obj->model::get_saved() ) {
				get_main()->return_result("OK");
			} else {
				throw entity_save_ex();
			}
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void create::create_shell(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
				std::map<std::string,any> primary_list;
			ModelFactory::ModelType type = ModelFactory::ModelType::Shell;
			std::map<std::string, any> list = this->create_generic(object, type);

			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, this->functions::get_database(), primary_list);		
			shell* tmp = dynamic_cast<shell*>(model_obj.get());
			std::unique_ptr<shell> shell_obj;
			if(tmp != nullptr)
			{
			    model_obj.release();
			    shell_obj.reset(tmp);
			}

			if(!shell_obj->model::check_required_fields(list))
			{
				throw missing_required_field_ex();
			}

			shell_obj->set_user(std::shared_ptr<user>(new user(this->functions::get_database(),get_main()->get_uid_from_token())));

			if ( list.count("active") == 1 ) {
	    		shell_obj->_active = list["active"].boolean;
	    	}

			shell_obj->save();

			std::cout << "After saving called" << std::endl;

			if( shell_obj->model::get_saved() ) {
				get_main()->return_result("OK");
			} else {
				throw entity_save_ex();
			}
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void create::create_subdomain(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			std::map<std::string,any> primary_list;
			ModelFactory::ModelType type = ModelFactory::ModelType::Subdomain;
			std::map<std::string, any> list = this->create_generic(object, type);

			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, this->functions::get_database(), primary_list);		
			subdomain* tmp = dynamic_cast<subdomain*>(model_obj.get());
			std::unique_ptr<subdomain> subdomain_obj;
			if(tmp != nullptr)
			{
			    model_obj.release();
			    subdomain_obj.reset(tmp);
			}

			if(!subdomain_obj->model::check_required_fields(list))
			{
				throw missing_required_field_ex();
			}

			subdomain_obj->set_name(list["name"].string);
			subdomain_obj->set_domain(std::shared_ptr<domain>(new domain(this->functions::get_database(),list["domain_name"].string)));

			if ( subdomain_obj->get_domain().get_user().get_uid() != get_main()->get_uid_from_token() ){
				throw auth_ex();
			}

			if ( list.count("active") == 1 ) {
	    		subdomain_obj->_active = list["active"].boolean;
	    	}
	    	if ( list.count("vhost_id") == 1 ) {
	    		subdomain_obj->set_vhost(std::shared_ptr<vhost>(new vhost(this->functions::get_database(),list.at("vhost_id").integer)));
	    	}

	    	std::cout << "Before saving called" << std::endl;

			subdomain_obj->save();

			std::cout << "After saving called" << std::endl;

			if( subdomain_obj->model::get_saved() ) {
				get_main()->return_result("OK");
			} else {
				throw entity_save_ex();
			}
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void create::create_setting(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		if ( get_main()->check_authenticated(role_types) ) {
			std::map<std::string,any> primary_list;
			ModelFactory::ModelType type = ModelFactory::ModelType::AppSettings;
			std::map<std::string, any> list = this->create_generic(object, type);

			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, this->functions::get_database(), primary_list);		
			app_settings* tmp = dynamic_cast<app_settings*>(model_obj.get());
			std::unique_ptr<app_settings> app_settings_obj;
			if(tmp != nullptr)
			{
			    model_obj.release();
			    app_settings_obj.reset(tmp);
			}

			if(!app_settings_obj->model::check_required_fields(list))
			{
				throw missing_required_field_ex();
			}

			app_settings_obj->set_key(list["key"].string); // validate?
			app_settings_obj->set_value(list["value"].string);
			app_settings_obj->set_default(list["default"].boolean);
			app_settings_obj->set_description(list["description"].string);

			app_settings_obj->save();

			std::cout << "After saving called" << std::endl;

			if( app_settings_obj->model::get_saved() ) {
				get_main()->return_result("OK");
			} else {
				throw entity_save_ex();
			}
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void create::create_database_user(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			std::map<std::string,any> primary_list;
			ModelFactory::ModelType type = ModelFactory::ModelType::DatabaseUser;
			std::map<std::string, any> list = this->create_generic(object, type);

			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, this->functions::get_database(), primary_list);		
			database_user* tmp = dynamic_cast<database_user*>(model_obj.get());
			std::unique_ptr<database_user> database_user_obj;
			if(tmp != nullptr)
			{
			    model_obj.release();
			    database_user_obj.reset(tmp);
			}

			if(!database_user_obj->model::check_required_fields(list))
			{
				throw missing_required_field_ex();
			}

			database_user_obj->set_name(list["name"].string); // validate?
			database_user_obj->set_password(list["password"].string);
			database_user_obj->set_permissions(list["permissions"].string);
			database_user_obj->set_user(std::shared_ptr<user>(new user(this->functions::get_database(),get_main()->get_uid_from_token())));

			database_user_obj->save();

			std::cout << "After saving called" << std::endl;

			if( database_user_obj->model::get_saved() ) {
				get_main()->return_result("OK");
			} else {
				throw entity_save_ex();
			}
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

void create::create_database(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			std::map<std::string,any> primary_list;
			ModelFactory::ModelType type = ModelFactory::ModelType::Database;
			std::map<std::string, any> list = this->create_generic(object, type);

			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, this->functions::get_database(), primary_list);		
			database* tmp = dynamic_cast<database*>(model_obj.get());
			std::unique_ptr<database> database_obj;
			if(tmp != nullptr)
			{
			    model_obj.release();
			    database_obj.reset(tmp);
			}

			if(!database_obj->model::check_required_fields(list))
			{
				throw missing_required_field_ex();
			}

			database_obj->set_name(list["name"].string); // validate?
			database_obj->set_database_type(std::shared_ptr<database_type>(new database_type(this->functions::get_database(),list["db_type"].string)));
			database_obj->set_user(std::shared_ptr<user>(new user(this->functions::get_database(),get_main()->get_uid_from_token())));

			database_obj->save();

			std::string username = object.get<std::string>("username");
			user_dbuser_db connect(this->functions::get_database(), username, database_obj->get_name()); // TODO verify db_type
			connect.save();

			std::cout << "After saving called" << std::endl;

			if( database_obj->model::get_saved() ) {
				get_main()->return_result("OK");
			} else {
				throw entity_save_ex();
			}
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* todo rewrite to pointer */
void create::create_queue(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		if ( get_main()->check_authenticated(role_types) ) {
			std::map<std::string,any> primary_list;
			ModelFactory::ModelType type = ModelFactory::ModelType::Queue;
			std::map<std::string, any> list = this->create_generic(object, type);

			queue queue(this->functions::get_database());

			queue._action = list["action"].string;
			queue.set_user(std::shared_ptr<user>(new user(this->functions::get_database(),get_main()->get_uid_from_token())));

			// optional
			if ( list.count("params") == 1 ) {
				queue._params = list.at("params").string;
			}
			if ( list.count("started") == 1 ) {
		    	queue._started = list.at("started").string;
		    }
		    if ( list.count("finished") == 1 ) {
		    	queue._finished = list.at("finished").string;
			}
			if ( list.count("status") == 1 ) {
	    		queue._status = list.at("status").string;
	    	}

			queue.save();

			std::cout << "After saving called" << std::endl;

			if( queue.model::get_saved() ) {
				get_main()->return_result("OK");
			} else {
				get_main()->return_error("Failed to save entity");
			}
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* todo rewrite to pointer */
void create::create_domain_alias(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			std::map<std::string,any> primary_list;
			ModelFactory::ModelType type = ModelFactory::ModelType::DomainAlias;
			std::map<std::string, any> list = this->create_generic(object, type);

			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, this->functions::get_database(), primary_list);		
			domain_alias* tmp = dynamic_cast<domain_alias*>(model_obj.get());
			std::unique_ptr<domain_alias> domain_alias_obj;
			if(tmp != nullptr)
			{
			    model_obj.release();
			    domain_alias_obj.reset(tmp);
			}

			if(!domain_alias_obj->model::check_required_fields(list))
			{
				throw missing_required_field_ex();
			}


			domain_alias domain_alias(this->functions::get_database());

			domain_alias.set_domain(std::shared_ptr<domain>(new domain(this->functions::get_database(),list["domain_name"].string)));
			domain_alias._source = list["source"].string;
			domain_alias._destination = list["destination"].string;

			if ( domain_alias.get_domain().get_user().get_uid() != get_main()->get_uid_from_token() ){
				throw auth_ex();
			}

			// optional
			if ( list.count("active") == 1 ) {
				domain_alias._active = list.at("active").boolean;
			}

			domain_alias.save();

			if( domain_alias.model::get_saved() ) {
				get_main()->return_result("OK");
			} else {
				get_main()->return_error("Failed to save entity");
			}
		} else {
			throw not_auth_ex();
		}
	} catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}


/* Helper methods */

std::map<std::string, any> create::create_generic(cppcms::json::value object, ModelFactory::ModelType type)
{
	cppcms::json::object ob_req;
	cppcms::json::object ob_opt;
	try {
		ob_req = object.get<cppcms::json::object>("required_list");
		ob_opt = object.get<cppcms::json::object>("optional_list");
	}	catch(std::exception &e) {
		throw missing_params_ex();
	}
	std::map<std::string, any> list;
	std::map<std::string, any> primary_list_empty;

	for (cppcms::json::object::const_iterator p=ob_req.begin(); p!=ob_req.end(); ++p) {
		helper::convert(ModelFactory::createModel(type, get_database(), primary_list_empty), p->first, p->second, list);
	}

	for (cppcms::json::object::const_iterator p=ob_opt.begin(); p!=ob_opt.end(); ++p) {
		helper::convert(ModelFactory::createModel(type, get_database(), primary_list_empty), p->first, p->second, list);
	}
	return list;
}

