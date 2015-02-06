main:	main.o student.o lab.o subject.o enrolment.o allocation.o admin.o
		g++ -Wall -o ass1 main main.o student.o lab.o subject.o enrolment.o allocation.o admin.o

main.o:	main.cpp
		g++ -c main.cpp

lab.o: 	lab.cpp lab.h
		g++ -c lab.cpp
		
subject.o:	subject.cpp subject.h
		g++ -c subject.cpp
		
enrolment.o: enrolment.cpp enrolment.h
		g++ -c enrolment.cpp
		
allocation.o: allocation.cpp allocation.h
		g++ -c allocation.cpp
		
admin.o: admin.cpp admin.h
		g++ -c admin.cpp
		
student.o:	student.cpp student.h
		g++ -c student.cpp
		
ass1:	main.o student.o lab.o subject.o enrolment.o allocation.o admin.o
		g++ -Wall -o ass1 main.o student.o lab.o subject.o enrolment.o allocation.o admin.o
		
# run the "make clean" command to remove the files from the current directory
clean:
		rm main.o ass1 student.o lab.o subject.o enrolment.o allocation.o admin.o