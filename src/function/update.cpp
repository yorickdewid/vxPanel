#include "update.h"
#include "../model/models.h"
#include "../validation/domain_validator.h"
#include "helper.h"

/* password,email,fname,lname,country,city,address,postal,note,user_type,active */
void update::update_user(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {

			int uid = -1;
			std::map<std::string,any> primary_list;
			primary_list["uid"] = uid;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::User, get_database(), primary_list), ModelFactory::ModelType::User);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* status, registrar, vhost_id */
void update::update_domain(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			
			std::string domain_name = "";
			std::map<std::string,any> primary_list;
			primary_list["name"] = domain_name;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Domain, get_database(), primary_list), ModelFactory::ModelType::Domain);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* address */
void update::update_dns(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			
			int dns_id = -1;
			std::map<std::string,any> primary_list;
			primary_list["id"] = dns_id;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Dns, get_database(), primary_list), ModelFactory::ModelType::Dns);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* password, permissions */
void update::update_ftp_account(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {
			
			std::string ftp_account = "";
			std::map<std::string,any> primary_list;
			primary_list["name"] = ftp_account;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::FtpAccount, get_database(), primary_list), ModelFactory::ModelType::FtpAccount);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* name ?, custom_config */ 
void update::update_vhost(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {

			int vhost_id = -1;
			std::map<std::string,any> primary_list;
			primary_list["id"] = vhost_id;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Vhost, get_database(), primary_list), ModelFactory::ModelType::Vhost);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* address */
void update::update_mailbox(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {

			int mailbox_id = -1;
			std::map<std::string,any> primary_list;
			primary_list["id"] = mailbox_id;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Mailbox, get_database(), primary_list), ModelFactory::ModelType::Mailbox);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* subdomain name , vhost_id */
void update::update_subdomain(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {

			std::string domain_name = "";
			std::string subdomain_name = "";
			std::map<std::string,any> primary_list;
			primary_list["name"] = subdomain_name;
			primary_list["domain_name"] = domain_name;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Subdomain, get_database(), primary_list), ModelFactory::ModelType::Subdomain);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* value, default, description */
void update::update_setting(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		if ( get_main()->check_authenticated(role_types) ) {

			std::string key = "";
			std::map<std::string,any> primary_list;
			primary_list["key"] = key;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::AppSettings, get_database(), primary_list), ModelFactory::ModelType::AppSettings);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* password, permissions */
void update::update_database_user(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {

			std::string username = "";
			std::map<std::string,any> primary_list;
			primary_list["name"] = username;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::DatabaseUser, get_database(), primary_list), ModelFactory::ModelType::DatabaseUser);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

/* database_type */
void update::update_database(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {

			std::string name = "";
			std::map<std::string,any> primary_list;
			primary_list["name"] = name;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Database, get_database(), primary_list), ModelFactory::ModelType::Database);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}


void update::update_domain_alias(cppcms::json::value object)
{
	try{
		std::vector<std::string> role_types;
		role_types.push_back(USER_TYPE_ADMINISTRATOR);
		role_types.push_back(USER_TYPE_USER);
		if ( get_main()->check_authenticated(role_types) ) {

			int id = -1;
			std::map<std::string,any> primary_list;
			primary_list["id"] = id;
			this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::DomainAlias, get_database(), primary_list), ModelFactory::ModelType::DomainAlias);

		} else {
			throw not_auth_ex();
		}
    } catch(std::exception &e) {
		get_main()->return_error(e.what());
	}
}

// TODO check if primary fields are supplied
void update::update_generic(cppcms::json::value object, std::unique_ptr<model> tmp, ModelFactory::ModelType type)
{
	try{
		std::map<std::string, any> update_list;
		cppcms::json::object ob = object.get<cppcms::json::object>("update_list");
		std::map<std::string, any> primary_list;
		std::map<std::string, any> primary_list_empty;
		std::map<std::string, any> primary_info = tmp->get_primary_info();

		for (cppcms::json::object::const_iterator p=ob.begin(); p!=ob.end(); ++p) {
			bool primary = false;
			for ( auto it = primary_info.begin(); it != primary_info.end(); ++it ) {
				if( this->check_default( (*it).second) && tmp->model::compare_primary_field(p->first) && (it->first.compare(p->first) == 0) ) {
					primary_list[it->first] = this->get_identifier( (*it).first, p->first.str(), p->second);
					primary = true;
				} 
			}
			if ( primary ) {
				continue; // skip primary value
			}
			helper::convert(ModelFactory::createModel(type, get_database(), primary_list_empty), p->first, p->second, update_list);
		}
		if ( !this->check_default(primary_list) ) {
			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, get_database(), primary_list);
			if (model_obj->model::update(update_list)) {
				get_main()->return_result("OK");
			} else { 
				get_main()->return_error("Failed to update model");
			}
		}
	} catch(std::exception &e) {
		std::cout << "User update Exception : " << e.what() << std::endl;
		get_main()->return_error(e.what());
	}
}

any update::get_identifier(std::string primary_field, cppcms::string_key first, cppcms::json::value second)
{
	std::cout << "Called get get_identifier" << std::endl;
	std::cout << first.str() << primary_field << std::endl;
	if( primary_field.compare(first.str()) == 0){
		switch(second.type())
		{
			case cppcms::json::json_type::is_number: 
			{
				return (int)second.number();
				break;
			}
			case cppcms::json::json_type::is_string: 
			{
				std::string val = (std::string)second.str();
				return val;
				break;
			}
			case cppcms::json::json_type::is_boolean:
			{
				return (bool)second.boolean();
				break;
			}
			case cppcms::json::json_type::is_undefined:
			{
				std::cout << "Undefined type detected, trying to convert to string" << std::endl;
				std::string val = (std::string)second.str();
				return val;
				break;
			}
			default:
			{
				return -1;
				break;
			}
		}
	}
	std::cout << " Primary field doesnt match " << std::endl;
	return -1;
}

bool update::check_default(std::map<std::string,any> primary_list)
{
	int count_defaults = 0;
	for ( auto it = primary_list.begin(); it != primary_list.end(); ++it ) {
		switch ((*it).second.tag) {
			case any::CHAR:
				if( ( (std::string)(*it).second.string).empty() ) {
					count_defaults++;
				}
				break;
			case any::INT:
				if( (*it).second.integer == -1 ){
					count_defaults++;
				}
				break;
			default: 
				count_defaults++;
				break;
		}
	}
	if ( count_defaults == 0 ) {
		return false;
	} else {
		return true;
	}
}

bool update::check_default(any value)
{
	switch (value.tag) {
		case any::CHAR:
			std::cout << " String " << std::endl;
			if ( ((std::string)value.string).empty() ) {
				return true;
			}
			return false;
			break;
		case any::INT:
			std::cout << " Integer " << std::endl;
			if ( value.integer == -1 ) {
				return true;
			}
			return false;
			break;
		default: 
			std::cout << "Default case" << std::endl;
			return true;
	}
}

