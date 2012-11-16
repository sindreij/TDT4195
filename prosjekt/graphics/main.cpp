
#include <stdio.h>    
#include <GL/glut.h>

void Render();
void Resize(int w, int h);
void Setup();
void Idle();


int main(int argc, char* argv[])
{ 

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
 
  
  glutInitWindowSize(500,500);
  glutInitWindowPosition(100,100);
  

  glutCreateWindow("Common Project");
  
  Setup();
  
  glutDisplayFunc(Render);
  glutReshapeFunc(Resize);
  glutIdleFunc(Idle);


  glutMainLoop();
  return 0;	
}  
