/**************************************************
Project: LITTLE PIGGY 2.0
Lab Num: Week 5
Author: Sarah Yeung
Purpose: Application File
**************************************************/
#include "LittlePiggy.h"
int main() {
	// seed randoms
	srand(unsigned(time(NULL)));
	// display intro blurb
	displayText("LittlePiggy.txt");
	// play the game
	setPlayers();
	playLittlePiggy();
	// wait and exit
	waitForPlayer();
	return 0;
}
/**************************************************
MAIN GAME FUNCTIONS
**************************************************/
void playLittlePiggy() {
	// reset variables
	resetGame();
	displayGameStats();
	// initialise local vars
	bool isGameOver = false;
	int dieVal = 0;
	int currentPlayer = rand() % numPlayers;
	int runningTotal = 0;
	turnCount = 1;
	starter = currentPlayer;

	while (!isGameOver) {
		//display the number of turns
		cout << "\n Turn numbers: " << turnCount<< endl;
		// show whose turn it is
		cout << "\n It's your turn, " << playerList[currentPlayer].getName();
		// ask player for their choice of action
		char choice = askForLetter("Do you want to [R]oll or [B]ank? ");
		switch (choice) {
		case 'R':
			dieVal = rand() % diceSize + 1;
			if (dieVal > 1) {
				// player can roll again
				runningTotal += dieVal;
			}
			else {
				// player rolled a 1 so loses all their points
				runningTotal = 0;
				currentPlayer = swapPlayers(currentPlayer);
			}
			cout << "\n You rolled: " << dieVal << "\tTotal: " << runningTotal
				<< endl;
			waitForPlayer();
			break;
		case 'B':
			playerList[currentPlayer].updateScore(runningTotal);
			// check for a winner
			isGameOver = checkGameOver(currentPlayer);
			if (!isGameOver) {
				runningTotal = 0;
				currentPlayer = swapPlayers(currentPlayer);
			}
			break;
		default:
			cout << "\n Please choose either [R]oll or [B]ank.\n";
		}
		displayGameStats();
	}
	// display winner and play again?
	gameOver(currentPlayer);
}
int swapPlayers(int current) {
	// change the current player
	current++;
	if (current > numPlayers - 1) {
		current = 0;
	}
	//add turns when both players finished their act
	if (current == starter) { turnCount += 1; }
	return current;
}
bool checkGameOver(int current) {
	if (playerList[current].getScore() >= targetScore) {
		return true;
	}
	else {
		return false;
	}
}
void gameOver(int current) {
	// print winner message
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << "\n\tThe winner is: " + playerList[current].getName();
	cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	char answer = askForLetter("Do you want to play again? (y/n): ");
	if (answer == 'Y') {
		// wants to play again
		playLittlePiggy();
	}
	else {
		// say goodbye!
		cout << "\n Thanks for playing, come back soon!" << endl;
	}
}
void resetGame() {
	// reset each player's score to zero
	for (int i = 0; i < numPlayers; i++) {
		playerList[i].setScore(0);
	}
	diceSize = 10; // (rand() % 3 + 3) * 2;
	targetScore = 100; // diceSize * 25;
}
void setPlayers() {
	displayTitle();
	numPlayers = askForNumber("How many players", 2, 6);
	cin.ignore();
	cout << endl;
	// add each player to the vector
	for (int i = 0; i < numPlayers; i++) {
		string playerName = askForString("Please enter a name: ");
		Player newPlayer = Player();
		newPlayer.setName(playerName);
		newPlayer.setScore(0);
		playerList.push_back(newPlayer);
	}
}
/**************************************************
WORKHORSE FUNCTIONS
**************************************************/
string askForString(string question) {
	// gets a line response (spaces included)
	string userInput = "";
	while (userInput == "") {
		cout << " " + question;
		getline(cin, userInput);
	}
	return userInput;
}
char askForLetter(string question) {
	// ask a single letter response question
	char choice = ' ';
	while (choice == ' ') {
		cout << "\n " << question;
		cin >> choice;
	}
	return toupper(choice);
}
int askForNumber(string question, int low, int high) {
	// gets a number
	int num = -99999;
	while (num < low || num > high) {
		cout << "\n " << question << " (" << low << "-" << high << "): ";
		cin >> num;
	}
	return num;
}
void waitForPlayer() {
	cout << "\n ";
	system("pause");
}
/**************************************************
DISPLAY FUNCTIONS
**************************************************/
void displayGameStats() {
	displayTitle();
	// display the results of a roll
	cout << " Score to beat: " << targetScore << "\tDice Size: " << diceSize <<
		endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	for (int i = 0; i < numPlayers; i++) {
		cout << " Player: " << playerList[i].getName();
		cout << "\t\tScore: " << playerList[i].getScore() << endl;
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n ";
}
void displayTitle() {
	system("cls");
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << " Little Piggy :: A Game of Chance\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
void displayText(string myFileName) {
	// local vars
	ifstream blurbData(myFileName);
	string line = "";
	// read in file data
	if (blurbData.is_open()) {
		while (!blurbData.eof()) {
			getline(blurbData, line);
			cout << line << "\n";
		}
		blurbData.close();
	}
	waitForPlayer();
}
  