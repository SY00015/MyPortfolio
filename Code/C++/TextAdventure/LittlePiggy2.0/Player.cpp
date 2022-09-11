/**************************************************
Project: LITTLE PIGGY 2.0
Lab Num: Week 5
Author: Sarah
Purpose: Player Class File
**************************************************/
#include "Player.h"
Player::Player() {
	playerName = "";
	playerScore = 0;
}
Player::~Player() {}
// ACCESSOR METHODS
string Player::getName() {
	return playerName;
}
int Player::getScore() {
	return playerScore;
}
// MUTATOR METHODS
void Player::setName(string name) {
	playerName = name;
}
void Player::setScore(int points) {
	playerScore = points;
}
void Player::updateScore(int points) {
	playerScore += points;
}