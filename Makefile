CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

csim: main.cpp 
	$(CC) $(CFLAGS) -o csim main.cpp 

clean:
	rm -f *.o csim
