#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4


//-------- Functions --------------------------------

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();
// Idle function

void Keyboard(unsigned char key, int x, int y);

void MenuSelect(int choice);