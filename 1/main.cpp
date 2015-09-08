#include <iostream>
#include <cstdlib>
#include "catalog.h"
#include "string.h"
#include "item.h"

int main() {
    Catalog& catalog = Catalog::getInstance();
    std::vector<Item> list;

    catalog.add(Item("apple", 2.0, rand() % 100));
    catalog.add(Item("orange", 3.0, rand() % 100));
    catalog.add(Item("banana", 0.50, rand() % 100));
    catalog.add(Item("pineapple", 4.0, rand() % 100));

    catalog.search_by_name("orange", list);
    std::cout << "Items with the name 'orange':" << std::endl;

    for (std::vector<Item>::const_iterator it = list.begin(); it != list.end(); it++)
        std::cout << *it << std::endl;

    list.clear();

    catalog.search_by_price(1.0, 3.0, list);
    std::cout << "Items between 1 and 3 dollars:" << std::endl;

    for (std::vector<Item>::const_iterator it = list.begin(); it != list.end(); it++)
        std::cout << *it << std::endl;
}
