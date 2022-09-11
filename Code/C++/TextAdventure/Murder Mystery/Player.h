/**************************************************
Purpose: Player Class Header
**************************************************/
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <array>
#include "Item.h"
#include "Enums.h"

using namespace std;
class Player {
public:
	// constructor
	Player();
	~Player();
	// accessor methods
	string getName();
	string getLocation();
	string getInventory();
	// mutator methods
	void setName(string name);
	void setLocation(string location);
	void updateLocation(string location);
	void addInventory(string newitem);
private:

	string playerName;
	string playerLocation;
	string playerInv;
};



#endif