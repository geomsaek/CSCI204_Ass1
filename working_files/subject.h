#include<iostream>
#include<string>
#include<cstdlib>
#include "lab.h"

class Subject {

	public:
		Subject();
		~Subject();
		void updateSubTitle(std::string);
		void updateSubCode(std::string);
		void updateCredits(int);
		
		void displaySubTitle();
		void displaySubCode();
		void displayCredits();
		void displaySubStatus();
		
		std::string returnTitle();
		std::string returnCode();
		int returnCredits();

		void associateLabs(Lab *, int, Subject *, int, int);
		int returnLabNum();
	private:
		std::string subTitle;
		std::string subjectCode;
		int credits;
		
		Lab * enrolled;
		int associatedLabs;
};
