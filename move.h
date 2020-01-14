#ifndef _MOVE_H_
#define _MOVE_H_

#include "stack.h"
#include "algorithm.h"

#define TIMER_ID 0
#define TIMER_INTERVAL 20
#define MAX_SIZE 100

//Move variables
int move_count;     //Counting number of moves made
int move_ongoing;	//Indicator that disk is moving
int move_done;		//Move completed indicator
int moving_up;		//Moving disk up
int moving_down;	//Moving disk down
int moving_side;	//Moving left or right

float speed;		//Positions increment while moving disks
float add_xpos;		//Increment of x position while moving disk left or right
float rotation;     //Disk rotation angle
float rotation_parameter; //Disk rotation angle increment
float distance;     // Distance from source to destination tower

float h_alpha;      //Rotation angle for hammer
int hammer_active;  //Indicator that hammer is moving to hit the platform
int bounce;         //Bounce variables
int bounce_counter;


//Timer function
void on_timer(int value);

//Setting up selected move
void initialize_move();

//Performing the selected move, moving disks
void perform_move();

//Updating stacks when current move is done and initializing next move
void move_complete();

//Hitting source tower with hammer
void hammer_hit();

//Bounce disks after the hammer hit
void bouncing();

//Checking if selected move is valid
int is_valid_move();

//Checking if the puzzle is solved
int is_solved();

#endif
