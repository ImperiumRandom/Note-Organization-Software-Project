#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>

class SubCatagory
{

private:

	// catagory name
	std::string catagoryName;

	// this will contain all the notes for this sub catagory
	//std::map < std::string, std::string > mapOfNotes;

public:

	// notes the name of the note will be the key, and the note will be the value

	std::map<std::string, std::vector<std::string>>Notes;

	// notes number and names can be iterated through for keys (note this will start at 1 so iterate while equal to size)
	
	std::map<int, std::string>Names;

	// constructor

	SubCatagory();
	
	SubCatagory(std::string catagoryName);

	// setters

	void setCatagoryName(std::string newCatagoryName);

	// getters

	std::string getANote(std::string NoteName);

	std::string getCatagoryName();

	std::string returnCatagoryName(int NumberForName);


};

