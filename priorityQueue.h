/*******************************************************************************
*   Example program to test the performance of different
*   priority queue implementations with dynamic memory 
*   allocation.
*
* (c) 2019-2023, Joris Remmers (Mechanical Engineering, TUE)
*
* 02-2019  Version 1.
* 01-2022  Cleaning up code
* 08-2023  Version for dijktra's algorithm
*******************************************************************************/

#include <stdbool.h>

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

typedef struct
{
  double prio;
  int    ID;
} ITEM;

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

typedef struct
{
  int  count;
  ITEM item[];
} PQ;


//-----------------------------------------------------------------------------
// clear:  Clears the priority queue. All items are removed
//
// Argument:
//   pq     the priority queue
//-----------------------------------------------------------------------------

void clear

  ( PQ*     pq );

//-----------------------------------------------------------------------------
// isEmpty:  checks if the priority queue is empty.
//
// Argument:
//   pq     the priority queue
//
// Returns:
//   bool   true if the queue is empty, false otherwise
//-----------------------------------------------------------------------------

bool isEmpty

  ( PQ*    pq );


//-----------------------------------------------------------------------------
// put:  adds an item to the queue
//
// Argument:
//   pq     the priority queue
//   ID     the ID of the item
//   prio   the prio value of the item. Must be positive.
//-----------------------------------------------------------------------------

void put

  ( PQ*      pq   , 
    int      ID   ,
    double   prio );


//-----------------------------------------------------------------------------
// getPrio:  returns the priority (the item with the lowest value
//
// Argument:
//   pq     the priority queue
//
// Returns:
//   ITEM   the item with the lowest value
//-----------------------------------------------------------------------------

ITEM getPrio

  ( PQ*    pq );
