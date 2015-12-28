#ifndef FTP_ACCOUNT_H
#define FTP_ACCOUNT_H
#include "domain.h"
#include "user.h"

class ftp_account : public model {

public:
	ftp_account(backend& db) :
		model(db)
	{
		this->table_name = "ftpuser";
		this->primary_info["name"] = "";
		this->field_list["id"] = true;
		this->field_list["name"] = true; 
		this->field_list["password"] = true; 
		this->field_list["uid"] = true; //linux
		this->field_list["gid"] = true;
		this->field_list["homedir"] = true;
		this->field_list["shell"] = true;
		this->field_list["count"] = true;
		this->field_list["userid"] = true;
		this->field_list["created"] = false;
		this->field_list["accessed"] = true;
		this->field_list["modified"] = true;
	};
	ftp_account(backend& db, std::string username) :
		model(db),
		_name(username),
		_user(NULL)
	{
		this->table_name = "ftpuser";
		this->primary_info["name"] = username;
		this->field_list["id"] = true;
		this->field_list["name"] = true; 
		this->field_list["password"] = true; 
		this->field_list["uid"] = true; //linux
		this->field_list["gid"] = true;
		this->field_list["homedir"] = true;
		this->field_list["shell"] = true;
		this->field_list["count"] = true;
		this->field_list["userid"] = true;
		this->field_list["created"] = false;
		this->field_list["accessed"] = true;
		this->field_list["modified"] = true;
	};
	
	void save();
	void load();
	bool m_delete();
	
	void set_username(std::string username);
	void set_password(std::string address);
	void set_uid(int uid);
	void set_gid(int gid);
	void set_homedir(std::string homedir);
	void set_shell(std::string shell);
	void set_count(int count);
	void set_user(std::shared_ptr<user> user);
	void set_accessed(std::string accessed);
	void set_modified(std::string modified);

	int get_id();
	std::string get_username();
	std::string get_password();
	int get_uid();
	int get_gid();
	std::string get_homedir();
	std::string get_shell();
	int get_count();
	user get_user();
	std::string get_created();
	std::string get_accessed();
	std::string get_modified();

private:
	int id; 
	std::string _name; // required
	std::string _password; // required
	int _uid; // required
	int _gid; // required
	std::string _homedir; // required
	std::string _shell; // required
	int _count; // required
	std::shared_ptr<user> _user; // required
	std::string _created; // required
	std::string _accessed; // required
	std::string _modified; // required

};

#endif /* FTP_ACCOUNT_H */

