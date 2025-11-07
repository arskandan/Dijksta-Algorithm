#ifndef MYLIB_H
#define MYLIB_H

/*
 * Header file for the library functions of the 
 * implementation of Dijkstra's algorithm.
 * 
 * Part of assignment 1 in the course 4EM30:
 *   Scientific Computing for Mechanical Engineering
 *   2023-2024
 *
 * (c) 2023-2024 Joris Remmers TU/e
 *
 * To be completed by students:
 *
 * TEAM: xxxx  
 * Member 1: Neeraj Dokania (1935917)
 * Member 2: Ariyanayag Ramesh Skandan (2012618) 
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


#define MAX_EDGES 10
#define SECONDSPERHOUR 3600
#define PIXELS 1000

//=============================================================================
//  Structures
//=============================================================================

//-----------------------------------------------------------------------------
//  Coordinate
//
//  Struct to describe a geogrphical coordinate
//     lat:   lateral component
//     lon:   longitudinal component
//-----------------------------------------------------------------------------


typedef struct
{
  double      lat;
  double      lon;
} Coordinate;


//------------------------------------------------------------------------------
//  Vertex
//
//  Struct to store all data of a single vertex in the graph
//     crd:         geographical coordinate
//     edgeCount:   number of edges connected to this vertex
//     edges:       array of unique edges connected to this vertex
//------------------------------------------------------------------------------


typedef struct
{
  Coordinate  crd;
  int         edgeCount;
  int         edges[MAX_EDGES];
} Vertex;


//-----------------------------------------------------------------------------
//  Edge
//
//  Struct to store all data of a single vertex in the graph
//     vertex1:     vertex ID 1
//     vertex2:     vertex ID 2
//     length:      geographical length of the edge
//     time:        time needed to travel the edge
//     type:        type of the edge: 
//                    0 = Highway, 1 = Provincial road, 2 = city road  
//-----------------------------------------------------------------------------


typedef struct 
{
  int         vertex1;
  int         vertex2;
  double      length;
  double      time;
  int         type;
  char        country[3];
} Edge;


//------------------------------------------------------------------------------
//  Graph
//
//  Struct that contains all data of the graph
//     edges       array with edges
//     vertices    array with vertices
//     nEdg        number of edges
//     nVer        number of vertices
//     box         corners of bounding box of the map: 
//                     min. lon.; min. lat.; max. lon.; max. lat. 
//------------------------------------------------------------------------------


typedef struct
{
  Edge        *edges;
  Vertex      *vertices;
  int         nEdg;
  int         nVer;  
  double      box[4];  
} Graph;


//------------------------------------------------------------------------------
//  Route
//
//  Struct that contains information on the route that is calculated
//     start     ID of starting vertex
//     finish    ID of finishing vertex
//  
//  Must be expanded
//------------------------------------------------------------------------------


typedef struct
{
  int         start;
  int         finish;
  int        *visitedVertices;
  int        *via;
  int        *viaTime;
} Route;


//==============================================================================
//  Functions
//==============================================================================

//------------------------------------------------------------------------------
//  readGraph
//
//  To be completed
//
//------------------------------------------------------------------------------


void readGraph

  ( char*             name  ,
    Graph*            graph );


//------------------------------------------------------------------------------
//  initialiseRoute
//
//  To be completed / arguments can be added
//------------------------------------------------------------------------------

 
 void initialiseRoute

  ( Route*            route    ,
    int               startID  ,
    int               finishID ,
    Graph*            graph);

  
//------------------------------------------------------------------------------
//  calculateRoute
//
//  To be completed / arguments can be added
//------------------------------------------------------------------------------


void calculateRoute

  ( Graph*            graph ,
    Route*            route  );

    



  

//------------------------------------------------------------------------------
//  plotRoute
//
//  To be completed / arguments can be added
//------------------------------------------------------------------------------


void plotRoute

  ( Graph*            graph ,
    Route*            route );
    
 
#endif
