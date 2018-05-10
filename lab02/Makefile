CXX=g++
CXXFLAGS=-ggdb -c -Wall -std=c++11

SOURCES=$(wildcard *.cpp)
H_FILES=$(wildcard *.h)
MAKEFILE=Makefile
TXT_FILES=$(wildcard *.txt)

OBJECTS=$(SOURCES:.cpp=.o)

END_NAME=lab01
TAR_NAME=lab01.tar


all: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(END_NAME)

%.o: %.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm $(OBJECTS) $(END_NAME) 

run:
	./$(END_NAME)

val: $(END_NAME)
	valgrind -v ./$(END_NAME)

tar:
	tar cvf $(TAR_NAME) $(SOURCES) $(H_FILES) $(MAKEFILE) $(TXT_FILES)
