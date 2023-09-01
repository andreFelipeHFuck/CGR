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

// Ellipse
void DrawEllipse(GLfloat x, GLfloat y, GLfloat z, GLfloat StAngle, GLfloat EndAngle, GLfloat RX, GLfloat RY){
    GLdouble i;

    glBegin(GL_LINE_STRIP);
    i = StAngle;
    while (i <= EndAngle)
    {
        glVertex3f((RX * cos(i) + y) + .5, (RY * sin(i) + x) + .5, z);
        i += .001;
    }
    
    glEnd();
}

void myEllipse(GLfloat x, GLfloat y, GLfloat z){

    for(float i = 0; i < 360; i=i+0.1){
        x = sin(i);
        y = cos(i);
        glVertex3f(x,y,z);
    }   

}

// Head
void DrawHead(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height){
  GLfloat heightQuarter = height/4.0;
  GLfloat radius1 = radius / 5.0;
  GLfloat radius2 = radius / 10.0;
  GLfloat radius3 = radius / 4.0;
  GLfloat height1 = height / 2.0;
  height -= heightQuarter;

  glPushMatrix();
    glTranslatef(point.x, point.y, point.z);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(pObj, radius, radius, height, 26, 13);

    glTranslatef(0.0, 0.0, height);
    glPushMatrix();
        gluSphere(pObj, radius, 26, 13);

        // Eyes
        glPushMatrix();
            glRotatef(-90, 1.0, 0.0, 0.0);
            glTranslatef(0.0, 0.0, - 1.3*radius);
            gluCylinder(pObj, radius / 2.0, radius / 2.0, height, 26, 13);
        glPopMatrix();

        // Antenna
        glTranslatef(0.0, 0.0, radius1);
        glPushMatrix();
            gluCylinder(pObj, radius1, radius1, height1, 26, 13);
        glPopMatrix();

        glTranslatef(0.0, 0.0, radius1);
        glPushMatrix();
            gluCylinder(pObj, radius2, radius2, height, 26, 13);
        glPopMatrix();

        glTranslatef(0.0, 0.0, 1.5 * height1);
        glPushMatrix();
            gluSphere(pObj,radius3, 26, 13);
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

        glPushMatrix();
            gluCylinder(pObj, radius1, radius2, height, 26, 13);

            glPushMatrix(); 
                glRotatef(-180, 1.0, 0.0, 0.0);
                gluDisk(pObj, 0.0, radius1, 26, 13);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0.0, 0.0, height);
                gluCylinder(pObj, radius2, radius2/3.0, heightFifth, 26, 13);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

   
}

// Hand
void DrawHand(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat radiusMiddle, GLfloat height){
    glTranslatef(0.0, 0.0, height / 3.0);
    gluCylinder(pObj, 0.0f, radius/1.2, height, 26, 13);
   
    glTranslatef(0.0, 0.0, height);
    gluDisk(pObj, 0.0f, radius/1.2, 26, 13);       
}

// Arm
void DrawArm(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height, int side){
    GLfloat radiusMiddle = radius/2.0;
    GLfloat radiusSphere = (radius * 0.25);
    GLfloat heightQuater = height/4.0;

    glPushMatrix();
         glTranslatef(point.x, point.y, point.z);
         glRotatef(side, 0.0, 1.0, 0.0);

        glPushMatrix();
            gluSphere(pObj, radius, 26, 13);

            glTranslatef (0.0 , 0.0, radiusMiddle);

            glPushMatrix();
                gluCylinder(pObj, radiusMiddle, radiusMiddle, height, 26, 13);

                glTranslatef(0.0, 0.0, radiusMiddle);
                glPushMatrix();
                    gluCylinder(pObj, radiusMiddle, radiusMiddle, height, 26, 13);  
                    DrawHand(pObj, point, radius, radiusMiddle, height);
                glPopMatrix();

            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

}

// Leg
void DrawLeg(GLUquadricObj *pObj, Point3D point, GLfloat radius, GLfloat height){
    GLfloat radiusMiddle = radius/2.0;
    GLfloat heightQuater = height/4.0;

    glPushMatrix();
        glTranslatef (point.x, point.y, point.z);
        glRotatef(-90, 1.0, 0.0, 0.0);
        gluCylinder(pObj, radiusMiddle, radiusMiddle, height, 26, 13);

        glTranslatef(0.0, 0.0, point.z - height);

        glPushMatrix();
            gluCylinder(pObj, radiusMiddle, radiusMiddle, height, 26, 13);
            
            glPushMatrix();
                gluCylinder(pObj, radius, radiusMiddle, heightQuater, 26, 13);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void DrawRobot(GLUquadricObj *pObj, Point3D point, GLfloat height);

// Scene
void RenderScene(void){
    GLUquadricObj *pObj;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

    glPushMatrix();

    glTranslatef(0.0f, -1.0f, -25.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 1.0f, 0.0f, 0.0f);


    pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);

    glColor3f(1.0, 1.0, 1.0);
    // Head
    Point3D pointHead;
    pointHead.x = 0.0f;
    pointHead.y = 5.5f;
    pointHead.z = 0.0f;

    DrawHead(pObj, pointHead, 0.7, 1.5);

    // Chest
    Point3D pointChest;
    pointChest.x = 0.0f;
    pointChest.y = 3.0f;
    pointChest.z = 0.0f;

    DrawChest(pObj, pointChest, 0.8, 1.5, 2.9);

    // Arm 1
    Point3D pointArm1;
    pointArm1.x = 1.5f;
    pointArm1.y = 5.0f;
    pointArm1.z = 0.0f;

    DrawArm(pObj, pointArm1, 0.4, 2.5, 90);

     // Arm 2
    Point3D pointArm2;
    pointArm2.x = -1.5f;
    pointArm2.y = 5.0f;
    pointArm2.z = 0.0f;

    DrawArm(pObj, pointArm2, 0.4, 2.5, -90);

    // Leg 1
    Point3D pointLeg1;
    pointLeg1.x = -0.4;
    pointLeg1.y = 1.5;
    pointLeg1.z = 0.0;

    DrawLeg(pObj, pointLeg1, 0.5, 2.0);

    // Leg 2
    Point3D pointLeg2;
    pointLeg2.x = 0.4;
    pointLeg2.y = 1.5;
    pointLeg2.z = 0.0;

     DrawLeg(pObj, pointLeg2, 0.5, 2.0);

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