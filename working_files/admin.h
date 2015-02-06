#include<iostream>
#include<fstream>
#include<cstdlib>
#include "student.h"

struct studentListNode;
struct subjectListNode;
struct labListNode;
struct enrolNode;

typedef studentListNode * nodePtr;
typedef subjectListNode * subNodePtr;
typedef labListNode * labNodePtr;
typedef enrolNode * enrolNodePtr;

struct studentListNode {
	Student stdInstance;
	nodePtr next;

};

struct subjectListNode {
	Subject sbjctInstance;
	subNodePtr next;
};

struct labListNode {
	Lab labInstance;
	labNodePtr next;
};

struct enrolNode {
	Enrolment enrolInstance;
	enrolNodePtr next;
};

class Admin {
	
	public:
		
		Admin();
		~Admin();
		void loadStudents(char[]);
		void loadSubjects(char[]);
		void loadLabs(char[]);
		void loadEnrolments(char[]);

		void printStudents();
		void printSubjects();
		void printLabs();
		void printEnrolments();
		
		void displaySubjects();
		void displayLabs();
		
		void organiseLabs();
		void printLabAllocationList();
		
	private:
		Student * stdSelect;
		int totalStuds;
		
		Subject * sbjtSelect;
		int totalSubs;
		
		Lab * labList;
		int totalLabs;
		
		Enrolment * enrols;
		int totalEnrol;
		
		// object of linked list for student's lab allocations

		int searchIndex(std::string, char);
		std::string subVal(std::string, int, int);
		void traverseList(nodePtr & currentList);
		std::string createSubString(std::string &, int, int);
		
		// operations for a list of students
		void createDynamicArray(nodePtr, int);
		void deleteList(nodePtr & list);
		
		// operations for a list of subjects
		void createSubjectArray(subNodePtr, int);
		void deleteSubList(subNodePtr &);
		
		//operations for a list of labs
		void createLabArray(labNodePtr, int);
		void deleteLabList(labNodePtr &);
		
		//operations for a list of Enrolments
		void createEnrolArray(enrolNodePtr, int);
		void deleteEnrolList(enrolNodePtr &);
		
		std::string* splitString(std::string splitValue, char searchValue);

		// associating enrolment data to a student
		void checkForEnrolments();
		
		// associating lab data to a subject
		void setSubjectLabData();
		
		void allocateStudentClasses();
		bool checkValue(std::string, std::string, int);
		void checkChangeLab(int, std::string, std::string &);
		void allocateStudentToLab(int, std::string, std::string);
		void findMatchingStudents(std::string, std::string);
		bool checkExistingEnrol(std::string, std::string);
		
};
