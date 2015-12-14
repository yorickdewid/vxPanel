#ifndef ANY_H
#define ANY_H

struct any {
    enum {CHAR, INT, BOOL} tag;
    union {
        const char *string;
        int integer;
        bool boolean;
    };
    any(){}
    any(const std::string& str) {
        string = str.c_str();
        tag = CHAR;
    }
    any(int i) : integer(i), tag(INT) {}
    any(bool b) : boolean(b), tag(BOOL) {}
};

#endif /* ANY_H */