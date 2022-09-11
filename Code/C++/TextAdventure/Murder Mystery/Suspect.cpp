#include "Suspect.h"
Suspect::Suspect(){}
Suspect::Suspect(string newName, CharacterType type, string location, string details) {
	suspectName = new string(newName);
	suspectType = new CharacterType(type);
	suspectLocation = new string(location);
	suspectDetails = new string(details);

}
Suspect::~Suspect() {
	delete suspectName;
	delete suspectType;
	delete suspectLocation;
	delete suspectDetails;
}

string Suspect::getSuspectName() { return *suspectName; }

string Suspect::getSuspectLocation() { return *suspectLocation; }
string Suspect::getSuspectDetails() { return *suspectDetails; }

string Suspect::getSuspectType() {
	switch (*suspectType) {
	case VICTIM:
		return "Victim";
	case MURDER:
		return "Murder";
	case INNOCIENT:
		return "Innocient";
	default:
		return "Nothing";
	}
}

void Suspect::setSuspectName(string newName) {
	*suspectName = newName;
}
void Suspect::setSuspectLocation(string location) {
	*suspectLocation = location;
}
void Suspect::setSuspectDetails(string details) {
	*suspectDetails = details;
}
void Suspect::setSuspectType(CharacterType newType) {
	if (newType > NOTHING && newType <= INNOCIENT) {
		*suspectType = newType;
	}
}