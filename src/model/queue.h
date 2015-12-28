#ifndef QUEUE_H
#define QUEUE_H

#include "user.h"
#include "../model.h"

class queue : public model {

public:
	queue(backend& db) :
		model(db),
		_params(""),
		_started(""),
		_finished(""),
		_status("")
	{
		this->table_name = "queue";
		this->primary_info["qid"] = -1; 
		this->field_list["qid"] = true;
		this->field_list["action"] = true; 
		this->field_list["params"] = false; 
		this->field_list["created"] = false; 
		this->field_list["started"] = false;
		this->field_list["finished"] = false;
		this->field_list["uid"] = true;
		this->field_list["status"] = false;
		this->field_list["result"] = false;
	};
	queue(backend& db, int qid) :
		model(db),
		qid(qid),
		_params(""),
		_started(""),
		_finished(""),
		_status("")
	{
		this->table_name = "queue";
		this->primary_info["qid"] = qid; 
		this->field_list["qid"] = true;
		this->field_list["action"] = true; 
		this->field_list["params"] = false; 
		this->field_list["created"] = false; 
		this->field_list["started"] = false;
		this->field_list["finished"] = false;
		this->field_list["uid"] = true;
		this->field_list["status"] = false;
		this->field_list["result"] = false;
	};
	
	void save();
	void load();
	void load(std::string domain_name);
	bool m_delete();

	void set_user(std::shared_ptr<user> user);

	std::string get_created();
	std::string get_result();
	user get_user();

	int qid;
	std::string _action;
	std::string _params;
	std::string _started;
	std::string _finished;
	std::string _status;

private:
	std::string _created;
	std::shared_ptr<user> _user;
	std::string _result;
};

#endif /* QUEUE_H */

