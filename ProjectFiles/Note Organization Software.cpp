// Note Organization Software.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MainProgramFunctions.h"






// current debing 
	//lines - in write file

// Phuedo Code - in our file creation the last index of the vector will always be the last loaded file

// ToDO:: 1. Figure Out how multifile compilation full works

// below is a quick copy and past code setup for debugging areas
		//std::cout << "worked";
		//system("pause");
		







		
// In parenthesis are the string constants I used for storing info into files, then parsing it into the program.

// store name (-N-) go to next line to get information

// repeat note storage until all notes have been stored

// store new note (-K-) go to next line to get name then number - order (name then number (,) )

// store what note says (-S-) go to next line to store elements into note vector

// store last loaded file in file for file names (-L-)


// assigns enum when user chooses location to go in console

enum functionCall { DeleteFile, ViewAndChooseSubCatagory, ExitProgram, MainMenu, CreateSubcatagory, EditOrViewOrCreateNote, ViewNote, CreateNote, EditNote, FileSelection, FileCreation };


// main program function

int main()
{

	// make sure notes file exists

	std::ofstream myFile("FileSaveNames.txt", std::ios::app);

	if (myFile.is_open()) {

		myFile.close();

	}

	// variable/enum for selection input - access different areas of program

	functionCall choice = MainMenu;

	// vector of SubCatagorys

	std::vector<SubCatagory>subCatagoryStorage;

	// variable for current sub catagory index
	
	int currentSubCatagoryIndex;

	// variable for key names when accessing a note

	std::string keyNameForNote;

	// open and read file names within txt file, then store into our note save files vectorvector
	
	std::vector<std::string> noteSaveFiles;

	std::string currentFile; // this will always be written as the last loaded file until the user changes there file

	readAndStoreFileContentsIntoVector(noteSaveFiles, currentFile);

	// read last opened file, or have user create one

	if (noteSaveFiles.size() == 0) {
	
		choice = FileCreation;

	}

	else {

		read(currentFile, subCatagoryStorage);

	}

	// main Program ----------------------------------------------------------------
	
	while (true) {
		
		switch (choice) {

		case DeleteFile: {

			deleteFile(choice, noteSaveFiles, currentFile);

			break;

		}


		case FileCreation: {

			fileCreation(choice, noteSaveFiles, currentFile);

			subCatagoryStorage.clear();

			break;

		}


		case FileSelection: {

			fileSelection(choice, noteSaveFiles, currentFile);

			subCatagoryStorage.clear();

			read(currentFile, subCatagoryStorage);

			break;

		}


		case MainMenu: {

			menu(choice, subCatagoryStorage, currentFile);

			break;

		}

		case ViewAndChooseSubCatagory : {

			chooseOrCreateSubCatagory(choice, subCatagoryStorage, currentSubCatagoryIndex);

			break;

		}

		case CreateSubcatagory: {

			createSubCatagory(currentFile, choice, subCatagoryStorage, currentSubCatagoryIndex);

			break;

		}

		case EditOrViewOrCreateNote: {

			editOrViewOrCreateNotes(choice, subCatagoryStorage, currentSubCatagoryIndex, keyNameForNote);

			break;

		}

		case CreateNote: {

			createNote(currentFile, choice, subCatagoryStorage, currentSubCatagoryIndex);

			break;

		}

		case EditNote: {

			editNote(currentFile, choice, subCatagoryStorage, currentSubCatagoryIndex, keyNameForNote);

			break;

		}


		case ExitProgram : {

			return 0;

			break;

		}

		}

	}

}

