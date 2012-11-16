#include <stdio.h>   
#include <string.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>

#include "bmp.h" 


using namespace std;

const int scale=100;

double angle = 0;

typedef struct point {
    float x;
    float y;
} point;

typedef struct object {
    char type; // 1 is circle, 2 is triangle and 3 is square
    point center;
    float radius;
    point * corners;
} object;

vector<object> objects;

vector<object> getObjectsFromFile(char * filename);

void drawFloor() {
    unsigned char *grass=read_bmp("input.bmp");
         
 
    glEnable(GL_TEXTURE_2D);
     
    glBindTexture(GL_TEXTURE_2D, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, 1, 100,100, 0, GL_RED, GL_UNSIGNED_BYTE,grass);
       
    glBindTexture(GL_TEXTURE_2D,1);

    glBegin(GL_QUADS);
		
		glColor3f(1.0, 1.0, 1.0);

		glTexCoord2d(0,0);
		glVertex3f(0, 0,0);

		glTexCoord2d(0,1);
		glVertex3f(0, 1,0);

		glTexCoord2d(1,1);
		glVertex3f(1, 1,0);

		glTexCoord2d(1,0);
		glVertex3f(1,0,0);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawTriangle(object o) {
    double x1 = o.corners[0].x;
    double y1 = o.corners[0].y;
    double x2 = o.corners[1].x;
    double y2 = o.corners[1].y;
    double x3 = o.corners[2].x;
    double y3 = o.corners[2].y;

    double x4 = o.center.x;
    double y4 = o.center.y;

    glColor3f(1, 0, 0);

    glBegin(GL_POLYGON);
        glVertex3f(x1, y1, 0);
        glVertex3f(x2, y2, 0);
        glVertex3f(x4, y4, -0.2);
    glEnd();

    glColor3f(0, 1, 0);

    glBegin(GL_POLYGON);
        glVertex3f(x2, y2, 0);
        glVertex3f(x3, y3, 0);
        glVertex3f(x4, y4, -0.2);
    glEnd();

    glColor3f(0, 0, 1);

    glBegin(GL_POLYGON);
        glVertex3f(x3, y3, 0);
        glVertex3f(x1, y1, 0);
        glVertex3f(x4, y4, -0.2);
    glEnd();
}

void drawCircle(object o) {
    glPushMatrix();
    glColor3f(0.5, 0.7, 0.5);
    glTranslatef(o.center.x, o.center.y, -o.radius);
    glutWireSphere(o.radius, 50, 24);
    glPopMatrix();
}

void drawSquare(object o) {
    double x1 = o.corners[0].x;
    double y1 = o.corners[0].y;
    double x2 = o.corners[1].x;
    double y2 = o.corners[1].y;
    double x3 = o.corners[2].x;
    double y3 = o.corners[2].y;
    double x4 = o.corners[3].x;
    double y4 = o.corners[3].y;

    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
        glVertex3f(x1, y1, 0);
        glVertex3f(x2, y2, 0);
        glVertex3f(x2, y2, -0.2);
        glVertex3f(x1, y1, -0.2);
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
        glVertex3f(x2, y2, 0);
        glVertex3f(x3, y3, 0);
        glVertex3f(x3, y3, -0.2);
        glVertex3f(x2, y2, -0.2);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
        glVertex3f(x3, y3, 0);
        glVertex3f(x4, y4, 0);
        glVertex3f(x4, y4, -0.2);
        glVertex3f(x3, y3, -0.2);
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
        glVertex3f(x4, y4, 0);
        glVertex3f(x1, y1, 0);
        glVertex3f(x1, y1, -0.2);
        glVertex3f(x4, y4, -0.2);
    glEnd();

    glColor3f(1, 1, 0);
    glBegin(GL_POLYGON);
        glVertex3f(x1, y1, -0.2);
        glVertex3f(x2, y2, -0.2);
        glVertex3f(x3, y3, -0.2);
        glVertex3f(x4, y4, -0.2);
    glEnd();
}

void Render() {    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();

    glRotatef(70, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
	
    glScalef(scale,scale,scale);
    glTranslatef(-0.5,-0.5,0.0);
    drawFloor();
    glTranslatef(0,1,0.0);
    glRotatef(-90,0,0,1);

    glColor3f(0.1, 0.6, 0.1);
    //glutSolidSphere(0.1,100,24);
    //glutSolidCube(0.1);

    for (int i = 0; i<objects.size(); i++) {
        object o = objects[i];
        switch (o.type) {
        case 1:
            drawCircle(o);
            break;
        case 2:
            drawTriangle(o);
            break;
        case 3:
            drawSquare(o);
            break;
        }
    }




  
    //TODO: Write your code here to draw 3D objects over 2D bitmap image

    glutSwapBuffers(); 
}

//-----------------------------------------------------------


void Resize(int w, int h) { 
    int width = min(w, h);
    if (width==0) 
        width=1;
    glViewport(0,0,width,width); 


    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();

    glOrtho (-100.0, 100.0, -100.0, 100.0, 100.0,-100.0);
	

}

void Idle() {
	 glutPostRedisplay();
     angle += 0.5;
     if (angle >= 360) {
        angle = angle-360;
     }
}


void Setup() { 
    objects = getObjectsFromFile("objects.txt");// this function reads the cordinats of objects from the file that you provided in MATLAB...

    glShadeModel (GL_SMOOTH);
	
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);  
    glClearDepth(1);

    glClearColor(0.0f,0.0f,0.0f,1.0f);

}

vector<object> getObjectsFromFile(char * filename) {
	FILE * file = fopen(filename,"r");
    if(file==NULL) 
	{
       cout << "Unable to open file " << filename << endl;
        exit(-1);
    }

    vector<object> objects;
	char linec [128];
	string line;
      while ( fgets ( linec, sizeof linec, file ) != NULL ) /* read a line */
      {
		line=string(linec);
        // Split string on spaces
        vector<string> values;
        int pos = line.find(" ");
        while(pos > 0) {
            string value = line.substr(0,pos);
            values.push_back(value);
            line = line.substr(pos+1);
            pos = line.find(" ");
        }
        values.push_back(line);

        object o;
        o.center.x = atof(values[0].c_str());
        o.center.y = atof(values[1].c_str());
        if(values.size() == 3) {
            o.type = 1; // Circle
            o.radius = atof(values[2].c_str());
        } else if(values.size() == 8) {
            o.type = 2; // Triangle
            o.corners = new point[3];
            for(int i = 0; i < 3; i ++) {
                o.corners[i].x = atof(values[i*2+2].c_str());
                o.corners[i].y = atof(values[i*2+3].c_str());
            }
        } else if(values.size() == 10) {
            o.type = 3; // Square
            o.corners = new point[4];
            for(int i = 0; i < 4; i ++) {
                o.corners[i].x = atof(values[i*2+2].c_str());
                o.corners[i].y = atof(values[i*2+3].c_str());
            }
        } else {
            cout << "Error: wrong number of attributes in file" << endl;
        }
        objects.push_back(o);
    }
      fclose ( file );

    return objects;
}