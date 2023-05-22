#pragma once
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



// global enum for selections

enum functionCall;

// return uppercase version of string

std::string stringUpper(std::string& stringToConvert);

// clear input stream

void clearInputStream();

// input validation

bool selectAndValidateInt(int& userInput, int minimum, int maximum);

bool selectAndValidateString(std::string& userSInput, int minimum, int maximum, std::string equalityCheck);

// parse strings

void extractCertainAmountOfCharactersIntoVector(std::string stringToExtract, std::vector<std::string>& storeSplitString);

bool checkStringForEndInput(std::string codeWordToEndInput, std::string& userSInput);

void InsertCharactersIntoVector(std::string newString, std::vector<std::string>& note, int placeForInsertion);

void parseStringForKeyValuePairs(std::string stringToParse, char symbolToFind, int& key, std::string& value);

void parseStringForKeyValuePairs(std::string stringToParse, std::string symbolToFind, std::string& key, std::string& value);

// convience functions

void NewLines(int ammountOfNewLines);

// read and write to files for storage / reload saved data

#pragma warning (push)
#pragma warning (disable : 4703)

void write(std::string fileName, std::vector<SubCatagory>& subCatagories);

void read(std::string fileName, std::vector<SubCatagory>& subCatagories);

#pragma warning (pop)

// display notes and subcatagories

void displaySubCatagoryNames(std::vector<SubCatagory>& subCatagoryStorage);

void displayNoteNamesInSubCatagory(std::vector<SubCatagory>& subCatagoryStorage, int& subCatagoryIndex);

// view note

void viewNote(functionCall& choice, std::vector<std::string>Note);

// edit note

void editNote(std::string fileName, functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, int& currentSubCatagoryIndex, std::string& keyNameForNote);

// create note

void createNote(std::string fileName, functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, int& currentSubCatagoryIndex);

// edit notes and sub catagories

void editOrViewOrCreateNotes(functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, int& currentSubCatagoryIndex, std::string& keyNameForNote);

void createSubCatagory(std::string fileName, functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, int& currentSubCatagoryIndex);

void chooseOrCreateSubCatagory(functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, int& subCatagoryIndex);

// main menu

void menu(functionCall& choice, std::vector<SubCatagory>& subCatagoryStorage, std::string currentFileName);

// file selection

void deleteAnElement(std::vector<std::string>& fileStorage, int indexToDelete);

void writeFiles(std::vector<std::string> fileStorage, std::string currentFile);

void readAndStoreFileContentsIntoVector(std::vector<std::string>& fileStorage, std::string& currentFile);

void fileCreation(functionCall& choice, std::vector<std::string>& fileStorage, std::string& currentFile);

void fileSelection(functionCall& choice, std::vector<std::string>& fileStorage, std::string& currentFile);

void deleteFile(functionCall& choice, std::vector<std::string>& fileStorage, std::string& currentFile);