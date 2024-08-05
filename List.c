#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"


typedef struct NodeObj{
	int data;
	Node next;
	Node prev;
	//int index = -1;
} NodeObj;

typedef struct ListObj{
	Node front;
	Node back;
	int length;
	Node cursor;
	int index;
} ListObj;

Node newnode(int data){
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	//N->index +=1; 
	return(N);
}

void freenode(Node* pN){
	if(pN!=NULL){
		//pN->next = NULL;
		//pN->prev = NULL;
		free(*pN);
		*pN = NULL;
	}
}

List newList(){
	List L;
	L = malloc(sizeof(ListObj));
	assert(L!=NULL);
	L->front=L->back = NULL;
	L->length=0;
	L->index=-1;
	L->cursor=NULL;
	return(L);
}

void freeList(List* pL){
	if(pL!=NULL && *pL!=NULL){
		while(length(*pL)>0){
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

int front(List L){
	if(L ==NULL){
		printf("list error: calling front() on Null list ref\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) < 1){
		printf("List error: calling front() on empty list");
		exit(EXIT_FAILURE);
	}
	return(L->front->data);
}

int back(List L){
        if(length(L) < 1 || L==NULL){
                printf("List error: calling back() on empty/NULL list");
                exit(EXIT_FAILURE);
        }
        return(L->back->data);
}

int length(List L){
        if(L ==NULL){
                printf("list error: calling length() on Null list ref\n");
                exit(EXIT_FAILURE);
        }
	return(L->length);
}

int index(List L){
	if(L == NULL){ return -1;}
	//if(L->index == -1){ return -1;}
	//will the index be always pointing to last tghing entered if so is it length -1?
	return L->index;
	}	//or will index be freely whatever we want and i need to crate an index data varaible
				 //inside of L struct ex: L->index???????

int get(List L){
	if(length(L)==0){return 0;}
	//if(index(L)==-1){return -1;}
	if(L==NULL || L->cursor == NULL){
		printf("List Error: calling get() on empty List/Cursor ref\n");
		exit(EXIT_FAILURE);
	}
	return L->cursor->data;
}
	//maybe the above is right since whatever it is pointing as cursor we need to take out with get
//if option is true this renders this func useless as we literally  call get front/get back to take these

bool equals(List A, List B){
   if( A==NULL && B==NULL ){return 1;}
   else if(A==NULL || B==NULL){return 0;}
   else if(length(B) != length(A)){return 0;}

   //bool eq;

   //eq = ( A->length == B->length );
   Node N = A->front;
   Node M = B->front;
   for(int i = 0;i< length(A) && i < length(B); i++){
      //eq = ( N->data==M->data );
      if(N->data != M->data){return 0;}
      N = N->next;
      M = M->next;
   }
   return 1;
}

// Manipulation functions //
void clear(List L){ // Resets L to its original empty state.
	if (L != NULL){
                while(length(L)>0){
                        deleteFront(L);
                }
                L->index = -1;
                L->cursor = NULL;

	}
	if(L==NULL){
                printf("List Error: calling clear() on NULL List ref\n");
                exit(EXIT_FAILURE);
	}

}
void set(List L, int x){// Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0
	if(length(L)>0 && index(L)>=0){
		L->cursor->data = x;
	}
	else{
                printf("List Error: calling set() on empty List ref\n");
                exit(EXIT_FAILURE);
        }

}
void moveFront(List L){// If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
 	if(L==NULL){
		fprintf(stderr, "calling moveFront() on NULL list\n");
	}
	if(length(L)==0){return;}
	if (length(L) > 0){
		L->index = 0;
		L->cursor = L->front;
	}
	
}
void moveBack(List L){
	if(L==NULL){
                fprintf(stderr, "calling moveBack() on NULL list\n");
        }
	if (length(L)==0){return;}
        L->cursor = L->back;
        L->index = length(L)-1;

} 
// If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void movePrev(List L){
        if(L == NULL){
                fprintf(stderr, "calling movePrev() on NULL list\n");
                exit(EXIT_FAILURE);
        }	
	if (index(L) < 0){
		L->index = -1;
		L->cursor = NULL;
		return;
	}
	L->index--;
	L->cursor = L->cursor->prev;
}
	
// If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L){
	if (L==NULL){
		fprintf(stderr, "Error: calling moveNext() on NULL list\n");
		return;
	}
        if (index(L) >= length(L)-1){
		L->index = -1;
		L->cursor = NULL;
		return;
	}
	L->index++;
        L->cursor = L->cursor->next;
}


// If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void prepend(List L, int x){
        if(L==NULL){
                fprintf(stderr, "Error: calling prepend() on NULL list");
                exit(EXIT_FAILURE);
        }
        if (L != NULL){
                Node t = newnode(x);
                if(L->length == 0){
                        L->front = L->back = t;
                }
                else if(L->length == 1){
                        L->front = t;
                        L->front->next = L->back;
                        L->back->prev = L->front;
                }
                else{
                        Node tem = L->front;
                        L->front = t;
                        L->front->next = tem;
                        tem->prev = L->front;
                        //freenode(&tem);
                }
                L->length++;
                if(L->index != -1){L->index++;}


        }

}
// Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void append(List L, int x){
        if(L==NULL){
                fprintf(stderr, "Error: calling append() on NULL list");
                exit(EXIT_FAILURE);
        }
        if (L != NULL){
                if(L->length == 0){
                        L->front = L->back = newnode(x);
                }
                else if(L->length == 1){
                        L->back = newnode(x);
                        L->front->next = L->back;
                        L->back->prev = L->front;
                }
                else{
                        L->back->next = newnode(x);
                        L->back->next->prev = L->back;
                        L->back = L->back->next;
                }
                L->length++;
        }

}

// Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void insertBefore(List L, int x){
        if(L==NULL){
                fprintf(stderr, "Error: calling insertBefore() on NULL list");
                exit(EXIT_FAILURE);
        }
        if(length(L)>0 && index(L)>=0){
                if(L->index == 0){
                        prepend(L,x);
                        //freenode(&n1);
                        return;
                }
                Node n1 = newnode(x);
                Node nprev = L->cursor->prev;
                n1->prev= nprev;
                nprev->next = n1;
                n1->next = L->cursor;
                L->cursor->prev = n1;
                L->length++;
                L->index++;

	}
}
// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, int x){
        if(L==NULL){
                fprintf(stderr, "Error: calling insertAfter() on NULL list");
                exit(EXIT_FAILURE);
        }
        //if(length(L)<0){append(L,x);}
        if (length(L)>0 && index(L)>=0){
                if(L->index == 0){
                        append(L,x);
                        //freenode(&n);
                        //return;
                }
                else if(L->cursor == L->back){
                        Node n = newnode(x);
                        L->cursor->next = n;//n
                        n->prev = L->cursor;
                        L->back = n;//n
                        L->length++;
                        //freenode(&n);
                        //return;
                }
                else{
                        Node n = newnode(x);
                        Node cursornext = L->cursor->next;
                        L->cursor->next = n;//n
                        n->prev = L->cursor; //n
                        n->next = cursornext;//cursornext //n
                        cursornext->prev = n;//cursornext //n
                //freenode(&n);
                //freenode(&cursornext);
                        L->length++;
                }
        }

}

// Insert new element after cursor.
 // Pre: length()>0, index()>=0
void deleteFront(List L){
        if(L==NULL){
                fprintf(stderr, "Error: calling deleteFront() on NULL list");
                exit(EXIT_FAILURE);
        }
        if (length(L)>0){
                if(L->length == 1){
                        Node t = L->front;
                        L->front = NULL;
                        L->back = NULL;
                        L->length--;
                        L->cursor = NULL;
                        L->index = -1;
                        freenode(&t);
                        return;
                }
                Node t = L->front;
                L->front=L->front->next;
                L->front->prev = NULL;
                if(L->index != -1){
                        L->index--;
                        //L->cursor = NULL;
                }
                if(t == L->cursor){
                        L->cursor = NULL;
                        L->index = -1;
                }
                freenode(&t);
                L->length--;
                return;
        }

}
// Delete the front element. Pre: length()>0
void deleteBack(List L){
        if(L==NULL){
                fprintf(stderr, "Error: calling deleteBack() on NULL list");
                exit(EXIT_FAILURE);
        }
        if(length(L)>0){
                if(length(L)==1){
                        Node t = L->front;
                        L->front=NULL;
                        L->back=NULL;
                        L->cursor=NULL;
                        L->index=-1;
                        freenode(&t);
                }else{
                        Node t = L->back;
                        L->back = L->back->prev;
                        L->back->next=NULL;
                        if(t == L->cursor){
                                L->cursor = NULL;
                                L->index = -1;
                        }
                        freenode(&t);
                }
                L->length--;
        }

}
// Delete the back element. Pre: length()>0
void delete(List L){
        if(L==NULL){
                fprintf(stderr, "Error: calling delete() on NULL list");
                exit(EXIT_FAILURE);
        }
        if (length(L)>0 && index(L)>=0){
                if(length(L)==1){
                        deleteFront(L);
                        //printf("cleared L as it was just 1 var\n");
                        return;
                }else if(index(L) == 0){deleteFront(L);}
                else if(index(L) == length(L)-1){deleteBack(L);}
                else{
                        Node t = L->cursor;
                        //Node nprev = L->cursor->prev;
                        //printf("gave nprev as l ursor prev\n");
                        //Node cursornext = L->cursor->next;
                        //printf("gave curs next as L->cursor->prev\n");
                        t->prev->next = t->next;
                        //printf(" nprev->next = cursornext\n");
                        t->next->prev=t->prev;
                        //printf(" cursornext->prev=nprev;\n");
                        L->index = -1;
                        freenode(&t);
                        L->length--;
                }
        }

}
// Delete cursor element, making cu
// Other operations
void printList(FILE* out, List L){
	Node temp = L->front;
	while (temp != NULL){
		fprintf(out, "%d", temp->data);
		if(temp != NULL){fprintf(out, " ");}
		temp=temp->next;
	}
	//fprintf(out,"\n");
}

List copyList(List L){
	List newL = newList();
	newL->length = length(L);
	Node temp=L->front;
	newL->front = newnode(temp->data);
	Node temp1 = newL->front;
	temp = temp->next;
	int x = 1;

	while(x < length(L)){
		temp1->next = newnode(temp->data);
		temp = temp->next;
		if(x<length(L)-1){temp1=temp1->next;}
		x++;
	}
	newL->back =temp1;
	return newL;
}
