// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "Queue.h"

#define CITY_NUMBER 30

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV; new->nE = 0;
	new->edges = malloc(nV*sizeof(int *));
	assert(new->edges != 0);
	for (v = 0; v < nV; v++) {
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != 0);
		for (w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}
	return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
//return the number of vertices in the path
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
   Vertex curr_src = src;
   Vertex curr_dest = dest;
   int path_index = 1;
   
   if(src == dest)
   {
      path[0] =src;
      return 1;
   }
   path[0] =src;
   
   while(curr_src!= curr_dest)
   {
      //printf("The curr_src is now %d\n",curr_src);
      if((curr_src = findNextVertex(g, curr_src, curr_dest, max)) != -1)
      {
         path[path_index] = curr_src;
         path_index++;
         
      }
      else
      {
         //printf("WARNING: No such a path!\n");
         return 0;
      }
   }
   path[path_index] = dest; 
   return path_index; // never find a path ... you need to fix this
}


// return the next vertex from src to dest
// return -1 if no such a vertex meaning no path is available
int findNextVertex(Graph g, Vertex src, Vertex dest, int max)
{
   
   //printf("Running findNextVertex! finding path from %d to %d\n",src, dest);
   if (src == dest)
   {
      return 0;
   }
   //find the vertex of the first step from src
   Vertex curr_src = dest;
   Vertex curr_dest = src;
   
   Queue q = newQueue();//to do que
   QueueJoin(q,curr_src);
   int visited[CITY_NUMBER] = {0};
   //int vertices_number = 0;
   
   while(!QueueIsEmpty(q))
   {
      
      Vertex curr_vertex = QueueLeave(q);
      visited[curr_vertex]=1;
      
      for(Vertex curr_next = 0; curr_next < CITY_NUMBER; curr_next++)
      {
         //printf("Current vertex is %d, next vertex is%d\n\n", curr_src,curr_next);
         //printf("The edge long is %d, the max long is %d\n\n",g->edges[curr_vertex][curr_next], max);
         // loop for valid edges
         if((g->edges[curr_vertex][curr_next] < max) && (g->edges[curr_vertex][curr_next] != 0))
         {
            //if visited, then continue
            
            if(visited[curr_next] == 1)
            {
               continue;
            }
            //if found the vertex
            //printf("curr_next is %d, curr_dest is %d\n", curr_next,curr_dest);
            if(curr_next == curr_dest)
            {
               //printf("I found it!!!\n\n\n");
               return curr_vertex;
            }
            //this is a new, available vertex
            else
            {
               QueueJoin(q,curr_next);
               visited[curr_next]=1;
            }
         }
      }
   }
	assert(g != NULL);
	return -1; // never find a path ... you need to fix this
}












