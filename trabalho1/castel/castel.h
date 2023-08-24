#include <GL/glut.h>

typedef struct point3D
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
}Point3D;

void DrawTower(GLUquadricObj *pObj, Point3D point);
void DrawParallelepiped(Point3D point1, Point3D point);
