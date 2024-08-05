//Kevin Gallegos 1858764 PA3

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"



int main(){
	Graph G = newGraph(8);
	List S = newList();
	for(int x =1; x<=8; x++){
		append(S,x);
	}
	printList(stdout,S);
	printf("\n\n");
	addArc(G,1,2);
	addArc(G,2,3);
	addArc(G,2,5);
	addArc(G,2,6);
	addArc(G,3,4);
	addArc(G,3,7);
	addArc(G,4,3);
	addArc(G,4,8);
        addArc(G,5,1);
        addArc(G,5,6);
        addArc(G,6,7);
	addArc(G,7,6);
	addArc(G,7,8);
	addArc(G,8,8);
	printGraph(stdout,G);
	printf("\n");
	//List L = newList();
	moveFront(S);
	//printf("got: %d\n", get(S));
	DFS(G, S);
	printList(stdout,S);
	printf("\n");
	Graph H = transpose(G);
	printGraph(stdout,H);
	printf("\n\n");
        moveFront(S);
        for(int i= 1; i<=length(S); i++){
                int j = get(S);
                printf("%d has a parent of %d\n", j,getParent(G,j));
                moveNext(S);
        }
	DFS(H, S);
	printList(stdout,S);
	printf("\n\n");
	int strong = 0;
	moveFront(S);
	for(int i= 1; i<=length(S); i++){
		int j = get(S);
		printf("%d has a parent of %d\n", j,getParent(H,j));
		if(getParent(H,j) == NIL){
			printf("%d is NIL\n", j);
			strong++;
		}
		moveNext(S);
	}
	moveBack(S);
	List U = newList();
	printf("There are %d strongly connected components\n", strong);
	for(int i = 1; i<=strong; i++){
		printf("Component %d: ",i);
		int x =get(S);
		//printf("got %d\n", x);
		while(getParent(H,x) != NIL){
			prepend(U,x);
			movePrev(S);
			//printf("index is now %d\n", index(S));
			x = get(S);
			//printf("got %d\n", x);
		}
		prepend(U,x);
		movePrev(S);
		printList(stdout,U);
		printf("\n");
		clear(U);
	}

}
