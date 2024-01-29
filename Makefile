all: proj3.mine.x

proj3.mine.x: proj3_driver.o bet.o
	g++ -std=c++11 proj3_driver.o bet.o -o proj3.mine.x

proj3_driver.o: proj3_driver.cpp
	g++ -std=c++11 -c proj3_driver.cpp

bet.o: bet.cpp
	g++ -std=c++11 -c bet.cpp

clean:
	rm *.o *.x