/*****
Project: String Analyser 01
Lab number: week2 
Author: Sarah Yeung
Purpose: Driver Class File
Using string function ro manipulate and find 
elements within a string. To create basic objects and
run functions on objects.

***/


#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//declaring functions
//define the functions--having a body
void displayTitle();
void stringAnalyser();
void runMenu();

int main() {
	// display the title
	displayTitle();
	// read the text in the file
	runMenu();
	// get user input for analysis
	stringAnalyser();
	// wait and exit
	system("pause");
	return 0;

}
//defining function 
void displayTitle() {
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout << "\tManipulating String Objects\n";
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";

}

void stringAnalyser() {
	// declare and initialise local variables
	string userString="";
	char userChar = ' ';
	cout << " Welcome to the string analyser \n\n";
	cout << " What is your word? ";
	cin >> userString;
	cout << " What character are you looking for?";
	cin >> userChar;
	cout << endl;
	//display results of string analysis
	cout << " The string you enter was " << userString <<endl;
	cout << " It has " << userString.length() << " characters\n\n";
	cout << " It has been allocated " << userString.capacity() << " bytes in memory\n";
	cout << " The first letter of your string is " << userString[0]<<endl;
	cout << " The last letter of your string is " << userString[userString.length() - 1] << endl;

	// if the result is really big the character was not found
	if (userString.find(userChar) < userString.length()) {
		cout << " The search character is found at " << userString.find(userChar) << endl;
	}
	else { 
		cout << " The search character is not found " << endl;
	}


}

void runMenu() {
	vector<string>quotes;
	int count;
	string data;

	ifstream myfile("Text.txt");
	while (getline(myfile, data)) {
		if (data.size() > 0) {
			quotes.push_back(data);
		}
	}
	cout << quotes[2];
}



