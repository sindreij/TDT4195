#include <stdio.h>     // - Just for some ASCII messages
#include <iostream>
#include <algorithm>
#include <math.h>
#include <GL/glut.h>   // - An interface and windows
                       //   management library
#include "visuals.h"   // Header file for our OpenGL functions

using namespace std;

float angle = 0;
float curr_x = 0;
float curr_y = 0;
float scale = 1;

const float PI = 3.141592;

//En liten enkel state-maskin i Idle
int state = 0;

const int STATE_ROTATE = 0;
const int STATE_MOVE = 1;
const int STATE_SCALE = 2;
const int STATE_FINISHED = 3;

void DrawAxes()
{
  glColor3f(0.6, 0.6, 0.6);
  glBegin(GL_LINES);
    glVertex2f(0.0,0.0);
	glVertex2f(100.0,0.0);
	glVertex2f(0.0,0.0);
	glVertex2f(0.0,100.0);
  glEnd();
}

void drawCircle(float cx, float cy, float r, 
        float start_angle, float end_angle) {
    float angle_res = 0.1;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        //Plotter ut alle punktene langs kanten av 
        //sirkelen
        for (float angle = start_angle; angle<=end_angle; angle+= angle_res) {
            float x = cosf(angle) * r + cx;
            float y = sinf(angle) * r + cy;
            glVertex2f(x, y);
        }
        //Avsluttende punkt for å få en komplett sirkel
        float x = cosf(end_angle) * r + cx;
        float y = sinf(end_angle) * r + cy;
        glVertex2f(x, y);
    glEnd();
}

void drawRoundedRect(float x1, float y1, float x2, float y2, float border) {
    float left = min(x1, x2);
    float right = max(x1, x2);
    float top = max(y1, y2);
    float bottom = min(y1, y2);

    //En rounded rect kan deles opp til å bestå av 9 deler. En
    //hoved-boks, 4 hjørner og 4 kanter. Her tegner jeg dette

    //Main box
    glRectf(left+border, bottom+border, right-border, top-border);
    //Corner upper left
    drawCircle(left+border,  top-border,    border, PI/2, PI);
    //Corner down left
    drawCircle(left+border,  bottom+border, border, PI, 3*PI/2);
    //Corner up right
    drawCircle(right-border, top-border,    border, 0, PI/2);
    //corner down right
    drawCircle(right-border, bottom+border, border, 3*PI/2, PI*2);
    //Line left
    glRectf(left, top-border, left+border, bottom+border);
    //Line bottom
    glRectf(left+border, bottom, right-border, bottom+border);
    //Line right
    glRectf(right-border, top-border, right, bottom+border);
    //Line top
    glRectf(left+border, top, right-border, top-border);
}

void Render()
{    
  
  glClear(GL_COLOR_BUFFER_BIT );  // Clean up the colour of the window
								  // and the depth buffer

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /* Setter opp transformations */
  glTranslatef(curr_x, curr_y, 0);
  glScalef(scale, scale, 0);
  glRotatef(angle, 0.0, 0.0, 1.0);

  glColor3f(0.15f, 0.15f, 1.0f);
  drawRoundedRect(-20, -20, 20, 20, 10);
  glColor3f(1.0f, 1.0f, 1.0f);
  glRectf(-11, -11, 11, 11);
  glColor3f(0.15f, 0.15f, 1.0f);
  drawCircle(0,0, 9, 0, 2*PI);


  glutSwapBuffers();             // All drawing commands applied to the 
                                 // hidden buffer, so now, bring forward
                                 // the hidden buffer and hide the visible one           

}

//-----------------------------------------------------------


void Resize(int w, int h)
{ 
  // define the visible area of the window ( in pixels )
  int width = min(w, h);
  if (width==0) 
    width=1; 
  glViewport(0,0,width,width);
  //glViewport(100,100,400,400);

  // Setup viewing volume
  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
 
  //         L	   R 	  B 	T	 N	   F
  glOrtho (-100.0, 100.0, -100.0, 100.0, 100.0,-100.0);
	
}

void Idle()
{
    switch (state) {
        case STATE_ROTATE:
            angle += 3;
            if (angle > 360) {
                angle = 0;
                state = STATE_MOVE;
            }
            break;
        case STATE_MOVE:
            curr_x -= 0.5;
            curr_y += 0.5;
            if (curr_x <= -50) {
                state = STATE_SCALE;
            }
            break;
        case STATE_SCALE:
            scale += 0.01;
            if (scale >= 2) {
                state = STATE_FINISHED;
            }
            break;
    }
    
    
	glutPostRedisplay();

}

//-----------------------------------------------------------

void Setup()  // DON'T TOUCH IT 
{ 
	//Parameter handling
	//glShadeModel (GL_SMOOTH);
	glShadeModel (GL_FLAT);

 
	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	GLfloat light_position[] = { -50.0, 20.0, 150.0, 1.0 };
	GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	   
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_POINT_SMOOTH);

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}





