#ifndef SUSPECT_H
#define SUSPECT_H
#include <iostream>
#include <sstream>
#include <string>
#include "Enums.h"
using namespace std;

class Suspect {
private:
	string* suspectName;
	CharacterType* suspectType;
	string* suspectLocation;
	string* suspectDetails;

public:
	Suspect();
	Suspect(string newName, CharacterType type, string location, string details);
	~Suspect();

	string getSuspectName();
	string getSuspectType();
	string getSuspectDetails();
	string getSuspectLocation();

	void setSuspectName(string newName);
	void setSuspectType(CharacterType newType);
	void setSuspectLocation(string location);
	void setSuspectDetails(string details);

};
#endif