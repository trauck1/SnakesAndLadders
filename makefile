CXX = g++
CXXFLAGS = -Wall

driver: snakes.o  snakes.cpp
	$(CXX) $(CXXFLAGS) snakes.o driver.cpp -o driver

mytest: snakes.o  driver.cpp
	$(CXX) $(CXXFLAGS) snakes.o mytest.cpp -o mytest

snakes.o: snakes.cpp snakes.h
	$(CXX) $(CXXFLAGS) -c snakes.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./driver

runTest:
	./mytest
