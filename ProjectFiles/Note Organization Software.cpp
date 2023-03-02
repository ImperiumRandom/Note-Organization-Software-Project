// Note Organization Software.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>
#include "SubCatagory.h"
#include <numeric>
#include <sstream>
#include <iterator>



// Phuedo Code

// ToDO:: 1. debug program from main menu to end
       // 2. create file saving system then create file creation function/system - program is then finished

//std::cout << "worked";

//system("pause");

// code setup: 

// symbol for name (-N-) symbol for key (-K-) symbol for value (-V-) symbol for adding finished object from read (-F-) use comma for parsing name and number order will be (name then number (,) )

// return uppercase version of string

std::string stringUpper(std::string &stringToConvert) {

	std::string newString;

	std::vector<std::string>Temp;
	
	// appends new string with upper case letters

	for (int i = 0; i < stringToConvert.size(); i ++) {

		newString.append(1, std::toupper(stringToConvert[i]));

	}

	return newString;

}

// clear input stream

void clearInputStream() {

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
}

// input validation

bool selectAndValidateInt(int &userInput, int minimum, int maximum) {

	std::string stringInteger;
	
	std::getline(std::cin, stringInteger);

	// tests if input is an integer

	if (std::isdigit(stringInteger[0])) {

		int Test = stringInteger[0] - '0';

		if (Test < minimum || Test > maximum) {

			return false;

		}

		else {
		
			userInput = (int)stringInteger[0] - '0';

			return true;
		
		}

	}

	// returns false if not

	else {
	
		return false;
	
	}

} 

bool selectAndValidateString(std::string& userSInput, int minimum, int maximum, std::string equalityCheck) {

	std::string stringInteger;

	std::getline(std::cin, stringInteger);

	// string test cases

	if (stringUpper(stringInteger) == "EXIT") {

		userSInput = stringInteger;

		return true;

	}

	else if (stringUpper(stringInteger) == equalityCheck) {

		userSInput = stringInteger;

		return true;

	}

	// tests if input is an integer

	else if (std::isdigit(stringInteger[0]) ) {

		int Test = stringInteger[0] - '0';

		if (Test < minimum || Test > maximum) {

			return false;

		}

		else {

			userSInput = stringInteger[0];

			return true;

		}

	}

	// returns false if not

	else {

		return false;

	}

}

// parse strings

void extractCertainAmountOfCharactersIntoVector(std::string stringToExtract, std::vector<std::string>&storeSplitString) {

	// temporary string - holds character extracted
	std::string temp;
	
	int counter = 0;

	storeSplitString.clear();

	for (int i = 0; i < stringToExtract.length(); i++) {
		
		
		if (counter == 20) {

			storeSplitString.push_back(temp);

			temp.clear();

			counter = 0;

			i = i - 1; // decrease i iteration by 1 due to extraction not happening

		}
		
		else {

			temp = temp + stringToExtract[i];

			counter ++;

		}


	}

	if (temp.size() > 0) {

		storeSplitString.push_back(temp);

	}

	return;

}

void InsertCharactersIntoVector(std::string newString, std::vector<std::string>& note, int placeForInsertion) {

	std::vector<std::string>newElements;

	extractCertainAmountOfCharactersIntoVector(newString, newElements);

	std::vector<std::string>transition;
	
	for (int i = 0; i < note.size(); i++) {

		
		if (i <= placeForInsertion) {

			continue;

		}

		else if (i > placeForInsertion) {

			transition.push_back(note[i]);

		}


	}

	note.erase(std::next(note.begin(), placeForInsertion - 1), std::next(note.begin(), note.size() - 1));
	

	// places new elements

	for (int i = 0; i < newElements.size(); i++) {

		note.push_back(newElements[i]);

	}


	// replaces old elements

	for (int i = 0; i < transition.size(); i++) {

		note.push_back(transition[i]);

	}

	return;


}

void parseStringForKeyValuePairs(std::string stringToParse, char symbolToFind, int& key, std::string& value) {
	
	// parse string and set key and value

	std::vector<std::string> result;

	std::stringstream parseString(stringToParse);

	while (parseString.good())
	{
		std::string tempString;

		std::getline(parseString, tempString, symbolToFind);

		result.push_back(tempString);

	}

	// stores extracted key and value into referenced variables

	value = result[0];

	key = std::stoi(result[1]);

}

void parseStringForKeyValuePairs(std::string stringToParse, std::string symbolToFind, std::string& key, std::string& value) {




}

// convience functions

void TwoNewLines() {

	std::cout << std::endl << std::endl;


}

std::string NewLine() {

	return "\n";

}

// read and write to files for storage / reload saved data

/*

#pragma warning (push)
#pragma warning (disable : 4703)
void readAndWriteFileWithNotes(std::string fileName, std::vector<SubCatagory> &subCatagories, bool read) {

	const char charSeperatorSymbol = ',';

	// reads file
	
	if (read == true) {

		// pointer object for vector

		SubCatagory* currentObject;

		// variables

		int nameNumber;

		std::string catagoryName;

		bool readingValue = false;

		bool readingName = false;

		bool readingKey = false;

		std::string currentKey;	
		
		// Opens File

		std::fstream myFile(fileName, std::ios::in);

		// String for storeing text from file

		std::string line;

		// while loop for reading file

		bool doOnce = true;

		while (std::getline(myFile, line)) {

			if (doOnce == true) {
				
				line = "-N-";

				doOnce = false;

			}
			
			if (line == "-N-") {

				readingName = true;
				readingKey = false;
				readingValue = false;
				continue;
				
			}

			else if (line == "-K-") {

				readingKey = true;
				readingName = false;
				readingValue = false;
				continue;

			}

			else if (line == "-V-") {

				readingValue = true;
				readingKey = false;
				readingName = false;
				continue;

			}


			if (readingName) {

				currentObject = new SubCatagory();
				currentObject->setCatagoryName(line);

			}


			else if (line == "-F-") {

				subCatagories.push_back(*currentObject);

			}

			else if (readingKey) {

				// parse string and get key and nameNumber
				parseStringForKeyValuePairs(line, charSeperatorSymbol, nameNumber, catagoryName);
				currentObject->Names[nameNumber] = catagoryName;
				currentKey = catagoryName;


			}

			else if (readingValue) {

				currentObject->Notes[currentKey].append(line);

			}



		}



	}

	// writes file

	else if (read == false) {

		const std::string nameSymbol = "-N-";

		const std::string keySymobl = "-K-";

		const std::string valueSymbol = "-V-";

		const std::string finishSymbol = "-F-";

		// opens file for writing

		std::fstream myFile(fileName, std::ios::out);

		for (int i = 0; i < subCatagories.size(); i++) {

			// marker for name

			myFile << nameSymbol << NewLine();

			// stores name

			myFile << subCatagories[i].getCatagoryName() << NewLine();
			
			// iterate through notes (map container) and store them within file

			for (i = 0; i < subCatagories[i].Names.size(); i++) {

				myFile << keySymobl << NewLine();

				std::string tempKey = subCatagories[i].Names[i + 1];

				myFile << tempKey << charSeperatorSymbol << i + 1 << NewLine();

				myFile << valueSymbol << NewLine();

				myFile << subCatagories[i].Notes[tempKey] << NewLine();

			}
			
			// markes finishing of current sub catagory and notes with names

			myFile << finishSymbol << NewLine();

		}

	}

	return;

}
#pragma warning (pop)


*/

// display notes and subcatagories

void displaySubCatagoryNames(std::vector<SubCatagory>&subCatagoryStorage) {

	for (int i = 0; i < subCatagoryStorage.size(); i++) {

		std::cout << i + 1 << ". " << subCatagoryStorage[i].getCatagoryName();

		TwoNewLines();

	}


}

void displayNoteNamesInSubCatagory(std::vector<SubCatagory>&subCatagoryStorage, int subCatagoryIndex) {

	for (int i = 0; i < subCatagoryStorage[subCatagoryIndex].Names.size(); i++) {

		std::cout << i + 1 << ": " << subCatagoryStorage[subCatagoryIndex].Names[i + 1];

		TwoNewLines();

	}

}

// edit note

void editNote(std::vector<SubCatagory>&subCatagoryStorage, int& userInput, int currentSubCatagoryIndex, std::string keyNameForNote) {

	std::string userSInput;

	// user selects whether they would like to edit entire line or edit 1 line in particular
	while (true) {

		system("cls");

		std::cout << "Enter (1) to retype entire note, Enter (2) to select a line and retype it in, Enter (3) to exit back to note selection";

		TwoNewLines();

		std::cout << "User Input: ";

		if (selectAndValidateInt(userInput, 1, 3)) {

			break;

		}

		else {

			system("cls");

			std::cout << "Invalid input please enter a integer of 1 or 2";

		}

	}

	// retype in whole note
	if (userInput == 1) {

		system("cls");

		"please enter note:";

		TwoNewLines();

		std::getline(std::cin,userSInput);

		extractCertainAmountOfCharactersIntoVector(userSInput, subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote]);

		std::cout << "New line has been entered";

		return;

	}

	// edit specific line of note
	else if (userInput == 2) {

		int lineToEdit;
		
		while (true) {

			while (true) {

				for (int i = 0; i < subCatagoryStorage[currentSubCatagoryIndex].Notes.size(); i++) {

					std::cout << "(" << i + 1 << ")  " << subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote][i];

					NewLine();

				}

				TwoNewLines();

				std::cout << "Please select a line to edit";

				if (selectAndValidateInt(userInput, 1, subCatagoryStorage[currentSubCatagoryIndex].Notes.size())) {

					lineToEdit = userInput - 1;

					break;

				}

			}

			system("cls");

			std::cout << "Previous Line: (" << subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote][lineToEdit] << ")\n\n";

			"please enter Changes to line:";

			TwoNewLines();

			std::getline(std::cin, userSInput);

			extractCertainAmountOfCharactersIntoVector(userSInput, subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote]);

			subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote][lineToEdit] = userSInput;

		}

		system("cls");

		"please enter line:";

		TwoNewLines();

		std::getline(std::cin, userSInput);

		InsertCharactersIntoVector(userSInput, subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote], lineToEdit);

		TwoNewLines();

		std::cout << "New line has been entered";

		return;

	}

	// returns back to note selection
	else if (userInput == 3) {

		return;

	}

}

// create note

void createNote(std::vector<SubCatagory>& subCatagoryStorage, int& userInput, int currentSubCatagoryIndex) {

	while (true) {

		system("cls");

		int newPlaceInNames = subCatagoryStorage[currentSubCatagoryIndex].Names.size() + 1;

		std::string KeyForNote;

		std::string userSInput;

		std::cout << ":: Please Enter the Name of Your New Note ::";

		TwoNewLines();

		std::getline(std::cin, userSInput);

		subCatagoryStorage[currentSubCatagoryIndex].Names[newPlaceInNames] = userSInput;

		KeyForNote = userSInput;

		subCatagoryStorage[currentSubCatagoryIndex].Notes[KeyForNote].push_back("None");

		while (true) {

			system("cls");

			std::cout << "Name of Note: " << KeyForNote;

			TwoNewLines();

			std::cout << "(1) Type in Your New Note";

			TwoNewLines();

			std::cout << "(2) Continue Back to Previous Selection";

			TwoNewLines();

			std::cout << "User Input: ";

			if (selectAndValidateInt(userInput, 1, 2)) {

				break;

			}

			else {

				std::cout << "Invalid Input, press any key to try again.";

				TwoNewLines();

				system("pause");

			}

		}

		if (userInput == 1) {

			system("cls");

			std::cout << "Please Enter Your New Note: ";

			TwoNewLines();

			std::getline(std::cin, userSInput);

			extractCertainAmountOfCharactersIntoVector(userSInput, subCatagoryStorage[currentSubCatagoryIndex].Notes[KeyForNote]);

			return;

		}

		else if (userInput == 2) {

			return;

		}



	}





}

// view note

void viewNote(std::vector<std::string>Note) {

	std::string currentPlace;

	int counter = 0;

	for (std::vector<std::string>::iterator it = Note.begin(); it != Note.end(); it ++) {

		if (counter == 3) {

			std::cout << *it + "\n";

			counter = 0;

		}

		else {

			std::cout << *it;

			counter++;

		}

	}

	

}

// edit notes and sub catagories

void editOrViewOrCreateNotes(std::vector<SubCatagory>&subCatagoryStorage, int &userInput, int currentSubCatagoryIndex){

	// string for input

	std::string userSInput;

	// int for note index

	int noteKey;

	std::string keyNameForNote;

	while (true) {

		if (userInput == 0) {

			return;
		}

		while (true) {

			system("cls");

			std::cout << ":: Please Select One of the Folowing Options ::";

			TwoNewLines();

			std::cout << ":: Current Sub Catagory: " << subCatagoryStorage[currentSubCatagoryIndex].getCatagoryName() << " ::";

			TwoNewLines();

			std::cout << "(1) Create Note";

			TwoNewLines();

			if (subCatagoryStorage[currentSubCatagoryIndex].Names.size() > 0) {

				std::cout << "(2) edit an existing note";

				TwoNewLines();

				std::cout << "(3) View a Note";

				TwoNewLines();

			}

			std::cout << "(4) Return to Sub Catagory Selection";

			TwoNewLines();

			std::cout << "(0) Return to Main Menu";

			TwoNewLines();

			std::cout << "User Input: ";

			if (selectAndValidateInt(userInput, 0, 4)) {

				break;

			}

			else {

				std::cout << "Invalid Input, press any key to try again.";

				TwoNewLines();

				system("pause");

			}

		}

		// creates notes

		if (userInput == 1) {

			// create notes 

			createNote(subCatagoryStorage, userInput, currentSubCatagoryIndex);

		}

		// edit existing note

		else if (userInput == 2) {

			while (true) {

				system("cls");

				std::cout << "Please select a note to edit, or enter (EXIT) to go back";

				TwoNewLines();

				displayNoteNamesInSubCatagory(subCatagoryStorage, currentSubCatagoryIndex);

				std::cout << "User Input: ";

				if (selectAndValidateString(userSInput, 1, subCatagoryStorage[currentSubCatagoryIndex].Notes.size(), "EXIT")) {

					// index for vector of map names and then note -- check it later

					break;

				}

			}

			if (stringUpper(userSInput) == "EXIT") {

				return;

			}

			else {

				noteKey = std::stoi(userSInput);

				keyNameForNote = subCatagoryStorage[currentSubCatagoryIndex].Names[noteKey];

				editNote(subCatagoryStorage, userInput, currentSubCatagoryIndex, keyNameForNote);

			}


		}

		// view a note

		else if (userInput == 3) {

			while (true) {

				system("cls");

				std::cout << ":: Please Select which Note you Would Like to Read. ::";

				TwoNewLines();

				displayNoteNamesInSubCatagory(subCatagoryStorage, currentSubCatagoryIndex);

				TwoNewLines();

				std::cout << "User Input: ";

				if (selectAndValidateInt(userInput, 1, subCatagoryStorage[currentSubCatagoryIndex].Names.size())) {	

					break;

				}

				else {

					std::cout << "Invalid Input, press any key to try again.";

					TwoNewLines();

					system("pause");

				}

			}
			
			while (true) {

				system("cls");

				std::cout << ":: Catagory Name: " << subCatagoryStorage[currentSubCatagoryIndex].getCatagoryName() << " ::";

				std::string noteKey = subCatagoryStorage[currentSubCatagoryIndex].Names[userInput];

				TwoNewLines();

				std::cout << ":: Note Name: " << noteKey << " ::";

				TwoNewLines();
				
				viewNote(subCatagoryStorage[currentSubCatagoryIndex].Notes[noteKey]);

				TwoNewLines();

				std::cout << "(1) Go Back";

				TwoNewLines();

				std::cout << "(0) Return to Main Menu";

				TwoNewLines();

				std::cout << "User Input: ";

				if (selectAndValidateInt(userInput, 0, 1)) {

					break;

				}

				if (userInput == 1) {

					continue;

				}

				else if (userInput == 0) {

					userInput = 0;

					return;


				}

			}

		}

		// return to sub catagory selection

		else if (userInput == 4) {

			userInput = 4;
			
			return;

		}

		// return to main menu

		else if (userInput == 0) {

			userInput = 0;
			
			return;
					
		}

	}


}

void createSubCatagory(std::vector<SubCatagory>& subCatagoryStorage, int& userInput) {

	std::string subCatagoryName;

	int subCatagoryIndex;

	while (true) {

		while (true) {

			system("cls");

			std::cout << ":: Please Enter the Name of Your New Sub Catagory ::";

			TwoNewLines();

			std::cout << "User Input: ";

			std::getline(std::cin, subCatagoryName);

			subCatagoryStorage.push_back(*new SubCatagory(subCatagoryName));

			subCatagoryIndex = subCatagoryStorage.size() - 1;

			editOrViewOrCreateNotes(subCatagoryStorage, userInput, subCatagoryIndex);

			if (userInput == 3 || userInput == 0 || userInput == 4) {

				return;

			}

			else {

				while (true) {

					system("cls");

					std::cout << "Enter (1) to create a new SubCatagory, Enter (2) to go back";

					TwoNewLines();

					std::cout << "User Input: ";

					if (selectAndValidateInt(userInput, 1, 2)) {

						break;

					}

					else {

						std::cout << "Invalid Input, press any key to try again.";

						TwoNewLines();

						system("pause");

					}


				}


				if (userInput == 2) {

					return;

				}

				else if (userInput == 1) {

					continue;

				}


			}

		}

	}

}

void chooseOrCreateSubCatagory(std::vector<SubCatagory>& subCatagoryStorage, int &userInput) {

	std::string userSInput;

	int minimumSubCatagorySpace = 0;

	while (true) {
		
		while (true) {

			if (subCatagoryStorage.size() > 0) {

				minimumSubCatagorySpace = 1;

			}

			system("cls");

			if (subCatagoryStorage.size() == 0) {

				std::cout << ":: Type (NEW) to Create a New Sub Catagory, or Type (EXIT) to Exit to Main Menu. ::";

			}

			else {

				std::cout << ":: Please Select a Number for one of the Sub Catagories, or Type (NEW) to Create a New Sub Catagory, or Type (EXIT) to Exit to Main Menu. ::";

			}

			TwoNewLines();

			displaySubCatagoryNames(subCatagoryStorage);

			std::cout << "User Input: ";

			if (selectAndValidateString(userSInput, minimumSubCatagorySpace, subCatagoryStorage.size(), "NEW")) {

				if (std::isdigit(userSInput[0])) {

					if (std::stoi(userSInput) == 0) {

						std::cout << "Invalid Input, press any key to try again.";

						TwoNewLines();

						system("pause");

						continue;

					}

					else {

						break;

					}

				}

				else {

					break;

				}
				
			}

			else {

				std::cout << "Invalid Input, press any key to try again.";

				TwoNewLines();

				system("pause");

			}


		}


		if (stringUpper(userSInput) == "NEW") {

			createSubCatagory(subCatagoryStorage, userInput);

		}

		else if (stringUpper(userSInput) == "EXIT") {

			return;

		}

		else {

			int subCatagoryIndex = std::stoi(userSInput) - 1;
			editOrViewOrCreateNotes(subCatagoryStorage, userInput, subCatagoryIndex);

		}


		if (userInput == 0) {

			return;

		}


	}

}

// main menu

void menu(int &userInput, std::vector<SubCatagory>& subCatagoryStorage) {

	if (userInput == 4) {

		chooseOrCreateSubCatagory(subCatagoryStorage, userInput);

	}


	while (true) {

		system("cls");

		// Introduction
		
		std::cout << ":: Notepad Program ::";

		TwoNewLines();

		std::cout << ":: Please select one of the options below! ::";

		TwoNewLines();

		// Options
		
		std::cout << "(1) View and Choose Sub Catagory";

		std::cout << "\n";

		std::cout << "(2) Exit Program";

		TwoNewLines();

		std::cout << "User Input: ";

		if (selectAndValidateInt(userInput, 1, 2)) {

			break;

		}

		else {

			std::cout << "Invalid Input, press any key to try again.";

			TwoNewLines();

			system("pause");
	
		}



	}

	return;

}

// main program function

int main()
{
	// text file names for notes

	std::vector<std::string> noteSaveFiles;

	noteSaveFiles.push_back("Notes.txt");

	// create and close file

	std::fstream myFile("Notes.txt", std::ios::out);
	
	if (myFile.is_open()) {
	
		myFile.close();
	
	}
	
	// vector of SubCatagorys

	std::vector<SubCatagory>subCatagoryStorage;

	// add test note
	/*
	
	subCatagoryStorage.push_back(*new SubCatagory);

	subCatagoryStorage[0].setCatagoryName("Test Catagory");

	subCatagoryStorage[0].Names[1] = "Test Name";

	subCatagoryStorage[0].Notes["Test Name"].push_back("hi there im a test note");

	*/

	// -----------------------------------------------------------------------------

	// reload saved data

	// readAndWriteFileWithNotes(notesTxtFileName, subCatagoryStorage, true);

	// -----------------------------------------------------------------------------

	// variable for selection input

	int userInput = 0;

	// main Program ----------------------------------------------------------------
	
	while (true) {

		// main menu

		menu(userInput, subCatagoryStorage);

		// create or edit sub catagory
		
		if (userInput == 1) {

			chooseOrCreateSubCatagory(subCatagoryStorage, userInput);

		}

		// exit program

		else if (userInput == 2) {

			return 0;

		}

	}
	


}

