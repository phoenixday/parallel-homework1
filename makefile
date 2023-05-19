CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCS = main.cpp PosixQueue.cpp LockFreeQueue.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = myprogram

.PHONY: all clean

all: $(EXECUTABLE)
	@./$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXECUTABLE)

main.o: main.cpp PosixQueue.cpp LockFreeQueue.cpp
	@$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

PosixQueue.o: PosixQueue.cpp PosixQueue.h Node.h
	@$(CXX) $(CXXFLAGS) -c PosixQueue.cpp -o PosixQueue.o

LockFreeQueue.o: LockFreeQueue.cpp LockFreeQueue.h Node.h
	@$(CXX) $(CXXFLAGS) -c LockFreeQueue.cpp -o LockFreeQueue.o

clean:
	@rm -f $(OBJS) $(EXECUTABLE)
