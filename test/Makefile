LD_LIB_DEF = -L/root/GitHub/common/lib
.PHONY : all clean

main : main.o
	cc -o main main.o $(LD_LIB_DEF) -lcommon
main.o : main.cpp
	cc -c -o main.o main.cpp

all : clean main

clean:
	rm -f main main.o
