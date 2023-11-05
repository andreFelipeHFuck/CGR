#include "formas.h"

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