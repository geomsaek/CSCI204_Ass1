#include<iostream>
#include<string>
#include<cstdlib>
#include "enrolment.h"
#include "Subject.h"
#include "Allocation.h"
using namespace std;

class Student {

	public:
		Student();
		~Student();
		void updateNum(int);
		void updateName(std::string);
		void updateEmail(std::string);
		void outNumber();
		
		int returnStudentNum();
		std::string returnName();
		std::string returnMail();
		
		void displayNum();
		void displayName();
		void displayMail();
		
		void displayStudent();
		
		void updateEnrolmentStatus(int, Enrolment *);
		void establishAllocation(Enrolment *, int, Lab *, int);
		void displayAllocations(bool);
		bool checkAllocation(std::string, std::string);
		void displayEnrolments();
		void displaySubjects();
		
		int getEnrolCount();
		int getSubjectCount();
		int getAllocate();
		
		void displaySubjectCodes();
		void updateStudentAllocate(int, std::string, std::string, Lab*, int);
		bool checkEnrolment(std::string, std::string);
		
		bool matchLabID(std::string, std::string);
	private:
		int studentNum;
		std::string name;
		std::string email;
		
		Enrolment * studentClasses;
		int enrolledSubs;
		
		Subject * studentSubjects;
		int subjectCount;
		
		allocatedList StudentAllocation;
		int allocateCount;

};
