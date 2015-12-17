#ifndef QUEUE_H
#define QUEUE_H

class queue : public model {

public:
	queue(backend& db) :
		model(db)
	{};
	queue(backend& db, int qid) :
		model(db),
		id(qid)
	{
		this->table_name = "queue";
		this->primary_info["qid"] = qid; 
		this->field_list.push_back("qid");
		this->field_list.push_back("action"); 
		this->field_list.push_back("params"); 
		this->field_list.push_back("created"); 
		this->field_list.push_back("started");
		this->field_list.push_back("finished");
		this->field_list.push_back("uid");
		this->field_list.push_back("status");
		this->field_list.push_back("result");
	};
	
	void save();
	void load();
	void load(std::string domain_name);
	bool m_delete();

	std::string get_created();
	std::string get_result();

	int qid;
	std::string action;
	std::string params;
	std::string started;
	std::string finished;
	unsigned int uid;
	std::string status;

private:
	std::string created;
	std::string result;
};

#endif /* QUEUE_H */

