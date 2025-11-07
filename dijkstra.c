/*------------------------------------------------------------------------------
 * dijkstra.c
 *
 * Implementation of Dijkstra's algorithm.
 * 
 * Part of assignment 1 in the course 4EM30:
 *   Scientific Computing for Mechanical Engineering
 *   2023-2024
 *
 * (c) 2023-2024 Joris Remmers TU/e
 *
 * To be completed by students:
 *
 * TEAM: 44 
 * Member 1: Neeraj Dokania (1935917)
 * Member 2: Ariyanayag Ramesh Skandan (2012618)
------------------------------------------------------------------------------*/

#include "mylib.h"
#include <stdlib.h>
#include <string.h>
#include "priorityQueue.h"
#include <math.h>
#include <limits.h>

int main ( void ) 
{  
  Graph graph;
  Route route;
  Route routeTime;
             
  readGraph( "mapBeNeLux.dat" , &graph ); 
  
  // USe the following: startID = 3327, finishID = 11510;
  
  initialiseRoute( &route , 3327 , 11510 , &graph);
  
  calculateRoute( &graph , &route);

  plotRoute( &graph , &route);
  
  free(graph.edges);
  free(graph.vertices);   
  
  return 0;
}
