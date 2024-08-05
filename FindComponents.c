//Kevin Gallegos 1858764 PA3

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"
#include "Graph.h"


int main(int argc, char* argv[]){
        int line1;
        int scan;
        FILE* in = fopen(argv[1], "r");
        if(argv[1]==NULL){fprintf(stderr, "can't read file\n");}
        FILE* out =  fopen(argv[2], "w");
        if(argv[2]==NULL){fprintf(stderr, "can't OPEN file\n");}
        //int lengthlimit = 100;
        //char str[10];
        scan = fscanf(in,"%d",&line1);
        Graph G = newGraph(line1);
        //fprintf(out,"your mom");
        //fclose(out);
        //printf("vertexs: %d\n",line1);
        //scan = fscanf(in,"%d",&line1);
        while(scan != EOF){
                fscanf(in,"%d",&line1);
                if(line1 == 0){fscanf(in,"%d",&line1);break;}
                int x = line1;
                fscanf(in,"%d",&line1);
                int y = line1;
                //printf("adding edge, List[%d] {%d}\n", x,y);
                addArc(G,x,y);
                //printGraph(stdout,G);
        }
	fprintf(out,"Adjacency list representation of G:\n");
        printGraph(out,G);
	fprintf(out,"\n");
	//-----create List containing {1...n}--------
	
	
	List S = newList();
        for(int x =1; x<=getOrder(G); x++){
                append(S,x);
        }
	moveFront(S);
	//----DFS 1------
	
	DFS(G,S);
	//---Transpose Graph--
	Graph H = transpose(G);
	//---DFS 2----
	DFS(H, S);
	//----Show Strong components---
	int strong = 0;
	moveFront(S);
        for(int i= 1; i<=length(S); i++){
                int j = get(S);
                //printf("%d has a parent of %d\n", j,getParent(H,j));
                if(getParent(H,j) == NIL){
                        //printf("%d is NIL\n", j);
                        strong++;
                }
                moveNext(S);
        }
        moveBack(S);
        List U = newList();//used to store sets of SCC of Graph H
        fprintf(out,"G contains %d strongly connected components:\n", strong);
	for(int i = 1; i<=strong; i++){
                fprintf(out,"Component %d: ",i);
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
                printList(out,U);
                fprintf(out,"\n");
                clear(U);
        }


	//--clean up---

	fclose(in);
	fclose(out);
	freeGraph(&G);
	freeGraph(&H);
	freeList(&S);
	freeList(&U);

}
