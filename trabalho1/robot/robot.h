#include <GL/glut.h>
#include <math.h>

typedef struct point3D
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
}Point3D;

typedef struct color{
    GLfloat r;
    GLfloat g;
    GLfloat b;
}Color;

void DrawParallelepiped(Point3D point1, Point3D point2);

void DrawHead(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height);
void DrawChest(GLUquadricObj *pObj, Point3D point, GLfloat radius1, GLfloat radius2, GLfloat height);
void DrawArm(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height, int side);
void DrawHand(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat radiusMiddle, GLfloat height);
void DrawLeg(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height);
void DrawRobot(GLUquadricObj *pObj, Point3D point, GLfloat height);
