/**************************************************
Project: LITTLE PIGGY 2.0
Lab Num: Week 5
Author: Cheryl Howard
Purpose: Player Class File
**************************************************/
#include "Player.h"

Player::Player() {
	playerName = "";
	playerLocation = "";
	playerInv = "";
}
Player::~Player() {
	
}
// ACCESSOR METHODS
string Player::getName() {
	return playerName;
}
string Player::getLocation() {
	return playerLocation;
}
string Player::getInventory() { return playerInv; }
// MUTATOR METHODS
void Player::setName(string name) {
	playerName = name;
}
void Player::setLocation(string location) {
	playerLocation = location;
}
void Player::updateLocation(string location) {
	playerLocation = location;
}
void Player::addInventory(string newitem) {
	playerInv = newitem;
}



