//Kevin Gallegos 1858764 PA3

#include "List.h"
#define UNDEF -1
#define NIL -99
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
//int getSource(Graph G);//old
int getParent(Graph G, int u);
//int getDist(Graph G, int u);//old
//void getPath(List L, Graph G, int u);//old
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);//old
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
//void BFS(Graph G, int s);//old
void DFS(Graph G, List L);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
