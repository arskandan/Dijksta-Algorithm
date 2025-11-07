#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "priorityQueue.h"
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>

/*
 * Implementation the library functions of the 
 * of Dijkstra's algorithm.
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
 */
 
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


void readGraph

  ( char*             name  ,
    Graph*            graph )
    
{
  FILE         *fp;
  
  float        lon,lat,len;
  int          id1,id2,ltn,typ;
  
  int          iEdg,iVer;

  double totalLength = 0.0;  
  double totalTime = 0.0; 
  
  char         country[3];

  if ( ( fp=fopen(name,"r") ) == NULL) 
  {
    printf("Cannot open file.\n");
  }
  
  fscanf( fp, "%d", &graph->nVer ); 
  fscanf( fp, "%d", &graph->nEdg );
  
  graph->edges    = (Edge*)  malloc(graph->nEdg * sizeof(Edge));
  graph->vertices = (Vertex*)malloc(graph->nVer * sizeof(Vertex));

  for ( iVer = 0 ; iVer < graph->nVer ; iVer++ )
  {
    fscanf( fp , "%f %f" , &lon , &lat ); 
   
    graph->vertices[iVer].crd.lon = lon;
    graph->vertices[iVer].crd.lat = lat;
  }
       
  for ( iEdg = 0 ; iEdg < graph->nEdg ; iEdg++ )
  {
    fscanf( fp , "%d %d %f %d %s\n" , 
                  &id1 , &id2 , &len , &typ , &country); 
   
    graph->edges[iEdg].vertex1 = id1;
    graph->edges[iEdg].vertex2 = id2;
    graph->edges[iEdg].length  = len;      
    graph->edges[iEdg].type    = typ; 
    strcpy(graph->edges[iEdg].country,country);
  }

int Ver[2];
      
      for ( iVer = 0 ;iVer< graph->nVer ; iVer++ )
        {  
        graph->vertices[iVer].edgeCount = 0;
        }
          for (iEdg = 0 ; iEdg< graph->nEdg ; iEdg++ )
          {
            Ver[0] = graph->edges[iEdg].vertex1;
            Ver[1] = graph->edges[iEdg].vertex2;
            for(int i = 0; i<2; i++)
             { graph->vertices[Ver[i]].edges[graph->vertices[Ver[i]].edgeCount] = iEdg;
              graph->vertices[Ver[i]].edgeCount++;
              }
          }
        
        double speedLimits[3][9] = 
        {
        // Country: NL, DE, UK, BE, DK, FR, SP, IT, Other
        {100.0, 130.0, 110.0, 120.0, 130.0, 110.0, 120.0, 130.0, 110.0}, // Motorway (0)
        {80.0, 100.0, 80.0, 70.0, 80.0, 90.0, 90.0, 80.0, 80.0},        // Provincial (1)
        {50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0}           // City (2)
        };

        int countryCode;
        for( iEdg = 0 ; iEdg<graph->nEdg ; iEdg++)
        {
          if (strcmp(country,"NL")==0)
            countryCode = 0;
          else if(strcmp(country,"DE")==0)
            countryCode = 1;
          else if(strcmp(country,"UK")==0)
            countryCode = 2;
          else if(strcmp(country,"BE")==0)
            countryCode = 3;
          else if(strcmp(country,"DK")==0)
            countryCode = 4;
          else if(strcmp(country,"FR")==0)
            countryCode = 5;
          else if(strcmp(country,"SP")==0)
            countryCode = 6;
          else if(strcmp(country,"IT")==0)
            countryCode = 7;
          else
            countryCode = 8;
            
         graph->edges[iEdg].time = (graph->edges[iEdg].length)/(speedLimits[graph->edges[iEdg].type][countryCode]);  
        }

        double minLon = graph->vertices[0].crd.lon , maxLon = graph->vertices[0].crd.lon;
        double minLat = graph->vertices[0].crd.lat , maxLat = graph->vertices[0].crd.lat;
        for(iVer = 1 ; iVer< graph->nVer ; iVer++)
        {
          if (graph->vertices[iVer].crd.lon < minLon)
              minLon = graph->vertices[iVer].crd.lon;
          else if (graph->vertices[iVer].crd.lon > maxLon)
              maxLon = graph->vertices[iVer].crd.lon;
        }

        for(iVer = 1 ; iVer< graph->nVer ; iVer++)
        {
          if (graph->vertices[iVer].crd.lat < minLat)
              minLat = graph->vertices[iVer].crd.lat;
          else if (graph->vertices[iVer].crd.lat > maxLat)
              maxLat = graph->vertices[iVer].crd.lat;
        }

        graph->box[0] = minLon;
        graph->box[1] = minLat;
        graph->box[2] = maxLon;
        graph->box[3] = maxLat;


        for(iEdg = 0 ; iEdg < graph->nEdg ; iEdg++)
            { 
              totalLength += graph->edges[iEdg].length;
            }
        printf("\n---------------------------------------------------------------------------------------------------");
        printf("\nPart (a) of the Assignment 1 \n\nSum of the length of all the roads is %4.5lf km", totalLength);

        for(iEdg = 0 ; iEdg < graph->nEdg ; iEdg++)
            {
              totalTime += graph->edges[iEdg].time;
            }  

    int time = totalTime;
    double remainingTime = (totalTime - time) * 60;
  //printf("\n%lf", totalTime);
  printf("\nTotal time to travel all the roads is %d hours and %.0lf minutes", time,remainingTime);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------


void initialiseRoute

  ( Route*     route    ,
    int        startID  ,
    int        finishID,
    Graph*     graph)
    
{
   route->start = startID;
   route->finish = finishID;

   route->visitedVertices =  malloc(graph->nVer * sizeof(int));
   route->via =  malloc(graph->nVer * sizeof(int));
   route->viaTime =  malloc(graph->nVer * sizeof(int));
}

double weight(ITEM u, ITEM v, Graph *graph) 
{
    int edgeIndex;
    for (int i = 0; i < graph->vertices[u.ID].edgeCount; i++) 
    {
        edgeIndex = graph->vertices[u.ID].edges[i];
        if (graph->edges[edgeIndex].vertex1 == u.ID && graph->edges[edgeIndex].vertex2 == v.ID) 
            
              return graph->edges[edgeIndex].length;
            
        else if ((graph->edges[edgeIndex].vertex1 == v.ID && graph->edges[edgeIndex].vertex2 == u.ID))
            {
              return graph->edges[edgeIndex].length;
            }
    }
   
}

//------------------------------------------------------------------------------
//  calculateRoute
//------------------------------------------------------------------------------

void calculateRoute

  ( Graph*            graph ,
    Route*            route )
    
{
  double alt[10], altTime[10];
  PQ  *pq = malloc(sizeof( PQ ) + (graph->nVer*sizeof(ITEM)));
  PQ  *rs = malloc(sizeof( PQ ) + (graph->nVer*sizeof(ITEM)));

  double shortestDist[graph->nVer] , fastestTime[graph->nVer];
  bool visitedShortestDist[graph->nVer] , visitedFastestTime[graph->nVer];
  float infy = INFINITY;
  int j, iVer, visitedCountDist = 0, visitedCountTime = 0, edgeIndex = 0;
  ITEM u,v,a,b;
    
    for (iVer = 0; iVer < graph->nVer; iVer++) {
        shortestDist[iVer] = infy; 
        visitedShortestDist[iVer] = false;
        route->via[iVer] = -1;
    }
  shortestDist[route->start] = 0;
  clear(pq);
  put(pq, route->start, 0);
  
 while(!isEmpty(pq))
 {      
        u = getPrio(pq);
        visitedShortestDist[u.ID] = true;

        for (j = 0; j < graph->vertices[u.ID].edgeCount; j++) 
        {
           route->visitedVertices[j] = u.ID;
           edgeIndex = graph->vertices[u.ID].edges[j];
           if (graph->edges[edgeIndex].vertex1 == u.ID) 
              {
              v.ID = graph->edges[edgeIndex].vertex2;
              } 
           else if (graph->edges[edgeIndex].vertex2 == u.ID)
              {
              v.ID = graph->edges[edgeIndex].vertex1;
              }

            alt[j] = shortestDist[u.ID] + weight(u, v, graph);
            
            if (alt[j] < shortestDist[v.ID]) 
            {
                shortestDist[v.ID] = alt[j]; 
                visitedShortestDist[v.ID] = true;
                route->via[v.ID] = u.ID;
                put(pq , v.ID, shortestDist[v.ID]);              
            }  
        }
}
free(pq);

// for fastest time

for ( iVer = 0; iVer < graph->nVer; iVer++) {
        fastestTime[iVer] = infy; 
        visitedFastestTime[iVer] = false;
        route->viaTime[iVer] = -1;
    }
fastestTime[route->start] = 0;
clear(rs);
put(rs, route->start, 0);
edgeIndex = 0;
while(!isEmpty(rs))
 {      
        a = getPrio(rs);
        visitedFastestTime[a.ID] = true;
        for (j = 0; j < graph->vertices[a.ID].edgeCount; j++) 
        {
           route->visitedVertices[j] = a.ID;
           edgeIndex = graph->vertices[a.ID].edges[j];
           if (graph->edges[edgeIndex].vertex1 == a.ID) 
              {
              b.ID = graph->edges[edgeIndex].vertex2;
              } 
           else if (graph->edges[edgeIndex].vertex2 == a.ID)
              {
              b.ID = graph->edges[edgeIndex].vertex1;
              }

            altTime[j] = fastestTime[a.ID] + graph->edges[edgeIndex].time;
            
            if (altTime[j] < fastestTime[b.ID]) 
            {
                fastestTime[b.ID] = altTime[j]; 
                visitedFastestTime[b.ID] = true;
                route->viaTime[b.ID] = a.ID;
                put(rs , b.ID, fastestTime[b.ID]);              
            }  
        }
}
free(rs);

}


//------------------------------------------------------------------------------
//  plotRoute
//------------------------------------------------------------------------------


void plotRoute

  ( Graph*            graph ,
    Route*            route )
    
{
  FILE *of;
  int iEdg,colorID;
  int VER, v1,v2,time;
  double remainingTime;
  
  Coordinate crd1,crd2,crd3,crd4;
  
  char color[5][10] = {"red" , "orange" , "green" , "blue" , "purple"};
  
  of=fopen("route.svg","w");
    
  double scalex = 0.9*PIXELS/(graph->box[2]-graph->box[0]);
  double scaley = 0.6*PIXELS/(graph->box[3]-graph->box[1]);
  
  if ( scalex > scaley )
  {
    scalex = scaley;
  }
  
  scaley = -scalex*243./150.;
  
  double transx = 0.5*(PIXELS-scalex*(graph->box[2]+graph->box[0]));
  double transy = 0.5*(PIXELS-scaley*(graph->box[3]+graph->box[1]));
  
  fprintf(of,"<svg version='1.1'\n");
  fprintf(of,"width='%f' height='%f'\n",(float)PIXELS,(float)PIXELS);
  fprintf(of,"xmlns='http://www.w3.org/2000/svg'>\n");
  fprintf(of,"<g transform='translate(%f,%f) scale(%f,%f)'>\n",transx,transy,scalex,scaley);
  fprintf(of,"<rect width='600' height='800' style='fill:rgb(255,255,255)' />\n");
  fprintf(of,"<style> line { stroke-width:%f;stroke-linecap: 'round';  }</style>\n",1.5/scalex);

  for (iEdg = 0; iEdg < graph->nEdg; iEdg++)
   {
    colorID = graph->edges[iEdg].type;
    crd1 = graph->vertices[graph->edges[iEdg].vertex1].crd;
    crd2 = graph->vertices[graph->edges[iEdg].vertex2].crd;

    fprintf(of, "<line x1='%lf' y1='%lf' x2='%lf' y2='%lf' style='stroke:%s;stroke-width:0.01' />\n",
            crd1.lon, crd1.lat, crd2.lon, crd2.lat, color[colorID]);
    }
  
    int destination = route->finish , current = destination , pathDist[graph->nVer] , pathLengthDist = 0;
    double shortestDistTime = 0, shortestDistDist = 0;
    while (current != -1) {
        pathDist[pathLengthDist++] = current;
        current = route->via[current];
    }
    
    for (int i = pathLengthDist - 1; i >= 0; i--) 
    { 
        v1 = pathDist[i];
        v2 = pathDist[i-1];
        int edgeIndex;
        for (int i = 0; i < graph->vertices[v1].edgeCount; i++) 
       {
        edgeIndex = graph->vertices[v1].edges[i];
        if (graph->edges[edgeIndex].vertex1 == v1 && graph->edges[edgeIndex].vertex2 == v2) 
             {shortestDistDist += graph->edges[edgeIndex].length;
              shortestDistTime += graph->edges[edgeIndex].time;}
            
        else if ((graph->edges[edgeIndex].vertex1 == v2 && graph->edges[edgeIndex].vertex2 == v1))
              {shortestDistDist += graph->edges[edgeIndex].length;
              shortestDistTime += graph->edges[edgeIndex].time;}
        }
      
    }
     time = shortestDistTime;
     remainingTime = (shortestDistTime - time) * 60;
    
    printf("\n---------------------------------------------------------------------------------------------------"); 
    printf("\nPart (d) and (e) of the Assignment 1\n");
    printf("\nThe shortest route is   :  %.2lf km and %d hrs and %.0lf minutes.\n",shortestDistDist ,time,remainingTime);

    for (VER = pathLengthDist-1; VER > 0; VER--)
    {
        colorID = 4; 
        crd1 = graph->vertices[pathDist[VER]].crd;
        crd2 = graph->vertices[pathDist[VER-1]].crd;
        fprintf(of, "<line x1='%f' y1='%f' x2='%f' y2='%f' style='stroke:%s;stroke-width:0.03' />\n",
                crd1.lon, crd1.lat, crd2.lon, crd2.lat, color[colorID]);
    }
    
// for fastest time 
    destination = route->finish;
    current = destination;
    int pathTime[graph->nVer] , pathLengthTime = 0;
    double fastestTimeDist = 0 , fastestTimeTime=0;
    while (current != -1) {
        pathTime[pathLengthTime++] = current;
        current = route->viaTime[current];
    }
    
    for (int i = pathLengthTime - 1; i >= 0; i--) { 
        v1 = pathTime[i];
        v2 = pathTime[i-1];
        int edgeIndex;
        for (int i = 0; i < graph->vertices[v1].edgeCount; i++) 
    {
        edgeIndex = graph->vertices[v1].edges[i];
        if (graph->edges[edgeIndex].vertex1 == v1 && graph->edges[edgeIndex].vertex2 == v2) 
             {fastestTimeDist += graph->edges[edgeIndex].length;
              fastestTimeTime += graph->edges[edgeIndex].time;}
            
        else if ((graph->edges[edgeIndex].vertex1 == v2 && graph->edges[edgeIndex].vertex2 == v1))
              {fastestTimeDist += graph->edges[edgeIndex].length;
              fastestTimeTime += graph->edges[edgeIndex].time;}
    }

    }
     time = fastestTimeTime;
     remainingTime = (fastestTimeTime - time) * 60;

    for (VER = pathLengthTime-1; VER > 0; VER--)
    {
        colorID = 3;
        crd3 = graph->vertices[pathTime[VER]].crd;
        crd4 = graph->vertices[pathTime[VER-1]].crd;
        fprintf(of, "<line x1='%f' y1='%f' x2='%f' y2='%f' style='stroke:%s;stroke-width:0.02' />\n",
                crd3.lon, crd3.lat, crd4.lon, crd4.lat, color[colorID]);
    }
  //printf("---------------------------------------------------------------------------------------------------\n");
  printf("The fastest route is    : %7.2lf km and %d hrs and %0.0lf minutes.\n", fastestTimeDist, time, remainingTime );
   printf("---------------------------------------------------------------------------------------------------\n");
  fclose(of);
  fprintf(of, "</g>\n");
  fprintf(of, "</svg>\n");
  fclose(of);
}