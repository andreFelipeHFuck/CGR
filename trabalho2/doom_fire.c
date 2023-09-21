// Trabalho 2: Fire

#include "doom_fire.h"

int window; 

// Criar particulas
void CreateParticle(int pos){
    float max = 1.0;
    float veloc_al = 0.1;

    particles[pos].x = ((float)rand()/(float)(RAND_MAX)) * max;
    particles[pos].y = -3;  

    particles[pos].veloc_x = 0.1;
    particles[pos].veloc_y = ((float)rand()/(float)(RAND_MAX)) * veloc_al;

    particles[pos].lifetime = rand() % 100;
}

// Initialize the firework
void InitParticle(int pause)
{
  int i;

  if(pause) usleep(200000 + rand() % 2000000);

  for(i=0;i<NUM_PARTICLES;i++) {
    CreateParticle(i); 
  }
}

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);

  InitParticle(0); // first firework
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene()
{
  int i, ative_particles=0;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
  glLoadIdentity();				// Reset The View

  glTranslatef(0.0f,0.0f,-6.0f);		// Move particles 6.0 units into the screen
	
  glBegin(GL_POINTS);
  for(i=0;i<NUM_PARTICLES;i++) {
    if(particles[i].lifetime) {
      ative_particles++;
      particles[i].veloc_y -= GRAVITY;

      particles[i].x += pow(-1, rand() % 5) * particles[i].veloc_x;
      particles[i].y += particles[i].veloc_y;

      particles[i].lifetime--;

      glVertex3f(particles[i].x, particles[i].y, 0.0f);
    }else{
      CreateParticle(i);
    }
  }
  glEnd();

  // swap buffers to display, since we're double buffered.
  glutSwapBuffers();
  usleep(20000);

  if(!ative_particles) InitParticle(1); // reset particles
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{

  if (key == ESCAPE) 
  { 
	glutDestroyWindow(window); 
	
	exit(0);                   
  }
}

int main(int argc, char **argv) 
{  
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  glutInitWindowSize(640, 480);  
  glutInitWindowPosition(0, 0);  
  window = glutCreateWindow("Fogos de artificio");  
  glutDisplayFunc(&DrawGLScene);  
  glutFullScreen();
  glutIdleFunc(&DrawGLScene);
  glutReshapeFunc(&ReSizeGLScene);
  glutKeyboardFunc(&keyPressed);
  InitGL(640, 480);
  glutMainLoop();  

  return 0;
}
