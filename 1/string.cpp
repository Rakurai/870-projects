#include "string.h"

#include <iostream>
#include <cstring>

string::string() :
    buf(new char[1])
{
    buf[0] = '\0';
}

string::string(const char* b) :
    buf(new char[strlen(b)+1])
{
    strcpy(buf, b);
}

string::string(const string& s) :
    buf(new char[strlen(s.buf)+1])
{
    strcpy(buf, s.buf);
}

string::~string() {
    delete [] buf;
}

string&
string::operator=(const string& s) {
    if (&s != this) {
        char *tmp = buf;
        buf = new char[strlen(s.buf) + 1];
        strcpy(buf, s.buf);
        delete [] tmp;
    }

    return *this;
}

bool
operator==(const string& lhs, const string& rhs) {
    return &lhs == &rhs || strcmp(lhs.buf, rhs.buf) == 0;
}

std::ostream&
operator<<(std::ostream& output, const string& s) {
    return output << s.buf;
}
