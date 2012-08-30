#include <stdio.h>     // - Just for some ASCII messages
#include <algorithm>
#include <GL/glut.h>   // - An interface and windows 
                       //   management library
#include <time.h>
#include "visuals.h"   // Header file for our OpenGL functions

using namespace std;

void Render() {
  srand(time(NULL));
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
													   // and the depth buffer
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
  glTranslatef(-50, -50, 0);
  //Tegne små tekanne
  for (int i=0; i<20; i++) {
    //Starter fra midten
    glLoadIdentity();
    //Flytter til et tilfeldig sted, pluss minus 40 i hver retning. Litt på Z-aksen også får å ikke få så stygge brudd
    glTranslatef(rand() % 80-40, rand() % 80-40, rand()%40-10);
    //Ca halvparten av tekannene er motsatt vei
    if (rand() % 2 == 0) {
      glRotatef(180, 0, 1, 0);
    }
    //Legger på litt rotering for å få litt mer kaos
    glRotatef(rand()%40-20, 1, 0, 1);
    //Tilfeldig farge
    glColor3f(rand() % 100/100.0, rand() % 100/100.0, rand() % 100/100.0);							   // Set drawing colour = orange
    //Og tegner en tekopp. Alle er like store
    glutSolidTeapot( 5.0 );
  }
  //Tegne stor tekanne med kuler
  glLoadIdentity();
  //Grønt er fint
  glColor3f(0.1, 0.6, 0.1);
  //Flytter litt opp  på grunn av rotering
  glTranslatef(0,6,0);
  //Roterer 30 grader til høyre for å se ut som det heller
  glRotatef(-30, 0, 0, 1);
  glutWireTeapot(20.0);

  glLoadIdentity();
  //Fin blåfarge
  glColor3f(0.3, 0.3, 1.0);
  //Tegner 4 bobler litt under hverandre under tuten til tekannen
  glTranslatef(38, -6, 0);
  glutSolidSphere( 1.5, 100, 24);
  glTranslatef(3, -5, 0);
  glutSolidSphere( 1.5, 100, 24);
  glTranslatef(2, -6, 0);
  glutSolidSphere( 1.5, 100, 24);
  glTranslatef(1, -6, 0);
  glutSolidSphere( 1.5, 100, 24);
  //glutSolidSphere(100.0,100,24);

  glutSwapBuffers();             // All drawing commands applied to the 
                                 // hidden buffer, so now, bring forward
                                 // the hidden buffer and hide the visible one
}

//-----------------------------------------------------------

void Resize(int w, int h) { 
  // w and h are window sizes returned by glut
  // define the visible area of the window ( in pixels )
  
  
  int width = min(w, h);
  if (width==0) 
    width=1; 
  glViewport(0,0,width,width);
  //glViewport(100,100,400,400);

  // Setup viewing volume
  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
 
 
  //         L,      R,      B,     T,     N,      F
  glOrtho (-50.0f, 50.0f, -50.0f, 50.0f, 100.0f, -100.0f);


}


void Setup() { // DON'T TOUCH IT  
	//Parameter handling
	glShadeModel (GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	GLfloat light_position[] = { 0.0, 30.0,-50.0,0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

