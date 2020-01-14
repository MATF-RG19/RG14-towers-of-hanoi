//Code copied from http://poincare.matf.bg.ac.rs/~ivan/?content=rg;
//Code translated to english and adapted for this project

#include "image.h"


Image *image_init(int width, int height) {

    Image *image;

    //Exit in case of error
    assert(width >= 0 && height >= 0);

    // Allocate space for Image structure
    image = (Image *) malloc(sizeof(Image));
    assert(image != NULL);

    //Initialize struct elements
    image->width = width;
    image->height = height;
    if (width == 0 || height == 0)
    image->pixels = NULL;
    else {
        image->pixels = (char *)malloc(3 * width * height * sizeof(char));
        assert(image->pixels != NULL);
    }

    return image;
}

void image_done(Image *image) {

    //Free space containing pixels data
    free(image->pixels);
    //Free space of the Image structure
    free(image);
}

void image_read(Image *image, char *filename) {

    FILE *file;
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    unsigned int i;
    unsigned char r, g, b, a;

    //Delete previous Image pixels data
    free(image->pixels);
    image->pixels = NULL;

    //Opening new file
    assert((file = fopen(filename, "rb")) != NULL);

    //Reading first header data
    fread(&bfh.type, 2, 1, file);
    fread(&bfh.size, 4, 1, file);
    fread(&bfh.reserved1, 2, 1, file);
    fread(&bfh.reserved2, 2, 1, file);
    fread(&bfh.offsetbits, 4, 1, file);

    //Reading second header data
    fread(&bih.size, 4, 1, file);
    fread(&bih.width, 4, 1, file);
    fread(&bih.height, 4, 1, file);
    fread(&bih.planes, 2, 1, file);
    fread(&bih.bitcount, 2, 1, file);
    fread(&bih.compression, 4, 1, file);
    fread(&bih.sizeimage, 4, 1, file);
    fread(&bih.xpelspermeter, 4, 1, file);
    fread(&bih.ypelspermeter, 4, 1, file);
    fread(&bih.colorsused, 4, 1, file);
    fread(&bih.colorsimportant, 4, 1, file);


    //from second header use only image size
    image->width = bih.width;
    image->height = bih.height;


    //Allocate space depending on whether we use RGB or RGBA
    if (bih.bitcount == 24)
    image->pixels = (char *)malloc(3 * bih.width * bih.height * sizeof(char));
    else if (bih.bitcount == 32)
    image->pixels = (char *)malloc(4 * bih.width * bih.height * sizeof(char));
    else {
        fprintf(stderr, "image_read(): Supported only textures which use 24 or 32 bits per pixel.\n");
        exit(1);
    }
    assert(image->pixels != NULL);

    //Reading pixel data
    if (bih.bitcount == 24)
    //24 bits = 3 bytes -> RGB
    for (i = 0; i < bih.width * bih.height; i++) {
        //colors are in reverse order
        fread(&b, sizeof(char), 1, file);
        fread(&g, sizeof(char), 1, file);
        fread(&r, sizeof(char), 1, file);

        image->pixels[3 * i] = r;
        image->pixels[3 * i + 1] = g;
        image->pixels[3 * i + 2] = b;
    }
    else if (bih.bitcount == 32)
    //32 bits = 4 bytes -> RGBA
    for (i = 0; i < bih.width * bih.height; i++) {
        fread(&b, sizeof(char), 1, file);
        fread(&g, sizeof(char), 1, file);
        fread(&r, sizeof(char), 1, file);
        fread(&a, sizeof(char), 1, file);

        image->pixels[4 * i] = r;
        image->pixels[4 * i + 1] = g;
        image->pixels[4 * i + 2] = b;
        image->pixels[4 * i + 3] = a;
    }

    fclose(file);
}

void load_background() {

    //Initializing Image structure
    Image *image = image_init(0, 0);

    //Creating texture for background
    image_read(image, "Textures/bg.bmp");

    //Setting texture parameters
    glGenTextures(1, &bg_tex);

    glBindTexture(GL_TEXTURE_2D, bg_tex); //Binding texture to a pointer
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    glBindTexture(GL_TEXTURE_2D, 0); //unbinding

    image_done(image);
}

void load_platform_tex() {

    //Initializing Image structure
    Image *image = image_init(0, 0);

    //Creating texture for platform
    image_read(image, "Textures/wood.bmp");

    //Setting texture parameters
    glGenTextures(1, &platform_tex);

    glBindTexture(GL_TEXTURE_2D, platform_tex); //Binding texture to a pointer
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    glBindTexture(GL_TEXTURE_2D, 0); //unbinding

    image_done(image);
}

void load_hammer_tex() {
        //Initializing Image structure
        Image *image = image_init(0, 0);

        //Creating texture for hammer head
        image_read(image, "Textures/hammer.bmp");

        //Setting texture parameters
        glGenTextures(1, &hammer_tex);

        glBindTexture(GL_TEXTURE_2D, hammer_tex); //Binding texture to a pointer
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     image->width, image->height, 0,
                     GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
        glBindTexture(GL_TEXTURE_2D, 0); //unbinding

        image_done(image);

}

void load_handle_tex() {
        //Initializing Image structure
        Image *image = image_init(0, 0);

        //Creating texture for hammer handle
        image_read(image, "Textures/handle.bmp");

        //Setting texture parameters
        glGenTextures(1, &handle_tex);

        glBindTexture(GL_TEXTURE_2D, handle_tex); //Binding texture to a pointer
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     image->width, image->height, 0,
                     GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
        glBindTexture(GL_TEXTURE_2D, 0); //unbinding

        image_done(image);

}
