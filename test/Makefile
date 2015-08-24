LD_LIB_DEF = -L/root/GitHub/common/lib
.PHONY : all clean

# change cc to g++, in order to solve the error when link the objects(undefined reference to `operator new(unsigned long))
main : main.o
	g++ -o main main.o $(LD_LIB_DEF) -lcommon
main.o : main.cpp
	cc -c -o main.o main.cpp

all : clean main

clean:
	rm -f main main.o
