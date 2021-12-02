// Graph ADT interface ... COMP9024 21T3
#include <stdbool.h>

typedef struct GraphRep *Graph;

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
   Vertex v;
   Vertex w;
} Edge;

Graph newGraph(int);
int   numOfVertices(Graph);
void  insertEdge(Graph, Edge); //Note that this is a directed graph and that inserting an edge will only add a direction from v to w
void  removeEdge(Graph, Edge); //Note that this is a directed graph and that removing an edge will only remove a direction from v to w
bool  adjacent(Graph, Vertex, Vertex);
void  showGraph(Graph);
void  freeGraph(Graph);