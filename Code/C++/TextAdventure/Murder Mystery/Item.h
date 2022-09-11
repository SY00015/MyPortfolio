/**************************************************
Item Class Header
**************************************************/

#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <sstream>
#include <string>
#include "Enums.h"
using namespace std;

class Item {
private:
	string* itemLocation;
	string* itemName;
	ItemType* itemType;


public:

	Item();
	Item(string newName, ItemType type, string Locations);

	~Item();

	string getItemName();
	ItemType getTypeNum();
	string getTypeName();
	string getItemDetails();
	string getItemLocation();

	void setItemName(string newName);
	void setItemType(ItemType newType);
	void setItemLocation(string newLocations);


};
#endif

