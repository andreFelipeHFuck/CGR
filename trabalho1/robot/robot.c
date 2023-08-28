#include "robot.h"

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

// Head
void DrawHead(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height){

}

// Chest

// Hand
void DrawHand(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat radiusMiddle, GLfloat height){
    glPushMatrix();
        glTranslatef(point.x + (1.2)*height, point.y, point.z);
        glRotatef(-90, 0.0, 1.0, 0.0);
        gluCylinder(pObj, radius/1.5, 0.0f, height, 26, 13);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(point.x + (1.1)*height, point.y, point.z);
        glRotated(90, 0.0, 1.0, 0.0);
        gluDisk(pObj, 0.0f, radiusMiddle, 26, 13);       
    glPopMatrix();
}

// Arm
void DrawArm(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height){
    GLfloat radiusMiddle = radius/2.0;
    GLfloat heightQuater = height/4.0;

    glPushMatrix();
        glPushMatrix();
            glTranslatef (point.x, point.y, point.z);
            glRotatef(-90, 0.0, 1.0, 0.0);
            gluCylinder(pObj, radiusMiddle, radiusMiddle, height, 26, 13);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(point.x + height, point.y, point.z);
            glRotatef(-90, 0.0, 1.0, 0.0);
            gluCylinder(pObj, radiusMiddle, radiusMiddle, height, 26, 13);
        glPopMatrix();

        DrawHand(pObj, point, radius, radiusMiddle, height);
    glPopMatrix();
}

// Foot
void DrawFoot();

// Leg
void DrawLeg(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height){
     GLfloat radiusMiddle = radius/2.0;
    GLfloat heightQuater = height/4.0;

    glPushMatrix();
        glPushMatrix();
            glTranslatef (point.x, point.y - height, point.z);
            glRotatef(-90, 1.0, 0.0, 0.0);
            gluCylinder(pObj, radiusMiddle, radiusMiddle, height, 26, 13);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(point.x, point.y, point.z);
            glRotatef(-90, 1.0, 0.0, 0.0);
            gluCylinder(pObj, radiusMiddle, radiusMiddle, height, 26, 13);
        glPopMatrix();

        //DrawFoot();
    glPopMatrix();
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

    // Arm 
    Point3D pointArm;
    pointArm.x = 0.0f;
    pointArm.y = 0.0f;
    pointArm.z = 1.0f;

    DrawLeg(pObj, pointArm, 0.25f, 1.0f);

   glPopMatrix();
    // Estudar
    glutSwapBuffers();
}

int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Robot");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();  
      
    return 0; 
}