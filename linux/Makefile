.PHONY : all clean

vpath % ../src

LIBPATH = ../lib
LIBNAME = libcommon.a
AR = ar cr


SRCS = liblog.cpp  logfile.cpp 
OBJS = liblog.o logfile.o

$(LIBNAME) : $(OBJS)
	$(AR) $(LIBPATH)/$(LIBNAME) $(OBJS)

$(OBJS) : %.o :%.cpp
	cc -c -o $@ $< 

$(SRCS) : basetype.h log_config.h  logfile.h  liblog.h 

clean :
	rm -f $(OBJS) $(LIBPATH)/$(LIBNAME)

all : clean $(LIBNAME) 
