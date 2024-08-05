#------------------------------------------------------------------------------
#Programming Assignment 3 - Depth First Search (DFS) algorithm
#
# make FindComponents          makes FindComponents
# make GraphTest               makes GraphTest
# make clean                   removes all binaries
# make checkFindComponents     checks FindComponents for memory errors
#------------------------------------------------------------------------------

CC      = clang
CFLAGS  = -std=c17 -Wall
LFLAGS  = -lm
EXEC    = FindComponents
Find_OBJS    = FindComponents.o Graph.o List.o
GraphTest_OBJS   = GraphTest.o Graph.o List.o

FindComponents: $(Find_OBJS)
	$(CC) $(LFLAGS) -o FindComponents $(Find_OBJS)

GraphTest: $(GraphTest_OBJS)
	$(CC) $(LFLAGS) -o GraphTest $(GraphTest_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<


clean :
	rm -f FindComponents GraphTest FindComponents.o Graph.o GraphTest.o List.o


checkFindPath :
	valgrind --leak-check=full FindComponents in3 blah3

