#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <GL/glut.h>

#define TOWER_DISTANCE 2.5
#define TOWER_RADIUS 0.1
#define DISK_RADIUS 0.15
#define DISK_HEIGHT 0.27
#define MAX_DISK_NUM 10

int DISK_NUM;
float TOWER_HEIGHT;

//Structure that keeps informations for each tower
typedef struct _stack {
    int top;                        //number of disks
    float size[MAX_DISK_NUM];		//size of each disk
    float tower_pos_x;			    //tower position along the X axis
    float disk_pos_y[MAX_DISK_NUM];	//position of each disk along the Y axis
    char id;                        //ID of the tower
} Stack;

//Towers A, B and C
Stack A;
Stack B;
Stack C;

//Pointers to the towers used in a disk movement
Stack *src;
Stack *dest;

//Stacks initialization
void initialize_stack();

//Pop disk
float pop(Stack *p);

//Push disk
void push(Stack *p, float size);

#endif
