#include<iostream>
#include<string>
#include<cstdlib>

class Enrolment {

	public:
		Enrolment();
		~Enrolment();
		
		void updateStudentNum(int);
		void updateSubjectCode(std::string);
		void updateEnrolDate(std::string);
		
		int getStudentNum();
		std::string getSubjectCode();
		std::string getEnrolDate();
		
		void displayEnrolment();
	
	private:
		int studentNum;
		std::string subjectCode;
		std::string enrolDate;
};
