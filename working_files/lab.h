#include<iostream>
#include<string>
#include<cstdlib>



struct integerRecord;
typedef integerRecord * intNodePtr;

void addValuetoList(intNodePtr & curList, int valueToAdd);
void destroyList(intNodePtr &);

struct integerRecord {

	int value;
	intNodePtr next;

};

class Lab {

	public:
	
		Lab();
		~Lab();
		void updateLabID(std::string);
		void updateCapacity(int);
		void updateSubjectCode(std::string);
		void updateBuilding(std::string);
		void updateRoom(std::string);
		void updateTime(std::string);
	
		std::string getLabID();
		int getCapacity();
		std::string getSubCode();
		std::string getBlding();
		std::string getRoomNum();
		std::string getTime();
		
		void displayLab();
		
	private:
		std::string labID;
		int maxCapacity;
		std::string subjectCode;
		std::string blding;
		std::string roomNum;
		std::string time;
};
