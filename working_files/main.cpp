#include<iostream>
#include<fstream>
#include<cstdlib>
#include "admin.h"

int main(int argc, char*argv[]){
	
	Admin test;

	for(int i = 0; i < argc; i++){
		switch(i){
			case 1:
				test.loadStudents(argv[i]);
			break;
			
			case 2:
				
				test.loadSubjects(argv[i]);
			break;
			
			case 3:
				test.loadLabs(argv[i]);
			break;
			
			case 4:
				
				test.loadEnrolments(argv[i]);
			break;
		}
		
	}
	
	test.printStudents();
	test.printSubjects();
	test.printLabs();
	test.printEnrolments();
	
	// manipulate lab allocation for students
	test.organiseLabs();
	
	// print out the lab allocation list for each lab;
	test.printLabAllocationList();


	return 0;
}
