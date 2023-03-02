#include "SubCatagory.h"

/*void SubCatagory::addANote(std::string newNoteName, std::string newNote)
{

	this -> mapOfNotes.insert(newNoteName, newNote);

	return;

}*/

SubCatagory::SubCatagory()
{

}

SubCatagory::SubCatagory(std::string catagoryName)
{

	this->catagoryName = catagoryName;


}


void SubCatagory::setCatagoryName(std::string newCatagoryName)
{

	this -> catagoryName = newCatagoryName;

	return;

}

std::string SubCatagory::getANote(std::string noteName)
{

	std::string temp;

	return temp;

}

std::string SubCatagory::getCatagoryName()
{

	return this->catagoryName;

}

std::string SubCatagory::returnCatagoryName(int NumberForName)
{
	return this->Names[NumberForName];

}




