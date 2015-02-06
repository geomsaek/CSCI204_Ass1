#include<iostream>
#include<string>
#include<cstdlib>
struct container;
class AllocationNode;
class Allocation;

typedef Allocation * AllocationClassPtr;
typedef AllocationNode * allocatePtr; 
typedef container * allocationNodeStructPtr;
class AllocationList;

struct container {
	 AllocationClassPtr newStudentAllocation;
	 allocationNodeStructPtr next;
};

struct AlloNodeContainer;
typedef AlloNodeContainer * alloListPtr;

struct AlloNodeContainer {
	allocatePtr currentAllocateNode;
	alloListPtr next;
};

typedef AllocationList * allocatedList;

class Allocation {

	public:
		Allocation();
		~Allocation();
		Allocation(int, std::string, std::string, int, std::string, std::string, std::string);

		void upAllocateStudentID(int);
		void upAllocateLab(std::string);
		void upAllocateSubCode(std::string);
		void upAllocateBuilding(int);
		void upAllocateRoom(std::string);
		void upAllocateLabTime(std::string);
		void upAllocateEnrolDate(std::string);
		
		int dStudentID();
		std::string dLabID();
		std::string dSubjectCode();
		int dbuildNum();
		std::string dRoomNum();
		std::string dLabTime();
		std::string dEnrolDate();
		
		void displayAllocation(bool);
	private:
		int studentNum;
		std::string labID;
		std::string subjectCode;
		int buildingNum;
		std::string roomNum;
		std::string labTime;
		std::string date;
		
};

class AllocationNode {
	
	public:
		AllocationNode();
		~AllocationNode();
		
		void updateNodeVals(int, std::string, std::string, std::string,std::string,std::string,std::string);
		void displayNodeAllocate(bool);
		
		std::string getAllocateSubjectCode();
		allocatePtr & returnHeadPointer();
		
		bool matchLabStudent(std::string, std::string);
		bool checkEnrol(std::string,std::string);
		bool checkLabEnrol(std::string, std::string);
		std::string returnNodeSubject();
		
	private:
		AllocationClassPtr allocationInstance;

		// points to the next Allocation Class Object

};

class AllocationList {
	
	public:
		AllocationList();
		~AllocationList();
		void createNewList(int allocateStudentID, std::string subjectCode, std::string allocateDate, std::string labID, std::string labTime, std::string labRoomNum, std::string labBuild);
		void findExistingList(int, std::string, std::string, std::string, std::string, std::string);
		void displayCurrentList(bool);
		bool studentAllocated(std::string, std::string);
		bool findMatchLabs(std::string, std::string);
		bool findExistingClass(std::string, std::string);
	private:
		
		alloListPtr head;
		alloListPtr list;
		alloListPtr tail;
		
};
