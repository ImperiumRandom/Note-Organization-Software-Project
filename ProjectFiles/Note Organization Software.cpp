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

// ToDO:: 1. figure out why insert characters into vector isn't working, then do a final cleanup before merge then file implementation
       // 2. create file saving system then create file creation function/system - program is then finished

//std::cout << "worked";

//system("pause");

// code setup: 

// symbol for name (-N-) symbol for key (-K-) symbol for value (-V-) symbol for adding finished object from read (-F-) use comma for parsing name and number order will be (name then number (,) )





// global enum for selections

enum functionCall { ViewAndChooseSubCatagory, ExitProgram, MainMenu, CreateSubcatagory, EditOrViewOrCreateNote, ViewNote, CreateNote, EditNote};

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
		
		if (i == placeForInsertion) {

			for (int i = 0; i < newElements.size(); i++) {

				transition.push_back(newElements[i]);

			}

		}

		else {

			transition.push_back(note[i]);

		}

	}

	note = transition;

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

void NewLines(int ammountOfNewLines) {

	for (int i = 0; i < ammountOfNewLines; i++) {

		std::cout << std::endl;

	}

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

		NewLines(2);

	}

}

void displayNoteNamesInSubCatagory(std::vector<SubCatagory>&subCatagoryStorage, int &subCatagoryIndex) {

	for (int i = 0; i < subCatagoryStorage[subCatagoryIndex].Names.size(); i++) {

		std::cout << i + 1 << ": " << subCatagoryStorage[subCatagoryIndex].Names[i + 1];

		NewLines(2);

	}

}

// edit note

void editNote(functionCall& choice, std::vector<SubCatagory>&subCatagoryStorage, int &currentSubCatagoryIndex, std::string &keyNameForNote) {

	// user string input	

	std::string userSInput;

	// user int input

	int userInput;

	// selection

	while (true) {

		system("cls");

		std::cout << ":: Enter (1) to retype entire note, Enter (2) to select a line and retype it in, Enter (3) to exit back to note selection ::";

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

		std::cout << ":: Please enter note: ::";

		NewLines(2);

		std::cout << "User Input: ";

		std::getline(std::cin,userSInput);

		extractCertainAmountOfCharactersIntoVector(userSInput, subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote]);

		NewLines(2);

		std::cout << ":: New Note has been Entered, Please press any key to continue. ::";

		NewLines(2);

		system("pause");

		choice = EditOrViewOrCreateNote;

		return;

	}

	// edit specific line of note

	else if (userInput == 2) {

		int lineToEdit;
		
		while (true) {


			system("cls");

			for (int i = 0; i < subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote].size(); i++) {

				std::cout << "(" << i + 1 << ")  " << subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote][i];

				TwoNewLines();

			}

			std::cout << "Please select a line to edit";

			TwoNewLines();

			std::cout << "User Input: ";	

			if (selectAndValidateInt(userInput, 1, subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote].size())) {	

			    lineToEdit = userInput - 1;		

				break;		

			}

			else {

				std::cout << "Invalid Input, press any key to try again.";

				TwoNewLines();

				system("pause");

			}

		}



		system("cls");

		std::cout << ":: Please enter line. ::";

		TwoNewLines();

		std::cout << "User Input: ";

		std::getline(std::cin, userSInput);

		InsertCharactersIntoVector(userSInput, subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote], lineToEdit);

		TwoNewLines();

		system("cls");

		std::cout << "New line has been entered";

		system("pause");

		choice = EditOrViewOrCreateNote;

		return;

	}

}

// create note

void createNote(functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, int &currentSubCatagoryIndex) {

	int userInput;

	while (true) {

		system("cls");

		int newPlaceInNames = subCatagoryStorage[currentSubCatagoryIndex].Names.size() + 1;

		std::string KeyForNote;

		std::string userSInput;

		std::cout << ":: Please Enter the Name of Your New Note ::";

		NewLines(2);

		std::getline(std::cin, userSInput);

		subCatagoryStorage[currentSubCatagoryIndex].Names[newPlaceInNames] = userSInput;

		KeyForNote = userSInput;

		subCatagoryStorage[currentSubCatagoryIndex].Notes[KeyForNote].push_back("None");

		// selection

		while (true) {

			system("cls");

			std::cout << "Name of Note: " << KeyForNote;

			NewLines(2);

			std::cout << "(1) Type in Your New Note";

			NewLines(2);

			std::cout << "(2) Continue Back to Previous Selection";

			NewLines(2);

			std::cout << "User Input: ";

			if (selectAndValidateInt(userInput, 1, 2)) {

				break;

			}

			else {

				std::cout << "Invalid Input, press any key to try again.";

				NewLines(2);

				system("pause");

			}

		}

		// type in new note
		
		if (userInput == 1) {

			system("cls");

			std::cout << "Please Enter Your New Note: ";

			NewLines(2);

			std::getline(std::cin, userSInput);

			extractCertainAmountOfCharactersIntoVector(userSInput, subCatagoryStorage[currentSubCatagoryIndex].Notes[KeyForNote]);

			choice = EditOrViewOrCreateNote;

			return;

		}

		// go back to edit view or create note

		else if (userInput == 2) {

			choice = EditOrViewOrCreateNote;

			return;

		}

	}

}

// view note

void viewNote(functionCall& choice, std::vector<std::string>Note) {

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

void editOrViewOrCreateNotes(functionCall& choice, std::vector<SubCatagory>&subCatagoryStorage, int &currentSubCatagoryIndex, std::string &keyNameForNote){

	// string for input

	std::string userSInput;

	// int for input

	int userInput;

	// int for note index

	int noteKey;



	// selection

	while (true) {

			system("cls");

			std::cout << ":: Please Select One of the Folowing Options ::";

			NewLines(2);

			std::cout << ":: Current Sub Catagory: " << subCatagoryStorage[currentSubCatagoryIndex].getCatagoryName() << " ::";

			NewLines(2);

			std::cout << "(1) Create Note";

			NewLines(2);

			if (subCatagoryStorage[currentSubCatagoryIndex].Names.size() > 0) {

				std::cout << "(2) edit an existing note";

				NewLines(2);

				std::cout << "(3) View a Note";

				NewLines(2);

			}

			std::cout << "(4) Return to Sub Catagory Selection";

			NewLines(2);

			std::cout << "(0) Return to Main Menu";

			NewLines(2);;

			std::cout << "User Input: ";

			if (selectAndValidateInt(userInput, 0, 4)) {

				break;

			}

			else {

				std::cout << "Invalid Input, press any key to try again.";

				NewLines(2);

				system("pause");

			}

		}

	// creates notes

	if (userInput == 1) {

			// create notes 

			choice = CreateNote;

			return;

		}

	// edit existing note

	else if (userInput == 2) {

			while (true) {

				system("cls");

				std::cout << ":: Please select a note to edit, or enter (EXIT) to go back ::";

				NewLines(2);

				displayNoteNamesInSubCatagory(subCatagoryStorage, currentSubCatagoryIndex);

				std::cout << "User Input: ";

				if (selectAndValidateString(userSInput, 1, subCatagoryStorage[currentSubCatagoryIndex].Notes.size(), "EXIT")) {

					// index for vector of map names and then note -- check it later

					break;

				}

			}

			if (stringUpper(userSInput) == "EXIT") {

				choice = EditOrViewOrCreateNote;

				return;

			}

			else {

				noteKey = std::stoi(userSInput);

				keyNameForNote = subCatagoryStorage[currentSubCatagoryIndex].Names[noteKey];

				choice = EditNote;

				return;

			}


		}

	// view a note

	else if (userInput == 3) {

			while (true) {

				system("cls");

				std::cout << ":: Please Select which Note you Would Like to Read. ::";

				NewLines(2);

				displayNoteNamesInSubCatagory(subCatagoryStorage, currentSubCatagoryIndex);

				std::cout << "User Input: ";

				if (selectAndValidateInt(userInput, 1, subCatagoryStorage[currentSubCatagoryIndex].Names.size())) {	

					break;

				}

				else {

					std::cout << "Invalid Input, press any key to try again.";

					NewLines(2);

					system("pause");

				}

			}
			
			while (true) {

				system("cls");

				std::cout << ":: Catagory Name: " << subCatagoryStorage[currentSubCatagoryIndex].getCatagoryName() << " ::";

				std::string noteKey = subCatagoryStorage[currentSubCatagoryIndex].Names[userInput];

				NewLines(2);

				std::cout << ":: Note Name: " << noteKey << " ::";

				NewLines(3);

				std::cout << "------------------------------";
				
				NewLines(2);
				
				viewNote(choice, subCatagoryStorage[currentSubCatagoryIndex].Notes[noteKey]);

				NewLines(2);
				
				std::cout << "------------------------------";

				NewLines(2);

				NewLines(2);

				std::cout << "(1) Go Back";

				NewLines(2);

				std::cout << "(0) Return to Main Menu";

				NewLines(2);

				std::cout << "User Input: ";

				if (selectAndValidateInt(userInput, 0, 1)) {

					break;

				}

				else {

					std::cout << "Invalid Input, press any key to try again.";

					NewLines(2);

					system("pause");

				}

			}

			if (userInput == 1) {

				choice = EditOrViewOrCreateNote;

				return;

			}

			else if (userInput == 0) {

				choice = MainMenu;

				return;

			}

		}

	// return to sub catagory selection

	else if (userInput == 4) {

			choice = ViewAndChooseSubCatagory;
			
			return;

		}

	// return to main menu

	else if (userInput == 0) {

			choice = MainMenu;
			
			return;
					
		}

}

void createSubCatagory(functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, int &currentSubCatagoryIndex) {

	std::string subCatagoryName;

	system("cls");

	std::cout << ":: Please Enter the Name of Your New Sub Catagory ::";

	NewLines(2);

	std::cout << "User Input: ";

	std::getline(std::cin, subCatagoryName);

	subCatagoryStorage.push_back(*new SubCatagory(subCatagoryName));

	currentSubCatagoryIndex = subCatagoryStorage.size() - 1;

	choice = EditOrViewOrCreateNote;	

	return;

}

void chooseOrCreateSubCatagory(functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, int &subCatagoryIndex) {

	// user input, string for number and word input

	std::string userSInput;

	// this is to restrict options when a subcatagory does not exist

	int minimumSubCatagorySpace = 0;
		
	

	// selection
	
	while (true) {

			// will raise selection limit

			if (subCatagoryStorage.size() > 0) {

				minimumSubCatagorySpace = 1;

			}

			system("cls");

			// prompt if no subcatagory exists

			if (subCatagoryStorage.size() == 0) {

				std::cout << ":: Type (NEW) to Create a New Sub Catagory, or Type (EXIT) to Exit to Main Menu. ::";

			}

			// prompt if subcatagories exist

			else {

				std::cout << ":: Please Select a Number for one of the Sub Catagories, or Type (NEW) to Create a New Sub Catagory, or Type (EXIT) to Exit to Main Menu. ::";

			}

			NewLines(2);

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

				NewLines(2);

				system("pause");

			}

		}

	// create new catagory

	if (stringUpper(userSInput) == "NEW") {

			choice = CreateSubcatagory;
			
			return;

		}

	// exit to main menu

	else if (stringUpper(userSInput) == "EXIT") {

			choice = MainMenu;

			return;

		}

	// access a sub catagory

	else {

			subCatagoryIndex = std::stoi(userSInput) - 1;
			
			choice = EditOrViewOrCreateNote;

			return;

		}

}

// main menu

void menu(functionCall &choice, std::vector<SubCatagory>& subCatagoryStorage) {

	int userInput;

	while (true) {

		system("cls");

		// Introduction
		
		std::cout << ":: Notepad Program ::";

		NewLines(2);

		std::cout << ":: Please select one of the options below! ::";

		NewLines(2);

		// Options
		
		std::cout << "(1) View and Choose Sub Catagory";

		std::cout << "\n";

		std::cout << "(2) Exit Program";

		NewLines(2);

		std::cout << "User Input: ";

		if (selectAndValidateInt(userInput, 1, 2)) {

			break;

		}

		else {

			std::cout << "Invalid Input, press any key to try again.";

			NewLines(2);

			system("pause");
	
		}

	}

	// assigns viewAndChooseSubCatagory

	if (userInput == 1) {

		choice = ViewAndChooseSubCatagory;

	}

	// assigns exit Program

	else if (userInput == 2) {

		choice = ExitProgram;

	}

	return;

}

// main program function

int main()
{
	// text file names for notes

	std::vector<std::string> noteSaveFiles;

	noteSaveFiles.push_back("Notes.txt");

	// create and closes file

	std::fstream myFile("Notes.txt", std::ios::out);
	
	if (myFile.is_open()) {
	
		myFile.close();
	
	}
	
	// vector of SubCatagorys

	std::vector<SubCatagory>subCatagoryStorage;

	// variable for current sub catagory index
	
	int currentSubCatagoryIndex;

	// variable for key names when accessing a note

	std::string keyNameForNote;


	// adds a test note
	
	subCatagoryStorage.push_back(*new SubCatagory);

	subCatagoryStorage[0].setCatagoryName("Test Catagory");

	subCatagoryStorage[0].Names[1] = "Test Name";

	subCatagoryStorage[0].Notes["Test Name"].push_back("hi there im a test note");


	// variable/enum for selection input - access different areas of program

	functionCall choice = MainMenu;

	// main Program ----------------------------------------------------------------
	
	while (true) {
		
		switch (choice) {

		case MainMenu: {

			menu(choice, subCatagoryStorage);

			break;

		}

		case ViewAndChooseSubCatagory : {

			chooseOrCreateSubCatagory(choice, subCatagoryStorage, currentSubCatagoryIndex);

			break;

		}

		case CreateSubcatagory: {

			createSubCatagory(choice, subCatagoryStorage, currentSubCatagoryIndex);

			break;

		}

		case EditOrViewOrCreateNote: {

			editOrViewOrCreateNotes(choice, subCatagoryStorage, currentSubCatagoryIndex, keyNameForNote);

			break;

		}

		case CreateNote: {

			createNote(choice, subCatagoryStorage, currentSubCatagoryIndex);

			break;

		}

		case EditNote: {

			editNote(choice, subCatagoryStorage, currentSubCatagoryIndex, keyNameForNote);

			break;

		}


		case ExitProgram : {

			return 0;

			break;

		}

		}

	}

}

