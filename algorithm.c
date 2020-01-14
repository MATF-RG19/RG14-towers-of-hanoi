#include "algorithm.h"

extern void on_timer();
extern void initialize_move();

void hanoi_solve() {
        hanoi_active = 1; //solving by algorithm activated
        m = 0; //counting moves in hanoi_alg() function

        //call solving algorithm
        hanoi_alg(DISK_NUM, &A, &C, &B);

        hanoi_counter = 0; //counter for how many moves are completed,
                           //used in perform_move() function in move.c file
        src = hanoi_moves[hanoi_counter].h_src;
        dest = hanoi_moves[hanoi_counter].h_dest;

        //Initializing first move
        initialize_move();
}

//Code copied from http://poincare.matf.bg.ac.rs/~janicic/courses/p2.pdf - page 62
void hanoi_alg(int n, Stack *start, Stack *finish, Stack *spare) {

        if (n > 0) {
                hanoi_alg(n-1,start,spare,finish);

                //Move disk from start to finish tower. Storing moves in an array
                hanoi_moves[m].h_src = start;
                hanoi_moves[m].h_dest = finish;
                m++;

                hanoi_alg(n-1,spare,finish,start);
        }
}
