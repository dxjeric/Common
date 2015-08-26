LD_LIB_DEF = -L/root/GitHub/common/lib
.PHONY : all clean

# change cc to g++, in order to solve the error when link the objects(undefined reference to `operator new(unsigned long))
logtest : logtest.o
	g++ -o logtest logtest.o $(LD_LIB_DEF) -lcommon
logtest.o : logtest.cpp
	cc -c -o logtest.o logtest.cpp

all : clean logtest

clean:
	rm -f logtest logtest.o
