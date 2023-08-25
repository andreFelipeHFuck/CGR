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

// Pyramid
void DrawPyramid(Point3D point1, Point3D point2, GLfloat height){
    GLfloat averageX = (point1.x + point2.x) / 2.0;
    GLfloat averageZ = (point1.z + point2.z) / 2.0;

    glBegin(GL_TRIANGLES);          
      // Front
      glColor3f(1.0f, 0.0f, 0.0f);     // Red

      glVertex3f( averageX, height, averageZ);
      glVertex3f(point1.x, point1.y, point2.z);
      glVertex3f(point2.x, point1.y, point2.z);
 
      // Right
      glVertex3f(averageX, height, averageZ);
      glVertex3f(point2.x, point1.y, point2.z);
      glVertex3f(point2.x, point1.y, point1.z);
 
      // Back
      glVertex3f(averageX, height, averageZ);
      glVertex3f(point2.x, point1.y, point1.z);
      glVertex3f(point1.x, point1.y, point1.z);
 
      // Left
      glVertex3f(averageX, height, averageZ);
      glVertex3f(point1.x, point1.y, point1.z);
      glVertex3f(point1.x, point1.y, point2.z);
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
void DrawTower(GLUquadricObj *pObj, Point3D point, GLfloat radius1, GLfloat radius2){
    GLfloat height1 = point.y / 2.0;
    GLfloat height2 = (point.y - height1) / 2.0;

    glColor3f(1.0f, 1.0f, 1.0f); 
    glPushMatrix();
        glTranslatef(point.x, 2.0f, point.z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, radius1, radius1, height1, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(point.x, (height1), point.z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluDisk(pObj, 0.0f, radius2, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(point.x, (1.0f + height1), point.z);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, radius2, radius2, height2, 26, 13);
    glPopMatrix();

    glColor3f(1.0f, 0.0f, 0.0f); 
     glPushMatrix();
        glTranslatef(point.x, (1.0f + height1), point.z);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        gluCylinder(pObj, radius2, 0.0f, height2, 26, 13);
    glPopMatrix();
}

// Parallelepid Tower
void DrawParaTower(Point3D point1, Point3D point2){
    GLfloat height = point2.y / 4.0;
    Point3D pointPyramid1;
    Point3D pointPyramid2;

    

    pointPyramid1.x = point1.x;
    pointPyramid1.y = point2.y - height;
    pointPyramid1.z = point1.z;

    pointPyramid2.x = point2.x;
    pointPyramid2.y = point2.y - height;
    pointPyramid2.z = point2.z;

    glColor3f(1.0f, 1.0f, 1.0f);
    DrawParallelepiped(point1, pointPyramid2);

    glColor3f(1.0f, 0.0f, 0.0f);
    DrawPyramid(pointPyramid1, pointPyramid2, point2.y);
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

void DrawWallX(Point3D point1, Point3D point2){
    GLfloat height = point2.y - (point2.y / 4.0);
    GLfloat widht = point2.x / 15.0;
    GLfloat depth = point2.z / 15.0;
 
    Point3D auxPoint1;
    Point3D auxPoint2;

    GLfloat auxX = point1.x;
    GLfloat auxZ = point1.z;

    glColor3f(1.0f, 1.0f, 1.0f);
    for(int i=0; i<10; i++){
        auxPoint1.x = auxX;
        auxPoint1.y = height;
        auxPoint1.z = auxZ;

        auxPoint2.x = auxX + widht;
        auxPoint2.y = point2.y;
        auxPoint2.z = auxZ + depth;

        DrawParallelepiped(auxPoint1, auxPoint2);

        auxX += 3 * widht;
    }

    auxX = point1.x;
    auxZ = point2.z - depth;

    for(int i=0; i<10; i++){
        auxPoint1.x = auxX;
        auxPoint1.y = height;
        auxPoint1.z = auxZ;

        auxPoint2.x = auxX + widht;
        auxPoint2.y = point2.y;
        auxPoint2.z = point2.z;

        DrawParallelepiped(auxPoint1, auxPoint2);

        auxX += 3 * widht;
    }
}

void DrawWallZ(Point3D point1, Point3D point2){
     GLfloat height = point2.y - (point2.y / 4.0);
    GLfloat widht = point2.x / 15.0;
    GLfloat depth = point2.z / 15.0;
 
    Point3D auxPoint1;
    Point3D auxPoint2;

    GLfloat auxX = point1.x;
    GLfloat auxZ = point1.z;

    glColor3f(1.0f, 1.0f, 1.0f);
    for(int i=0; i<10; i++){
        auxPoint1.x = auxX;
        auxPoint1.y = height;
        auxPoint1.z = auxZ;

        auxPoint2.x = auxX + widht;
        auxPoint2.y = point2.y;
        auxPoint2.z = auxZ + depth;

        DrawParallelepiped(auxPoint1, auxPoint2);

        auxZ += 3 * depth;
    }

    auxX = point1.x + 3 * widht;
    auxZ = point1.z;

    for(int i=0; i<10; i++){
        auxPoint1.x = auxX;
        auxPoint1.y = height;
        auxPoint1.z = auxZ;

        auxPoint2.x = auxX + widht;
        auxPoint2.y = point2.y;
        auxPoint2.z = auxZ + depth;

        DrawParallelepiped(auxPoint1, auxPoint2);

        auxZ += 3 * depth;
    }
}

// Wall
void DrawWall(Point3D point1, Point3D point2, int opcao){
    if(opcao == 0)
        DrawWallX(point1, point2);
    else if(opcao == 1)   
        DrawWallZ(point1, point2);

    glColor3f(1.0f, 1.0f, 1.0f);
    point2.y = point2.y - (point2.y / 4.0);

    DrawParallelepiped(point1, point2);
}

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

    // Floor
    Color colorFloor;
    colorFloor.r = 0.204f;
    colorFloor.g = 0.549f;
    colorFloor.b = 0.192f;

    DrawFloor(10.0f, 0.0f, 0.25f, colorFloor);

    // Castel
    Point3D pointTower1;
    pointTower1.x = 3.0f;
    pointTower1.y = 4.0f;
    pointTower1.z = 3.0f;
    DrawTower(pObj, pointTower1, 0.7f, 1.0f);

    // Wall 1
    Point3D pointWall1A;
    pointWall1A.x = 2.6f;
    pointWall1A.y = 0.27f;
    pointWall1A.z = 2.5f;
    
    Point3D pointWall1B;
    pointWall1B.x = -2.6f;
    pointWall1B.y = 1.5f;
    pointWall1B.z = 3.5f;
    DrawWall(pointWall1A, pointWall1B, 0);

    Point3D pointTower2;
    pointTower2.x = -3.0f;
    pointTower2.y = 4.0f;
    pointTower2.z = 3.0f;
    DrawTower(pObj, pointTower2, 0.7f, 1.0f);

    // Tower 3
    Point3D pointTower3A;
    pointTower3A.x = -3.5f;
    pointTower3A.y = 0.27f;
    pointTower3A.z = -3.5f;

    Point3D pointTower3B;
    pointTower3B.x = -2.5f;
    pointTower3B.y = 4.0f;
    pointTower3B.z = -2.5f;
    DrawParaTower(pointTower3A, pointTower3B);

    // Wall 2
    Point3D pointWall2A;
    pointWall2A.x = 2.6f;
    pointWall2A.y = 0.27f;
    pointWall2A.z = -2.5f;
    
    Point3D pointWall2B;
    pointWall2B.x = -2.6f;
    pointWall2B.y = 1.5f;
    pointWall2B.z = -3.5f;
    DrawWall(pointWall2A, pointWall2B, 0);

    // Tower 4
    Point3D pointTower4;
    pointTower4.x = 3.0f;
    pointTower4.y = 4.0f;
    pointTower4.z = -3.0f;
    DrawTower(pObj, pointTower4, 0.7f, 1.0f);

    // Wall 3
    Point3D pointWall3A;
    pointWall3A.x = 2.5f;
    pointWall3A.y = 0.27f;
    pointWall3A.z = 3.0f; 
    
    Point3D pointWall3B;
    pointWall3B.x = 3.5f;
    pointWall3B.y = 1.5f;
    pointWall3B.z = -3.0f;
    DrawWall(pointWall3A, pointWall3B, 1);

    // Wall 4
    Point3D pointWall4A;
    pointWall4A.x = -2.5f;
    pointWall4A.y = 0.27f;
    pointWall4A.z = 3.0f; 
    
    Point3D pointWall4B;
    pointWall4B.x = -3.5f;
    pointWall4B.y = 1.5f;
    pointWall4B.z = -3.0f;
    DrawWall(pointWall4A, pointWall4B, 1);
    
    // Tree
    Point3D pointTree;
    pointTree.x = 5.0f;
    pointTree.y = 2.0f;
    pointTree.z = 4.0f;
    DrawTree(pObj, pointTree);

    pointTree.x = -5.0f;
    pointTree.y = 2.0f;
    pointTree.z = 2.0f;
    DrawTree(pObj, pointTree);

    pointTree.x = -7.0f;
    pointTree.y = 2.0f;
    pointTree.z = -1.0f;
    DrawTree(pObj, pointTree);

    pointTree.x = -4.5f;
    pointTree.y = 2.0f;
    pointTree.z = 5.0f;
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