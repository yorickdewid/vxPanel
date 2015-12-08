#ifndef UPDATE_OBJ_H
#define UPDATE_OBJ_H

#include <boost/any.hpp>

struct update_obj{
public:
    std::string field;
    boost::any value;
};


#endif /* UPDATE_OBJ_H */
