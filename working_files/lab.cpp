#include<iostream>
#include<cstdlib>
#include "lab.h"

Lab::Lab(){
	labID = "";
	maxCapacity = 0;
	subjectCode = "";
	blding = "";
	roomNum = "";
	time ="";
}

Lab::~Lab(){
	labID = "";
	maxCapacity = 0;
	subjectCode = "";
	blding = "";
	roomNum = "";
	time ="";
}

// update the details of the hidden lab data

void Lab::updateLabID(std::string newLab){ labID = newLab; }
void Lab::updateCapacity(int newCapacity){ maxCapacity = newCapacity; }
void Lab::updateSubjectCode(std::string allocateCode) { subjectCode = allocateCode; }
void Lab::updateBuilding(std::string allocateBuilding) { blding = allocateBuilding; }
void Lab::updateRoom(std::string allocateRoom){ roomNum = allocateRoom; }
void Lab::updateTime(std::string assignTime){ time = assignTime; }

std::string Lab::getLabID(){ return labID; }
int Lab::getCapacity(){ return maxCapacity; }
std::string Lab::getSubCode(){ return subjectCode; }
std::string Lab::getBlding(){ return blding; }
std::string Lab::getRoomNum(){ return roomNum; }
std::string Lab::getTime(){ return time; }

void Lab::displayLab(){

	std::cout << labID << ", " << maxCapacity << ", " << subjectCode << ", " << blding << ", " << roomNum << ", " << time << std::endl;
}


/************* GENERIC LIST FUNCTIONS *************/

void addValuetoList(intNodePtr & curList, int valueToAdd){

	intNodePtr tmp = new integerRecord;
	tmp->value = valueToAdd;
	tmp->next = NULL;
	
	if(curList == NULL){
		curList = tmp;
	}else {
		intNodePtr current = curList;
		while(current->next != NULL){
			current = current->next;
		}
		current->next = tmp;
		tmp = curList;
	}
}

void destroyList(intNodePtr & list){

	intNodePtr tmpCopy;

	if(list != NULL){
		while(list->next != NULL){
			tmpCopy = list;
			list = list->next;
			delete tmpCopy;
		}
		
		delete list;
		list = NULL;
	}
}
