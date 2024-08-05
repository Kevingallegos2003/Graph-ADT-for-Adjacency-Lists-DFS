//Kevin Gallegos 1858765 PA3

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"


//#define maxvertices 100
#define white 0
#define grey 1
#define black 2

typedef struct GraphObj{
        List *lists;
        //[maxvertices];//fix  struct list* lists
        int *colors; //[maxvertices];
        int *par; //[maxvertices];
        int *discover;
	int *finish;
        int order;
        int size;

}GraphObj;




/*** Constructors-Destructors ***/
Graph newGraph(int n){
        //Graph G;
        Graph G = malloc(sizeof(GraphObj));
        assert(G!=NULL);
        //fix
        //n++;i
        G->lists = malloc(sizeof(List) * (n+1));
        G->colors = malloc(sizeof(int) * (n+1));
        G->par = malloc(sizeof(int) * (n+1));
	G->discover = malloc(sizeof(int) * (n+1));
	G->finish = malloc(sizeof(int) * (n+1));
        //G->lists[1] = newList();
        G->order =  n;
        G->size = 0;
        for(int z = 1;z <= n; z++){
                //printf("i++\n")
                G->lists[z] = newList();
		G->colors[z] = white;
                G->par[z] = NIL;
		G->discover[z] = NIL;
		G->finish[z] = NIL;
        }
        return G;
}
void freeGraph(Graph* pG){
	if (!pG){
		fprintf(stderr, "freeGraph: Graph is NULL\n"); exit(1);
	}
	for (int i = 1; i <= (*pG)->order; i++){
		freeList(&(*pG)->lists[i]);
	}
	free((*pG)->lists);
	free((*pG)->colors);
	free((*pG)->par);
	free((*pG)->discover);
	free((*pG)->finish);
	free(*pG);
        *pG = NULL;
}
/*** Access functions ***/
int getOrder(Graph G){
        if (!G){
                fprintf(stderr, "getOrder: Graph is NULL\n"); exit(1);
        }
        return G->order;
}
int getSize(Graph G){
        if (!G){
                fprintf(stderr, "getSize: Graph is NULL\n"); exit(1);
        }
        return G->size;
}
int getParent(Graph G, int u){
        if (!G){
                fprintf(stderr, "getParent: Graph is NULL\n"); exit(1);
        }
        return G->par[u];
}
int getDiscover(Graph G, int u){
        if (!G){
                fprintf(stderr, "getDiscover: Graph is NULL\n"); exit(1);
        }
        return G->discover[u];
}
int getFinish(Graph G, int u){
        if (!G){
                fprintf(stderr, "getFinish: Graph is NULL\n"); exit(1);
        }
	return G->finish[u];
}
/*** Manipulation procedures ***/
void makeNull(Graph G){//fix
        G->size = 0;
        for(int i= 1; i<=(G->order); i++){
                List L = G->lists[i];
                clear(L);
                G->lists[i] = L;
                G->colors[i] = white;
                G->par[i] = NIL;
                G->discover[i] = NIL;
		G->finish[i] = NIL;
        }
}
void addEdge(Graph G, int u, int v){
        if (!G){
                fprintf(stderr, "addEdge: Graph is NULL\n"); exit(1);
        }
        addArc(G,u,v);
        addArc(G,v,u);
        //make a sort so it goes in numericallly
        //append(U, v);
        //append(V,u);    //append(V, u); This looks dumb i pray this is the right idea at least.
        //printf("size++\n");
        G->size--;//Also append (append(list[v], u) because undirected
        //printf("finished size\n");
}
void addArc(Graph G, int u, int v){
        if (!G){
                fprintf(stderr, "addArc: Graph is NULL\n"); exit(1);
        }
        //printf("in arc\n");
        //if (G->size > 100){G->size = 0;}
        if (length(G->lists[u]) == 0){
                //printf("in arc 0\n");
                //append(G->lists[u],NIL);
                append(G->lists[u],v);
                G->size++;
                return;
        }
        //printf("in arc 1\n");
        List F = G->lists[u];
        moveFront(F);
        //printf("index: %d\n", index(F));
        //while(index(F) != 1 && get(F) < v){moveNext(F);}
        //if(index(F) == -1){append(F,v);}
        //else{insertBefore(F,v);}
        while(v<get(F)){
                if(index(F) == 1){break;}
                movePrev(F);
        }
        insertAfter(F,v);
        G->size++;
}
void visit(Graph G,List L, int x, int *t){
	G->discover[x] = (*t)++;
	G->colors[x] = grey;
	List Q = G->lists[x];
	moveFront(Q);
	for(int y = 1; y<=length(Q); y++){
		int  j = get(Q);
		if(G->colors[j] == white){
		     G->par[j] = x;
		     visit(G,L,j,t);
		}
		moveNext(Q);
	}
	G->colors[x] = black;
	G->finish[x] = (*t)++;
	prepend(L,x);

}
void DFS(Graph G, List S){
        if (!G){
                fprintf(stderr, "DFS: Graph is NULL\n"); exit(1);
        }
	for(int x = 1; x <= getOrder(G); x++){
		G->colors[x] = white;
		G->par[x] = NIL;
	}
	int t = 0;
	int *time = &t;
	moveFront(S);
	int len = length(S);
	for(int k = 1; k <= len; k++){
		//printf("This is loop %d out of %d\n",k,len);
		int x = get(S);
		//printf("DFS visiting %d\n", get(S));
		if(G->colors[x] == white){
			visit(G,S, x, time);
		}
		moveNext(S);
	}
	for(int z = 1; z <= len; z++){
		deleteBack(S);
	}
}
/*** Other operations ***/
Graph transpose(Graph G){
        if (!G){
                fprintf(stderr, "transpose: Graph is NULL\n"); exit(1);
        }
	Graph newG = newGraph(getOrder(G));
	newG->order = getOrder(G);
        newG->size = getSize(G);
	for(int x=1; x <= getOrder(G); x++){
		List L = G->lists[x];
		moveFront(L);
		for(int y = 1; y <= length(L); y++){
			int z = get(L);
			List N = newG->lists[z];
			append(N,x);
			moveNext(L);
		}
	}
	for(int z = 1; z <= getOrder(G); z++){
                newG->colors[z] = white;
                newG->discover[z] = 0;
                newG->par[z] = NIL;
                newG->finish[z] = 0;
	}
	return newG;

}
Graph copyGraph(Graph G){
        if (!G){
                fprintf(stderr, "copyGraph: Graph is NULL\n"); exit(1);
        }
	Graph newG = newGraph(getOrder(G));
	newG->order = getOrder(G);
	newG->size = getSize(G);
	//newG->recent = getSource(G);
	for(int z = 0; z <= getOrder(G); z++){
		newG->lists[z] = G->lists[z];
		newG->colors[z] = G->colors[z];
		newG->discover[z] = G->discover[z];
		newG->par[z] = G->par[z];
		newG->finish[z] = G->finish[z];
	}
	return newG;
}
void printGraph(FILE* out, Graph G){
        if (!G){
                fprintf(stderr, "printGraph: Graph is NULL\n"); exit(1);
        }
        //if(getSource(G) != NIL){
                for(int i=1; i<=(G->order); i++){//1=i
                        fprintf(out, "%d", i);
                        fprintf(out, ": ");
                        List L = G->lists[i];
                        if(L == NULL){break;}
                        moveFront(L);
                        //if(get(L) == NIL){delete(L);}
                        printList(out,L);
                        //fprintf(out, "%d", get(L));
                        fprintf(out, "\n");
                        //fprintf(out,"loop %d done\n", i);

                }
                //fprintf(out, "its done\n");

        //}
}
