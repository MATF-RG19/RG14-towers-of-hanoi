#include "stack.h"

//Stacks initialization
void initialize_stack()
{
    A.id = 'A';
    B.id = 'B';
    C.id = 'C';

    //setting stack tops
    A.top = 0;
    B.top = 0;
    C.top = 0;

    //setting x positions
    A.tower_pos_x = -TOWER_DISTANCE;
    B.tower_pos_x = 0;
    C.tower_pos_x = TOWER_DISTANCE;

    //computing disk size depending on number of disks
    float size = DISK_RADIUS + DISK_NUM * 0.1;

    //placing disks to first tower
    for(int i = 0; i < DISK_NUM; i++) {
        push(&A, size);
        size = size - 0.1;
    }
}

//Pop disc
float pop(Stack *p) {

    float temp = p->size[p->top-1];		//size of popped disk
    p->top--;
    return temp;
}

//Push disc
void push(Stack *p, float size) {

    p->size[p->top] = size;
    p->disk_pos_y[p->top] = DISK_HEIGHT * (p->top + 1) - DISK_HEIGHT/2;
    p->top++;
}
