#ifndef ANY_H
#define ANY_H

#include <string.h>

struct any {
    enum {CHAR, INT, BOOL} tag;
    union {
        char *string = NULL;
        int integer;
        bool boolean;
    };
    any(){}
    any(const std::string& str) {
        string = (char *)calloc(1, str.size() + 1);
        strncpy(string, str.c_str(), str.size());
        string[str.size()] = '\0';
        tag = CHAR;
    }
    any(int i) : integer(i), tag(INT) {}
    any(bool b) : boolean(b), tag(BOOL) {}
};

#endif /* ANY_H */