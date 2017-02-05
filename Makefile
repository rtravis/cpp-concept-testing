CC        := g++
LD        := g++
AR        := ar

CPPFLAGS  := -std=c++1y -fconcepts -O3 -Wall -Wextra
LDFLAGS   :=

.PHONY: all clean

all: tester_exe

tester_exe: tester.o
	$(LD) tester.o -o tester_exe $(LDFLAGS)

tester.o: tester.cpp $(wildcard *.hpp) $(wildcard concept/*.hpp)
	$(CC) -c $(CPPFLAGS) -o tester.o tester.cpp

clean:
	@rm -rf tester_exe tester.o


