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


// Parallelepiped
void DrawParallelepiped(Point3D point1, Point3D point2){
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

// Floor
void DrawFloor(GLfloat height, GLfloat widht1, GLfloat widht2, Color color){
    glColor3f(color.r, color.g, color.b); 

    Point3D floor1;
    floor1.x = height;
    floor1.y = widht1;
    floor1.z = height;
    
    Point3D floor2;
    floor2.x = -height;
    floor2.y = widht2;
    floor2.z = -height;

    DrawParallelepiped(floor1, floor2);
}

// Tower
void DrawTower(GLUquadricObj *pObj, Point3D point){
    glColor3f(1.0f, 1.0f, 1.0f); 
    glPushMatrix();
        glTranslatef(point.x, 1.0f, point.z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.0f, 1.0f, 1.7f, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(point.x, 1.0f, point.z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluDisk(pObj, 0.0f, 1.3f, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(point.x, 1.7f, point.z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.3f, 1.3f, 0.7f, 26, 13);
    glPopMatrix();

    glColor3f(1.0f, 0.0f, 0.0f); 
     glPushMatrix();
        glTranslatef(point.x, 1.7f, point.z);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 1.3f, 0.0f, 1.3f, 26, 13);
    glPopMatrix();
}

// Tree
void DrawTree(GLUquadricObj *pObj, Point3D point){
    GLfloat height1 = point.y / 4.0;
    GLfloat height2 = (point.y - height1) / 2.0;

    // Stem
    glColor3f(0.38, 0.231, 0.086);
    glPushMatrix();
        glTranslatef(point.x, 0.75, point.z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.1f, 0.1f, height1, 26, 13);
    glPopMatrix();

    // Sheets
    glColor3f(0.047f, 0.682f, 0.357f);
    glPushMatrix();
        glTranslatef(point.x, (0.75 + height1), point.z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.0f, 0.5f, height2, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(point.x, (0.75 + 2 * height1), point.z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, 0.0f, 0.4f, height2, 26, 13);
    glPopMatrix();
}

// Wall



// Scene
void RenderScene(void){
    GLUquadricObj *pObj;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

    glPushMatrix();

    glTranslatef(0.0f, -1.0f, -18.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 1.0f, 0.0f, 0.0f);


    pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);  

    // glColor3f(1.0f, 1.0f, 1.0f); 

    // Point3D pointTower1;
    // pointTower1.x = -2.3f;
    // pointTower1.y = 0.0f;
    // pointTower1.z = 0.0f;
    // DrawTower(pObj, pointTower1);
    
    // // Wall A
    // Point3D pointWallA1;
    // pointWallA1.x = -1.5f;
    // pointWallA1.y = -0.7f;
    // pointWallA1.z = -0.5f;
    
    // Point3D pointWallA2;
    // pointWallA2.x = 1.5f;
    // pointWallA2.y = 0.1f;
    // pointWallA2.z = 0.5f;

    // DrawParallelepiped(pointWallA1, pointWallA2);

    // Point3D pointTower2;
    // pointTower2.x = 2.3f;
    // pointTower2.y = 0.0f;
    // pointTower2.z = 0.0f;
    // DrawTower(pObj, pointTower2);

    // // Wall B
    // Point3D pointWallB1;
    // pointWallB1.x = 1.8f;
    // pointWallB1.y = -0.7f;
    // pointWallB1.z = 0.8f;
    
    // Point3D pointWallB2;
    // pointWallB2.x = 3.0f;
    // pointWallB2.y = 0.1f;
    // pointWallB2.z = 3.8f;
    // DrawParallelepiped(pointWallB1, pointWallB2);

    // Point3D pointTower3;
    // pointTower3.x = 2.3f;
    // pointTower3.y = 0.0f;
    // pointTower3.z = 4.0f;
    // DrawTower(pObj, pointTower3);

    // // Wall C
    // Point3D pointWallC1;
    // pointWallC1.x = -1.5f;
    // pointWallC1.y = -0.7f;
    // pointWallC1.z = 3.5f;
    
    // Point3D pointWallC2;
    // pointWallC2.x = 1.5f;
    // pointWallC2.y = 0.1f;
    // pointWallC2.z = 4.5f;

    // DrawParallelepiped(pointWallC1, pointWallC2);
        
    // // Draw Parallelepiped Tower
    // Point3D pointTower4A;
    // pointTower4A.x = -1.45f;
    // pointTower4A.y = -0.7f;
    // pointTower4A.z = 3.0f;

    // Point3D pointTower4B;
    // pointTower4B.x = -3.15f;
    // pointTower4B.y = 2.3f;
    // pointTower4B.z = 5.0f;

    // DrawParallelepiped(pointTower4A, pointTower4B);

    // // Wall D
    // Point3D pointWallD1;
    // pointWallD1.x = -1.8f;
    // pointWallD1.y = -0.7f;
    // pointWallD1.z = 0.8f;
    
    // Point3D pointWallD2;
    // pointWallD2.x = -3.0f;
    // pointWallD2.y = 0.1f;
    // pointWallD2.z = 3.8f;
    // DrawParallelepiped(pointWallD1, pointWallD2);

    // Floor
    Color colorFloor;
    colorFloor.r = 0.204f;
    colorFloor.g = 0.549f;
    colorFloor.b = 0.192f;

    DrawFloor(6.0f, 0.0f, 0.25f, colorFloor);

    // Tree
    Point3D pointTree;
    pointTree.x = 0.0f;
    pointTree.y = 2.0f;
    pointTree.z = 0.0f;
    DrawTree(pObj, pointTree);


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