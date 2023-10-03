GTESTINC=$(HOME)/packages/googletest/googletest/include
GTESTLIB=$(HOME)/packages/googletest/build/lib
CC=g++
CFLAGS=-c -g -std=c++2a -Wall -Werror -pedantic -pedantic-errors -I $(GTESTINC)
LIBFLAGS=-lgtest -lgtest_main -lpthread

SRCS=main.cpp auction.cpp
OBJS=$(addsuffix .o,$(basename $(SRCS))) 
EXE=auction
.PHONY	: clean all run

all : $(EXE)

$(EXE)	: $(OBJS)
		$(CC) -o $@ -L $(GTESTLIB) $(OBJS) $(LIBFLAGS)


$(OBJS)	:	%.o	: %.cpp auction.h
		$(CC) $(CFLAGS) $<

run: all
	./$(EXE)

test:
	echo "No tests yet"

clean :
	rm $(OBJS) $(EXE)