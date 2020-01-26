#ifndef _DRAW_H_
#define _DRAW_H_

#include "stack.h"
#include "image.h"
#include "move.h"
#include <GL/glut.h>

//Drawing background
void draw_background();

//Drawing towers
void draw_towers();

//Drawing disks
void draw_disks();

//Drawing Superman
void draw_superman();

//Setting material for objects
void set_material(char id);

#endif
