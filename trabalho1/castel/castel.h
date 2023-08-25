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
void DrawPyramid(Point3D point1, Point3D point2, GLfloat height);
void DrawFloor(GLfloat height, GLfloat widht1, GLfloat widht2, Color color);
void DrawTower(GLUquadricObj *pObj, Point3D point, GLfloat radius1, GLfloat radius2);
void DrawParaTower(Point3D point1, Point3D point2);
void DrawTree(GLUquadricObj *pObj, Point3D point);
void DrawWall(Point3D point1, Point3D point2, int opcao);
