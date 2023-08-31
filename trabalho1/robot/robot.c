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
  GLfloat heightQuarter = height/4.0;
  GLfloat radius1 = radius / 5.0;
  GLfloat radius2 = radius / 10.0;
  GLfloat height1 = height / 2.0;
  height -= heightQuarter;

  glPushMatrix();
    glTranslatef(point.x, point.y, point.z);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(pObj, radius, radius, height, 26, 13);

    glTranslatef(point.x, point.y, point.z + height);
    glPushMatrix();
        gluSphere(pObj, radius, 26, 13);

        glTranslatef(point.x, point.y, point.z +  radius1);
        glPushMatrix();
            gluCylinder(pObj, radius1, radius1, height1, 26, 13);
        glPopMatrix();

        glTranslatef(point.x, point.y, point.z +  radius1);
        glPushMatrix();
            gluCylinder(pObj, radius2, radius2, height, 26, 13);
        glPopMatrix();
    glPopMatrix();

    
  glPopMatrix();
}

// Chest
void DrawChest(GLUquadricObj *pObj, Point3D point, GLfloat radius1, GLfloat radius2, GLfloat height){
    GLfloat heightFifth = height/4.0;
    height -= heightFifth;

    glPushMatrix();
        glTranslatef(point.x, point.y, point.z);
        glRotatef(-90, 1.0, 0.0, 0.0);
        gluCylinder(pObj, radius1, radius2, height, 26, 13);

        glTranslatef(point.x, point.y, point.z + height);
        glPushMatrix();
            gluCylinder(pObj, radius2, radius2/3.0, heightFifth, 26, 13);
        glPopMatrix();
    glPopMatrix();

   
}

// Hand
void DrawHand(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat radiusMiddle, GLfloat height){
    glTranslatef(point.x , point.y, point.z + height / 3.0);
    //glRotatef(-90, 0.0, 1.0, 0.0);
    gluCylinder(pObj, 0.0f, radius/1.2, height, 26, 13);
   
    glTranslatef(point.x , point.y, point.z + height);
    //glRotated(180, 0.0, 1.0, 0.0);
    gluDisk(pObj, 0.0f, radius/1.2, 26, 13);       
}

// Arm
void DrawArm(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height){
    GLfloat radiusMiddle = radius/2.0;
    GLfloat radiusSphere = (radius * 0.25);
    GLfloat heightQuater = height/4.0;

    glPushMatrix();
        glTranslatef(point.x, point.y, point.z);
        glRotatef(-90, 0.0, 1.0, 0.0);

        gluSphere(pObj, radius - radiusSphere, 26, 13);


        GLfloat pointZ1 = point.z + radiusMiddle;
        glTranslatef (point.x , point.y, pointZ1);

        glPushMatrix();
            gluCylinder(pObj, radiusMiddle, radiusMiddle, height, 26, 13);

            glTranslatef(point.x, point.y, pointZ1 + radiusMiddle);
            glPushMatrix();
                gluCylinder(pObj, radiusMiddle, radiusMiddle, height, 26, 13);  
                DrawHand(pObj, point, radius, radiusMiddle, height);
            glPopMatrix();

        glPopMatrix();
    glPopMatrix();

}

// Foot
void DrawFoot(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height){
}

// Leg
void DrawLeg(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height){
    GLfloat radiusMiddle = radius/2.0;
    GLfloat heightQuater = height/4.0;

    glPushMatrix();
        glTranslatef (point.x, point.y, point.z);
        glRotatef(-90, 1.0, 0.0, 0.0);
        gluCylinder(pObj, radiusMiddle, radiusMiddle, height, 26, 13);

        glTranslatef(point.x, point.y, point.z - height);

        glPushMatrix();
            gluCylinder(pObj, radiusMiddle, radiusMiddle, height, 26, 13);
            

            glPushMatrix();
                gluCylinder(pObj, radius, radiusMiddle, heightQuater, 26, 13);
            glPopMatrix();
        glPopMatrix();
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
    pointArm.z = 0.0f;

    DrawHead(pObj, pointArm, 0.7, 1.5);

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