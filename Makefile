.PHONY = all clean

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
#./test to run
EXECUTABLE=test 

CC=g++
CFLAGS=-c -Wall

all: $(SOURCES) $(EXECUTABLE)
	

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@	
	
	
clean:
	echo "Cleaning up..."
	rm -rvf *.o ${OBJECTS}