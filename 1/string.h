#ifndef STRING_H
#define STRING_H

#include <iostream>

class string {
public:
    string();
    string(const char*);
    string(const string& s);
    ~string();

    string& operator=(const string&);

    friend std::ostream& operator<<(std::ostream&, const string&);
    friend bool operator==(const string&, const string&);

private:
    char* buf;
};

#endif // STRING_H
