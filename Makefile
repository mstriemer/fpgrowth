crun : compile run

run : fpgrowth.out
	./fpgrowth.out db4.txt 2 5

compile : fpgrowth.cpp Database.cpp Transaction.cpp Header.cpp TreeElement.cpp
	g++ fpgrowth.cpp Database.cpp Transaction.cpp Header.cpp TreeElement.cpp hElement.cpp -o fpgrowth.out
