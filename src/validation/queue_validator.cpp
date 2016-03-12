#include "queue_validator.h"

bool queue_validator::valid_action(std::string action)
{
	std::transform(action.begin(), action.end(), action.begin(), ::tolower);
	for ( int actionInt = USERADD; actionInt != DELETEDATABASE; actionInt++ )
	{
	   if(this->action_mapping[actionInt].compare(action) == 0 ){
	   		return true;
	   }
	}
	throw invalid_queue_action_ex();
}
