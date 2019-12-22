//Ahlden Brough
//ajbrough
//pa5

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]) {
  FILE *in, *out;
  int n;
  int u;
  int v;
  List L = newList();
  // check command line for correct number of arguments
    if( argc != 3 ){
      printf("Usage: FindComponents <input file> <output file>\n");
      exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
    }
    if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
    }
    fscanf(in, "%d", &n);
    Graph G = newGraph(n);
    fscanf(in, "%d", &u);
    fscanf(in, "%d", &v);
    while(u != 0 && v != 0){
      addArc(G, u, v);
      fscanf(in, "%d", &u);
      fscanf(in, "%d", &v);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");
    for(int z = 1; z <= n; z++){
      append(L, z);
    }
    DFS(G, L);
    Graph T = transpose(G);
    DFS(T, L);
    int counter = 0;
    for(int i = 1; i <= getOrder(G); i++){
      if(getParent(T, i) == NIL){
        counter++;
      }
    }
    if(counter == 1){
      fprintf(out, "G contains 1 strongly connected component: ");
    }
    else{
      fprintf(out, "G contains %d strongly connected components: ", counter);
    }
    moveBack(L);
    int count = 1;
    List temp = newList();
    while(index(L) > -1){
      prepend(temp, get(L));
      if(getParent(T, get(L)) == NIL){
        fprintf(out, "\n");
        fprintf(out, "Component %d: ", count);
        printList(out, temp);
        clear(temp);
        count++;
      }
      movePrev(L);
    }
    
  fprintf(out, "\n");
  fclose(in);
  fclose(out);

  freeList(&L);
  freeGraph(&G);
  freeGraph(&T);
  freeList(&temp);
  return(0);
}