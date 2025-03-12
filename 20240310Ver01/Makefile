CPPFLAGS=-g 
LDFLAGS=-g 
LDLIBS=

SRCS=Trig.cc Sin.cc Cos.cc Oscill.cc Bank.cc main.cc
OBJS=$(subst .cc,.o,$(SRCS))

Oscillo: $(OBJS)
	g++ $(LDFLAGS) -o oscillo $(OBJS) $(LDLIBS)

Trig.o: Trig.cpp Trig.h
	g++ $(CPPFLAGS) -c Trig.cpp

Sin.o: Sin.cpp Sin.h
	g++ $(CPPFLAGS) -c Sin.cpp

Cos.o: Cos.cpp Cos.h
	g++ $(CPPFLAGS) -c Cos.cpp

Oscill.o: Oscill.cpp Oscill.h
	g++ $(CPPFLAGS) -c Oscill.cpp

Bank.o: Bank.cpp Bank.h
	g++ $(CPPFLAGS) -c Bank.cpp

main.o: main.cpp Bank.h
	g++ $(CPPFLAGS) -c main.cpp
