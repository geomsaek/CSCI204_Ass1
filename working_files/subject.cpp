#include<iostream>
#include<cstdlib>
#include "subject.h"
using namespace std;
		
Subject::Subject(){
	subTitle = "";
	subjectCode = "";
	credits = 0;
	enrolled = NULL;
	associatedLabs = 0;
}

Subject::~Subject(){
	
	subTitle = "";
	subjectCode = "";
	credits = 0;
	
	if(enrolled != NULL){
		for(int i = 0; i < associatedLabs; i++){
			enrolled[i].~Lab();
		}
		delete enrolled;
		enrolled = NULL;
	}
	associatedLabs = 0;
}

void Subject::updateSubTitle(std::string newTitle){

	subTitle = newTitle;
}

void Subject::updateSubCode(std::string newCode){
	subjectCode = newCode;
}

void Subject::updateCredits(int creditValue){
	credits = creditValue;
}

void Subject::displaySubTitle(){
	std::cout << subTitle << std::endl;
}

void Subject::displaySubCode(){
	std::cout << subjectCode << std::endl;
}

void Subject::displayCredits(){
	std::cout << credits << std::endl;
}

void Subject::displaySubStatus(){
	std::cout << subjectCode << ", " << subTitle << ", " << credits << std::endl;
}

std::string Subject::returnTitle(){
	return subTitle;
}

std::string Subject::returnCode(){
	return subjectCode;
}

int Subject::returnCredits(){
	return credits;
}

// creates an association of labs to a selection of subjects

void Subject::associateLabs(Lab * curLabList, int curLabCount, Subject * curSubList, int curSubCount, int curSubject){
	
	intNodePtr labMatchIndex = NULL;
	int labCount = 0;
	int indexCount = 0;
	
	// loop through and retrieve all the indexes of the labs that match the current subject selection
	for(int k = 0; k < curLabCount; k ++){

		if(curSubList[curSubject].returnCode() == curLabList[k].getSubCode()){	
			addValuetoList(labMatchIndex, k);
			labCount = labCount + 1;
		}
	}
	
	// if there are a selection of indexes, loop through the stored indexes and create a new Lab array associated to the
	// current subject. Store the labs in the array for the current subject
	
	if(labCount > 0){
		curSubList[curSubject].enrolled = new Lab[labCount];
		
		intNodePtr cur = labMatchIndex;
		
		
		while(cur->next != NULL){
			curSubList[curSubject].enrolled[indexCount].updateLabID(curLabList[cur->value].getLabID());			
			indexCount = indexCount + 1;
			cur= cur->next;
		}
		curSubList[curSubject].enrolled[indexCount].updateLabID(curLabList[cur->value].getLabID());
		curSubList[curSubject].associatedLabs = labCount;
		
		destroyList(labMatchIndex);
		labCount = 0;
	}else {
	
		// if there are no subjects, assign the current enrolment pointer to NULL
		curSubList[curSubject].enrolled = NULL;
	}
	
}

int Subject::returnLabNum(){ return associatedLabs; }
