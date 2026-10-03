# iliyacod@gmail.com
CXX = clang++ 
CXXFLAGS = -std=c++17 -Wall -Wextra

# object files
OBJS = main.o SquareMat.o

# object files for tests
TEST_OBJS = tests.o SquareMat.o 

# the target
all: main test

# main target
main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

# test target
test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o test $(TEST_OBJS)

# SquareMat object file
SquareMat.o: SquareMat.cpp SquareMat.hpp
	$(CXX) $(CXXFLAGS) -c SquareMat.cpp	

# valgrind tests to check for memory leaks
valgrind: main test
	valgrind --leak-check=full ./main
	valgrind --leak-check=full ./test

# clean up 
clean:
	rm -f *.o main test