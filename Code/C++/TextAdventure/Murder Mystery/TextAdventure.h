/**************************************************
Project: Text Adventure---A Murder Mystery
Author: Sarah Yeung
Purpose: Application Header File
**************************************************/
#ifndef TextAdventure_H
#define TextAdventure_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>
#include"Player.h"
#include "Enums.h"
#include "Item.h"
#include "Suspect.h"
using namespace std;

void displayTitle();
void displayRules();
void waitForPlayer();
void setPlayers();
void playGame();

void gameOver();

void addItems();


void setLocations();
void displaymap();
void setSuspects();
bool checkGameOver();

string mydata;
string askForString(string question);

vector<Player> playerList;
vector<Item*> gameItems;
vector<Suspect*> suspectList;
vector<string> gameLocations;
vector<string> Locations;
vector<string> Attributes;
vector<string> Inv;
vector<string> pair1;
vector<string> pair2;
vector<string> randName;
vector<string> crimeScene;
vector<string> Items;
vector<string> Items2;
vector <string> characters;
vector<string> descriptions;
vector<string>::iterator new_end, new_end2;
int secretNum;
int y = 0;

#endif