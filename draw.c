#include "draw.h"
#include <math.h>

void draw_background() {

    //Background is not affected by lighting
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, bg_tex);

    glPushMatrix();
	    //Drawing background
	    glBegin(GL_QUADS);
	        glNormal3f(0, 0, 1);
	        glTexCoord2f(0, 0); glVertex3f(-15, -15, -3);
	        glTexCoord2f(1, 0); glVertex3f(15, -15, -3);
	        glTexCoord2f(1, 1); glVertex3f(15, 15, -3);
	        glTexCoord2f(0, 1); glVertex3f(-15, 15, -3);
	    glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
	//Everything else is affected by lighting
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void draw_towers() {

    glBindTexture(GL_TEXTURE_2D, platform_tex);
    set_material('w');

	//Drawing plarform for towers
	glPushMatrix();
	glBegin(GL_QUADS);

		//Front
		glNormal3f(0, 0, 1);
		glTexCoord2f(0, 0); glVertex3f(-4, -1, 1.5);
        glTexCoord2f(1, 0);	glVertex3f(4, -1, 1.5);
        glTexCoord2f(1, 1);	glVertex3f(4, 0, 1.5);
        glTexCoord2f(0, 1);	glVertex3f(-4, 0, 1.5);

		//Right
		glNormal3f(1, 0, 0);
		glTexCoord2f(0, 0); glVertex3f(4, -1, -1.5);
		glTexCoord2f(1, 0); glVertex3f(4, 0, -1.5);
		glTexCoord2f(1, 1); glVertex3f(4, 0, 1.5);
		glTexCoord2f(0, 1); glVertex3f(4, -1, 1.5);

		//Back
		glNormal3f(0, 0, -1);
		glTexCoord2f(0, 0); glVertex3f(-4, -1, -1.5);
		glTexCoord2f(0, 1); glVertex3f(-4, 0, -1.5);
		glTexCoord2f(1, 1); glVertex3f(4, 0, -1.5);
		glTexCoord2f(1, 0); glVertex3f(4, -1, -1.5);

		//Left
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0, 0); glVertex3f(-4, -1, -1.5);
		glTexCoord2f(0, 1); glVertex3f(-4, -1, 1.5);
		glTexCoord2f(1, 1); glVertex3f(-4, 0, 1.5);
		glTexCoord2f(1, 0); glVertex3f(-4, 0, -1.5);

		//Top
		glNormal3f(0, 1, 0);
		glTexCoord2f(0, 0); glVertex3f(-4, 0, -1.5);
		glTexCoord2f(0, 1); glVertex3f(-4, 0, 1.5);
		glTexCoord2f(1, 1); glVertex3f(4, 0, 1.5);
		glTexCoord2f(1, 0); glVertex3f(4, 0, -1.5);

		//Bottom
		glNormal3f(0, -1, 0);
		glTexCoord2f(0, 0); glVertex3f(-4, -1, -1.5);
		glTexCoord2f(0, 1); glVertex3f(-4, -1, 1.5);
		glTexCoord2f(1, 1); glVertex3f(4, -1, 1.5);
		glTexCoord2f(1, 0); glVertex3f(4, -1, -1.5);
	glEnd();
	glPopMatrix();

	//Drawing towers
	GLUquadricObj *obj = gluNewQuadric();
    gluQuadricTexture(obj, platform_tex);

    glPushMatrix();
		//First tower
		glTranslatef(-TOWER_DISTANCE, 0, 0);
		glPushMatrix();
			glRotatef(-90,1,0,0);
			gluCylinder(obj, TOWER_RADIUS, TOWER_RADIUS, TOWER_HEIGHT, 20, 20);
		glPopMatrix();

		//Second tower
		glTranslatef(TOWER_DISTANCE,0,0);
		glPushMatrix();
			glRotatef(-90,1,0,0);
			gluCylinder(obj, TOWER_RADIUS, TOWER_RADIUS, TOWER_HEIGHT, 20, 20);
		glPopMatrix();

		//Third tower
		glTranslatef(TOWER_DISTANCE,0,0);
		glPushMatrix();
			glRotatef(-90,1,0,0);
			gluCylinder(obj, TOWER_RADIUS, TOWER_RADIUS, TOWER_HEIGHT, 20, 20);
		glPopMatrix();
	glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void draw_disks() {
	//Setting blue color of the disks
    set_material('b');

	glPushMatrix();
		//Disks on the first tower
		for(int i=0; i<A.top; i++) {
			glPushMatrix();
				//Position of top disk, the one that is moving
				if(src == &A && i == A.top - 1) {
					glTranslatef(A.tower_pos_x + add_xpos, A.disk_pos_y[i], 0);
					if (moving_side) {
						//Rotating disk to destination tower using sinusoid function curve
						//Transforming distance between towers to [0, pi] range
						glTranslatef(0, sin(add_xpos*M_PI / distance), 0);
					}
					glRotatef(rotation, 0, 0, 1); //Spinning disk
				}
				else
					glTranslatef(A.tower_pos_x, A.disk_pos_y[i], 0); //Positions of remaining disks
				glRotatef(90, 1, 0, 0);
				glutSolidTorus(DISK_RADIUS, A.size[i], 20, 20);
			glPopMatrix();
		}

		//Disks on the second tower
		for(int i=0; i<B.top; i++) {
			glPushMatrix();
				//Position of top disk, the one that is moving
				if (src == &B && i == B.top - 1) {
					glTranslatef(B.tower_pos_x + add_xpos, B.disk_pos_y[i], 0);
					if (moving_side) {
						//Rotating disk to destination tower using sinusoid function curve
						//Transforming distance between towers to [0, pi] range
						glTranslatef(0, sin(add_xpos*M_PI / distance), 0);
					}
					glRotatef(rotation, 0, 0, 1); //Spinning disk
				}
				else
					glTranslatef(B.tower_pos_x, B.disk_pos_y[i], 0); //Positions of remaining disks
				glRotatef(90, 1, 0, 0);
				glutSolidTorus(DISK_RADIUS, B.size[i], 20, 20);
			glPopMatrix();
		}

		//Disks on the third tower
		for(int i=0; i<C.top; i++) {
			glPushMatrix();
				//Position of top disk, the one that is moving
				if (src == &C && i == C.top - 1) {
					glTranslatef(C.tower_pos_x + add_xpos, C.disk_pos_y[i], 0);
					if (moving_side) {
						//Rotating disk to destination tower using sinusoid function curve
						//Transforming distance between towers to [0, pi] range
						glTranslatef(0, sin(add_xpos*M_PI / distance), 0);
					}
					glRotatef(rotation, 0, 0, 1); //Spinning disk
				}
				else
					glTranslatef(C.tower_pos_x, C.disk_pos_y[i], 0); //Positions of remaining disks
				glRotatef(90, 1, 0, 0);
				glutSolidTorus(DISK_RADIUS, C.size[i], 20, 20);
			glPopMatrix();
		}

	glPopMatrix();

}

void draw_superman() {

	glPushMatrix();
		glTranslatef(0 + superman_xpos, -3 + superman_ypos, 0);

		//Head
		set_material('s');
		glPushMatrix();
			glTranslatef(0, 0.3, 0);
			glutSolidSphere(0.3, 100, 100);
		glPopMatrix();
	
		//Body
		//Front
		glBindTexture(GL_TEXTURE_2D, logo_tex);
		set_material('w');
		
		glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			glTexCoord2f(0, 0); glVertex3f(-0.4, -0.9, 0.2);
			glTexCoord2f(1, 0);	glVertex3f(0.4, -0.9, 0.2);
			glTexCoord2f(1, 1);	glVertex3f(0.4, 0, 0.2);
			glTexCoord2f(0, 1);	glVertex3f(-0.4, 0, 0.2);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);

	
		set_material('d');
		glBegin(GL_QUADS);
	
			//Right
			glNormal3f(1, 0, 0);
			glVertex3f(0.4, -0.9, -0.2);
			glVertex3f(0.4, 0, -0.2);
			glVertex3f(0.4, 0, 0.2);
			glVertex3f(0.4, -0.9, 0.2);

			//Back
			glNormal3f(0, 0, -1);
			glVertex3f(-0.4, -0.9, -0.2);
			glVertex3f(-0.4, 0, -0.2);
			glVertex3f(0.4, 0, -0.2);
			glVertex3f(0.4, -0.9, -0.2);

			//Left
			glNormal3f(-1, 0, 0);
			glVertex3f(-0.4, -0.9, -0.2);
			glVertex3f(-0.4, -0.9, 0.2);
			glVertex3f(-0.4, 0, 0.2);
			glVertex3f(-0.4, 0, -0.2);

			//Top
			glNormal3f(0, 1, 0);
			glVertex3f(-0.4, 0, -0.2);
			glVertex3f(-0.4, 0, 0.2);
			glVertex3f(0.4, 0, 0.2);
			glVertex3f(0.4, 0, -0.2);

			//Bottom
			glNormal3f(0, -1, 0);
			glVertex3f(-0.4, -0.9, -0.2);
			glVertex3f(-0.4, -0.9, 0.2);
			glVertex3f(0.4, -0.9, 0.2);
			glVertex3f(0.4, -0.9, -0.2);			

		glEnd(); //GL_QUADS
	

		GLUquadricObj *obj = gluNewQuadric();

		//Left leg
		glPushMatrix(); 
			glTranslatef(-0.2, -6*0.3, 0);   
			glRotatef(-90,1,0,0);
			gluCylinder(obj, 0.13, 0.13, 3*0.3, 20, 20);  
		glPopMatrix();
		
		//Right leg
		glPushMatrix(); 
			glTranslatef(0.2, -6*0.3, 0);   
			glRotatef(-90,1,0,0);
			gluCylinder(obj, 0.13, 0.13, 3*0.3, 20, 20); 
		glPopMatrix();

		//Left arm	
		glPushMatrix();
			glTranslatef(-0.2 - 0.1, 0, 0);
			glRotatef(160 + left_arm_rotation, 0, 0, 1);
			glRotatef(-90,1,0,0);
			gluCylinder(obj, 0.1, 0.1, 3*0.3, 20, 20);
		glPopMatrix();
		
		//Right arm
		glPushMatrix();
			glTranslatef( 0.4/2 + 0.1, 0, 0);
			glRotatef(-160, 0.0, 0.0, 1.0);
			glRotatef(-90,1,0,0);
			gluCylinder(obj, 0.1, 0.1, 3*0.3, 20, 20);
		glPopMatrix();
		
		//Cape
		set_material('r');
		glBegin(GL_QUADS);
			glNormal3f(0, 0, 1);
			glVertex3f(-0.6, -1.5, -0.4);
			glVertex3f( 0.6, -1.5, -0.4);
			glVertex3f( 0.4, 0.0, -0.2);
			glVertex3f(-0.4, 0.0, -0.2);
		glEnd();
			
	glPopMatrix();
	
}

void set_material(char id) {

    //Material parameters
    GLfloat ambient_coeffs[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat diffuse_coeffs[] = { 0, 0, 0, 1 }; // r g b a
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
    //Shininess parameter
    GLfloat shininess = 5;

    switch (id) {
        case 'w': //white color
            diffuse_coeffs[0] = 1;
            diffuse_coeffs[1] = 1;
            diffuse_coeffs[2] = 1;
            break;
        case 'b': //blue color
            diffuse_coeffs[0] = 0.2;
            diffuse_coeffs[1] = 0.8;
            diffuse_coeffs[2] = 0.8;
            break;
		case 'd': //dark blue color
			diffuse_coeffs[0] = 0.0;
            diffuse_coeffs[1] = 0.13;
            diffuse_coeffs[2] = 0.41;
			break;
		case 's': //skin color
			diffuse_coeffs[0] = 0.98;
            diffuse_coeffs[1] = 0.83;
            diffuse_coeffs[2] = 0.64;
			break;
		case 'r': //red color
			diffuse_coeffs[0] = 1.0;
            diffuse_coeffs[1] = 0.0;
            diffuse_coeffs[2] = 0.0;
			break;
    }

    //Material
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
