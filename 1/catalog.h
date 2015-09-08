#ifndef CATALOG_H
#define CATALOG_H

class Item;
class string;

#include <vector>

class Catalog {
public:
	static Catalog& getInstance();

	void add(const Item&);
	void search_by_name(const string&, std::vector<Item>&) const;
	void search_by_price(float, float, std::vector<Item>&) const;

private:
	std::vector<Item> items;

	Catalog();
	Catalog(const Catalog&);
	Catalog& operator=(const Catalog&);
};

#endif // CATALOG_H
