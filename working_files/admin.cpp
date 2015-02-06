#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include "admin.h"

Admin::Admin(){

	stdSelect = NULL;
	totalStuds = 0;
	
	sbjtSelect = NULL;
	totalSubs = 0;
	
	labList = NULL;
	totalLabs = 0;
	
	enrols = NULL;
	totalEnrol = 0;
	
}

Admin::~Admin(){
	
	if(stdSelect != NULL){
		for(int s = 0; s < totalStuds; s++){
			stdSelect[s].~Student();
		}
		delete [] stdSelect;
		stdSelect = NULL;
	}
	
	totalStuds = 0;
	
	if(sbjtSelect == NULL){
		for(int l = 0; l < totalSubs; l++){
			sbjtSelect[l].~Subject();
		}
		delete [] sbjtSelect;
		sbjtSelect = NULL;
	}
	
	totalSubs = 0;
	
	if(labList != NULL){
		for(int b= 0; b < totalLabs; b++){
			labList[b].~Lab();
		}
		delete [] labList;
		labList = NULL;
	}
	totalLabs = 0;
	
	if(enrols != NULL){
		for(int e = 0; e < totalEnrol; e++){
			enrols[e].~Enrolment();
		}
		delete [] enrols;
		enrols = NULL;	
	}

	totalEnrol = 0;
	
}

// LOAD THE STUDENTS FROM A DESIGNATED FILE

void Admin::loadStudents(char loadStudent[]){
	
	if(totalStuds == 0){
		stdSelect = NULL;
	}
	
	std::string tempString, studentNum, name, email;
	int studentConvert = 0, comFind = 0, foundStudents = 0, convertLoop=0, value = 0;
	std::ifstream file;
	
	char separator = ',';
	nodePtr tempList = NULL;
	bool breakString = false;
	std::string fileName;
	std::cout << std::endl;

	std::cout << "Load students' records......" << std::endl;
	
	char * ptr;
	ptr = new char[(strlen(loadStudent) - 8) + 1];
	
	int arrayCount = 0;
	int length = strlen(loadStudent);
	for(int i = 8; i < length; i++){
		ptr[arrayCount] = loadStudent[i];
		arrayCount = arrayCount + 1;
	}
	ptr[length] = '\0';

	file.open(ptr);
	
	while(!file.eof()){

		std::getline(file, tempString);

		if(tempString.length() > 20){
			while(convertLoop < 2){
				// get the student number
				comFind = searchIndex(tempString, separator);
				
				switch(convertLoop){
					case 0:
						studentNum = subVal(tempString, 0, comFind);
					break;
					
					case 1:
						name = subVal(tempString, 0, comFind);
					break;
				}
				tempString = createSubString(tempString, comFind + 1, tempString.length());				
				convertLoop = convertLoop + 1;
			}

			email = tempString;
			convertLoop = 0;
			foundStudents = foundStudents + 1;
		
		}
		// create the new node
		studentConvert = atoi(studentNum.c_str());
		nodePtr tmp = new studentListNode;
		tmp->stdInstance.updateNum(studentConvert);
		tmp->stdInstance.updateName(name);
		tmp->stdInstance.updateEmail(email);
		tmp->next = NULL;
		
		if(tempList == NULL){
			tempList = tmp;
		}else {
			nodePtr cur = tempList;
			traverseList(cur);
			cur->next = tmp;
			tmp = tempList;
		}
	}

	createDynamicArray(tempList, foundStudents);
	deleteList(tempList);
	
	checkForEnrolments();
}

//create a dynamic array for the list of students
void Admin::createDynamicArray(nodePtr tempList, int studentTotal){
	
	stdSelect = new Student[studentTotal];
	totalStuds = studentTotal;
	int studentArray = 0;
	
	while(tempList->next != NULL){
		stdSelect[studentArray].updateNum(tempList->stdInstance.returnStudentNum());
		stdSelect[studentArray].updateName(tempList->stdInstance.returnName());
		stdSelect[studentArray].updateEmail(tempList->stdInstance.returnMail());
		tempList = tempList->next;
		studentArray = studentArray + 1;
	}
	
}

// delete a temporary list of student nodes
void Admin::deleteList(nodePtr & list){

	nodePtr tmpCopy;

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

// create a dynamic array of subjects based on a temporary list
void Admin::createSubjectArray(subNodePtr tempList, int subjectTotal){
	
	sbjtSelect = new Subject[subjectTotal];
	totalSubs = subjectTotal;
	int subjectArray = 0;
	
	while(tempList->next != NULL){
		sbjtSelect[subjectArray].updateSubTitle(tempList->sbjctInstance.returnTitle());
		sbjtSelect[subjectArray].updateSubCode(tempList->sbjctInstance.returnCode());
		sbjtSelect[subjectArray].updateCredits(tempList->sbjctInstance.returnCredits());
		tempList = tempList->next;
		subjectArray = subjectArray + 1;
	}
	
	sbjtSelect[subjectArray].updateSubTitle(tempList->sbjctInstance.returnTitle());
	sbjtSelect[subjectArray].updateSubCode(tempList->sbjctInstance.returnCode());
	sbjtSelect[subjectArray].updateCredits(tempList->sbjctInstance.returnCredits());
}

// delete a temporary list of subject nodes
void Admin::deleteSubList(subNodePtr & list){

	subNodePtr tmpCopy;

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



int Admin::searchIndex(std::string value, char searchChar){
	return value.find(searchChar);
}

std::string Admin::subVal(std::string value, int start, int finish){
	return value.substr(start, finish);
}

std::string Admin::createSubString(std::string & value, int startIndex, int finish){

	value = value.substr(startIndex, finish);
	return value;
}

void Admin::traverseList(nodePtr & currentList){

	if(currentList != NULL){

		// otherwise, go through list	
		while(currentList->next != NULL){
			currentList = currentList->next;
		}
		
	}
}

// FUNCTIONS DEFINING THE ACTION OF LOADING THE SUBJECTS INTO THE SYSTEM

void Admin::loadSubjects(char subjectFile[]){

	if(totalSubs == 0){
		sbjtSelect = NULL;
	}
	
	std::ifstream file;
	std::string fileName, tempString;
	char separator = ',';
	int loadedSubjects = 0;
	
	subNodePtr tmpList = NULL;
	int tempCredit = 0;
	
	std::string * valPointer = NULL;
	
	std::cout << std::endl;
	std::cout << "Load subjects' records......" << std::endl;
	
	char * ptr;
	ptr = new char[(strlen(subjectFile) - 8) + 1];
	
	int arrayCount = 0;
	int length = strlen(subjectFile);
	for(int i = 8; i < length; i++){
		ptr[arrayCount] = subjectFile[i];
		arrayCount = arrayCount + 1;
	}
	ptr[length] = '\0';
	
	file.open(ptr);
	
	while(!file.eof()){
		std::getline(file, tempString);
		if(tempString.length() > 5){
			valPointer= splitString(tempString, separator);
			
			tempCredit = atoi(valPointer[2].c_str());
			subNodePtr tmp = new subjectListNode;
			tmp->sbjctInstance.updateSubCode(valPointer[0]);
			tmp->sbjctInstance.updateSubTitle(valPointer[1]);

			tmp->sbjctInstance.updateCredits(tempCredit);
			tmp->next = NULL;
			
			if(tmpList == NULL){
				tmpList = tmp;
			}else {
				subNodePtr cur = tmpList;
				while(cur->next != NULL){
					cur = cur->next;
				}
				cur->next = tmp;
				tmp = tmpList;
			}
			loadedSubjects = loadedSubjects + 1;
			
		}

	}
	
	createSubjectArray(tmpList, loadedSubjects);
	deleteSubList(tmpList);
	delete [] valPointer;
	valPointer = NULL;
	
}

std::string * Admin::splitString(std::string splitValue, char searchValue){
	
	int amount = 0;
	int word = 0;
	int letter = 0;
	
	for(int i = 0; i < splitValue.length(); i++){
		if(splitValue[i] == searchValue){
			amount = amount + 1;
			if(letter > 0){
				word = word + 1;
			}
			
		}else {
			letter = letter + 1;
		}
		
	}
	
	if(letter > 0){
		word = word + 1;
	}
	
	std::string * values = NULL;
	values = new std::string[word];
	std::string dupString = splitValue;
	bool end = false;
	int commaCount = 0;
	int arrayPoint = 0;
	
	//storeValues = &values;
	
	while(commaCount < amount){	
		values[arrayPoint] = dupString.substr(0, dupString.find(searchValue));

		dupString = dupString.substr(dupString.find(searchValue) + 1, dupString.length());
		arrayPoint = arrayPoint + 1;
		commaCount = commaCount + 1;

		if(commaCount  == amount && dupString.length() > 0){
			values[arrayPoint] = dupString;
			arrayPoint = arrayPoint + 1;			
		}
	}
	
	return values;
	
}


/** LOAD LABS **/

void Admin::loadLabs(char labFile[]){
	
	if(totalLabs == 0){
		labList = NULL;
	}
	
	std::ifstream file;
	std::string fileName, tempString;
	char separator = ',';
	
	int loadedLabs = 0;
	int capacityTemp = 0;
	labNodePtr labTempList = NULL;
	
	std::string * valPointer;
	
	std::cout << std::endl;
	std::cout << "Load labs' records......" << std::endl;
	
	char * ptr;
	ptr = new char[(strlen(labFile) - 4) + 1];
	
	int arrayCount = 0;
	int length = strlen(labFile);
	for(int i = 4; i < length; i++){
		ptr[arrayCount] = labFile[i];
		arrayCount = arrayCount + 1;
	}
	ptr[length] = '\0';
	
	file.open(ptr);
	
	while(!file.eof()){
		
		std::getline(file, tempString);
		
		if(tempString.length() > 10){
			valPointer= splitString(tempString, separator);

			labNodePtr tempLabNode = new labListNode;
			
			tempLabNode->labInstance.updateLabID(valPointer[0]);
			capacityTemp = atoi(valPointer[1].c_str());
			
			tempLabNode->labInstance.updateCapacity(capacityTemp);
			tempLabNode->labInstance.updateSubjectCode(valPointer[2]);
			tempLabNode->labInstance.updateBuilding(valPointer[3]);
			tempLabNode->labInstance.updateRoom(valPointer[4]);
			tempLabNode->labInstance.updateTime(valPointer[5]);
			tempLabNode->next = NULL;
			
			if(labTempList == NULL){
				labTempList = tempLabNode;
			}else {
				labNodePtr curLabList = labTempList;
				while(curLabList->next){
					curLabList = curLabList->next;
				}
				curLabList->next = tempLabNode;
				tempLabNode = labTempList;
			}
			loadedLabs = loadedLabs + 1;
			
		}
	}
	createLabArray(labTempList, loadedLabs);
	deleteLabList(labTempList);
	delete [] valPointer;
	valPointer = NULL;

	setSubjectLabData();
	
}

void Admin::createLabArray(labNodePtr tempList, int labTotal){
	
	labList = new Lab[labTotal];
	totalLabs = labTotal;
	
	int labArray = 0;

	while(tempList->next != NULL){
		labList[labArray].updateLabID(tempList->labInstance.getLabID());
		labList[labArray].updateCapacity(tempList->labInstance.getCapacity());
		labList[labArray].updateSubjectCode(tempList->labInstance.getSubCode());
		labList[labArray].updateBuilding(tempList->labInstance.getBlding());
		labList[labArray].updateRoom(tempList->labInstance.getRoomNum());
		labList[labArray].updateTime(tempList->labInstance.getTime());
		tempList = tempList->next;
		labArray = labArray + 1;
	}
		
	labList[labArray].updateLabID(tempList->labInstance.getLabID());
	labList[labArray].updateCapacity(tempList->labInstance.getCapacity());
	labList[labArray].updateSubjectCode(tempList->labInstance.getSubCode());
	labList[labArray].updateBuilding(tempList->labInstance.getBlding());
	labList[labArray].updateRoom(tempList->labInstance.getRoomNum());
	labList[labArray].updateTime(tempList->labInstance.getTime());	
}

void Admin::deleteLabList(labNodePtr & list){

	labNodePtr tmpCopy;

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

/** LOAD ENROLMENTS **/

void Admin::loadEnrolments(char enrolFile[]){
	
	if(totalEnrol == 0){
		enrols = NULL;
	}
	
	std::ifstream file;
	std::string fileName, tempString;
	char separator = ',';
	
	int recordEnrol = 0;
	int stdNumTemp = 0;
	enrolNodePtr tmpList = NULL;
	
	std::string * valPointer = NULL;
	
	std::cout << std::endl;
	std::cout << "Load enrolments' records......" << std::endl;
	
	char * ptr;
	ptr = new char[(strlen(enrolFile) - 10) + 1];
	
	int arrayCount = 0;
	int length = strlen(enrolFile);
	for(int i = 10; i < length; i++){
		ptr[arrayCount] = enrolFile[i];
		arrayCount = arrayCount + 1;
	}
	ptr[length] = '\0';
	
	file.open(ptr);
	
	while(!file.eof()){
		std::getline(file, tempString);
		
		
		if(tempString.length() > 10){
			
			valPointer= splitString(tempString, separator);
			stdNumTemp = atoi(valPointer[1].c_str());

			enrolNodePtr tmp = new enrolNode;
			tmp->enrolInstance.updateSubjectCode(valPointer[0]);
			tmp->enrolInstance.updateStudentNum(stdNumTemp);
			tmp->enrolInstance.updateEnrolDate(valPointer[2]);
			tmp->next = NULL;
			
			if(tmpList == NULL){
				tmpList = tmp;
			}else {
				enrolNodePtr curItem = tmpList;
				
				while(curItem->next != NULL){
					curItem = curItem->next;
				}
				curItem->next = tmp;
				tmp = tmpList;
			}
			recordEnrol = recordEnrol + 1;
		}

	}
	
	createEnrolArray(tmpList, recordEnrol);
	deleteEnrolList(tmpList);
	delete [] valPointer;
	valPointer = NULL;
	checkForEnrolments();
	allocateStudentClasses();
}

void Admin::createEnrolArray(enrolNodePtr tempList, int enrolledTotal){
	
	enrols = new Enrolment[enrolledTotal];
	totalEnrol = enrolledTotal;
	
	int enrolArray = 0;
	
	while(tempList->next != NULL){
		enrols[enrolArray].updateStudentNum(tempList->enrolInstance.getStudentNum());
		enrols[enrolArray].updateSubjectCode(tempList->enrolInstance.getSubjectCode());
		enrols[enrolArray].updateEnrolDate(tempList->enrolInstance.getEnrolDate());
		
		tempList = tempList->next;
		enrolArray = enrolArray + 1;
	}
	
	enrols[enrolArray].updateStudentNum(tempList->enrolInstance.getStudentNum());
	enrols[enrolArray].updateSubjectCode(tempList->enrolInstance.getSubjectCode());
	enrols[enrolArray].updateEnrolDate(tempList->enrolInstance.getEnrolDate());
}

void Admin::deleteEnrolList(enrolNodePtr & list) {

	enrolNodePtr tmpCopy;

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


/********************* PRINTING STUDENT FUNCTION *********************/

void Admin::printStudents(){
	if(stdSelect != NULL){
		std::cout << std::endl;
		std::cout << "The total of students that exist is: " << totalStuds << std::endl;
		for(int i = 0; i < totalStuds; i ++){
			stdSelect[i].displayStudent();
		}
		std::cout << std::endl;
		
	}else {
		std::cout << std::endl;
		std::cout << "*********** ERROR!! Students need to be uploaded before they can be displayed! ***********" << std::endl;
		std::cout << std::endl;
	}
}

/********************* PRINTING SUBJECT FUNCTION *********************/

void Admin::printSubjects(){

	if(sbjtSelect != NULL){
	
		std::cout << std::endl;
		std::cout << "The total of subjects that exist is: " << totalSubs << std::endl;
		for(int i = 0; i < totalSubs; i ++){
			sbjtSelect[i].displaySubStatus();
		}
		std::cout << std::endl;
		
	}else {
		std::cout << std::endl;
		std::cout << "*********** ERROR!! Subjects need to be uploaded before they can be displayed! ***********" << std::endl;
		std::cout << std::endl;
	}
}

/********************* PRINTING LAB FUNCTION *********************/

void Admin::printLabs(){

	if(labList != NULL){
	
		std::cout << std::endl;
		std::cout << "The total of labs that exist is: " << totalLabs << std::endl;
		for(int i = 0; i < totalLabs; i ++){
			labList[i].displayLab();
		}
		std::cout << std::endl;
		
	}else {
		std::cout << std::endl;
		std::cout << "*********** ERROR!! Labs need to be uploaded before they can be displayed! ***********" << std::endl;
		std::cout << std::endl;
	}
}

/********************* PRINTING ENROLMENT FUNCTION *********************/

void Admin::printEnrolments(){

	if(labList != NULL){
	
		std::cout << std::endl;
		std::cout << "The total of enrolments that exist is: " << totalEnrol << std::endl;
		for(int i = 0; i < totalEnrol; i ++){
			enrols[i].displayEnrolment();
		}
		std::cout << std::endl;
		
	}else {
		std::cout << std::endl;
		std::cout << "*********** ERROR!! Enrolments need to be uploaded before they can be displayed! ***********" << std::endl;
		std::cout << std::endl;
	}
}

/********** DISPLAY SUBJECTS FOR A STUDENT *************/

void Admin::displaySubjects() {

	bool inputExit = false;
	std::string searchValue;
	int convertNumber = 0;
	bool match = false;
	int storeIndex = 0;
	
	while(inputExit == false){
	
		std::cout << "Student number (0-Exit): ";
		getline(std::cin, searchValue);
		if(searchValue == "0"){
			std::cout << "Input has been terminated" << std::endl;
			inputExit = true;
		}else {
			convertNumber = atoi(searchValue.c_str());
			for(int i = 0; i < totalStuds; i++){
				if(stdSelect[i].returnStudentNum() == convertNumber){
					storeIndex = i;
					match = true;
				}
			}
		
			if(match){
				std::cout << "Student number " << searchValue << std::endl;
				std::cout << "Enrolled in the following subjects: ";
				stdSelect[storeIndex].displayEnrolments();
				std::cout << std::endl;
				inputExit = true;
			}else {
				std::cout << "Student number " << searchValue << " does not exist!" << std::endl;
				std::cin.clear();
			}
		}
	}

}

/************ DISPLAY LABS FOR A SUBJECT *****************/


void Admin::displayLabs(){
	
	bool inputExit = false;
	std::string searchValue;
	bool match = false;
	bool labMatch = false;
	int storeIndex = 0;
	bool initialLab = true;
	
	while(inputExit == false){
		std::cout << "Subject code (0-Exit): ";
		getline(std::cin, searchValue);
		if(searchValue == "0"){
			std::cout << "Input has been terminated" << std::endl;
			inputExit = true;
		}else {
			for(int i = 0; i < totalSubs; i++){
				if(sbjtSelect[i].returnCode() == searchValue){
					match = true;
				}
			}
			if(match){
				for(int i = 0; i < totalLabs; i++){
					if(labList[i].getSubCode() == searchValue){
						if(initialLab){
							std::cout << "Available labs/tutorials: ";
							initialLab = false;
						}
						labMatch = true;
						std::cout << labList[i].getLabID() << ", ";
					}
				}
				if(!labMatch){
					std::cout << "Sorry, there were no tutorials for this subject" << std::endl;
					inputExit = true; 
				}else {
					std::cout << std::endl;
					inputExit = true;
				}
			}else {
				std::cout << "Incorrect subject code." << std::endl;
			}	
		}
	}
	
} 


/******** ASSOCIATING VALUES TO STUDENT ***********/

// ADDING ENROLMENTS TO A STUDENT
void Admin::checkForEnrolments(){
	if(totalEnrol > 0){
		for(int i = 0; i < totalStuds; i++){
			stdSelect[i].updateEnrolmentStatus(totalEnrol, enrols);

		}	
	}
}

/***** CREATE THE ALLOCATION LIST  **************/

void Admin::allocateStudentClasses() {

	if(totalStuds > 0 && totalLabs > 0){
		for(int i = 0; i < totalStuds; i++){
			stdSelect[i].establishAllocation(enrols,totalEnrol, this->labList, this->totalLabs);

			// display associated classes to each student
			//stdSelect[i].displayAllocations();
		}
	}
}

/*********ASSOCIATING LABS TO SUBJECT **************/

void Admin::setSubjectLabData(){

	if(totalLabs > 0 && totalSubs > 0){
		for(int i = 0; i < totalSubs; i++){
			sbjtSelect[i].associateLabs(labList, totalLabs, sbjtSelect, totalSubs, i);
		}
	}
}

/********* PRINT LAB ALLOCATION LIST *********/

void Admin::printLabAllocationList(){
	std::cout << std::endl;
	std::string labIDCopy;
	std::string curSubject;
	for(int i = 0; i < totalSubs; i++){
		curSubject = sbjtSelect[i].returnCode();
		
		if(sbjtSelect[i].returnLabNum() > 0){
			
			for(int l = 0; l < totalLabs; l++){
				
				if(labList[l].getSubCode() == curSubject){
					std::cout << curSubject << "--" << sbjtSelect[i].returnTitle() << std::endl;
					std::cout << "Lab/ Tutorial: ";

					//labIDCopy = labList[l].getLabID();
					std::cout << labList[l].getLabID() << std::endl;
					findMatchingStudents(labList[l].getLabID(), labList[l].getSubCode());
					std::cout << std::endl;
				}
			}
		}else {
			std::cout << curSubject << "--" << sbjtSelect[i].returnTitle() << std::endl;
			std::cout << "Lab/ Tutorial: N/A";
			std::cout << std::endl;
			std::cout << std::endl;
		}
		
		
		
	}
}

void Admin::findMatchingStudents(std::string curLabID, std::string subCode) {

	bool found = false;
	for(int i = 0; i < totalStuds; i++){
	
		found = stdSelect[i].matchLabID(curLabID, subCode);
		if(found){
			std::cout << stdSelect[i].returnStudentNum() << ", " << stdSelect[i].returnName() << ", " << stdSelect[i].returnMail() << std::endl;
		}
		found = false;
	}
}

/********** MANIPULATE THE IMPORTED DATA *************/

void Admin::organiseLabs(){

	bool correctInput = false;
	int responseType = 0;
	std::string studentInput ="";
	std::string subjectInput ="";
	std::string labAllocation ="";
	bool innerTrue = false;
	int changeStudentNum = 0;
	
	bool showMessage= true;
	bool showSubjectMessage = true;
	
	std::string terminate  = "0";
	
	while(correctInput == false){
	
		if(showMessage){
			 std::cout << "Student number (0-Exit): ";
			 showMessage= false;
		}
		getline(std::cin, studentInput);

		if(studentInput == "0"){
			std::cout << "Input has been terminated" << std::endl;
			correctInput = true;
		}else {
			innerTrue = checkValue(studentInput, subjectInput, 1);
		}
		if(innerTrue){
			innerTrue = false;
			showSubjectMessage = true;
			while(innerTrue == false){
				if(showSubjectMessage){
					std::cout << "Subject code (0-Stop): ";
					showSubjectMessage = false;
				}
				getline(std::cin, subjectInput);
				if(subjectInput == "0"){
					innerTrue = true;
					showMessage = true;
				}else {
					innerTrue = checkValue(studentInput, subjectInput, 2);
					if(innerTrue){
						checkChangeLab(changeStudentNum, subjectInput,labAllocation);
						changeStudentNum = atoi(studentInput.c_str());
						allocateStudentToLab(changeStudentNum, subjectInput, labAllocation);

						correctInput = true;
						innerTrue = true;
					}else {
						showSubjectMessage = true;
					}
				}
			}
			innerTrue = false;
			correctInput = false;
			showSubjectMessage = true;
			 showMessage= true;
		}else {
			 showMessage= true;
		}
		
	}
	
}

bool Admin::checkValue(std::string studentNum, std::string subjectCode, int selection){
	
	int studentNumConvert = 0;
	bool found = false;
	int find = 0;
	bool alreadyEnrolled = false;
	
	switch(selection){
		case 1:
			studentNumConvert = atoi(studentNum.c_str());
			
			for(int s = 0; s < totalStuds; s++){
				if(stdSelect[s].returnStudentNum() == studentNumConvert){
					found = true;
				}
			}
			if(!found){
				std::cout << "Incorrect student code" << std::endl;
			}
			
		break;
		
		case 2:
		
			for(int i = 0; i < totalSubs; i++){
				if(sbjtSelect[i].returnCode() == subjectCode){
					found = true;
				}
			}
			if(!found){
				std:cout << "Please enter a correct subject code" <<std::endl;
			}else {
				alreadyEnrolled = checkExistingEnrol(studentNum, subjectCode);
				if(alreadyEnrolled){
					found = false;
					std::cout << "The student has already been allocated in a lab/tutorial for this subject." << std::endl;
				}else {
					std::cout << "Available labs/tutorials: ";
					for(int l = 0; l < totalLabs; l++){
						if(subjectCode == labList[l].getSubCode()){
							std::cout << labList[l].getLabID() << ", ";
							find = find + 1;
						}
					}
					if(find == 0){
						std::cout << "There are no labs/ tutorials for this subject" << std::endl;
						found = false;
					}else {
						found = true;
						std::cout << std::endl;
					}
				}
			
			}
			
		break;
	}
	
	return found;
}

bool Admin::checkExistingEnrol(std::string studentID, std::string subjectCode){
	
	bool found = false;
	int convertNum = 0;
	convertNum = atoi(studentID.c_str());
	
	for(int i = 0; i < totalStuds; i++){
		if(stdSelect[i].returnStudentNum() == convertNum){
			found = stdSelect[i].checkAllocation(studentID, subjectCode);
			i = totalStuds;
		}
	}
	return found;
}

void Admin::checkChangeLab(int singleStudentId, std::string labSubjectCode, std::string & labAllocation){
	
	int storeIndex = 0;
	int * ptr;
	bool found = false;
	bool userInput = false;
	int countSubs = 0;
	bool initial = true;
	int arrayCount = 0;
	
	for(int i = 0; i < totalLabs; i++){
		if(labList[i].getSubCode() == labSubjectCode){
			storeIndex = i;
			countSubs = countSubs + 1;
			found = true;
		}
	}
	if(found){
		ptr = new int[countSubs];
	
		for(int m = 0; m < totalLabs; m++){
			if(labList[m].getSubCode() == labSubjectCode){
				ptr[arrayCount] = m;
				arrayCount = arrayCount + 1;
			}
		}
			
		while(userInput == false){
			
			if(initial){
				std::cout << "Lab ID: ";
				initial = false;
			}
			getline(std::cin, labAllocation);
		
			for(int k = 0; k < countSubs; k++){
				if(labList[ptr[k]].getLabID() == labAllocation){
					userInput = true;
					k = countSubs;
				}
			}
			if(!userInput){
				std::cout << "Student cannot be allocated in this lab/tutorial." << std::endl;
				std::cout << "Lab ID: ";
			}
		}
		
		delete []ptr;
	}
}

void Admin::allocateStudentToLab(int studentUserID, std::string subjectUserCode, std::string labUserAllocate){

	// is the student already enrolled in the list
	// if they are modify the labID and possibly the date
	// if they are not, create a new list item in their allocation list
	
	for(int i = 0; i < totalStuds; i++){
		if(stdSelect[i].returnStudentNum() == studentUserID){
			stdSelect[i].updateStudentAllocate(studentUserID, subjectUserCode, labUserAllocate, this->labList, totalLabs);
			std::cout << "Enrolled in the subjects: ";
			stdSelect[i].displayAllocations(false);
			i = totalStuds;
		}
	}
}

