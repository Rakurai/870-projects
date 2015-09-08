#ifndef ITEM_H
#define ITEM_H

#include "string.h"

class Item {
public:
    Item(const string&, float, int);
    Item(const Item&);
    ~Item();

    Item& operator=(const Item&);

    // accessors
    const string& getName() const { return name; }
    float getPrice() const { return price; }
    const char* getBytes() const { return some_bytes; }

    friend std::ostream& operator<<(std::ostream&, const Item&);

private:
    string name;
    float price;
    char* some_bytes;

    Item();
};

#endif // ITEM_H
