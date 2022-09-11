#include "Item.h"
Item::Item() {
	// Default constructor
	/*itemName = "Undefined";
	itemType = NONE;
	pointModifier = 0;*/
}
Item::Item(string newName, ItemType type, string Locations) {
	// Set values based 
	itemName = new string (newName);
	itemType = new ItemType (type);
	itemLocation = new string(Locations);
}
Item::~Item() {
	delete itemName;
	delete itemType;
	delete itemLocation;
}
// ACCESSOR FUNCTIONS
// Written like this to reduce space in this document
string Item::getItemName() { return *itemName; }
ItemType Item::getTypeNum() { return *itemType; }
string Item::getTypeName() {
	// Return string depending on itemType value
	switch (*itemType) {
	case WEAPON:
		return "Weapon";
	
	default:
		return "None";
	}
}
string Item::getItemLocation() { return*itemLocation; }
string Item::getItemDetails() {
	// Returns a formatted string containing information on the item.
	stringstream itemDetails;

	//itemDetails << "\nItem Name: " << itemName;
	//itemDetails << "\nItem Type: " << getTypeName();
	itemDetails << "\nLocation : " << *itemLocation;

	return itemDetails.str();
}
// MUTATOR FUNCTIONS
void Item::setItemName(string newName) {
	// Make sure that the type is valid
	*itemName = newName;

}
void Item::setItemType(ItemType newType) {
	// Make sure that the type is valid
	// Assumption here that none is invalid. Should never be set.
	if (newType > NONE && newType <= WEAPON) {
		*itemType = newType;
	}
}
void Item::setItemLocation(string Location) {
	// Currently no validation.
	// May be changed in future (no negative numbers?)
	*itemLocation = Location;
}