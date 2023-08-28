#include <GL/glut.h>

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
void DrawArm(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height);
void DrawHand(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat radiusMiddle, GLfloat height);


void DrawLeg(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height);
