crun : compile run
	./fpgrowth.out db1000.txt 5 1000

run :
	./fpgrowth.out db1000.txt 5 1000

compile : fpgrowth.cpp Database.cpp Transaction.cpp Header.cpp TreeElement.cpp
	g++ fpgrowth.cpp Database.cpp Transaction.cpp Header.cpp TreeElement.cpp -o fpgrowth.out
