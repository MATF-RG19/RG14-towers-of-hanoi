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

float speed;		//Positions increment while moving disks, animation speed
float add_xpos;		//Increment of x position while moving disk left or right
float rotation;     //Disk rotation angle
float rotation_parameter; //Disk rotation angle increment
float distance;     // Distance from source to destination tower

int superman_active;  //Indicator that Superman is activated
int superman_fly;     //Indicator that Superman is below the source tower and is ready to fly
float superman_xpos;  //x position increment for Superman translation
float superman_ypos;  //y position increment for Superman translation
float left_arm_rotation; //Rotation angle for left arm

int bounce;         //Bounce variables
int bounce_counter;


//Timer function
void on_timer(int value);

//Initializing selected move
void initialize_move();

//Performing selected move, moving disks
void perform_move();

//Updating stacks when current move is done and initializing next move
void move_complete();

//Superman moving to hit source tower
void superman_hit();

//Bounce disks after Superman hit
void bouncing();

//Check if selected move is valid
int is_valid_move();

//Check if the puzzle is solved
int is_solved();

#endif
