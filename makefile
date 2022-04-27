#to run: make
#to elminate .o file: make clean
calc: myCalcTst.o myCalc.o stack2.o list.o
	g++ -o myCalc myCalcTst.o myCalc.o stack2.o list.o

myCalcTst.o: myCalcTst.cpp
	g++ -c myCalcTst.cpp 

myCalc.o: myCalc.cpp
	g++ -c myCalc.cpp 

stack1.o: stack1.cpp
	g++ -c stack2.cpp 

list1.o: list.cpp
	g++ -c list.cpp 

clean :
	rm *.o
