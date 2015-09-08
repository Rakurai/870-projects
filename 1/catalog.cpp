#include "catalog.h"
#include "item.h"
#include "string.h"

Catalog::Catalog() :
    items()
{ }

Catalog&
Catalog::getInstance()
{
    static Catalog instance;
    return instance;
}

void
Catalog::add(const Item& item)
{
    items.push_back(item);
}

void
Catalog::search_by_name(const string& name, std::vector<Item>& matching) const
{
    for (std::vector<Item>::const_reverse_iterator it = items.rbegin(); it != items.rend(); ++it)
        if (it->getName() == name)
            matching.push_back(*it);
}

void
Catalog::search_by_price(float low, float high, std::vector<Item>& matching) const
{
    for (std::vector<Item>::const_reverse_iterator it = items.rbegin(); it != items.rend(); ++it)
        if (it->getPrice() >= low && it->getPrice() <= high)
            matching.push_back(*it);
}
