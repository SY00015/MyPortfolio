#include "TextAdventure.h"
/*
Project: Murder Mystery
Author: Sarah Yeung
Purpose: Application Class File
*/


int main(){
	mapCreated = false;
	clearTextFile();
	displayTitle();
    displayRules();
	
	setLocations();
	
	setSuspects();
	
	setPlayers();
	
	addItems();
	
	createMap();
	
	cout << " Type 'HELP' to see the command keys and rules to win" << endl;
	playGame();
	gameOver();
	waitForPlayer();
	return 0;
}

void displayTitle() {
	cout << R"(
             __  __               _             __  __           _                  
     /\     |  \/  |             | |           |  \/  |         | |                 
    /  \    | \  / |_   _ _ __ __| | ___ _ __  | \  / |_   _ ___| |_ ___ _ __ _   _ 
   / /\ \   | |\/| | | | | ___/ _  |/ _ | ___| | |\/| | | | | __| __/ _ | ___| | | |
  / ____ \  | |  | | |_| | | | (_| |  __| |    | |  | | |_| \__ | ||  __| |  | |_| |
 /_/    \_\ |_|  |_|\____|_|  \____|\___|_|    |_|  |_|\___ |___/\__\___|_|   \___ |
                                                        __/ |                  __/ |
                                                       |___/                  |___/
)" << '\n';
	waitForPlayer();
}

void displayRules() {
	system("CLS");
	ReadFromFile("MurderMystery.txt");
	waitForPlayer();
}
void waitForPlayer() {
	cout << "\n ";
	system("pause");
}
void playGame() {
	bool isGameOver = false;
	
	while (!isGameOver) {
		string input;
		string input2 = "";
		string input3;
		string input4 = "";
		string input5;
		string input6 = "";
		string input7;

		
		cout << " What do you want to do? ";
		cin >> input, input2;
		getline(cin, input2);
		input2.erase(remove(input2.begin(), input2.end(), ' '), input2.end());
		if (input == "MAP") {
			displayMap();
			playGame();
		}
		if (input == "GO") {
			bool locationFound = false;
			int x = 0;
			for (int i = 0; i < 11; i++) {
				if (checkName(Locations[i], input2)){
					locationFound = true;
					playerList[0].updateLocation(Locations[i]);
					cout << " You are now at the " << playerList[0].getLocation() << endl;
					cout << " " << Attributes[i] << endl;
					if (Locations[i] == crimeScene[0]) {
						cout << " You found bloodstains on the floor." << endl;

					}
				}
			}for (unsigned int index = 0; index < suspectList.size(); index++) {
				if (suspectList[index]->getSuspectLocation() == input2) {
					if (suspectList[index]->getSuspectType() == "Victim") {
						cout << " You found the body of " << suspectList[index]->getSuspectName() << ". " << suspectList[index]->getSuspectName() << " is dead" << endl;
						cout << " " << suspectList[index]->getSuspectDetails() << endl;
						x++;
					}
					if (suspectList[index]->getSuspectType() != "Victim") {
						cout << " You saw " << suspectList[index]->getSuspectName() << endl;
						cout << " " << suspectList[index]->getSuspectDetails() << endl;
						x++;
					}

				}
			}
			if (locationFound == false ) { cout << " --Location Not Found-- " << endl; }
			//invalid users' input
			if (locationFound == true && x == 0) { cout << " You saw no one." << endl; }


			playGame();
		}
		if (input == "SEARCH") {
			bool locationFound = false;
			int x = 0;
			for (int i = 0; i < 11; i++) {
				
				if (checkName(Locations[i], input2)) {
					locationFound = true;
					cout << " You searched the " << Locations[i] << endl;

					for (unsigned int index = 0; index < gameItems.size(); index++) {
						if (gameItems[index]->getItemLocation() == Locations[i]) {
							cout << " You found a " << gameItems[index]->getItemName() << endl;
							x++;
						}
					}
				}
			}
			if (x == 0 && locationFound==true) { cout << " You found nothing." << endl; }
			//invalid users' input
			if (x == 0 && locationFound == false) { cout << " --Location Not Found-- " << endl; }

			playGame();
		}
		if (input == "E") {
			bool ItemFound = false;
			cout << " You examined the " << input2 << endl;
			for (unsigned int index = 0; index < gameItems.size(); index++) {
				if (checkName(gameItems[index]->getItemName(), input2)) {
					if (gameItems[index]->getTypeName() == "Weapon") {

						cout << " You found bloodstains on the " << gameItems[index]->getItemName() << "." << endl;
					}
					if (gameItems[index]->getTypeName() == "None") {
						cout << " You found nothing." << endl;
					}
					ItemFound = true;
				}
				
			}
			if (ItemFound!=true){
				cout << " --Item Not Found-- " << endl;
			}
			playGame();
		}
		if (input == "G") {
			for (unsigned int index = 0; index < gameItems.size(); index++) {
				if (gameItems[index]->getItemName() == input2) {
					Inv.push_back(input2);
					cout << " You pick up the " << input2 << endl;

				}
			}
			playGame();
		}
		if (input == "O") {
			cout << "You have ";
			for (int i = 0; i < Inv.size(); i++) {
				cout << Inv[i] << ", ";
			}
		}
		if (input == "D") {
			for (int i = 0; i < Inv.size(); i++) {
				if (Inv[i] == input2) {
					remove(Inv.begin(), Inv.end(), Inv[i]);
					cout << "You drop the" << Inv[i] << endl;
				}

			}
		}

		if (input == "Q") {
			int x = 0;
			for (unsigned int index = 0; index < suspectList.size(); index++) {
				if (suspectList[index]->getSuspectName() == input2) {

					if (suspectList[index]->getSuspectType() == "Innocient") {
						cout << " You questioned " << input2 << endl;
						if (suspectList[index]->getSuspectName() == pair1[0]) {
							cout << " " << suspectList[index]->getSuspectName() << ": I was with " << pair1[1] << endl;
							x++;
						}
						if (suspectList[index]->getSuspectName() == pair1[1]) {
							cout << " " << suspectList[index]->getSuspectName() << ": I was with " << pair1[0] << endl;
							x++;
						}
						if (suspectList[index]->getSuspectName() == pair2[0]) {
							cout << " " << suspectList[index]->getSuspectName() << ": I was with " << pair2[1] << endl;
							x++;
						}
						if (suspectList[index]->getSuspectName() == pair2[1]) {
							cout << " " << suspectList[index]->getSuspectName() << ": I was with " << pair2[0] << endl;
							x++;
						}
						if (x == 0) {
							cout << " " << suspectList[index]->getSuspectName() << ": I was alone at that time" << endl;
						}

					}
					if (suspectList[index]->getSuspectType() == "Murder") {
						cout << " You questioned " << input2 << endl;
						cout << " " << suspectList[index]->getSuspectName() << ": I was with " << randName[0] << endl;
						x++;
					}
					if (suspectList[index]->getSuspectType() == "Victim") {
						cout << " The victim is dead, you can not question the victim" << endl;
						x++;
					}

				}
			}
			playGame();
		}
		if (input == "GATHER") {
			
			cout << " You gathered the group." << endl;
			cout << " You said you have solve the case. The crime scene happened at the ";
			cin >> input3;
			if (input3 == crimeScene[0]) {
				cout << " Yes, you are right " << endl;
				
				cout << " What is the weapon? ([U] Weapon) ";
				cin >> input4, input5;
				getline(cin, input5);
				input5.erase(remove(input5.begin(), input5.end(), ' '), input5.end());
				if (input4 == "U") {
					cout << " You pulled out the " << input5 << endl;

					for (unsigned int index = 0; index < gameItems.size(); index++) {

						if (gameItems[index]->getItemName() == input5) {

							if (gameItems[index]->getTypeName() == "Weapon") {
								
								cout << " Accuse the murderer! ([A] Murderer) ";
								cin >> input6, input7;
								getline(cin, input7);
								input7.erase(remove(input7.begin(), input7.end(), ' '), input7.end());
								if (input6 == "A") {
									for (int j = 0; j < suspectList.size(); j++) {
										if (suspectList[j]->getSuspectName() == input7) {
											if (suspectList[j]->getSuspectType() == "Murder") {
												
												cout << " " << suspectList[j]->getSuspectName() << " , you are the murderer!" << endl;
												cout << " Congratulation, You solve the murder case!" << endl;
												for (int i = 0; i < 3; i++) {
													y++;
												}
												isGameOver = checkGameOver();

											}
										}
									}
								}
							}
							else {
								cout << "Err...It seems that" << input5 << " is not the weapon." << endl;
								cout << " The suspects are dismissed" << endl;
								playGame();
							}

						}
					}
				}
			}
		}
		if (input == "HELP") {

			ReadFromFile("Rules.txt");
			playGame();
		}

		if (input == "QUIT") {
			for (int i = 0; i < 3; i++) {
				y++;
			}
			isGameOver = checkGameOver();

		}

		else {
			playGame();
		}
	}
	isGameOver = checkGameOver();
	if (isGameOver) {
		clearTextFile();
		gameOver();
		waitForPlayer();
		exit(0);
	}
}

bool checkGameOver() {
		if (y==3) {
			return true;
		}
		
		else {
			return false;
		}
	}

bool checkName(string name, string userInput)	
{
	//convert user inputs to lowercaseand allow the program to identify user input in both lowercaseand uppercase
	if (name.length() == userInput.length()) {
		for (int i = 0; i < name.length(); i++) {
			if (tolower(name[i]) != towlower(userInput[i])) {
				return false;
			}


		}
		return true;
	}
	else {
		return false;
	}
}

void gameOver() {
	string line = "\n\t+---------+----------+----------+----------+";
	cout << line << endl;
	cout << "\n\tThanks for playing. See you. " << endl;
	cout << line << endl;
	cout << endl;

}


void setLocations() {
	ifstream myfile("Locations.txt");
	while (getline(myfile, mydata)) {
		if (mydata.size() > 0) {
			Locations.push_back(mydata);

		}

	}
	myfile.close();

	ifstream fileToRead;
	fileToRead.open("Attributes.txt");
	while (getline(fileToRead, mydata)) {
		if (mydata.size() > 0) {
			Attributes.push_back(mydata);

		}

	}
	fileToRead.close();

	fileToRead.close();
	for (int i = 0; i < 7; i++) {
		srand(unsigned(time(NULL)));
		int secretNum = rand() % 18 + 1;
		vector<string>::iterator new_end, new_end2;

		remove(Locations.begin(), Locations.end(), Locations[secretNum]);
		remove(Attributes.begin(), Attributes.end(), Attributes[secretNum]);
	}
	int secretNum = rand() % 10+1;
	crimeScene.push_back(Locations[secretNum]);

}

void setPlayers() {
	system("CLS");
	string name = askForString("What is your name? ");
	Player newPlayer = Player();
	newPlayer.setName(name);
	srand(unsigned(time(NULL)));
	int secretNum = rand() % 11;
	newPlayer.setLocation(Locations[secretNum]);
	newPlayer.addInventory(" You have nothing");
	playerList.push_back(newPlayer);
	

}

void createMap() {

	vector<string> map;
	cout << " You are now at " << playerList[0].getLocation()<<endl;
	for (int i = 0; i < 11; i++) {
		map.push_back(Locations[i]);
	}
	random_shuffle(map.begin(), map.end());
	ofstream fileToWrite("Map.txt", ios::app);
	if (fileToWrite.is_open()) {
		string line = "\n\t+---------+----------+----------+----------+";
		string line2 = "\n\t|         |          |          |          |";
		cout << line;
		fileToWrite << line ;
		cout << line2;
		fileToWrite << line2;
		cout << "\n\t| " << map[0] << "     " << map[1] << "     " << map[2] << "     " << map[3];
		fileToWrite << "\n\t| " << map[0] << "     " << map[1] << "     " << map[2] << "     " << map[3] ;
		cout << line2;
		fileToWrite << line2 ;
		cout << line;
		fileToWrite << line ;
		cout << line2;
		fileToWrite << line2 ;
		cout << "\n\t| " << map[4] << "     " << map[5] << "     " << map[6] << "     " << map[7];
		fileToWrite << "\n\t| " << map[4] << "     " << map[5] << "     " << map[6] << "     " << map[7] ;
		cout << line2;
		fileToWrite << line2 ;

		cout << line;
		fileToWrite << line;
		cout << line2;
		fileToWrite << line2 ;
		cout << "\n\t| " << map[8] << "     " << map[9] << "     " << map[10];
		fileToWrite << "\n\t| " << map[8] << "     " << map[9] << "     " << map[10] ;
		cout << line2;
		fileToWrite << line2 ;
		cout << line << endl;
		fileToWrite << line ;
		}
		fileToWrite.close();

	
}

void displayMap(){
	ReadFromFile("Map.txt");


}

void addItems() {

	ifstream fileToRead;
	fileToRead.open("Items.txt");
	while (getline(fileToRead, mydata)) {
		if (mydata.size()>0)  {
			Items.push_back(mydata);
		}
			
	}
	fileToRead.close();

	for (int i = 0; i < 6; i++) {
		srand(unsigned(time(NULL)));
		int secretNum = rand() % 10+1;
		vector<string>::iterator new_end;
		new_end = remove(Items.begin(), Items.end(), Items[secretNum]);

	}

	


	int secretNum = rand() % 5;
	int secretNum2 = rand() % 10+ 1;
	gameItems.clear();

	gameItems.push_back(new Item(Items[secretNum], WEAPON, Locations[secretNum2]));
	for (int i = 0; i <4; i++) {
		if (Items[i] !=Items[secretNum]){
			int secretNum2 = rand() % 10+ 1;
			gameItems.push_back(new Item(Items[i], NONE, Locations[secretNum2]));
		}
	}
	
}
void clearTextFile()
{
	std::ofstream ofs;
	ofs.open("Map.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}
void setSuspects() {
	ifstream fileToRead;
	fileToRead.open("Suspects.txt");
	while (getline(fileToRead, mydata)) {
		if (mydata.size() > 0) {
			characters.push_back(mydata);
		}

	}
	fileToRead.close();

	ifstream myfile("Descriptions.txt");
	while (getline(myfile, mydata)) {
		if (mydata.size() > 0) {
			descriptions.push_back(mydata);
		}
	}
	myfile.close();
	srand(unsigned(time(NULL)));
	int secretNum = rand() % 7;
	int secretNum2 = rand() % 11;
	suspectList.clear();
	suspectList.push_back(new Suspect(characters[secretNum],VICTIM, Locations[secretNum2],descriptions[secretNum]));
	remove(characters.begin(), characters.end(), characters[secretNum]);
	remove(descriptions.begin(), descriptions.end(), descriptions[secretNum]);
	
	int secretNum3 = rand() % 5;
	int secretNum4 = rand() % 11;
	suspectList.push_back(new Suspect(characters[secretNum3], MURDER, Locations[secretNum4], descriptions[secretNum3]));
	
	remove(characters.begin(), characters.end(), characters[secretNum3]);
	remove(descriptions.begin(), descriptions.end(), descriptions[secretNum3]);
	
	for (int i = 0; i < 5; i++) {	
		int secretNum5 = rand() % 11;
		suspectList.push_back(new Suspect(characters[i], INNOCIENT, Locations[secretNum5], descriptions[i]));
	}
	
	vector <string> copy;
	for (int i = 0; i < 5; i++) {
		copy.push_back(characters[i]);
	}
	random_shuffle(copy.begin(), copy.end());
	pair1.push_back(copy[0]);
	pair1.push_back(copy[1]);
	pair2.push_back(copy[2]);
	pair2.push_back(copy[3]);
	
	int secretNum6 = rand() % 6;
		randName.push_back(characters[secretNum6]);
	
}

void ReadFromFile(string name)
{
	ifstream fileToRead;
	fileToRead.open(name);
	while (getline(fileToRead, mydata)) {
		cout << mydata << endl;
	}
	fileToRead.close();
	
}


string askForString(string question) {
	string userInput = "";
	while (userInput == "") {
		cout << " " + question;
		getline(cin, userInput);
	}
	return userInput;

}