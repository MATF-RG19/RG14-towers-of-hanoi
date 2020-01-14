//Code copied from http://poincare.matf.bg.ac.rs/~ivan/?content=rg;
//Code translated to english and adapted for this project

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

GLuint bg_tex;
GLuint platform_tex;
GLuint handle_tex;
GLuint hammer_tex;

//Structures that represent bitmap headers
typedef struct {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offsetbits;
} BITMAPFILEHEADER;

typedef struct {
    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitcount;
    unsigned int compression;
    unsigned int sizeimage;
    int xpelspermeter;
    int ypelspermeter;
    unsigned int colorsused;
    unsigned int colorsimportant;
} BITMAPINFOHEADER;

//Structure that keeps picture data
typedef struct Image {
    int width, height;
    char *pixels;
} Image;

//Pointer to initialized Image structure
Image *image_init(int width, int height);

//Free Image space
void image_done(Image *image);

//Load picture(filename) data to Image structure
void image_read(Image *image, char *filename);

//Load background texture
void load_background();

//Load platform texture
void load_platform_tex();

//Load hammer head and handle texture
void load_hammer_tex();

void load_handle_tex();

#endif
