#include <cppcms/json.h>
#include <cppcms/session_interface.h>
#include <cppcms/url_mapper.h>
#include <cppcms/http_request.h>
#include <iostream>
#include <fstream>
#include <typeinfo>

#include "master.h"
#include "config.h"
#include "exceptions.h"
#include "model.h"
#include "any.h"
#include "model/models.h"

/*
 * Bind JSON RPC calls to class methods
 */
master::master(cppcms::service &srv) : cppcms::rpc::json_rpc_server(srv)
{
	init_backend();

#ifdef SAMPLE
	bind("sum", cppcms::rpc::json_method(&master::sum, this), method_role);
	bind("div", cppcms::rpc::json_method(&master::div, this), method_role);
	bind("notify", cppcms::rpc::json_method(&master::notify, this), notification_role);
	bind("both", cppcms::rpc::json_method(&master::both, this));
#endif
	bind("header", cppcms::rpc::json_method(&master::header, this), method_role);
	bind("authenticate", cppcms::rpc::json_method(&master::authenticate, this), method_role);
	// bind("logged_in", cppcms::rpc::json_method(&master::check_authenticated, this), method_role);
	bind("uptime", cppcms::rpc::json_method(&master::system_uptime, this), method_role);
	bind("version", cppcms::rpc::json_method(&master::version, this), method_role);
	bind("db_version", cppcms::rpc::json_method(&master::db_version, this), method_role);

	bind("create_user", cppcms::rpc::json_method(&master::create_user, this), method_role);
	bind("create_domain", cppcms::rpc::json_method(&master::create_domain, this), method_role);
	bind("create_dns", cppcms::rpc::json_method(&master::create_dns, this), method_role);
	bind("create_ftp_account",cppcms::rpc::json_method(&master::create_ftp_account, this), method_role);
	bind("create_vhost",cppcms::rpc::json_method(&master::create_vhost, this), method_role);
	bind("create_mailbox",cppcms::rpc::json_method(&master::create_mailbox, this), method_role);
	bind("create_shell",cppcms::rpc::json_method(&master::create_shell, this), method_role);
	bind("create_subdomain",cppcms::rpc::json_method(&master::create_subdomain, this), method_role);
	bind("create_setting",cppcms::rpc::json_method(&master::create_setting, this), method_role);
	bind("create_database_user", cppcms::rpc::json_method(&master::create_database_user, this), method_role);
	bind("create_database", cppcms::rpc::json_method(&master::create_database, this), method_role);
	bind("create_queue", cppcms::rpc::json_method(&master::create_queue, this), method_role);

	bind("get_user", cppcms::rpc::json_method(&master::get_user, this), method_role);
	bind("get_domain", cppcms::rpc::json_method(&master::get_domain, this), method_role);
	bind("get_dns", cppcms::rpc::json_method(&master::get_dns, this), method_role);
	bind("get_ftp_account", cppcms::rpc::json_method(&master::get_ftp_account, this), method_role);
	bind("get_vhost", cppcms::rpc::json_method(&master::get_vhost, this), method_role);
	bind("get_mailbox", cppcms::rpc::json_method(&master::get_mailbox, this), method_role);
	bind("get_shell", cppcms::rpc::json_method(&master::get_shell, this), method_role);
	bind("get_subdomain", cppcms::rpc::json_method(&master::get_subdomain, this), method_role);
	bind("get_setting", cppcms::rpc::json_method(&master::get_setting, this), method_role);
	bind("get_database_types", cppcms::rpc::json_method(&master::get_database_types, this), method_role);
	bind("get_database_user", cppcms::rpc::json_method(&master::get_database_user, this), method_role);
	bind("get_database", cppcms::rpc::json_method(&master::get_database, this), method_role);
	bind("get_queue", cppcms::rpc::json_method(&master::get_queue, this), method_role);

	bind("get_ip", cppcms::rpc::json_method(&master::get_ip, this), method_role);

	bind("update_user", cppcms::rpc::json_method(&master::update_user, this), method_role);
	bind("update_domain", cppcms::rpc::json_method(&master::update_domain, this), method_role);
	bind("update_dns", cppcms::rpc::json_method(&master::update_dns, this), method_role);
	bind("update_ftp_account", cppcms::rpc::json_method(&master::update_ftp_account, this), method_role);
	bind("update_vhost", cppcms::rpc::json_method(&master::update_vhost, this), method_role);
	bind("update_mailbox", cppcms::rpc::json_method(&master::update_mailbox, this), method_role);
	bind("update_subdomain", cppcms::rpc::json_method(&master::update_subdomain, this), method_role);
	bind("update_setting", cppcms::rpc::json_method(&master::update_setting, this), method_role);
	bind("update_database_user", cppcms::rpc::json_method(&master::update_database_user, this), method_role);
	bind("update_database", cppcms::rpc::json_method(&master::update_database, this), method_role);

	/* TODO update */

	bind("delete_user", cppcms::rpc::json_method(&master::delete_user, this), method_role);
	bind("delete_domain", cppcms::rpc::json_method(&master::delete_domain, this), method_role);
	bind("delete_dns", cppcms::rpc::json_method(&master::delete_dns, this), method_role);
	bind("delete_ftp_account", cppcms::rpc::json_method(&master::delete_ftp_account, this), method_role);
	bind("delete_vhost", cppcms::rpc::json_method(&master::delete_vhost, this), method_role);
	bind("delete_mailbox", cppcms::rpc::json_method(&master::delete_mailbox, this), method_role);
	bind("delete_shell", cppcms::rpc::json_method(&master::delete_shell, this), method_role);
	bind("delete_subdomain", cppcms::rpc::json_method(&master::delete_subdomain, this), method_role);
	bind("delete_setting", cppcms::rpc::json_method(&master::delete_setting, this), method_role);
	bind("delete_database_type", cppcms::rpc::json_method(&master::delete_database_type, this), method_role);
	bind("delete_database_user", cppcms::rpc::json_method(&master::delete_database_user, this), method_role);
	bind("delete_database", cppcms::rpc::json_method(&master::delete_database, this), method_role);

	bind("write_ip_to_db", cppcms::rpc::json_method(&master::write_ip_to_db, this), method_role);
}

master::~master()
{
	if (db)	{
		delete db;
	}
}

void master::init_backend()
{
	std::string user = settings().get<std::string>("db.user");
	std::string password = settings().get<std::string>("db.password");
	std::string database = settings().get<std::string>("db.database");
	db = new backend(user, password, database);
}

backend& master::get_database()
{
	return *db;
}

#ifdef SAMPLE
void master::sum(int x, int y)
{
	std::cout << "Sum Called" << std::endl;
	return_result(x + y);
}
#endif

void master::div(int x, int y)
{
	std::cout << "Div Called" << std::endl;
	if (y == 0) {
		return_error("Division by zero");
	} else {
		return_result(x / y);
	}
}

void master::notify(std::string msg)
{
	std::cout << "We got notification " << msg << std::endl;
}

void master::both(std::string msg)
{
	if (notification()) {
		std::cout << "We got notification " << msg << std::endl;
	} else {
		return_result("call:" + msg);
	}
}

void master::header()
{
	std::map<std::string,std::string> env = cppcms::application::request().getenv();
	std::string env2 = cppcms::application::request().getenv("HTTP_X_AUTH_TOKEN");
	std::cout << env2 << std::endl;

	for (auto p=env.begin(); p!=env.end(); ++p) {
		std::cout << "Key " << p->first << " Value " << p->second << std::endl;
	}
	return_result("OK");
}

std::string master::format_uptime(std::string sec){
	std::ostringstream os;

	long seconds = atol(sec.c_str());
	unsigned int days = seconds / 86400;
	seconds = seconds % 86400;
	unsigned int hours = seconds / 3600;
	seconds = seconds % 3600;
	unsigned int mins = seconds / 60;
	seconds = seconds % 60;
	unsigned int secs = seconds;

	os << days << " days " << ", " << hours << ":" << mins << ":" << secs << std::endl;
	std::string s = os.str();
	return s;
}

void master::system_uptime()
{
	std::ifstream uptime;
	std::string result;
	uptime.open("/proc/uptime");

	if (uptime.is_open()) { 
		for(
			std::string line;
			getline( uptime, line );
		)
		{
			std::size_t pos = line.find(" ");
			std::string s = line.substr(0, pos);
			result = format_uptime(s);
		}
	}

	uptime.close();
	return_result(result);
}

void master::version()
{
	std::ostringstream os;

	os << "VxPanel version " << VERSION;
	return_result(os.str());
}

void master::db_version()
{
	return_result(db->version().c_str());
}

void master::authenticate(std::string username, std::string password)
{
	cppdb::statement stat;
	std::ostringstream query;

	query << "SELECT uid FROM user WHERE username = ? AND password = encrypt(?,password)";
	stat = get_database().session() << query.str() << username << password;
	cppdb::result r = stat.query();
	bool error;

	if(r.next())
	{
		int uid = -1;
		r.fetch(0, uid);
		std::cout << "UID == " << uid << std::endl;
		if( uid != -1 ) {
			std::string token;
			token = this->create_auth_token(uid);
			if ( !token.empty() ){
				cppcms::json::value json;
				std::string remote_address = cppcms::application::request().remote_addr();

				auth_token auth_token(get_database(),token,remote_address);
				auth_token.load();

				json["auth"]["token"] = auth_token.session_id;
				json["auth"]["refresh_token"] = auth_token._refresh;
				json["auth"]["valid"] = auth_token._valid;

				return_result(json);
			} else {
				error = true;
			}
		} else {
			error = true;
		}
		if( error ) {
			return_error("Failed to create token");
		}
	} else {
		return_error("Incorrect credentials");
	}
}

bool master::check_authenticated()
{
	cppdb::statement stat;

	std::string remote = cppcms::application::request().remote_addr();
	std::string token = cppcms::application::request().getenv("HTTP_X_AUTH_TOKEN");

	if(token.size() != 40) {
		return_error("invalid token supplied");
	} else {
		stat = get_database().session() << 
			"SELECT * FROM auth_token WHERE session_id = ? and remote = inet6_aton(?) and valid > now()" << token << remote;
		cppdb::result r = stat.query();

		if(r.next()){
			return true;
		} else {
			return false;
		}
	}
	return false;
}

/*
	Create
*/

void master::create_user(cppcms::json::value object)
{
	std::map<std::string,any> primary_list;

	try{
		ModelFactory::ModelType type = ModelFactory::ModelType::User;
		std::map<std::string, any> list = this->create_generic(object, type);

		std::unique_ptr<model> model_obj = ModelFactory::createModel(type, get_database(), primary_list);		
		user* tmp = dynamic_cast<user*>(model_obj.get());
		std::unique_ptr<user> user_obj;
		if(tmp != nullptr)
		{
		    model_obj.release();
		    user_obj.reset(tmp);
		}

		if(!user_obj->model::check_required_fields(list))
		{
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
			return_result("OK");
		} else {
			throw entity_save_ex();
		}
	} catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::create_domain(cppcms::json::value object)
{
	std::map<std::string,any> primary_list;

	try{
		ModelFactory::ModelType type = ModelFactory::ModelType::Domain;
		std::map<std::string, any> list = this->create_generic(object, type);

		std::unique_ptr<model> model_obj = ModelFactory::createModel(type, get_database(), primary_list);		
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
		
		domain_obj->name = list["name"].string;
		domain_obj->_status = list["status"].string;
		domain_obj->_registrar = list["registrar"].string;
		domain_obj->set_user(std::shared_ptr<user>(new user(get_database(),list["uid"].integer)));

		// optional
    	if ( list.count("vhost_id") == 1 ) {
    		domain_obj->set_vhost(std::shared_ptr<vhost>(new vhost(get_database(),list.at("vhost_id").integer)));
    	}
    	if ( list.count("active") == 1 ) {
    		domain_obj->_active = list.at("active").boolean;
    	}

		domain_obj->save();

		std::cout << "After saving called" << std::endl;

		if( domain_obj->model::get_saved() ) {
			return_result("OK");
		} else {
			throw entity_save_ex();
		}
	} catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::create_dns(cppcms::json::value object)
{
	std::map<std::string,any> primary_list;

	try{
		ModelFactory::ModelType type = ModelFactory::ModelType::Dns;
		std::map<std::string, any> list = this->create_generic(object, type);

		std::unique_ptr<model> model_obj = ModelFactory::createModel(type, get_database(), primary_list);		
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
		dns_obj->set_domain(std::shared_ptr<domain>(new domain(get_database(),list["domain_name"].string)));

		// optional
    	if ( list.count("active") == 1 ) {
    		dns_obj->_active = list.at("active").boolean;
    	}

		dns_obj->save();

		std::cout << "After saving called" << std::endl;

		if( dns_obj->model::get_saved() ) {
			return_result("OK");
		} else {
			throw entity_save_ex();
		}
	} catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::create_ftp_account(cppcms::json::value object)
{
	std::map<std::string,any> primary_list;

	try{
		ModelFactory::ModelType type = ModelFactory::ModelType::FtpAccount;
		std::map<std::string, any> list = this->create_generic(object, type);

		std::unique_ptr<model> model_obj = ModelFactory::createModel(type, get_database(), primary_list);		
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
		ftp_account_obj->set_user(std::shared_ptr<user>(new user(get_database(),list["userid"].integer)));

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
			return_result("OK");
		} else {
			throw entity_save_ex();
		}
	} catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::create_vhost(cppcms::json::value object)
{
	std::map<std::string,any> primary_list;

	try{
		ModelFactory::ModelType type = ModelFactory::ModelType::Vhost;
		std::map<std::string, any> list = this->create_generic(object, type);

		std::unique_ptr<model> model_obj = ModelFactory::createModel(type, get_database(), primary_list);		
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
			return_result("OK");
		} else {
			throw entity_save_ex();
		}
	} catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::create_mailbox(cppcms::json::value object)
{
	std::map<std::string,any> primary_list;

	try{
		ModelFactory::ModelType type = ModelFactory::ModelType::Mailbox;
		std::map<std::string, any> list = this->create_generic(object, type);

		std::unique_ptr<model> model_obj = ModelFactory::createModel(type, get_database(), primary_list);		
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
		mailbox_obj->set_domain(std::shared_ptr<domain>(new domain(get_database(),list["domain_name"].string)));

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
			return_result("OK");
		} else {
			throw entity_save_ex();
		}
	} catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::create_shell(cppcms::json::value object)
{
	std::map<std::string,any> primary_list;

	try{
		ModelFactory::ModelType type = ModelFactory::ModelType::Shell;
		std::map<std::string, any> list = this->create_generic(object, type);

		std::unique_ptr<model> model_obj = ModelFactory::createModel(type, get_database(), primary_list);		
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

		shell_obj->set_user(std::shared_ptr<user>(new user(get_database(),list["uid"].integer)));

		if ( list.count("active") == 1 ) {
    		shell_obj->_active = list["active"].boolean;
    	}

		shell_obj->save();

		std::cout << "After saving called" << std::endl;

		if( shell_obj->model::get_saved() ) {
			return_result("OK");
		} else {
			throw entity_save_ex();
		}
	} catch(std::exception &e) {
		return_error(e.what());
	}
}

void master::create_subdomain(std::string subdomain_name, std::string domain_name, int uid)
{
	subdomain subdomain(get_database(),subdomain_name, domain_name);

	subdomain.save();

	return_result("OK");
}

void master::create_setting(std::string key, std::string value, bool default_, std::string description)
{
	app_settings app_settings(get_database(),key);

	app_settings.set_value(value);
    app_settings.set_default(default_);
	app_settings.set_description(description);

	app_settings.save();

	return_result("OK");
}

void master::create_database_user(std::string name, std::string password, std::string permissions, int uid)
{
	database_user database_user(get_database(),name);

	database_user.set_password(password);
	database_user.set_permissions(permissions);
	database_user.set_user(std::shared_ptr<user>(new user(get_database(),uid)));

	database_user.save();

	return_result("OK");
}

void master::create_database(std::string db_name, std::string db_type, std::string db_username, int uid)
{
	try{
		database database(get_database(),db_name);

		database.set_database_type(std::shared_ptr<database_type>(new database_type(get_database(),db_type)));
		database.set_user(std::shared_ptr<user>(new user(get_database(),uid)));

		database.save();

		/* now connect the db_username and db_name */
		user_dbuser_db connect(get_database(),db_username,db_name);
		connect.save();

		if ( connect.get_saved() ) {
			return_result("OK");
		}
	}
	catch(std::exception &e)
	{
		std::cout << "Exception occured " << e.what() << std::endl;
	}
}

void master::create_queue(cppcms::json::value object)
{
	//required_fields qid,action,created,uid
	//optional_fields params,started,finished,status,result
	/*
	std::string _action;
	std::string _params;
	std::string _started;
	std::string _finished;
	std::string _status;
	*/

	try{
		ModelFactory::ModelType type = ModelFactory::ModelType::Queue;
		std::map<std::string, any> list = this->create_generic(object, type);

		queue queue(get_database());

		queue._action = list["action"].string;
		queue.set_user(std::shared_ptr<user>(new user(get_database(),list["uid"].integer)));

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
			return_result("OK");
		} else {
			return_error("Failed to save entity");
		}
	} catch(std::exception &e) {
		return_error(e.what());
	}
}

std::string master::create_auth_token(int uid)
{
	try{
		std::string remote_address = cppcms::application::request().remote_addr();

		auth_token auth_token(get_database());

		auth_token.remote = remote_address;
		auth_token.set_user(std::shared_ptr<user>(new user(get_database(),uid)));

		auth_token.save();

		if( auth_token.model::get_saved() ) {
			return auth_token.session_id;
		} else {
			return "";
		}
	} catch(std::exception &e) {
		return "";
	}
}

std::map<std::string, any> master::create_generic(cppcms::json::value object, ModelFactory::ModelType type)
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
		this->convert(ModelFactory::createModel(type, get_database(), primary_list_empty), p->first, p->second, list);
	}

	for (cppcms::json::object::const_iterator p=ob_opt.begin(); p!=ob_opt.end(); ++p) {
		this->convert(ModelFactory::createModel(type, get_database(), primary_list_empty), p->first, p->second, list);
	}
	return list;
}

/* get */

void master::get_user(int uid)
{
	cppcms::json::value json;

	user user(get_database(), uid);

	user.load();

	json["user"]["username"] = user.get_username();
	json["user"]["password"] = user.get_password();
	json["user"]["email"] =  user.get_email();

	return_result(json);
}

void master::get_domain(std::string domain_name, int uid)
{
	cppcms::json::value json;

	domain domain(get_database(), domain_name);

	domain.load();

	if (domain.get_user().get_uid() == uid ) {

		json["domain"]["domainname"] = domain.name;
		json["domain"]["status"] = domain._status;
		json["domain"]["registrar"] =  domain._registrar;

		return_result(json);
	} else {
		return_error("Unauthorized");
	}
}


void master::get_dns(std::string domain_name, int uid)
{
	cppcms::json::value json;

	dns dns(get_database(), 0);
	dns.load(domain_name);

	if (dns.get_domain().get_user().get_uid() == uid ) {

		json["dns"]["address"] = dns.get_name();
		json["dns"]["created"] = dns.get_created();
		json["dns"]["domain_name"] = domain_name;

		return_result(json);
	} else {
		return_error("Unauthorized");
	}
}

// TODO add missing fields
void master::get_ftp_account(std::string ftp_username, int uid)
{
	cppcms::json::value json;

	ftp_account ftp_account(get_database(), ftp_username);
	ftp_account.load();

	if (ftp_account.get_user().get_uid() == uid){

		json["ftp_account"]["username"] = ftp_account.get_username();
		json["ftp_account"]["password"] = ftp_account.get_password();
		json["ftp_account"]["created"] = ftp_account.get_created();

		return_result(json);
	}
	else{
		return_error("Unauthorized");
	}
}

void master::get_vhost(std::string domain_name, int uid)
{
	cppcms::json::value json;

	vhost vhost(get_database(),0);
	vhost.load(domain_name);

	json["vhost"]["id"] = vhost.get_id();
	json["vhost"]["name"] = vhost.get_name();
	json["vhost"]["custom_config"] = vhost.get_custom_config();
	json["vhost"]["created"] = vhost.get_created();
	json["vhost"]["active"] = vhost.get_active();

	return_result(json);
}

void master::get_mailbox(std::string domain_name, int uid)
{
	cppcms::json::value json;

	mailbox mailbox(get_database(),0);
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

		return_result(json);
	}
	else{
		return_error("Unauthorized");
	}
}

void master::get_shell(int id,int uid)
{
	cppcms::json::value json;

	shell shell(get_database(),id);
	shell.load();

	if ( shell.get_user().get_uid() == uid) {
		json["shell"]["created"] = shell.get_created();

		return_result(json);
	}
	else{
		return_error("Unauthorized");
	}
}

/* todo check if domain belongs to logged in user */
void master::get_subdomain(std::string subdomain_name, std::string domain_name, int uid)
{
	cppcms::json::value json;

	subdomain subdomain(get_database(),subdomain_name, domain_name);
	subdomain.load();

	json["subdomain"]["name"] = subdomain.get_name();	
	json["subdomain"]["created"] = subdomain.get_created();
	if ( subdomain.get_domain_ptr() !=  NULL ) { /* good enough? */
			json["subdomain"]["domain"] = subdomain.get_domain().name;
	}

	return_result(json);
}

void master::get_setting(std::string key)
{
	cppcms::json::value json;

	app_settings app_settings(get_database(),key);
	app_settings.load();

	json["app_settings"]["key"] = app_settings.get_key();
	json["app_settings"]["value"] = app_settings.get_value();
	json["app_settings"]["default"] = app_settings.get_default();
	json["app_settings"]["description"] = app_settings.get_description();
	json["app_settings"]["updated"] = app_settings.get_updated();	
	json["app_settings"]["created"] = app_settings.get_created();

	return_result(json);
}

/* TODO Inspect for memory leakage */
void master::get_database_types()
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
	return_result(json);
}

void master::get_database_user(std::string username, int uid)
{

	cppcms::json::value json;

	database_user database_user(get_database(),username);
	database_user.load();

	if ( database_user.get_user().get_uid() == uid ) {
		json["db_user"]["username"] = database_user.get_name();
		json["db_user"]["password"] = database_user.get_password();
		json["db_user"]["permissions"] = database_user.get_permissions();
		json["db_user"]["created"] = database_user.get_created();

		return_result(json);
	}
	else {
		return_error("Unauthorized");
	}
}

void master::get_database(std::string db_name, int uid)
{
	cppcms::json::value json;

	database database(get_database(),db_name);
	database.load();

	if ( database.get_user().get_uid() == uid ) {
		json["db"]["name"] = database.get_name();
		json["db"]["created"] = database.get_created();
		json["db"]["db_type"] = database.get_database_type().get_name();

		return_result(json);
	}
	else {
		return_error("Unauthorized");
	}
}

void master::get_queue(int qid)
{
	cppcms::json::value json;

	queue queue(get_database(),qid);
	queue.load();

	json["queue"]["id"] = queue.qid;
	json["queue"]["action"] = queue._action;
	json["queue"]["params"] = queue._params;
	json["queue"]["created"] = queue.get_created();
	json["queue"]["started"] = queue._started;
	json["queue"]["finished"] = queue._finished;
	json["queue"]["uid"] = queue.get_user().get_uid();
	json["queue"]["status"] = queue._status;
	json["queue"]["result"] = queue.get_result();

	return_result(json);
}

void master::get_ip()
{
	std::string remote_address = cppcms::application::request().remote_addr();
	return_result(remote_address);
}

/* Update */

/* Dump map contents */
void dump_map(const std::map<std::string,any>& map) {
	for (std::map<std::string, any>::const_iterator it = map.begin(); it != map.end(); it++) {
		std::cout << "Key: " << it->first << std::endl;
		std::cout << "Value: " << std::endl;
		switch (it->second.tag) {
			case any::CHAR:
				puts(it->second.string);
				break;
			case any::LONG_INT:
				printf("%ld\n", it->second.long_integer);
				break;
			case any::LL_INT:
				printf("%lld\n", it->second.ll_integer);
				break;
			case any::INT:
				printf("%d\n", it->second.integer);
				break;
			case any::BOOL:
				printf("%d\n", it->second.boolean);
				break;
		}
	}
}

bool master::convert(std::unique_ptr<model> tmp, cppcms::string_key first, cppcms::json::value second, std::map<std::string,any> &update_list)
{
	std::cout << "convert" << std::endl;
	std::cout << "Field " << first.str() << std::endl;
	if ( tmp->model::compare_field(first.str()) ) {
		switch(second.type()) {
			case cppcms::json::json_type::is_number: 
			{
				update_list[first.str()] = any((int)second.number());
				break;
			}
			case cppcms::json::json_type::is_string: 
			{
				std::string val = (std::string)second.str();
				update_list[first.str()] = any(val);
				break;
			}
			case cppcms::json::json_type::is_boolean:
			{
				update_list[first.str()] = any((bool)second.boolean());
				break;
			}
			default:
				break;
		}
		dump_map(update_list);
		return true;
	}
	throw unrecognized_field_ex();
	return false;
}

any master::get_identifier(std::string primary_field, cppcms::string_key first, cppcms::json::value second)
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

bool master::check_default(any value)
{
	switch (value.tag) {
		case any::CHAR:
			std::cout << " String " << std::endl;
			if( ((std::string)value.string).empty() )
			{
				return true;
			}
			return false;
			break;
		case any::INT:
			std::cout << " Integer " << std::endl;
			if( value.integer == -1 )
			{
				return true;
			}
			return false;
			break;
		default: 
			std::cout << "Default case" << std::endl;
			return true;
	}
}

bool master::check_default(std::map<std::string,any> primary_list)
{
	int count_defaults = 0;
	for ( auto it = primary_list.begin(); it != primary_list.end(); ++it ) {
		switch ((*it).second.tag) {
			case any::CHAR:
				if( ((std::string)(*it).second.string).empty() )
				{
					count_defaults++;
				}
				break;
			case any::INT:
				if( (*it).second.integer == -1 )
				{
					count_defaults++;
				}
				break;
			default: 
				count_defaults++;
				break;
		}
	}
	if(count_defaults == 0 )
	{
		return false;
	} else {
		return true;
	}
}

bool master::check_primary_field(std::vector<any> primary_list, std::string field)
{
	for ( auto it = primary_list.begin(); it != primary_list.end(); ++it ) {
		if(field.compare((*it).string) == 0)
		{
			return true;
		}
	}
	return false;
}

void master::update_generic(cppcms::json::value object, std::unique_ptr<model> tmp, ModelFactory::ModelType type)
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
			this->convert(ModelFactory::createModel(type, get_database(), primary_list_empty), p->first, p->second, update_list);
		}
		dump_map(primary_list);
		if ( !this->check_default(primary_list) ) {
			std::unique_ptr<model> model_obj = ModelFactory::createModel(type, get_database(), primary_list);
			if (model_obj->model::update(update_list)) {
				return_result("OK");
			} else { 
				return_error("Failed to update user");
			}
		}
	} catch(std::exception &e) {
		std::cout << "User update Exception : " << e.what() << std::endl;
		return_error("Unrecognized field");
	}
}

/* password,email,fname,lname,country,city,address,postal,note,user_type,active */
void master::update_user(cppcms::json::value object)
{
	int uid = -1;
	std::map<std::string,any> primary_list;
	primary_list["uid"] = uid;
	this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::User, get_database(), primary_list), ModelFactory::ModelType::User);
}

/* status, registrar, vhost_id */
void master::update_domain(cppcms::json::value object)
{
	std::string domain_name = "";
	std::map<std::string,any> primary_list;
	primary_list["name"] = domain_name;
	this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Domain, get_database(), primary_list), ModelFactory::ModelType::Domain);
}

/* address */
void master::update_dns(cppcms::json::value object)
{
	int dns_id = -1;
	std::map<std::string,any> primary_list;
	primary_list["id"] = dns_id;
	this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Dns, get_database(), primary_list), ModelFactory::ModelType::Dns);
}

/* password, permissions */
void master::update_ftp_account(cppcms::json::value object)
{
	std::string ftp_account = "";
	std::map<std::string,any> primary_list;
	primary_list["name"] = ftp_account;
	this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::FtpAccount, get_database(), primary_list), ModelFactory::ModelType::FtpAccount);
}

/* name ?, custom_config */ 
void master::update_vhost(cppcms::json::value object)
{
	int vhost_id = -1;
	std::map<std::string,any> primary_list;
	primary_list["id"] = vhost_id;
	this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Vhost, get_database(), primary_list), ModelFactory::ModelType::Vhost);
}

/* address */
void master::update_mailbox(cppcms::json::value object)
{
	int mailbox_id = -1;
	std::map<std::string,any> primary_list;
	primary_list["id"] = mailbox_id;
	this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Mailbox, get_database(), primary_list), ModelFactory::ModelType::Mailbox);
}

/* subdomain name , vhost_id */
void master::update_subdomain(cppcms::json::value object)
{
	std::string domain_name = "";
	std::string subdomain_name = "";
	std::map<std::string,any> primary_list;
	primary_list["name"] = subdomain_name;
	primary_list["domain_name"] = domain_name;
	this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Subdomain, get_database(), primary_list), ModelFactory::ModelType::Subdomain);
}

/* value, default, description */
void master::update_setting(cppcms::json::value object)
{
	std::string key = "";
	std::map<std::string,any> primary_list;
	primary_list["key"] = key;
	this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::AppSettings, get_database(), primary_list), ModelFactory::ModelType::AppSettings);
}

/* password, permissions */
void master::update_database_user(cppcms::json::value object)
{
	std::string username = "";
	std::map<std::string,any> primary_list;
	primary_list["name"] = username;
	this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::DatabaseUser, get_database(), primary_list), ModelFactory::ModelType::DatabaseUser);
}

/* database_type */
void master::update_database(cppcms::json::value object)
{
	std::string name = "";
	std::map<std::string,any> primary_list;
	primary_list["name"] = name;
	this->update_generic(object, ModelFactory::createModel(ModelFactory::ModelType::Database, get_database(), primary_list), ModelFactory::ModelType::Database);
}

/* delete */

void master::delete_user(std::string username, int uid)
{
	user user(get_database(),uid);

	user.load();

	if ( user.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_domain(std::string domain_name, int uid)
{
	domain domain(get_database(),domain_name);

	domain.load();

	if ( domain.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_dns(int dns_id, int uid)
{
	dns dns(get_database(),dns_id);

	dns.load();

	if ( dns.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_ftp_account(std::string ftp_username, int uid)
{
	ftp_account ftp_account(get_database(),ftp_username);

	ftp_account.load();

	if ( ftp_account.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_vhost(int vhost_id, int uid)
{
	vhost vhost(get_database(),vhost_id);

	vhost.load();

	if ( vhost.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_mailbox(int mailbox_id, int uid)
{
	mailbox mailbox(get_database(),mailbox_id);

	mailbox.load();

	if ( mailbox.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_shell(int id, int uid)
{
	shell shell(get_database(),id);

	shell.load();

	if ( shell.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_subdomain(std::string subdomain_name, std::string domain_name, int uid)
{
	subdomain subdomain(get_database(),subdomain_name,domain_name);

	subdomain.load();

	if ( subdomain.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_setting(std::string key)
{
	app_settings app_settings(get_database(),key);

	app_settings.load();
	if ( app_settings.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_database_type(std::string name)
{
	database_type database_type(get_database(),name);

	database_type.load();

	if ( database_type.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_database_user(std::string username, int uid)
{
	database_user database_user(get_database(),username);

	database_user.load();
	if ( database_user.m_delete() ) {
		return_result("OK");
	} else {
		return_error("Delete failed");
	}
}

void master::delete_database(std::string db_name, std::string db_username, int uid)
{
	database database(get_database(),db_name);

	database.load();
	user_dbuser_db connect(get_database(),db_username,db_name);
	if ( connect.m_delete() ) {
		if ( database.m_delete() ) {
			return_result("OK");
		}
		else {
			return_error("Failed to delete database, and remove connection with username");
		}
	} else {
		return_error("Delete failed");
	}
}

void master::write_ip_to_db()
{
	std::string remote_address = cppcms::application::request().remote_addr();

	cppdb::statement stat;

	stat = get_database().session() << 
		"UPDATE user set remote = inet6_aton(?)" << remote_address;

	stat.exec();
	stat.reset();

	std::ostringstream stream;
	stream << "Saved ip to db, " << remote_address;

	return_result(stream.str());
}

