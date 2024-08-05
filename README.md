//Kevin Gallegos 1858764 PA3

The FindComponents program

FindComponents.c  | Uses the Graph ADT (Graph.h) to print an adjacency matrix and its strongly connected components into an output file
Graph.c           | Creates adjacency matrix and uses DFS
Graph.h           | Prototypes of functions that will be used in Graph.c
List.c            | All Functions created from the prototypes in List.h
GraphTest.c       | Testing file used to test functions from Graph.c all tests are outputed on the line
List.h            | Prototypes of functions that will be used in the findcomponents program
Makefile          | Compiles and Makes the FindComponents program as well as other testing code optionally
 Note: For creating a stack because S is shared after the stack is created from DFS, it removes 1-n at end to make way for stack based on finish, Graph from pa2 was used almost in its entirety to create pa3
