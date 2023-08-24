#include "castel.h"

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
void DrawTower(GLUquadricObj *pObj, Point3D point){
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
        glTranslatef(point.x, 1.7f, point.z);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.3f, 0.0f, 1.3f, 26, 13);
    glPopMatrix();


    glColor3f(1.0f, 1.0f, 1.0f); 
    glPushMatrix();
        glTranslatef(point.x, 1.7f, point.z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.3f, 1.3f, 0.7f, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(point.x, 1.0f, point.z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluDisk(pObj, 0.0f, 1.3f, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(point.x, 1.0f, point.z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.0f, 1.0f, 1.7f, 26, 13);
    glPopMatrix();
}

// Wall
void DrawParallelepiped(Point3D point1, Point3D point2){
    glColor3f(1.0f, 1.0f, 1.0f); 
    glBegin(GL_QUADS);
    // FRONT
	glVertex3f(point1.x, point1.y, point2.z);
	glVertex3f(point2.x, point1.y, point2.z);
	glVertex3f(point2.x, point2.y, point2.z);
	glVertex3f(point1.x, point2.y, point2.z);
	// BACK
	glVertex3f(point1.x, point1.y, point1.z);
	glVertex3f(point1.x, point2.y, point1.z);
	glVertex3f(point2.x, point2.y, point1.z);
	glVertex3f(point2.x, point1.y, point1.z);

	// LEFT
	glVertex3f(point1.x, point1.y, point2.z);
	glVertex3f(point1.x, point2.y, point2.z);
	glVertex3f(point1.x, point2.y, point1.z);
	glVertex3f(point1.x, point1.y, point1.z);
	// RIGHT
	glVertex3f(point2.x, point1.y, point1.z);
	glVertex3f(point2.x, point2.y, point1.z);
	glVertex3f(point2.x, point2.y, point2.z);
	glVertex3f(point2.x, point1.y, point2.z);

	// TOP
	glVertex3f(point1.x, point2.y, point2.z);
	glVertex3f(point2.x, point2.y, point2.z);
	glVertex3f(point2.x, point2.y, point1.z);
	glVertex3f(point1.x, point2.y, point1.z);

	// BOTTOM
	glVertex3f(point1.x, point1.y, point2.z);
	glVertex3f(point1.x, point1.y, point1.z);
	glVertex3f(point2.x, point1.y, point1.z);
	glVertex3f(point2.x, point1.y, point2.z);
    glEnd();
}

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

    Point3D pointTower1;
    pointTower1.x = -2.3f;
    pointTower1.y = 0.0f;
    pointTower1.z = 0.0f;
    DrawTower(pObj, pointTower1);
    
    Point3D pointWallA1;
    pointWallA1.x = -1.5f;
    pointWallA1.y = -0.7f;
    pointWallA1.z = -0.5f;
    
    Point3D pointWallA2;
    pointWallA2.x = 1.5f;
    pointWallA2.y = 0.3f;
    pointWallA2.z = 0.5f;

    DrawParallelepiped(pointWallA1, pointWallA2);

    Point3D pointTower2;
    pointTower2.x = 2.3f;
    pointTower2.y = 0.0f;
    pointTower2.z = 0.0f;
    DrawTower(pObj, pointTower2);

    Point3D pointWallB1;
    pointWallB1.x = 1.8f;
    pointWallB1.y = -0.7f;
    pointWallB1.z = 0.8f;
    
    Point3D pointWallB2;
    pointWallB2.x = 3.0f;
    pointWallB2.y = 0.3f;
    pointWallB2.z = 3.8f;
    DrawParallelepiped(pointWallB1, pointWallB2);

    Point3D pointTower3;
    pointTower3.x = 2.3f;
    pointTower3.y = 0.0f;
    pointTower3.z = 4.0f;
    DrawTower(pObj, pointTower3);

    Point3D pointWallC1;
    pointWallC1.x = -1.5f;
    pointWallC1.y = -0.7f;
    pointWallC1.z = 3.3f;
    
    Point3D pointWallC2;
    pointWallC2.x = 1.5f;
    pointWallC2.y = 0.3f;
    pointWallC2.z = 4.3f;

    DrawParallelepiped(pointWallC1, pointWallC2);
        
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