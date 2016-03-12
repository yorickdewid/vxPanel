#ifndef QUEUE_VALIDATOR_H
#define QUEUE_VALIDATOR_H

#include <fstream>
#include <string>
#include <algorithm>
#include <map>

#include "../exceptions.h"

class queue_validator {

public:
	queue_validator(){
		action_mapping[USERADD] = "user_add";
		action_mapping[USERDEL] = "user_del";
		action_mapping[MAILSEND] = "mail_send";
		action_mapping[CONFIGCHECK] = "config_check";
		action_mapping[CREATEVHOST] = "create_vhost";
		action_mapping[DELETEVHOST] = "delete_vhost";
		action_mapping[RELOADSERVICE] = "reload_service";
		action_mapping[RESTARTSERVICE] = "restart_service";
		action_mapping[CREATEDATABASE] = "create_database";
		action_mapping[DELETEDATABASE] = "delete_database";
	};

	bool valid_action(std::string action);

	enum Action {
		USERADD,
		USERDEL,

		MAILSEND,

		CONFIGCHECK,

		CREATEVHOST,
		DELETEVHOST,

		RELOADSERVICE,
		RESTARTSERVICE,

		CREATEDATABASE,
		DELETEDATABASE,
	};

private:
	std::map<int,std::string> action_mapping;

};


#endif /* QUEUE_VALIDATOR_H */

