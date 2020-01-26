#include "move.h"
#include <string.h>
#include <unistd.h>

#define BOUNCE_OFF 0
#define BOUNCE_UP 1
#define BOUNCE_DOWN 2

extern char message[MAX_SIZE];

void initialize_move() {

    //If the move is made by player
    if(!hanoi_active) {
        sprintf(message, "Moving from %c to %c.\n", src->id, dest->id);

        //Checking if the move is valid
        if(!is_valid_move()) { return; }
        move_count++;
    }

    //Activating superman and bouncing
    superman_active = 1;
    superman_fly = 0;
    bounce = BOUNCE_UP;
    bounce_counter = 0;

    //Distance between source and destination towers
    distance = dest->tower_pos_x - src->tower_pos_x;

    //Calculating increment of disk rotation based on tower distance
    //For closer tower, disk rotates semi-circle, for further tower, disk rotates full circle
    float rotation_range = (abs(distance) < 2.6) ? 180 : 360;
    rotation_parameter = (rotation_range * speed) / distance;

    //Calling timer function
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
}

void on_timer(int value) {

    if (value != TIMER_ID)
        return;

    //Performing selected move
    if (superman_active)
        superman_hit();
    if (move_ongoing)
        perform_move();

    //Sending new picture to the screen
    glutPostRedisplay();

    //If the move is still active, timer function is called
    if (superman_active || move_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }

    //If automatic solving is active and current move is done, initialize next move,
    //which was set up in move_complete function
    if(hanoi_active && !move_ongoing && !superman_active) {
        initialize_move();
    }
}


void superman_hit() {

    //Moving to the source tower left or right
    if (src == &A && !superman_fly) { //Move to tower A
        superman_xpos -= speed;

        //Superman is below destination tower
        if (superman_xpos <= A.tower_pos_x) {
            superman_xpos = A.tower_pos_x;
            superman_fly = 1;
        }
    }
    else if (src == &B && !superman_fly) { //Move to tower B

        if (superman_xpos <= B.tower_pos_x) { //move to the right, A->B
            superman_xpos += speed;

            if (superman_xpos >= B.tower_pos_x) { //Superman is below destination tower
                superman_xpos = B.tower_pos_x;
                superman_fly = 1;
            }
        }
        else { //move to the left, B<-C
            superman_xpos -= speed;

            if (superman_xpos <= B.tower_pos_x) { //Superman is below destination tower
                superman_xpos = B.tower_pos_x;
                superman_fly = 1;
            }
        }
    }
    else if (src == &C && !superman_fly) { //Move to tower C
        superman_xpos += speed;

        if (superman_xpos >= C.tower_pos_x) { //Superman is below destination tower
            superman_xpos = C.tower_pos_x;
            superman_fly = 1;
        }
    }

    //Moving up and down
    if(superman_fly) {
        //Moving up to hit the platform
        if(!move_ongoing) {
            left_arm_rotation = -160;
            superman_ypos += speed;
            if(superman_ypos >= 1.6)
                move_ongoing = 1;
        }
        else { //Moving down to start position
            superman_ypos -= speed;
    
            if (superman_ypos <= 0) { //Start position reached, deactivating Superman
                superman_ypos = 0;
                superman_active = 0;
                superman_fly = 0;
                left_arm_rotation = 0;
            }
        }
    } 

}


void perform_move() {

    //Index of the top disk on the destination tower
    //If the tower is empty, decrementing top would cause error
    int dest_top = (dest->top == 0) ? 0 : dest->top - 1;

    if(bounce) { 
        bouncing(); 
    }

    //moving disk up until it reaches top of the tower
    if(moving_up) {
        src->disk_pos_y[src->top - 1] += speed;

        if(src->disk_pos_y[src->top - 1] > TOWER_HEIGHT + DISK_HEIGHT) {
            moving_up = 0;
            moving_side = 1;
        }
    }

    //moving disk from left to right until it reaches position of the destination tower
    if(moving_side && src->tower_pos_x < dest->tower_pos_x) {
        add_xpos += speed;
        rotation -= rotation_parameter;

        if(src->tower_pos_x + add_xpos >= dest->tower_pos_x) {
            add_xpos = dest->tower_pos_x - src->tower_pos_x;
            rotation = 0;

            moving_side = 0;
            moving_down = 1;
        }
    }

    //moving disk from right to left until it reaches position of the destination tower
    else if(moving_side && src->tower_pos_x > dest->tower_pos_x) {
        add_xpos -= speed;
        rotation -= rotation_parameter;

        if(src->tower_pos_x + add_xpos <= dest->tower_pos_x) {
            add_xpos = dest->tower_pos_x - src->tower_pos_x;
            rotation = 0;

            moving_side = 0;
            moving_down = 1;
        }
    }

    //moving disk down until it reaches disk on top
    if(moving_down) {
        src->disk_pos_y[src->top - 1] -= speed;

        if(src->disk_pos_y[src->top - 1] <= dest->disk_pos_y[dest_top] + DISK_HEIGHT){
            moving_down = 0;
            move_done = 1;
        }
    }

    //move is completed, updating stacks and initializing next move
    if(move_done) {
        move_complete();
    }
}

void move_complete() {

    //Updating tower stacks and setting up move variables for next move
    push(dest, pop(src));
    move_ongoing = 0;
    moving_up = 1;
    move_done = 0;
    add_xpos = 0.0;
    rotation = 180;
    message[0] = '\0';

    //Checking if the player solved the puzzle
    if(!hanoi_active && is_solved()) {
        sprintf(message, "Congratulations! You solved the puzzle in %d moves.\n", move_count);
        return;
    }

    //If automatic solving is active proceed to the next move in the array 'hanoi_moves'
    if(hanoi_active) {
        if(hanoi_counter == m-1) {
            //All moves are completed
            hanoi_active = 0;
            sprintf(message, "Solved in %d moves!", m);
            return;
        }

        //Otherwise, initialize next move
        hanoi_counter++;
        src = hanoi_moves[hanoi_counter].h_src;
        dest = hanoi_moves[hanoi_counter].h_dest;
    }
}


void bouncing() {
    //Bounce up
    if(bounce == BOUNCE_UP) {
        for (int i = 0; i < src->top-1; i++) {
            src->disk_pos_y[i] = src->disk_pos_y[i] + 0.015*(i+2);
        }
        bounce_counter++;
        if(bounce_counter > 8){
            bounce = BOUNCE_DOWN;
        }
    }
    //Bounce down
    else if(bounce == BOUNCE_DOWN) {
        for (int i = 0; i < src->top-1; i++) {
            src->disk_pos_y[i] = src->disk_pos_y[i] - 0.015*(i+2);
        }
        bounce_counter--;
        if(bounce_counter == 0){
            bounce = BOUNCE_OFF;
        }
    }

}

int is_valid_move() {

    //If the moved disk is bigger than the disk on top
    if(dest->top != 0 && src->size[src->top - 1] > dest->size[dest->top - 1]) {
        sprintf(message, "Error: Disk from %c is bigger than top disk on %c\n", src->id, dest->id);
        glutPostRedisplay(); //This is called so that message can be shown
        return 0;
    }

    //If we try to move disk from an empty tower
    if(src->top == 0) {
        sprintf(message, "Error: Tower %c is empty.\n", src->id);
        glutPostRedisplay();
        return 0;
    }

    return 1;
}

int is_solved() {
    return (C.top == DISK_NUM);
}
