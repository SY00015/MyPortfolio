/**************************************************
Project: LITTLE PIGGY 2.0
Lab Num: Week 5
Author: Sarah 
Purpose: Application Header File
**************************************************/
#ifndef LITTLEPIGGY_H
#define LITTLEPIGGY_H
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "Player.h"
using namespace std;
vector<Player> playerList;
int numPlayers;
int diceSize;
int targetScore;
string askForString(string question);
char askForLetter(string question);
int askForNumber(string question, int low, int high);
bool checkGameOver(int current);
int swapPlayers(int current);
int turnCount;
int starter;

void displayTitle();
void displayGameStats();
void displayText(string myFileName);
void gameOver(int current);
void playLittlePiggy();
void resetGame();
void setPlayers();
void waitForPlayer();
#endif