/*
Project: FIle Read-Writer 1.0
Lab Num: Week 3
Author: Sarah 
Purpose: Driver Class File
Exploring writing data to a file, storing data
 in variables, getting user input, display data
 to the screen, and using functions to structure
 a program.

*/

#include <fstream> // for writing and reading files
#include <string>
#include <iostream>
using namespace std;

//declare varibles and constants here
string textFileName = "";
void displayTitle();
void setFileName();
void writeFile();
void readFile();

int main() {
	//display title
	displayTitle();
	//ask user for the 'write' file name
	setFileName();
	writeFile();
	readFile();
	
}
void displayTitle() {
	cout << "Writing & Reading Data to /from a File";
}

void setFileName() {
	textFileName = "";
	cout << "\n Enter file name (no exit) : ";
	getline(cin, textFileName);
	textFileName += ".txt";
	
}

void writeFile() {
	//writing to a file 
	string myData = "";

	//This allows you to open a file using the name you specified earlier
	//(if a file doesn’t exist it will create one for you).
	ofstream fileToWrite;
	cout << "\n Type what you want then press enter.\n";
	getline(cin, myData); //capture the whole line
	
	fileToWrite.open(textFileName);
	fileToWrite << myData << endl;
	fileToWrite.close();
}

void  readFile() {
	cout << "\n Reading the data in to display.\n ";
	string myData = "";
	
	ifstream fileToRead; //activate the reading process
	fileToRead.open(textFileName);
	getline(fileToRead, myData);
	fileToRead.close();
	cout << myData << "\n\n";
}
