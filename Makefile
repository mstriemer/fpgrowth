crun : compile run

run : fpgrowth.out
	./fpgrowth.out db4.txt 2 5

compile : fpgrowth.cpp Database.cpp Transaction.cpp Header.cpp TreeElement.cpp ItemSet.cpp
	g++ fpgrowth.cpp Database.cpp Transaction.cpp Header.cpp TreeElement.cpp hElement.cpp ItemSet.cpp -o fpgrowth.out
