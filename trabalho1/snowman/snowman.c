#include <GL/glut.h>

static GLfloat yRot = 0.0f;

// ESTUDAR
void ChangeSize(int w, int h){
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

// ESTUDAR
void SetupRC(){
    GLfloat whiteLight[] = {0.05f, 0.05f, 0.05f, 1.0f};
    GLfloat sourceLight[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat lightPos[] = {-10.f, 5.0f, 5.0f, 1.0f};

    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);

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

// ESTUDAR
void SpecialKeys(int key, int x, int y){  

    if(key == GLUT_KEY_LEFT)  
        yRot -= 5.0f;  
  
    if(key == GLUT_KEY_RIGHT)  
        yRot += 5.0f;  
                  
    yRot = (GLfloat)((const int)yRot % 360);  
  
    glutPostRedisplay();  
}

void RenderScene(void){
    GLUquadricObj *pObj;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glPushMatrix();

    // ESTUDAR
    glTranslatef(0.0f, -1.0f, -5.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  

    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);

    // Hat
    glColor3f(0.61f, 0.11f, 0.05f);
    glPushMatrix();
        glTranslatef(0.0f, 1.7f, 0.0f);
        glRotated(90, 1, 0, 0);
        gluCylinder(pObj, 0.20f, 0.18f, 0.35f, 26, 13);
    glPopMatrix();
        
    glPushMatrix();
       glTranslatef(0.0f, 1.35f, 0.0f);
       glRotated(90, 1, 0, 0);
       gluCylinder(pObj, 0.36f, 0.36f, 0.03f, 26, 13);
    glPopMatrix();

    // Nose
    glColor3f(1.0f, 0.4f, 0.51f);
    glPushMatrix();
        glTranslatef(0.0f, 1.145f, 0.2f);
        gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);
    glPopMatrix();

    // Arm
    // Arm right
    glPushMatrix();
       glTranslatef(0.2f, 0.75f, 0.0f);
       glRotated(90, 0, 1, 0);
       glRotated(-30, 1, 0, 0);
       gluCylinder(pObj, 0.04f, 0.0f, 0.8f, 26, 13);
    glPopMatrix();

    glPushMatrix();
       glTranslatef(-0.2f, 0.75f, 0.0f);
       glRotated(-90, 0, 1, 0);
       glRotated(-30, 1, 0, 0);
       gluCylinder(pObj, 0.04f, 0.0f, 0.8f, 26, 13);
    glPopMatrix();

    // Eyes
    glColor3f(0.0f, 0.0f, 0.0f);
    // Eye left
    glPushMatrix();
        glTranslatef(-0.10f, 1.23f, 0.26f);
        gluDisk(pObj, 0.0f, 0.04f, 26, 13);
    glPopMatrix();

    // Eye right
    glPushMatrix();
        glTranslatef(0.10f, 1.23f, 0.26f);
        gluDisk(pObj, 0.0f, 0.04f, 26, 13);
    glPopMatrix();

    // Smile
    glPushMatrix();
        glTranslatef(0.0f, 1.03f, 0.29f);
        gluDisk(pObj, 0.0f, 0.02f, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.05f, 1.05f, 0.29f);
        gluDisk(pObj, 0.0f, 0.02f, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.05f, 1.05f, 0.29f);
        gluDisk(pObj, 0.0f, 0.02f, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.09f, 1.08f, 0.29f);
        gluDisk(pObj, 0.0f, 0.02f, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.09f, 1.08f, 0.29f);
        gluDisk(pObj, 0.0f, 0.02f, 26, 13);
    glPopMatrix();

    // Button
    glPushMatrix();
        glTranslatef(0.0f, 0.7f, 0.35f);
        gluDisk(pObj, 0.0f, 0.04f, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.85f, 0.30f);
        gluDisk(pObj, 0.0f, 0.04f, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.55f, 0.35f);
        gluDisk(pObj, 0.0f, 0.04f, 26, 13);
    glPopMatrix();



    glColor3f(1.0f, 1.0f, 1.0f);
    // Head
    glPushMatrix();
        glTranslatef(0.0f, 1.145f, 0.0f);
        gluSphere(pObj, 0.27f, 26, 13);
    glPopMatrix();

    // Body
    glPushMatrix();
        glTranslatef(0.0f, 0.62f, 0.0f);
        gluSphere(pObj, 0.35f, 26, 13);
    glPopMatrix();

    // Foot 
     glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        gluSphere(pObj, 0.45f, 26, 13);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Snowman");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    SetupRC();  
    glutMainLoop();  
      
    return 0; 
}