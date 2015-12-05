#ifndef USER_DBUSER_DB_H
#define USER_DBUSER_DB_H

class user_dbuser_db : public model {

public:
	user_dbuser_db(backend& db, std::string db_username,std::string db_name) :
		model(db),
		db_username(db_username),
		db_name(db_name)
	{};
	
	void save();
	void load();
	void load(std::string db_username,std::string db_name);
	bool update(std::string field);
	bool update(std::vector<update_obj> list);
	bool m_delete();

	void set_db_username(std::string db_username);
	void set_db_name(std::string db_name);

	std::string get_db_username();
	std::string get_db_name();

private:
	std::string db_username;
	std::string db_name;

};

#endif /* USER_DBUSER_DB_H */

