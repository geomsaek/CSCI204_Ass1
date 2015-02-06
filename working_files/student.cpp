#include<iostream>
#include<string>
#include<cstdlib>
#include "student.h"

Student::Student(){

	studentNum = 0;
	name = "";
	email = "";
	enrolledSubs = 0;
	studentClasses = NULL;
	studentSubjects = NULL;
	StudentAllocation = new AllocationList();

}

Student::~Student(){

	studentNum = 0;
	enrolledSubs = 0;
	name = "";
	email = "";
	
	if(studentClasses != NULL){
	
		for(int i = 0; i < enrolledSubs; i++){
			studentClasses[i].~Enrolment();
		}
		delete [] studentClasses;
		studentClasses = NULL;
	}
	
	if(studentSubjects != NULL){
		for(int s = 0; s < subjectCount; s++){
			studentSubjects[s].~Subject();
		}
		delete [] studentSubjects;
		studentSubjects = NULL;
	}
	
	if(StudentAllocation != NULL){
		
		StudentAllocation->~AllocationList();
		delete StudentAllocation;
		StudentAllocation = NULL;
		
		allocateCount = 0;
	}

}

// update the current values
void Student::updateNum(int value){ studentNum = value; }
void Student::updateName(std::string studentName) { name = studentName; }
void Student::updateEmail(std::string newEmail){ email = newEmail; }
void Student::outNumber(){ std::cout << "studentNumber: " << studentNum; }


void Student::displayAllocations(bool alterDisplay) {

	StudentAllocation->displayCurrentList(alterDisplay);
	std::cout << std::endl;
}

void Student::displayEnrolments(){
	if(this->enrolledSubs > 0){
		for(int i = 0; i < this->enrolledSubs; i++){
			std::cout << studentClasses[i].getSubjectCode() << ", ";
		}
	}else {
		std::cout << "Student is not enrolled in any subjects" << std::endl;
	}
}

void Student::displaySubjects(){
	
}

// return values
int Student::returnStudentNum(){ return studentNum; }
std::string Student::returnName(){ return name; }
std::string Student::returnMail(){ return email; }
int Student::getEnrolCount(){ return enrolledSubs; }
int Student::getSubjectCount(){ return enrolledSubs; }
int Student::getAllocate(){ return allocateCount; }

// display values
void Student::displayNum(){ std::cout << studentNum << std::endl; }
void Student::displayName(){ std::cout << name << std::endl; }
void Student::displayMail(){ std::cout << email << std::endl; }

void Student::displaySubjectCodes(){

	std::cout << "enrolledSubs: " << enrolledSubs << std::endl;
}

void Student::displayStudent(){

	std::cout << studentNum << ", " << name << ", " << email << std::endl;
}

void Student::updateEnrolmentStatus(int enrolCount, Enrolment * connect){
	
	intNodePtr indexList = NULL;
	
	int count = 0;
	for(int i = 0;i < enrolCount; i++){
		if(studentNum == connect[i].getStudentNum()){
			intNodePtr tmp = new integerRecord;
			tmp->value = i;
			tmp->next = NULL;

			count = count + 1;
			
			if(indexList == NULL){
				indexList = tmp;
			}else {
				intNodePtr tempCur = indexList;
				while(tempCur->next != NULL){
					tempCur = tempCur->next;
				}
				tempCur->next = tmp;
				tmp = indexList;
			}
		}
	}
	
	if(count > 0){
		studentClasses = new Enrolment[count];
		enrolledSubs = count;
		int indexCount = 0;
		intNodePtr cur = indexList;
	
		while(cur->next != NULL){
			studentClasses[indexCount].updateStudentNum(connect[cur->value].getStudentNum());
			studentClasses[indexCount].updateSubjectCode(connect[cur->value].getSubjectCode());
			studentClasses[indexCount].updateEnrolDate(connect[cur->value].getEnrolDate());
			indexCount = indexCount +1;
			cur = cur->next;
		}
		
		studentClasses[indexCount].updateStudentNum(connect[cur->value].getStudentNum());
		studentClasses[indexCount].updateSubjectCode(connect[cur->value].getSubjectCode());
		studentClasses[indexCount].updateEnrolDate(connect[cur->value].getEnrolDate());
		destroyList(indexList);
	}
	
}

// CREATE AN ALLOCATION LIST FOR THE CURRENT STUDENT

void Student::establishAllocation(Enrolment * currentEnrols, int totalEnrols, Lab * labList, int labListLength){
	
	intNodePtr classIndexList = NULL;
	int countIndex = 0;
	int indexCount = 0;
	
	for(int i = 0; i < totalEnrols; i++){
		
		if(currentEnrols[i].getStudentNum() == this->returnStudentNum()){
			addValuetoList(classIndexList, i);
			countIndex = countIndex + 1;
		}
	
	}
	
	if(countIndex > 0){
		
		int enrolID = 0;
		std::string subCode;
		std::string enrolDate;
		
		std::string labBuild;
		std::string labRoomNum;
		std::string labTime;
		std::string labID;
		
		if(this->allocateCount == 0){
			
			intNodePtr currentItem = classIndexList;
			
			while(currentItem->next != NULL){
				
				enrolID = currentEnrols[currentItem->value].getStudentNum();
				subCode = currentEnrols[currentItem->value].getSubjectCode();
				enrolDate = currentEnrols[currentItem->value].getEnrolDate();
				for(int k = 0; k < labListLength; k++){
					if(labList[k].getSubCode() == subCode){
						labID = labList[k].getLabID();
						labTime = labList[k].getTime();
						labRoomNum = labList[k].getRoomNum();
						labBuild = labList[k].getBlding();
						
						k = labListLength;
					}
				}
				
				this->StudentAllocation->createNewList(enrolID, subCode, enrolDate, labID, labTime, labRoomNum, labBuild);
				
				currentItem = currentItem->next;
			}
			
			for(int k = 0; k < labListLength; k++){
				if(labList[k].getSubCode() == subCode){
					labID = labList[k].getLabID();
					labTime = labList[k].getTime();
					labRoomNum = labList[k].getRoomNum();
					labBuild = labList[k].getBlding();
					
					k = labListLength;
				}
			}
			enrolID = currentEnrols[currentItem->value].getStudentNum();
			subCode = currentEnrols[currentItem->value].getSubjectCode();
			enrolDate = currentEnrols[currentItem->value].getEnrolDate();
			
			
			this->StudentAllocation->createNewList(enrolID, subCode, enrolDate, labID, labTime, labRoomNum, labBuild);
			
		}
		destroyList(classIndexList);
		this->allocateCount = countIndex;
	}
	
}

void Student::updateStudentAllocate(int studentID, std::string subjectCode, std::string labEnrolIDSelect, Lab * labList, int labCount){
	
	//std::string labID;
	std::string labTime;
	std::string labRoomNum;
	std::string labBuild;
	
	for(int k = 0; k < labCount; k++){
		if(labList[k].getSubCode() == subjectCode){
			//labID = labList[k].getLabID();
			labTime = labList[k].getTime();
			labRoomNum = labList[k].getRoomNum();
			labBuild = labList[k].getBlding();
			
			k =  labCount;
		}
	}

	this->StudentAllocation->findExistingList(studentID, subjectCode, labEnrolIDSelect, labTime, labRoomNum, labBuild);
	
}

bool Student::checkEnrolment(std::string studID, std::string subCode){
	
	bool matched = false;
	matched = StudentAllocation->studentAllocated(studID, subCode);

	return matched;
}

bool Student::matchLabID(std::string labID, std::string subjectCode){
	bool find = false;
	
	find = this->StudentAllocation->findMatchLabs(labID, subjectCode);
	
	return find;
	
}

bool Student::checkAllocation(std::string studentID, std::string subjectCode) {
	

	bool found = false;
	found =	this->StudentAllocation->findExistingClass(studentID, subjectCode);
	return found;
}
