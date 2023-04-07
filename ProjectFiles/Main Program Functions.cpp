#include "Main Program Functions.h"
#include <numeric>
#include <sstream>
#include <iterator>
#include <cstdio>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <map>
#include <string>
#include "SubCatagory.h"
#include "Main Program Functions.h"



// global enum for selections

enum functionCall { DeleteFile, ViewAndChooseSubCatagory, ExitProgram, MainMenu, CreateSubcatagory, EditOrViewOrCreateNote, ViewNote, CreateNote, EditNote, FileSelection, FileCreation };

// return uppercase version of string

std::string stringUpper(std::string& stringToConvert) {

	std::string newString;

	std::vector<std::string>Temp;

	// appends new string with upper case letters

	for (int i = 0; i < stringToConvert.size(); i++) {

		newString.append(1, std::toupper(stringToConvert[i]));

	}

	return newString;

}

// clear input stream

void clearInputStream() {

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}

// input validation

bool selectAndValidateInt(int& userInput, int minimum, int maximum) {

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

	else if (std::isdigit(stringInteger[0])) {

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

void extractCertainAmountOfCharactersIntoVector(std::string stringToExtract, std::vector<std::string>& storeSplitString) {

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

			counter++;

		}


	}

	if (temp.size() > 0) {

		storeSplitString.push_back(temp);

	}

	return;

}

bool checkStringForEndInput(std::string codeWordToEndInput, std::string& userSInput) {

	if (stringUpper(userSInput) == "/END") {

		return true;

	}

	else {

		return false;

	}

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

	// define bool to see if key has been already stored

	bool hasKeyBeenStored = false;

	std::stringstream parse(stringToParse);

	std::vector<std::string>results;

	std::string temp;

	while (parse.good()) {

		std::getline(parse, temp, ',');

		results.push_back(temp);

	}

	int counter = 0;

	std::vector<std::string>::iterator it;

	for (it = results.begin(); it != results.end(); it++, counter++) {

		// limits storage of key once

		if (hasKeyBeenStored == false) {

			if (isdigit(results[counter][0])) {

				key = stoi(results[counter]);

				hasKeyBeenStored = true;

			}

		}

		else {

			value = *it;

		}

	}

}

void parseStringForKeyValuePairs(std::string stringToParse, std::string symbolToFind, std::string& key, std::string& value) {

	// may use in the future


}

// convience functions

void NewLines(int ammountOfNewLines) {

	for (int i = 0; i < ammountOfNewLines; i++) {

		std::cout << std::endl;

	}

}

// read and write to files for storage / reload saved data

#pragma warning (push)
#pragma warning (disable : 4703)

void write(std::string fileName, std::vector<SubCatagory>& subCatagories) {

	const char charSeperatorSymbol = ',';

	const std::string storeName = "-N-\n";

	const std::string storeNote = "-K-\n";

	const std::string storeNoteInfo = "-S-\n";

	const std::string appendNewlyMadeCatagory = "-V-";

	std::ofstream myFile(fileName);

	// key for note in for loop below

	std::string currentNoteKey;

	// iterates through our sub catagories

	std::vector<SubCatagory>::iterator currentSubcatagory;
	for (currentSubcatagory = subCatagories.begin(); currentSubcatagory != subCatagories.end(); currentSubcatagory++) {

		myFile << storeName;

		// stores catagory name

		myFile << currentSubcatagory->getCatagoryName() << "\n";

		// iterates through all the different notes

		for (int i = 0; i < currentSubcatagory->Names.size(); i++) {

			// assigns key for note

			currentNoteKey = currentSubcatagory->Names[i + 1];

			myFile << storeNote;

			// adding 1 to i because the numbers in my names map start at 1

			myFile << i + 1 << charSeperatorSymbol << currentNoteKey << "\n";

			myFile << storeNoteInfo;

			// iterates through vector to store note in file

			std::vector<std::string>::iterator note;
			for (note = currentSubcatagory->Notes[currentNoteKey].begin(); note != currentSubcatagory->Notes[currentNoteKey].end(); note++) {

				myFile << *note << "\n";

			}

		}

		myFile << appendNewlyMadeCatagory;

		if (currentSubcatagory == subCatagories.end()) {

			continue;

		}

		else {

			myFile << "\n";

		}

	}

	myFile.close();

	return;

}

void read(std::string fileName, std::vector<SubCatagory>& subCatagories) {

	// constants for reading file

	const char charSeperatorSymbol = ',';

	const std::string storeName = "-N-"; // case 1

	const std::string storeNote = "-K-"; // case 2

	const std::string storeNoteInfo = "-S-"; // case 3

	const std::string appendNewlyMadeCatagory = "-V-"; // case 4

	// string for reading line

	std::string line;

	// choice on were to place contents

	int choiceForLine = 1;

	// variable to keep track of current index | a bool to keep track of whether the first iteration has occured or not

	SubCatagory* tempCatagory;

	// variables to store note key value pairs

	int key; // this is the key for the names map, this map is within our vector of subcatagories

	std::string value; // this is the value for the names map as well as the key for the notes map, this map is within our vector of subcatagories

	// opens file for input into program

	std::ifstream myFile(fileName);

	// reads lines of file and places contents into vector of SubCatagory class

	if (myFile.is_open()) {

		while (std::getline(myFile, line)) {

			// in case an empty line shows up it will exit with an error

			if (line == "") {

				std::cout << "Error! There is an empty space in your file, please restart program and load another file, or fix the broken one.";

				NewLines(2);

				system("pause");

				return;

			}

			// assigns choice to store a name

			if (line == storeName) {

				choiceForLine = 1;

				continue;

			}

			// asigns choice to store a note

			else if (line == storeNote) {

				choiceForLine = 2;

				continue;

			}

			// asigns choice to store note info

			else if (line == storeNoteInfo) {

				choiceForLine = 3;

				continue;

			}

			else if (line == appendNewlyMadeCatagory) {

				choiceForLine = 4;

			}




			switch (choiceForLine)
			{

				// store name

			case 1: {

				tempCatagory = new SubCatagory;

				tempCatagory->setCatagoryName(line);

				break;

			}

				  // store note

			case 2: {

				parseStringForKeyValuePairs(line, charSeperatorSymbol, key, value);

				tempCatagory->Names[key] = value; // again the value will turn into the key in case 3 below !!!!!!!!!!!!!!!!!!!!!!!!!!

				break;

			}

				  // store note info

			case 3: {

				tempCatagory->Notes[value].push_back(line);

				break;

			}

				  // push back subCatagories vector with new object

			case 4: {

				subCatagories.push_back(*tempCatagory);

				break;

			}

			}

		}

		tempCatagory = NULL;

		myFile.close();

	}

	return;

}

#pragma warning (pop)

// display notes and subcatagories

void displaySubCatagoryNames(std::vector<SubCatagory>& subCatagoryStorage) {

	for (int i = 0; i < subCatagoryStorage.size(); i++) {

		std::cout << i + 1 << ". " << subCatagoryStorage[i].getCatagoryName();

		NewLines(2);

	}

}

void displayNoteNamesInSubCatagory(std::vector<SubCatagory>& subCatagoryStorage, int& subCatagoryIndex) {

	for (int i = 0; i < subCatagoryStorage[subCatagoryIndex].Names.size(); i++) {

		std::cout << i + 1 << ": " << subCatagoryStorage[subCatagoryIndex].Names[i + 1];

		NewLines(2);

	}

}

// view note

void viewNote(functionCall& choice, std::vector<std::string>Note) {

	std::string currentPlace;

	for (std::vector<std::string>::iterator it = Note.begin(); it != Note.end(); it++) {

		std::cout << *it << "\n";

	}

}

// edit note

void editNote(std::string fileName, functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, int& currentSubCatagoryIndex, std::string& keyNameForNote) {

	// once first cycle happens text will display please continue entering note

	bool firstNoteInputCycleHasHappened = false;

	// this string will end input sequence below 

	std::string endInput = "/END";

	// user string input	

	std::string userSInput;

	// user int input

	int userInput;

	// selection

	while (true) {

		system("cls");

		std::cout << ":: Enter (1) to retype entire note, Enter (2) to select a line and retype it in, Enter (3) to exit back to note selection ::";

		NewLines(2);

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

		subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote].clear();

		while (true) {

			system("cls");

			std::cout << ":: Please enter note - enter (/end) on one line to finish entering note ::";

			NewLines(2);

			std::cout << "------------------------------";

			NewLines(2);

			viewNote(choice, subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote]);

			NewLines(1);

			std::cout << "------------------------------";

			NewLines(2);

			std::cout << "User Input: ";

			std::getline(std::cin, userSInput);

			if (checkStringForEndInput(endInput, userSInput)) {

				break;

			}

			subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote].push_back(userSInput);

		}

		system("cls");

		std::cout << ":: New Note has been Entered, Please press any key to continue. ::";

		NewLines(2);

		system("pause");

		choice = EditOrViewOrCreateNote;

		write(fileName, subCatagoryStorage);

		return;

	}

	// edit specific line of note

	else if (userInput == 2) {

		int lineToEdit;

		while (true) {


			system("cls");

			for (int i = 0; i < subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote].size(); i++) {

				std::cout << "(" << i + 1 << ")  " << subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote][i];

				NewLines(2);

			}

			std::cout << "Please select a line to edit";

			NewLines(2);

			std::cout << "User Input: ";

			if (selectAndValidateInt(userInput, 1, subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote].size())) {

				lineToEdit = userInput - 1;

				break;

			}

			else {

				std::cout << "Invalid Input, press any key to try again.";

				NewLines(2);

				system("pause");

			}

		}

		system("cls");

		std::cout << ":: Please enter line. ::";

		NewLines(2);

		std::cout << "User Input: ";

		std::getline(std::cin, userSInput);

		InsertCharactersIntoVector(userSInput, subCatagoryStorage[currentSubCatagoryIndex].Notes[keyNameForNote], lineToEdit);

		NewLines(2);

		system("cls");

		std::cout << "New line has been entered";

		system("pause");

		choice = EditOrViewOrCreateNote;

		write(fileName, subCatagoryStorage);

		return;

	}

}

// create note

void createNote(std::string fileName, functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, int& currentSubCatagoryIndex) {

	// this string will end input sequence below 

	std::string endInput = "/END";

	// int for user to select next destination

	int userInput;

	while (true) {

		system("cls");

		int newPlaceInNames = subCatagoryStorage[currentSubCatagoryIndex].Names.size() + 1;

		std::string KeyForNote;

		std::string userSInput;

		std::cout << ":: Please Enter the Name of Your New Note ::";

		NewLines(2);

		std::cout << "User Input: ";

		std::getline(std::cin, userSInput);

		subCatagoryStorage[currentSubCatagoryIndex].Names[newPlaceInNames] = userSInput;

		KeyForNote = userSInput;

		subCatagoryStorage[currentSubCatagoryIndex].Notes[KeyForNote].push_back("None");

		write(fileName, subCatagoryStorage);

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

			subCatagoryStorage[currentSubCatagoryIndex].Notes[KeyForNote].clear();

			system("cls");

			while (true) {

				system("cls");

				std::cout << ":: Please enter note - enter (/end) on one line to finish entering note ::";

				NewLines(2);

				std::cout << "------------------------------";

				NewLines(2);

				viewNote(choice, subCatagoryStorage[currentSubCatagoryIndex].Notes[KeyForNote]);

				NewLines(1);

				std::cout << "------------------------------";

				NewLines(2);

				std::cout << "User Input: ";

				std::getline(std::cin, userSInput);

				if (checkStringForEndInput(endInput, userSInput)) {

					break;

				}

				subCatagoryStorage[currentSubCatagoryIndex].Notes[KeyForNote].push_back(userSInput);

			}

			choice = EditOrViewOrCreateNote;

			write(fileName, subCatagoryStorage);

			return;

		}

		// go back to edit view or create note

		else if (userInput == 2) {

			choice = EditOrViewOrCreateNote;

			return;

		}

	}

}

// edit notes and sub catagories

void editOrViewOrCreateNotes(functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, int& currentSubCatagoryIndex, std::string& keyNameForNote) {

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

			std::cout << ":: Please Select which Note you Would Like to Read. Enter 0 to go back ::";

			NewLines(2);

			displayNoteNamesInSubCatagory(subCatagoryStorage, currentSubCatagoryIndex);

			std::cout << "User Input: ";

			if (selectAndValidateInt(userInput, 0, subCatagoryStorage[currentSubCatagoryIndex].Names.size())) {

				break;

			}

			else {

				std::cout << "Invalid Input, press any key to try again.";

				NewLines(2);

				system("pause");

			}

		}

		if (userInput == 0) {

			choice = EditOrViewOrCreateNote;

			return;

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

			NewLines(1);

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

void createSubCatagory(std::string fileName, functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, int& currentSubCatagoryIndex) {

	std::string subCatagoryName;

	system("cls");

	std::cout << ":: Please Enter the Name of Your New Sub Catagory ::";

	NewLines(2);

	std::cout << "User Input: ";

	std::getline(std::cin, subCatagoryName);

	subCatagoryStorage.push_back(*new SubCatagory(subCatagoryName));

	currentSubCatagoryIndex = subCatagoryStorage.size() - 1;

	choice = EditOrViewOrCreateNote;

	write(fileName, subCatagoryStorage);

	return;

}

void chooseOrCreateSubCatagory(functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, int& subCatagoryIndex) {

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

					NewLines(2);

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

void menu(functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, std::string currentFileName) {

	int userInput;

	while (true) {

		system("cls");

		// Introduction

		std::cout << ":: Notepad Program ::";

		NewLines(2);

		std::cout << ":: Current File: " << currentFileName << " ::";

		NewLines(2);

		std::cout << ":: Please select one of the options below! ::";

		NewLines(2);

		// Options

		std::cout << "(1) Select and Load A Seperate FIle/Save";

		NewLines(1);

		std::cout << "(2) Create a New File Save";

		NewLines(1);

		std::cout << "(3) Delete a File Save";

		NewLines(1);

		std::cout << "(4) View and Choose Sub Catagory";

		NewLines(1);

		std::cout << "(5) Exit Program";

		NewLines(2);

		std::cout << "User Input: ";

		if (selectAndValidateInt(userInput, 0, 5)) {

			break;

		}

		else {

			std::cout << "Invalid Input, press any key to try again.";

			NewLines(2);

			system("pause");

		}

	}

	// assigns next function/location user will be sent based on above inputs

	if (userInput == 1) {

		choice = FileSelection;

	}

	else if (userInput == 2) {

		choice = FileCreation;

	}

	else if (userInput == 3) {

		choice = DeleteFile;

	}

	else if (userInput == 4) {

		choice = ViewAndChooseSubCatagory;

	}

	else if (userInput == 5) {

		choice = ExitProgram;

	}

	return;

}

// file selection

void deleteAnElement(std::vector<std::string>& fileStorage, int indexToDelete) {

	std::vector<std::string> oldFileStorage(fileStorage);

	fileStorage.clear();

	for (int i = 0; i < oldFileStorage.size(); i++) {

		if (oldFileStorage[i] == oldFileStorage[indexToDelete]) {

			continue;

		}

		else {

			fileStorage.push_back(oldFileStorage[i]);

		}

	}

	return;

}

void writeFiles(std::vector<std::string> fileStorage, std::string currentFile) {

	const std::string storeCurrentFile = "-L-\n";

	std::ofstream myFile("FileSaveNames.txt");

	if (myFile.is_open()) {

		std::vector<std::string>::iterator currentFileName;
		for (currentFileName = fileStorage.begin(); currentFileName != fileStorage.end(); currentFileName++) {

			myFile << *currentFileName << "\n";

		}

		myFile << storeCurrentFile;

		myFile << currentFile;

		myFile.close();

	}

	return;

}

void readAndStoreFileContentsIntoVector(std::vector<std::string>& fileStorage, std::string& currentFile) {

	const std::string storeCurrentFile = "-L-";

	// open then close file to make sure it exists, if it doesn't it will be created

	std::ifstream myFile("FileSaveNames.txt");

	std::string holdFileContents;

	bool isThisLineOurLastOpenedFile = false;

	if (myFile.is_open()) {

		while (std::getline(myFile, holdFileContents)) {

			// this if statement will check if we need to store last opened file

			if (holdFileContents == storeCurrentFile) {

				isThisLineOurLastOpenedFile = true;

				continue;

			}

			// decides with data type to pass (holdFileContents) into

			if (isThisLineOurLastOpenedFile) {

				currentFile = holdFileContents;

				break;

			}

			else {

				fileStorage.push_back(holdFileContents);

			}

		}

		myFile.close();

	}

	return;

}

void fileCreation(functionCall& choice, std::vector<std::string>& fileStorage, std::string& currentFile) {

	// defines variable that will hold the file name

	std::string userSInput;

	// user will create file for program

	system("cls");

	std::cout << ":: Please Type in the Name of Your New File ::";

	NewLines(2);

	std::cout << "User Input: ";

	std::getline(std::cin, userSInput);

	currentFile = userSInput + ".txt";

	fileStorage.push_back(currentFile);

	writeFiles(fileStorage, currentFile);

	choice = MainMenu;

	return;

}

void fileSelection(functionCall& choice, std::vector<std::string>& fileStorage, std::string& currentFile) {

	// variable for recieving input then input validating input

	std::string userSInput;

	int userInput = 0;

	// displays current number for loop

	while (true) {

		system("cls");

		std::cout << "|| Please Select a File, Enter 0 to Return to Main Menu ||";

		NewLines(2);

		for (int i = 0; i < fileStorage.size(); i++) {

			std::cout << i + 1 << ": " << fileStorage[i];

			NewLines(2);

		}

		std::cout << "User Input: ";

		if (selectAndValidateInt(userInput, 0, fileStorage.size())) {

			// returns to main menu if user entered 0

			if (userInput == 0) {

				choice = MainMenu;

				return;

			}


			break;

		}

		else {

			std::cout << "Invalid Input, press any key to try again.";

			NewLines(2);

			system("pause");

		}

	}

	currentFile = fileStorage[userInput - 1];

	writeFiles(fileStorage, currentFile);

	choice = MainMenu;

}

void deleteFile(functionCall& choice, std::vector<std::string>& fileStorage, std::string& currentFile) {

	// variable for recieving input then input validating input

	std::string userSInput;

	int userInput = 0;

	// displays current number for loop

	while (true) {

		system("cls");

		std::cout << "|| Please Select a File to Delete, Enter 0 to Return to Main Menu ||";

		NewLines(2);

		for (int i = 0; i < fileStorage.size(); i++) {

			if (fileStorage[i] == currentFile) {

				std::cout << i + 1 << ": Current File: " << fileStorage[i];

				NewLines(2);

				continue;

			}

			std::cout << i + 1 << ": " << fileStorage[i];

			NewLines(2);

		}

		std::cout << "User Input: ";

		if (selectAndValidateInt(userInput, 0, fileStorage.size())) {

			// returns to main menu if user entered 0

			if (userInput == 0) {

				choice = MainMenu;

				return;

			}

			userInput--; // allows userInput variable to access element in vector

			if (fileStorage[userInput] == currentFile) {

				std::cout << "Invalid Input, this file is currently loaded. Please unload the file, or select another file.";

				system("pause");

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

	// all below code deletes selected file

	int fileToDeleteLength = fileStorage[userInput].size();

	const char* ptc = fileStorage[userInput].c_str();

	deleteAnElement(fileStorage, userInput);

	writeFiles(fileStorage, currentFile);

	std::cout << *ptc;

	remove(ptc);

	ptc = NULL;

	choice = MainMenu;

	return;

}