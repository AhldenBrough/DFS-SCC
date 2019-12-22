//Ahlden Brough
//ajbrough
//pa5

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
	Graph G = newGraph(5);
	addEdge(G, 1, 2);
	addEdge(G, 1, 2);
	addEdge(G, 2, 3);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	addEdge(G, 5, 1);
	addEdge(G, 5, 5);
	printGraph(stdout, G);
	List L = newList();
	for(int i = 1; i < 6; i++){
		append(L, i);
	}
	DFS(G, L);
	printf("\n");
	printList(stdout, L);
	printf("\n");
	Graph A = newGraph(3);
	addArc(A, 1, 2);
	addArc(A, 2, 3);
	addArc(A, 3, 1);
	printGraph(stdout, A);
	Graph T = transpose(A);
	printGraph(stdout, T);
	Graph C = copyGraph(T);
	printGraph(stdout, C);

	clear(L);
	Graph B = newGraph(100);
	addArc(B, 64, 4);
    addArc(B, 64, 3);
    addArc(B, 42, 2);
    addArc(B, 2, 64);
    addArc(B, 4, 2);
    addArc(B, 3, 42);
    for (int i = 1; i <= 100; i++) {
    	prepend(L, i);
    }
    DFS(B, L);
    printf("getDiscover(B, 100) = %d\n", getDiscover(B, 100));
    printf("getDiscover(B, 64) = %d\n", getDiscover(B, 64));
    printf("getDiscover(B, 4) = %d\n", getDiscover(B, 4));
    printList(stdout, L);
    printf("\n");
    DFS(B, L);
    printf("getDiscover(B, 4) = %d\n", getDiscover(B, 4));
    printf("getDiscover(B, 63) = %d\n", getDiscover(B, 63));
    DFS(B, L);
    printList(stdout, L);
    printf("\n");
    printf("getDiscover(B, 65) = %d\n", getDiscover(B, 65));
    printf("getDiscover(B, 1) = %d\n", getDiscover(B, 1));

	//makeNull(G);
	// printGraph(stdout, G);
	// addEdge(G, 1, 2);
	// addEdge(G, 1, 2);
	// addEdge(G, 2, 3);
	// addEdge(G, 3, 4);
	// addEdge(G, 4, 5);
	// addEdge(G, 5, 1);
	// addEdge(G, 5, 5);
	//DFS(G, 1);
	//List L = newList();
	//getPath(L, G, 3);
	//printList(stdout, L);
	// Graph A  = newGraph(99);
	// 	if(getSize(A) != 0){
	// 		printf("size wasn't zero\n");
	// 	}
	// 	printf("gets past\n");
 //        addArc(A, 54, 1);
 //        printf("adds arc 1\n");
 //        addArc(A, 54, 2);
 //        printf("adds arc 2\n");
 //        addArc(A, 54, 3);
 //        printf("adds arc 3\n");
 //        addArc(A, 1, 54);
 //        printf("adds arc 4\n");
 //        addArc(A, 1, 55);
 //        printf("adds arc 5\n");
 //        if (getSize(A) != 5){
 //        	printf("size wasn't 5\n");
 //        }
 //        //BFS(A, 67);
 //        printf("BFS\n");
 //        if (getSize(A) != 5){
 //        	printf("size wasn't 5 (2)\n");
 //        }
 //        addArc(A, 55, 1);
 //        printf("adds arc 6\n");
 //        if (getSize(A) != 6){
 //        	printf("size wasn't 6\n");
 //        }
    // printf("getOrder(G) = %d\n", getOrder(G));
    // printf("getSize(G) = %d\n", getSize(G));
    // printf("getSource(G) = %d\n", getSource(G));
    // printf("getDist(G, 5) = %d\n", getDist(G, 5));
	return(0);
}
