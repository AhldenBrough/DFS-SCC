//Ahlden Brough
//ajbrough
//pa5

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

int INF = -1;
int NIL = 0;
int UNDEF = -2;
int WHITE = 1;
int GRAY = 2;
int BLACK = 3;

typedef struct GraphObj{
  int size;
  int order;
  List* neighbors;
  int* color;
  int* parent;
  int* discover;
  int* finish;
}GraphObj;

void makeNull(Graph G){
  if(G == NULL){
    printf("Graph Error: calling makeNull() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  for(int i = 1; i< getOrder(G) + 1; i++){
    clear(G->neighbors[i]);
    G->color[i] = 0;  
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
    G->parent[i] = NIL;
  }
  G->size = 0;
}

void visit(Graph G, List S, int x, int *time){
  //1. d[x] = (++time) //discover x
  //2. color[x] = gray
  //3. for all y in the adjacency list of x
  //4.    if color[y] == white
  //5,      p[y] = x
  //6.      visit(y)
  //7. color[x] = black
  //8. f[x] = (++time) //finish x
  int y;
  *time = *time + 1;
  G->discover[x] = *time;
  G->color[x] = GRAY;
  List adj = G->neighbors[x];
  if(length(adj) != 0){
    moveFront(adj);
  }
  while(index(adj) > -1){
    y = get(adj);
    if(G->color[y] == WHITE){
      G->parent[y] = x;
      visit(G, S, y, time);
    }
    moveNext(adj);
  }
    G->color[x] = BLACK;
    *time = *time + 1;
    G->finish[x] = *time;
    prepend(S, x);
  
}

/*** Constructors-Destructors ***/
Graph newGraph(int n){
  Graph G;
  G = malloc(sizeof(GraphObj));
  G->size = 0;
  G->order = n;
  G->neighbors = calloc(n+1, sizeof(List));
  G->color = calloc(n+1, sizeof(int));
  G->parent = calloc(n+1, sizeof(int));
  G->discover = calloc(n+1, sizeof(int));
  G->finish = calloc(n+1, sizeof(int));
  for(int i = 1; i < n+1; i++){
    G->neighbors[i] = newList();
    G->color[i] = WHITE;  
    G->parent[i] = NIL;
    G->discover[i] = UNDEF;
    G->finish[i] = UNDEF;
  }
  return G;
}

void freeGraph(Graph* pG){
  if(pG!=NULL && *pG!=NULL){
    makeNull(*pG);
    for(int i = 1; i < (*pG)->order + 1; i++){
      freeList(&(*pG)->neighbors[i]);
    }
    free((*pG)->neighbors);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->discover);
    free((*pG)->finish);
    (*pG)->color =  NULL;
    (*pG)->parent = NULL;
    (*pG)->discover = NULL;
    (*pG)->finish = NULL;
    (*pG)->neighbors = NULL;
    (*pG)->order = 0;
    (*pG)->size = 0;
    free(*pG);
    *pG = NULL;
  }
}

/*** Access functions ***/
int getOrder(Graph G){
  if(G == NULL){
    printf("Graph Error: calling getOrder() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->order;
}

int getSize(Graph G){
  if(G == NULL){
    printf("Graph Error: calling getSize() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->size;
}


int getParent(Graph G, int u){
  if(G == NULL){
    printf("Graph Error: calling getParent() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->parent[u];
}

int getDiscover(Graph G, int u){
  if(G == NULL){
    printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->discover[u];

}
int getFinish(Graph G, int u){
  if(G == NULL){
    printf("Graph Error: calling getFinish() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->finish[u];
}

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v){
  //printf("starts addEdge\n");
  if(G == NULL){
    printf("Graph Error: calling addEdge() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if(u == v){
    addArc(G, u, v);
  }
  else{
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
  }
}

void addArc(Graph G, int u, int v){
  if(G == NULL){
    printf("Graph Error: calling addArc() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(G->neighbors[u]) != 0){
    moveFront(G->neighbors[u]);
    while(index(G->neighbors[u]) > -1){
      if(get(G->neighbors[u]) == v){
        return;
      }
      moveNext(G->neighbors[u]);
    }
    moveFront(G->neighbors[u]);
    while(1){
      if( (get(G->neighbors[u]) < v) && (get(G->neighbors[u]) != back(G->neighbors[u])) ){
        moveNext(G->neighbors[u]);
      }
      //bigger and at the back
      else if( (get(G->neighbors[u]) < v) && (get(G->neighbors[u]) == back(G->neighbors[u])) ){
        append(G->neighbors[u], v);
        G->size++;
        break;
      }
      //smaller
      else{
        insertBefore(G->neighbors[u], v);
        G->size++;
        break;
      }
    }
  }
  else{
    append(G->neighbors[u], v);
    G->size++;
  }
}

void DFS(Graph G, List S){
  if(G == NULL){
    printf("Graph Error: calling DFS() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if(S == NULL){
    printf("Graph Error: calling DFS() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  //1. for all x in the vertex set of G
  //2.    color[x] = white
  //3.    p[x] = nil
  //4. time = 0
  //5. for all x in the vertex set of G
  //6. if color[x] == white
  //7.    Visit(x)
  //printf("starts DFS\n");
  int time;
  int x;
  if(length(S) != 0){
    moveFront(S);
  }
  while(index(S) > -1){
    x = get(S);
    G->color[x] = WHITE;
    G->parent[x] = NIL;
    moveNext(S);
  }
  time = 0;
  if(length(S) != 0){
    moveFront(S);
  }
  while(index(S) > -1){
    x = get(S);
    if(G->color[x] == WHITE){
      visit(G, S, x, &time);
    }
      moveNext(S);
    }
    for(int i = 1; i <= G->order; i++){
      deleteBack(S);
    }
  
}

Graph transpose(Graph G){
  if(G == NULL){
    printf("Graph Error: calling transpose() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  Graph T = newGraph(G->order);
  for(int i = 1; i <= G->order; i++){
    List temp = G->neighbors[i];
    if(length(temp) != 0){
      moveFront(temp);
    }
    while(index(temp) > -1){
      append(T->neighbors[get(temp)], i);
      moveNext(temp);
    }
  }
  T->size = G->size;
  return T;
}

Graph copyGraph(Graph G){
  if(G == NULL){
    printf("Graph Error: calling transpose() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  Graph C = newGraph(G->order);
  C->size = G->size;
  for(int i = 1; i <= G->order; i++){
    C->neighbors[i] = copyList(G->neighbors[i]);
    C->color[i] = G->color[i];
    C->discover[i] = G->discover[i];
    C->finish[i] = G->finish[i];
    C->parent[i] = G->parent[i];
  }
  return C;
}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
  if(G == NULL){
    printf("Graph Error: calling printGraph() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  for(int i = 1; i < getOrder(G) + 1; i++){
    fprintf(out, "%d: ", i);
    if(length(G->neighbors[i]) != 0){
      moveFront(G->neighbors[i]);
      while(index(G->neighbors[i]) > -1){
        fprintf(out, "%d ", get(G->neighbors[i]));
        moveNext(G->neighbors[i]);
      }
    }
    fprintf(out, "\n");
  }
}

