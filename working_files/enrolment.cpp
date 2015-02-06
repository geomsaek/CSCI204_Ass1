#include<iostream>
#include<cstdlib>
#include "enrolment.h"

Enrolment::Enrolment(){
	studentNum = 0;
	subjectCode = "";
	enrolDate = "";
}

Enrolment::~Enrolment(){
	studentNum = 0;
	subjectCode = "";
	enrolDate = "";
}

void Enrolment::updateStudentNum(int newStudentNum){ studentNum = newStudentNum; }
void Enrolment::updateSubjectCode(std::string newSubjectCode){ subjectCode = newSubjectCode; }
void Enrolment::updateEnrolDate(std::string newEnrolment){ enrolDate = newEnrolment; }

int Enrolment::getStudentNum(){ return studentNum; }
std::string Enrolment::getSubjectCode(){ return subjectCode; }
std::string Enrolment::getEnrolDate(){ return enrolDate; }

void Enrolment::displayEnrolment(){
	std::cout << subjectCode << ", " << studentNum << ", " << enrolDate << std::endl;
}
