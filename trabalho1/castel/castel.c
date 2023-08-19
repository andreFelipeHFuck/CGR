#include <GL/glut.h>

static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;

void ChangeSize(int w, int h)  
    {  
    GLfloat fAspect;  
  
    if(h == 0)  
        h = 1;  
  
    glViewport(0, 0, w, h);  
  
    fAspect = (GLfloat)w/(GLfloat)h;  
  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
}  
  
void SetupRC(){  

    // Light values and coordinates  
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal  
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out  
    glEnable(GL_CULL_FACE);     // Do not calculate inside  
  
    glEnable(GL_LIGHTING);  
  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  
  
    glEnable(GL_COLOR_MATERIAL);  
      
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
  
    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);  

}  
  
void SpecialKeys(int key, int x, int y){  

    if(key == GLUT_KEY_LEFT)  
        yRot -= 5.0f;  
  
    if(key == GLUT_KEY_RIGHT)  
        yRot += 5.0f;  
    
    if(key == GLUT_KEY_UP)
        zRot += 5.0f;
    
    if(key == GLUT_KEY_DOWN)
        zRot -= 5.0f;
                  
    yRot = (GLfloat)((const int)yRot % 360);  
    zRot = (GLfloat)((const int)zRot % 360);
  
    glutPostRedisplay();  
}

// Tower
void RenderTower(GLUquadricObj *pObj, GLfloat x, GLfloat z){
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
        glTranslatef(x, 1.7, z);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.3f, 0.0f, 1.3f, 26, 13);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f); 
    glPushMatrix();
        glTranslatef(x, 1.7f, z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.3f, 1.3f, 0.7f, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(x, 1.0f, z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluDisk(pObj, 0.0f, 1.3f, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(x, 1.0f, z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.0f, 1.0f, 1.7f, 26, 13);
    glPopMatrix();
}

// Wall


// Scene
void RenderScene(void){
    GLUquadricObj *pObj;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

    glPushMatrix();

    glTranslatef(0.0f, -1.0f, -5.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 1.0f, 0.0f, 0.0f);


    pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);  

    RenderTower(pObj, 0.0f, 0.0f);

    glColor3f(1,0, 0);
    glBegin(GL_QUADS);
        glVertex3f(0.5, 0.5, 0.5);    
        glVertex3f(0.5, -0.7, 0.5);    
        glVertex3f(3.5, -0.7, 0.5);  
        glVertex3f(3.5, 0.5, 0.5); 
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(0.5, 0.5, -0.5);    
        glVertex3f(0.5, -0.7, -0.5);    
        glVertex3f(3.5, -0.7, -0.5);  
        glVertex3f(3.5, 0.5, -0.5); 
    glEnd();

    // Roof
    glBegin(GL_QUADS);
        glVertex3f(0.5, 0.5, 0.5);    
        glVertex3f(0.5, 0.5, -0.7);    
        glVertex3f(3.5, 0.5, -0.7);  
        glVertex3f(3.5, 0.5, 0.5); 
    glEnd();

    RenderTower(pObj, 3.5f, 0.0f);

    glPopMatrix();
    // Estudar
    glutSwapBuffers();
}

int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Castel");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();  
      
    return 0; 
}