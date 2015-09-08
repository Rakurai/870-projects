#include <cstdlib>
#include <cstring>

#include "item.h"

Item::Item(const string& n, float p, int size) :
    name(n),
    price(p),
    some_bytes(new char[size])
{
    for (int i = 0; i < size-1; i++)
        some_bytes[i] = rand() % 256;

    some_bytes[size-1] = '\0';
}

Item::Item(const Item& t) :
    name(t.name),
    price(t.price),
    some_bytes(new char[strlen(t.some_bytes)+1])
{
    strcpy(some_bytes, t.some_bytes);
}

Item::~Item() {
    delete[] some_bytes;
}

Item&
Item::operator=(const Item& t) {
    if (&t != this) {
        char* tmp = some_bytes;
        some_bytes = new char[strlen(t.some_bytes)+1];
        strcpy(some_bytes, t.some_bytes);
        delete[] tmp;

        name = t.name;
        price = t.price;
    }

    return *this;
}

std::ostream&
operator<<(std::ostream& output, const Item& i) {
    return output << i.name << ", $" << i.price;
}
