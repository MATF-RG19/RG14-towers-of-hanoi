#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "stack.h"
#define MAX_MOVES 1024 // MAX_DISK_NUM = 10 --> MAX_MOVES = 2^10 - 1

//Structure that keeps track of moves made by solving algorithm
typedef struct _hmove {
        Stack *h_src; //Source tower
        Stack *h_dest; //Destination tower
} Hmove;

//Array for storing all moves made by solving algorithm
Hmove hanoi_moves[MAX_MOVES];

//Indicator that automatic solving is active
int hanoi_active;
//Move counters
int m;
int hanoi_counter;

//Initializing automatic solving
void hanoi_solve();

//Function that solves towers of hanoi and stores moves in hanoi_moves[] array
void hanoi_alg(int n, Stack *start, Stack *finish, Stack *spare);

#endif
