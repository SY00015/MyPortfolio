/**************************************************
Project: LITTLE PIGGY 2.0
Lab Num: Week 6
Author: Sarah
Purpose: Player Class Header
**************************************************/
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
using namespace std;
class Player {
public:
	// constructor
	Player();
	~Player();
	// accessor methods
	string getName();
	int getScore();
	// mutator methods
	void setName(string name);
	void setScore(int points);
	void updateScore(int points);
private:
	// player variables
	string playerName;
	int playerScore;
};
#endif