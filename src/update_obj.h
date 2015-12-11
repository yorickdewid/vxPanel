#ifndef UPDATE_OBJ_H
#define UPDATE_OBJ_H

#include "any.h"

struct update_interface{
	virtual std::string get_field() = 0;
	virtual any get_value() = 0;
};

template<typename T>
struct update_obj : public update_interface{
public:
    update_obj(std::string field, T value) : 
    field(field),
    value(value)
    {};
    std::string field;
    T value;
    any get_value(){
    	return value;
    }
    std::string get_field(){
    	return field;
    }
};


#endif /* UPDATE_OBJ_H */