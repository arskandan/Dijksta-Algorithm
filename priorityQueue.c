/*******************************************************************************
*   Example program to test the performance of different
*   priority queue implementations with dynamic memory 
*   allocation.
*
* (c) 2019-2022, Joris Remmers (Mechanical Engineering, TUE)
*
* 02-2019  Version 1.
* 01-2022  Cleaning up code
*******************************************************************************/

#include "priorityQueue.h"
#include <stdio.h>
#include <math.h>


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

void clear

  ( PQ*  pq )
{
  pq->count = 0;
}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

bool isEmpty

  ( PQ*    pq )
{
  return pq->count == 0;
}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

void put

  ( PQ*    pq    , 
    int    ID    ,
    double prio  )
    
{
  ITEM item;
  
  item.ID   = ID;
  item.prio = prio;
 
  pq->item[pq->count] = item;

  if( pq->count == 0 )
  {
    pq->count++;
    return;
  }
    
  int now    = pq->count;
  int parent = (now-1)/2;

  while( pq->item[parent].prio > item.prio )
  {
    pq->item[now] = pq->item[parent];
    now    = parent;
    parent = (now-1)/2;

    if ( now == 0 )
    {
      break;
    }
  }

  pq->item[now] = item;
  pq->count++;
}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
  
ITEM getPrio

  ( PQ*    pq )
  
{
  ITEM prioItem, lastItem;
  int  child,   now;
  
  prioItem = pq->item[0];

  lastItem = pq->item[pq->count-1];

  for( now = 0 ; 2*(now+1) < pq->count ; now = child )
  {    
    child = 2*now+1;

    if( child != pq->count+1 && pq->item[child+1].prio < pq->item[child].prio ) 
    {
      child++;
    }
            
    if( lastItem.prio > pq->item[child].prio )
    {
      pq->item[now] = pq->item[child];
    }
    else
    {
      break;
    }
  }

  pq->item[now] = lastItem;

  pq->count--;

  return prioItem;
}
