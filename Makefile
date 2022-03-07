CPP = g++ -std=c++11
CPPFLAGS = -g -Wall -Werror

all: base64

base64: base64.o
	$(CPP) -o base64 base64.o

base64.o: base64.cpp
	$(CPP) -c base64.cpp