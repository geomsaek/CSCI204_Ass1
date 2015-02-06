#include<iostream>
#include<cstdlib>
#include "allocation.h"
#include<string>
#include <time.h>


/************************* ALLOCATION CLASS *************************/

Allocation::Allocation(){

	studentNum = 0;
	labID = "";
	subjectCode = "";
	buildingNum = 0;
	roomNum = "";
	labTime = "";
	date = "";
}

Allocation::~Allocation(){
	studentNum = 0;
	labID = "";
	subjectCode = "";
	buildingNum = 0;
	roomNum = "";
	labTime = "";
	date = "";
}

Allocation::Allocation(int studentID, std::string updateLab, std::string updateCode, int updateBuild, std::string updateRoom, std::string updateLabTime, std::string enrolledDate){

	studentNum = studentID;
	labID = updateLab;
	subjectCode = updateCode;
	buildingNum = updateBuild;
	roomNum = updateRoom;
	labTime = updateLabTime;
	date = enrolledDate;
}


// return the private values of the Allocation class

int Allocation::dStudentID(){ return studentNum; }
std::string Allocation::dLabID(){ return labID; }
std::string Allocation::dSubjectCode(){ return subjectCode; }
int Allocation::dbuildNum() { return buildingNum; }
std::string Allocation::dRoomNum() { return roomNum; }
std::string Allocation::dLabTime() { return labTime; }
std::string Allocation::dEnrolDate() { return date; }

// functions that update the private values for the class

void Allocation::upAllocateStudentID(int newID){ studentNum = newID; }
void Allocation::upAllocateLab(std::string newLab) { labID = newLab; }
void Allocation::upAllocateSubCode(std::string newCode) { subjectCode = newCode; }
void Allocation::upAllocateBuilding(int newBuild){ buildingNum = newBuild; }
void Allocation::upAllocateRoom(std::string newRoom){ roomNum = newRoom; }
void Allocation::upAllocateLabTime(std::string newLabTime) { labTime = newLabTime; }
void Allocation::upAllocateEnrolDate(std::string newDate) { date = newDate; }

void Allocation::displayAllocation(bool alterDisplay){
	
	if(alterDisplay){
		std::cout << "Student Number: " << studentNum << std::endl;
		std::cout << "Lab ID: " << labID << std::endl;
		std::cout << "Subject Code: " << subjectCode << std::endl;
		std::cout << "Building Number: " << buildingNum <<std::endl;
		std::cout << "Room Number: " << roomNum << std::endl;
		std::cout << "Lab Time: " << labTime << std::endl;
		std::cout << "Enrolment Date: " << date << std::endl;
		std::cout << std::endl;
	}else {
		std::cout << subjectCode << " ";
	}
	
}


/************************* ALLOCATION NODE *************************/

AllocationNode::AllocationNode(){
	
	this->allocationInstance = NULL;
}


AllocationNode::~AllocationNode(){
	
	if(this->allocationInstance != NULL){
		this->allocationInstance->~Allocation();
		delete this->allocationInstance;
		this->allocationInstance = NULL;
	}
}

void AllocationNode::updateNodeVals(int updateID, std::string updateSubjectCode, std::string enrolmentDate, std::string labID, std::string labTime, std::string labRoomNum, std::string labBuild ){
	
	int convertBuild = 0;
	convertBuild = atoi(labBuild.c_str());
			
	this->allocationInstance = new Allocation();
	this->allocationInstance->upAllocateStudentID(updateID);
	this->allocationInstance->upAllocateSubCode(updateSubjectCode);
	this->allocationInstance->upAllocateLab(labID);
	this->allocationInstance->upAllocateBuilding(convertBuild);
	this->allocationInstance->upAllocateRoom(labRoomNum);
	this->allocationInstance->upAllocateLabTime(labTime);
	this->allocationInstance->upAllocateEnrolDate(enrolmentDate);
	
}

void AllocationNode::displayNodeAllocate(bool alterDisplay){
	this->allocationInstance->displayAllocation(alterDisplay);
}

std::string AllocationNode::getAllocateSubjectCode(){
	return this->allocationInstance->dSubjectCode();
}

bool AllocationNode::matchLabStudent(std::string labID, std::string subCode){
	
	bool found = false;
	if((this->allocationInstance->dSubjectCode() == subCode) && (this->allocationInstance->dLabID() == labID)){
		found = true;
	}
	
	return found;
}

bool AllocationNode::checkEnrol(std::string studentID,std::string subjectCode) {

	int convertID = 0;
	
	convertID = atoi(studentID.c_str());
	
	if(this->allocationInstance->dSubjectCode() == subjectCode && this->allocationInstance->dStudentID() == convertID){
		return true;
	}else {
		return false;
	}
}


bool AllocationNode::checkLabEnrol(std::string studentID,std::string subjectCode){
	int convertID = 0;
	bool found = false;
	
	convertID = atoi(studentID.c_str());
	if(this->allocationInstance != NULL){
			if(this->allocationInstance->dLabID() == "N/A"){
				return false;
			}else {
				return true;
			}
	}else {
		found = false;
	}
	return found;
}

std::string AllocationNode::returnNodeSubject(){
	return this->allocationInstance->dSubjectCode();
}


/************************* ALLOCATION LIST *************************/

AllocationList::AllocationList(){
	this->head = NULL;
	this->tail = NULL;
	this->list = NULL;
}

AllocationList::~AllocationList(){
	
	alloListPtr cur;
	
	if(this->list != NULL){
		
		while(this->list != NULL){
		
			this->list->currentAllocateNode->~AllocationNode();
			cur = this->list;
			
			this->list = this->list->next;
			delete this->list;
		}	
		delete this->list;
		
		this->list = NULL;
	}
	if(this->head != NULL){
		delete this->head;
		this->head = NULL;
	}
	if(this->tail != NULL){
		delete this->tail;
		this->tail = NULL;
	}
}

void AllocationList::createNewList(int allocateStudentID, std::string subjectCode, std::string allocateDate, std::string labID, std::string labTime, std::string labRoomNum, std::string labBuild ){
	
	alloListPtr tmp = new AlloNodeContainer;
	tmp->currentAllocateNode = new AllocationNode();
	// LabID is equal to N/A as no student is associated to a class
	labID = "N/A";
	
	tmp->currentAllocateNode->updateNodeVals(allocateStudentID, subjectCode, allocateDate, labID, labTime, labRoomNum, labBuild);
	tmp->next = NULL;

	if(this->list == NULL){
		this->list = tmp;
		this->head = this->list;
		this->tail = this->list;
	}else {
		this->head = this->list;
		alloListPtr cur = this->list;
		while(cur->next != NULL){
			
			cur = cur->next;
		}
		cur->next = tmp;
		tmp = this->list;
		this->head = this->list;
		this->tail = cur->next;
	}

}

void AllocationList::displayCurrentList(bool alterDisplay){
	
	if(this->list != NULL){
		alloListPtr current = this->list;
		while(current->next != NULL){
			current->currentAllocateNode->displayNodeAllocate(alterDisplay);
			current = current->next;
		}
	
		current->currentAllocateNode->displayNodeAllocate(alterDisplay);
	}
}

void AllocationList::findExistingList(int studentID, std::string subjectCode, std::string labEnrolIDSelect, std::string labTime, std::string labRoomNum, std::string labBuild){
	
	bool existEnrol = false;

	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);

	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
	int year = aTime->tm_year + 1900; // Year is # years since 1900
	
	std::string stringDay = "04";
	std::string stringMonth = "04";
	std::string stringYear = "14";

	std::string allocateDate = stringDay + "/" + stringMonth + "/" + stringYear;

	if(this->list== NULL){
		alloListPtr tmp = new AlloNodeContainer;
		tmp->currentAllocateNode = new AllocationNode();
		tmp->currentAllocateNode->updateNodeVals(studentID, subjectCode, allocateDate, labEnrolIDSelect, labTime, labRoomNum, labBuild);
		this->list = tmp;
		
	}else {
		alloListPtr cur = this->list;
		
		while(cur->next != NULL){
			if(cur->currentAllocateNode->getAllocateSubjectCode() == subjectCode){
				cur->currentAllocateNode->updateNodeVals(studentID, subjectCode, allocateDate, labEnrolIDSelect, labTime, labRoomNum, labBuild);
			}
			cur = cur->next;
		}
		if(cur->currentAllocateNode->getAllocateSubjectCode() == subjectCode){
			cur->currentAllocateNode->updateNodeVals(studentID, subjectCode, allocateDate, labEnrolIDSelect, labTime, labRoomNum, labBuild);
		}
	}
	
}

bool AllocationList::findMatchLabs(std::string labID, std::string subjectCode){

	alloListPtr current = this->list;
	bool found = false;
	bool stopList = false;
	
	if(this->list != NULL){
		while(current->next != NULL){
			if(stopList == false){
				found = current->currentAllocateNode->matchLabStudent(labID, subjectCode);
			}
			if(found){
				stopList = true;
			}
			current = current->next;
		}
		if(found == false && stopList == false){
			found = current->currentAllocateNode->matchLabStudent(labID, subjectCode);
		}
	}
	return found;
}

bool AllocationList::studentAllocated(std::string studentID, std::string subjectCode){
	 
	 bool confirm = false;
	 bool found = false;
	 
	 alloListPtr cur = this->list;
	 if(this->list != NULL){
		 while(cur->next != NULL){
		 
			if(found == false){
				confirm = cur->currentAllocateNode->checkEnrol(studentID, subjectCode);
				if(confirm){
					found = true;
					confirm = true;
				}
			}
			cur = cur->next;
		
		 }
	 
		 if(confirm == false && found == false){
			confirm = cur->currentAllocateNode->checkEnrol(studentID, subjectCode);
		 }
	}else {
		confirm = false;
	}	 
	
	return confirm;
	 
}

bool AllocationList::findExistingClass(std::string studentID, std::string subjectCode){

	bool found = false;
	bool track = true;
	if(this->list == NULL){
		return false;
	}else {
		alloListPtr cur = this->list;
		
		while(cur->next != NULL){
			if(track){
				if(cur->currentAllocateNode->returnNodeSubject() == subjectCode){
					found = cur->currentAllocateNode->checkLabEnrol(studentID, subjectCode);
					track = false;
				}
			}
			cur = cur->next;
		}
		if(track == false){
			if(cur->currentAllocateNode->returnNodeSubject() == subjectCode){
				found = cur->currentAllocateNode->checkLabEnrol(studentID, subjectCode);
			}
		}
	}
	return found;
	
}