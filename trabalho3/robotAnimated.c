#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define GLFW_INCLUDE_NONE
#include <GL/gl.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#define PI 3.141592

// Animação da mão

typedef struct robo_anim_s{
  float leftLegUpperA, leftLegLowerA;
  float rightLegUpperA, rightLegLowerA;
  float walkAnimTime;
}RobotAnim;

typedef struct robo_left_arm_anim_s{
  float leftArmUpper, leftArmLower;
  float armAnimTime;
}RobotArmAnim;

static RobotAnim ANIMATION;
static RobotArmAnim ARM_ANIMATION;

void glinputHandlr(GLFWwindow *win, int key, int scancode, int action, int mods);
void errHandlr(int errCode, char *errText, void *errData);

GLFWwindow *initWindow(unsigned wid, unsigned hei, char *name);
void initDraw(GLFWwindow *win);
void viewportDraw(GLFWwindow *win);
void loopDraw(GLFWwindow *win);

void zglHexaprism(GLfloat len, GLfloat wid, GLfloat spreadAng, GLfloat hei);
void zglCuboid(GLfloat wid, GLfloat hei, GLfloat dep);
void zgluCappedCylinder(GLUquadric *quad, GLdouble base, GLdouble top, GLdouble height,
  GLint slices, GLint stacks);

float degToRad(float deg);
float radToDeg(float rad);
float cosDeg(float deg);
float sinDeg(float deg);
float tanDeg(float deg);

void animateWalk(RobotAnim *a, float animPercentage);
float getWalkPercentage();
void initAnims();

void animateArm(RobotArmAnim *a, float animPercentage);
float getArmPercentage();

static GLfloat rotTetha = 0, rotPhi = 0, zoomR = -30;
static GLfloat panHor = 0, panVert = 0;

//altera os angulos da animacao por um delta t
void animateWalk(RobotAnim *a, float animPercentage){
  const float LEFT_UPPER_FORWARD_ANGLE_P1 = 0;
  const float LEFT_UPPER_BACK_ANGLE_P1 = -44.827244;

  const float LEFT_LOWER_FORWARD_ANGLE_P1 = 0;
  const float LEFT_LOWER_BACK_ANGLE_P1 = -29.838892;

  const float LEFT_UPPER_ANGLE_DIFF_P1 = -180;
  const float LEFT_LOWER_ANGLE_DIFF_P1 = -120;

  const float LEFT_UPPER_FORWARD_ANGLE_P2 = 0;
  const float LEFT_UPPER_BACK_ANGLE_P2 = 22.491379;

  const float LEFT_LOWER_FORWARD_ANGLE_P2 = 0;
  const float LEFT_LOWER_BACK_ANGLE_P2 = -29.939253;

  const float LEFT_UPPER_ANGLE_DIFF_P2 = 90;
  const float LEFT_LOWER_ANGLE_DIFF_P2 = -120;


  const float RIGHT_UPPER_FORWARD_ANGLE_P1 = 0;
  const float RIGHT_UPPER_BACK_ANGLE_P1 = 22.491379;

  const float RIGHT_LOWER_FORWARD_ANGLE_P1 = 0;
  const float RIGHT_LOWER_BACK_ANGLE_P1 = -29.939253;

  const float RIGHT_UPPER_ANGLE_DIFF_P1 = 90;
  const float RIGHT_LOWER_ANGLE_DIFF_P1 = -120;
 
  
  if(animPercentage < 0.25){//passo direito
      a->leftLegUpperA = LEFT_UPPER_FORWARD_ANGLE_P1 + animPercentage * LEFT_UPPER_ANGLE_DIFF_P1;
      a->leftLegLowerA = LEFT_LOWER_FORWARD_ANGLE_P1 + animPercentage * LEFT_LOWER_ANGLE_DIFF_P1;
      
      a->rightLegUpperA = LEFT_UPPER_FORWARD_ANGLE_P2 + animPercentage * LEFT_UPPER_ANGLE_DIFF_P2;
      a->rightLegLowerA = LEFT_LOWER_FORWARD_ANGLE_P2 - animPercentage * LEFT_LOWER_ANGLE_DIFF_P2;

  }
  else if(animPercentage >= 0.25 && animPercentage < 0.5){//passo esquerdo
      a->leftLegUpperA = LEFT_UPPER_BACK_ANGLE_P1 - (animPercentage - 0.25)  * LEFT_UPPER_ANGLE_DIFF_P1;
      a->leftLegLowerA = LEFT_LOWER_BACK_ANGLE_P1 - (animPercentage - 0.25)  * LEFT_LOWER_ANGLE_DIFF_P1;

     a->rightLegUpperA = LEFT_UPPER_BACK_ANGLE_P2 - (animPercentage - 0.25)  * LEFT_UPPER_ANGLE_DIFF_P2;
     a->rightLegLowerA = -LEFT_LOWER_BACK_ANGLE_P2 + (animPercentage - 0.25)  * LEFT_LOWER_ANGLE_DIFF_P2;
      
  }else if(animPercentage >= 0.5 && animPercentage < 0.75){
      a->leftLegUpperA = LEFT_UPPER_FORWARD_ANGLE_P2 + (animPercentage - 0.5) * LEFT_UPPER_ANGLE_DIFF_P2;
      a->leftLegLowerA = LEFT_LOWER_FORWARD_ANGLE_P2 + (animPercentage - 0.5) * LEFT_LOWER_ANGLE_DIFF_P2;

      a->rightLegUpperA = LEFT_UPPER_FORWARD_ANGLE_P1 + (animPercentage - 0.5) * LEFT_UPPER_ANGLE_DIFF_P1;
      a->rightLegLowerA = LEFT_LOWER_FORWARD_ANGLE_P1 - (animPercentage - 0.5) * LEFT_LOWER_ANGLE_DIFF_P1;

  }else{
     a->leftLegUpperA = LEFT_UPPER_BACK_ANGLE_P2 - (animPercentage - 0.75)  * LEFT_UPPER_ANGLE_DIFF_P2;
     a->leftLegLowerA = LEFT_LOWER_BACK_ANGLE_P2 - (animPercentage - 0.75)  * LEFT_LOWER_ANGLE_DIFF_P2;

     a->rightLegUpperA =  LEFT_UPPER_BACK_ANGLE_P1 - (animPercentage - 0.75)  * LEFT_UPPER_ANGLE_DIFF_P1;
     a->rightLegLowerA = -LEFT_LOWER_BACK_ANGLE_P1 + (animPercentage - 0.75)  * LEFT_LOWER_ANGLE_DIFF_P1;
  }
}

float getWalkPercentage(){
  const float WALK_DURATION = 2.5;//segundos
  static struct timespec lastCheck, curCheck;
  float deltaTime;
  static float curTime = 0;
  static char firstRun = 1;

  if(firstRun){
    clock_gettime(CLOCK_MONOTONIC, &lastCheck);
    firstRun = 0;
  }

  clock_gettime(CLOCK_MONOTONIC, &curCheck);
  deltaTime = ((float) (curCheck.tv_sec - lastCheck.tv_sec) + (float) (curCheck.tv_nsec - lastCheck.tv_nsec) / 1e9f);
  lastCheck.tv_sec = curCheck.tv_sec;
  lastCheck.tv_nsec = curCheck.tv_nsec;

  curTime += deltaTime;
  if(curTime > WALK_DURATION)
    curTime = 0;
  return curTime / WALK_DURATION;
}

void initAnims(){
  ANIMATION.rightLegUpperA = 0;
  ANIMATION.rightLegLowerA = 0;
  ANIMATION.leftLegUpperA = 0;
  ANIMATION.leftLegLowerA = 0;
}

//Animação do braço
void animateArm(RobotArmAnim *a, float animPercentage){
  const float LEFT_UPPER_FORWARD_ANGLE = 0;
  const float LEFT_LOWER_FORWARD_ANGLE = 0;

  const float LEFT_UPPER_ANGLE_DIFF = -180;
  const float LEFT_LOWER_ANGLE_DIFF = -180;

  //fprintf(stdout, "%f deg\n", a->leftArmLower);  

  if(animPercentage < 0.5){
      a->leftArmUpper = LEFT_UPPER_FORWARD_ANGLE + animPercentage * LEFT_UPPER_ANGLE_DIFF;
      a->leftArmLower = 0;
  }else{
      a->leftArmLower = LEFT_LOWER_FORWARD_ANGLE + (animPercentage -0.5)  * LEFT_LOWER_ANGLE_DIFF;
  }
}

float getArmPercentage(){
  const float ARM_DURATION = 2.5;//segundos
  static struct timespec lastCheck, curCheck;
  float deltaTime;
  static float curTime = 0;
  static char firstRun = 0;

  if(firstRun){
    clock_gettime(CLOCK_MONOTONIC, &lastCheck);
    firstRun = 0;
  }

  clock_gettime(CLOCK_MONOTONIC, &curCheck);
  deltaTime = ((float) (curCheck.tv_sec - lastCheck.tv_sec) + (float) (curCheck.tv_nsec - lastCheck.tv_nsec) / 1e9f);
  lastCheck.tv_sec = curCheck.tv_sec;
  lastCheck.tv_nsec = curCheck.tv_nsec;

  curTime += deltaTime;
  if(curTime > ARM_DURATION)
    curTime = 0;
  return curTime / ARM_DURATION;
}

void initArm(){
  ARM_ANIMATION.leftArmUpper = 0;
  ARM_ANIMATION.leftArmLower = 0;
}



int main(){
  GLFWwindow *screen;
  unsigned long stage = 0;
  
  if(!glfwInit()){
    errHandlr(1, "Unable to init glfw\n", NULL);
    return 1;
  }

  screen = initWindow(640, 480, "roboto");
  if(!screen)
    errHandlr(1, "Unable to init GL", NULL);
  else
    stage = 1;

  if(stage > 0){
    
    glfwSwapInterval(1);
    fprintf(stdout, "Using OGL> %s\n", glGetString(GL_VERSION));
    fprintf(stdout, "wasd or arrows to rotate\n"
            "hold shift to zoom\n");
    initDraw(screen);
    initAnims();
    initArm();

    int cont = 0;
    
    while(!glfwWindowShouldClose(screen)){
      loopDraw(screen);
      if(cont < 150)
        animateArm(&ARM_ANIMATION, getArmPercentage());
      glfwSwapBuffers(screen);
      glfwPollEvents();
      cont++;
    }


    fprintf(stdout, "Quitting!\n");
    glfwDestroyWindow(screen);
  }

  glfwTerminate();
  return 0;
}

GLFWwindow *initWindow(unsigned wid, unsigned hei, char *name){
  GLFWwindow *win;
  
  win = glfwCreateWindow((int) wid, (int) hei, name, NULL, NULL);
  if(!win){
    errHandlr(1, "Unable to init GL", NULL);
    return NULL;
  }
  
  glfwSetKeyCallback(win, glinputHandlr);
  glfwMakeContextCurrent(win);
  return win;
}

void loopDraw(GLFWwindow *win){
  GLUquadricObj *shape;
  float sq;

  viewportDraw(win);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glTranslatef(panHor, -1 + panVert, zoomR);
  glRotatef(rotTetha, 0, 1, 0);
  glRotatef(rotPhi, -1, 0, 0);
  shape = gluNewQuadric();
  gluQuadricNormals(shape, GLU_SMOOTH);

  animateWalk(&ANIMATION, getWalkPercentage());
  
 
  //transform whole robot here

  //hip core
  {glPushMatrix(); 
    
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    gluCylinder(shape, 0.5, 0.5, 0.6, 8, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -1.2, 0);
    gluSphere(shape, 1, 8, 4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.2, -1.2, 0);
    glRotatef(90, 0, 1, 0);
    gluCylinder(shape, 0.4, 0.4, 4.4, 8, 1);
    glPopMatrix();

    glPushMatrix();
    //transform left leg
    
    //left upper leg
    {glPushMatrix();

      glPushMatrix();
      glTranslatef(-2.2, -1.2, 0);
      glRotatef(90, 0, 1, 0);
      zgluCappedCylinder(shape, 0.5, 0.5, 1.2, 8, 1);
     
        glRotatef(ANIMATION.leftLegUpperA, 0, 0, 1);

        glPushMatrix();
          glRotatef(-90, 0, 1, 0);
          glTranslatef(0.125, -1.2, 0.25);
          

          zglCuboid(1, 1, -0.6);

          glPushMatrix();
          glTranslatef(0.5, -3, -0.3);
          glRotatef(90, 0, 1, 0);
          zglHexaprism(0.8, 0.7, 100, 3);
          glPopMatrix();

          glPushMatrix();
          glTranslatef(0, -3.5, 0);
          zglCuboid(1, 0.8, -0.6);
          glPopMatrix();

          //transform left lower leg
          //glRotatef(ANIMATION.leftLegLowerA, -1, 0, 0);

          glPushMatrix();
          glTranslatef(-0.1, -3.8, -0.3);
          glRotatef(90, 0, 1, 0);
          zgluCappedCylinder(shape, 0.5, 0.5, 1.2, 8, 1);

          
            glRotatef(ANIMATION.leftLegLowerA, 0, 0, -1);
            glPushMatrix();
            // teste
              glRotatef(-90, 0, 1, 0);
              glTranslatef(0.125, -1.2, 0.25);

              //left lower leg
              {glPushMatrix();
                zglCuboid(1, 0.8, -0.6);

                glPushMatrix();
                glTranslatef(0.5, -3, -0.3);
                glRotatef(90, 0, 1, 0);
                zglHexaprism(0.8, 0.7, 100, 3);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0.5, -3, -0.3);
                glRotatef(90, 1, 0, 0);
                gluCylinder(shape, 0.4, 0.4, 1, 8, 1);
                glPopMatrix();

                //transform left foot
                glTranslatef(0.5, -3.8, -0.3);

                //left foot
                {
                gluSphere(shape, 0.7, 8, 4);

                glPushMatrix();
                glTranslatef(0, -1, 0.6);
                zglHexaprism(1.7, 0.9, 95, 1);
                glPopMatrix();
                }
              glPopMatrix();

              
            }glPopMatrix();

            glPopMatrix();

          
          glPopMatrix();

          
          
            
      }glPopMatrix();
      //end of left leg

    glPopMatrix();

    glPushMatrix();
    //transform right leg
    //
   

    //right upper leg
    {glPushMatrix();
      
      glPushMatrix();
        glTranslatef(1.0, -1.2, 0);
        glRotatef(90, 0, 1, 0);
        zgluCappedCylinder(shape, 0.5, 0.5, 1.2, 8, 1);

        glRotatef(ANIMATION.rightLegUpperA, 0, 0, 1);
         glPushMatrix();
            glRotatef(-90, 0, 1, 0);
            glTranslatef(0.105, -1.2, 0.25);

            zglCuboid(1, 1, -0.6);

            glPushMatrix();
            glTranslatef(0.5, -3, -0.3);
            glRotatef(90, 0, 1, 0);
            zglHexaprism(0.8, 0.7, 100, 3);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, -3.5, 0);
            zglCuboid(1, 0.8, -0.6);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-0.1, -3.8, -0.3);
            glRotatef(90, 0, 1, 0);
            zgluCappedCylinder(shape, 0.5, 0.5, 1.2, 8, 1);
            

              glRotatef(ANIMATION.rightLegLowerA, 0, 0, 1);
              glPushMatrix();
                  glRotatef(-90, 0, 1, 0);
                  glTranslatef(0.105, -1.2, 0.25);

                  //right lower leg
                  {glPushMatrix();
                    zglCuboid(1, 0.8, -0.6);

                    glPushMatrix();
                    glTranslatef(0.5, -3, -0.3);
                    glRotatef(90, 0, 1, 0);
                    zglHexaprism(0.8, 0.7, 100, 3);
                    glPopMatrix();

                    glPushMatrix();
                    glTranslatef(0.5, -3, -0.3);
                    glRotatef(90, 1, 0, 0);
                    gluCylinder(shape, 0.4, 0.4, 1, 8, 1);
                    glPopMatrix();

                    //transform right foot
                    glTranslatef(0.5, -3.8, -0.3);

                    //right foot
                    {
                      gluSphere(shape, 0.7, 8, 4);

                      glPushMatrix();
                      glTranslatef(0, -1, 0.6);
                      zglHexaprism(1.7, 0.9, 95, 1);
                      glPopMatrix();
                    }
                  }glPopMatrix();
                }glPopMatrix();


              glPopMatrix();
            


            glPopMatrix();
         glPopMatrix();
      glPopMatrix();

     

     
      //transform right lower leg
      //glRotatef(ANIMATION.rightLegLowerA, -1, 0, 0);

      
    //end of right leg
    glPopMatrix();

    glPushMatrix();
    //transform upper body

    //upper body
    {glPushMatrix();
      zglHexaprism(3, sqrt(6.75), 120, 8);

      glPushMatrix();
      glTranslatef(-(sqrt(6.75) / 2  + 2.5), 4, 0);
      glRotatef(90, 0, 1, 0);
      gluCylinder(shape, 0.5, 0.5, sqrt(6.75) + 5, 8, 1);
      glPopMatrix();

      glPushMatrix();
      //transform left arm
      //glTranslatef(-(sqrt(6.75) / 2  + 2.5), 4, 0);

        //left upper arm
        //glRotatef(ARM_ANIMATION.leftArmUpper, 1, 0, 0);
        {glPushMatrix();
          glTranslatef(-(sqrt(6.75) / 2  + 2.5), 4, 0);
          glRotatef(ARM_ANIMATION.leftArmUpper, 1, 0, 0); 

          gluSphere(shape, 1, 8, 4);

          glPushMatrix();
          glTranslatef(0, -0.5, 0);

          gluCylinder(shape, 0.4, 0.4, 1, 8, 1);
         
          glPopMatrix();

          glPushMatrix();
          glTranslatef(0, -4.0, 0);
          glRotatef(90, 0, 1, 0);
          zglHexaprism(1, 0.8, 90, 3);
          glPopMatrix();


          glPushMatrix();
          glTranslatef(-0.5, -4.7, 0.3);
          zglCuboid(1, 1, -0.6);
          glPopMatrix();

          {glPushMatrix();

             glPushMatrix();
                glTranslatef(-0.6, -4.8, 0);
                glRotatef(ARM_ANIMATION.leftArmLower, 1, 0, 0);
                glRotatef(90, 0, 1, 0);
                zgluCappedCylinder(shape, 0.5, 0.5, 1.2, 8, 1);

                
               
                glPushMatrix();
                    glTranslatef(-0.3, -1.0, 0.1);
                    glRotatef(-90, 0, 1, 0);
                    

                    zglCuboid(1, 1, -0.6);    

                    glPushMatrix();
                    glTranslatef(0.5, -2.6, -0.3);
                    glRotatef(90, 0, 1, 0);
                    zglHexaprism(1, 0.8, 90, 3);
                    glPopMatrix();

                    glPushMatrix();
                    glTranslatef(0.5, -2.4, -0.3);
                    glRotatef(90, 1, 0, 0);
                    gluCylinder(shape, 0.4, 0.4, 0.6, 8, 1);
                    glPopMatrix();

                    //left hand transform
                    glTranslatef(0.5, -3.6, -0.3);

                    //left hand
                    {glPushMatrix();
                      zglHexaprism(1, sqrt(3) / 2, 120, 0.8);

                      //put finger code here ?
                    }glPopMatrix();

                glPopMatrix();
             glPopMatrix();
            
          }glPopMatrix();
        }glPopMatrix();
        //end of left arm
        glPopMatrix();
       

      glPushMatrix();
      //transform right arm
      glTranslatef(+(sqrt(6.75) / 2  + 2.5), 4, 0);

      //right upper arm
      {glPushMatrix();
        gluSphere(shape, 1, 8, 4);

        glPushMatrix();
        glTranslatef(0, -0.5, 0);
        glRotatef(90, 1, 0, 0);
        gluCylinder(shape, 0.4, 0.4, 1, 8, 1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, -4.0, 0);
        glRotatef(90, 0, 1, 0);
        zglHexaprism(1, 0.8, 90, 3);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.5, -4.7, 0.3);
        zglCuboid(1, 1, -0.6);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.6, -4.8, 0);
        glRotatef(90, 0, 1, 0);
        zgluCappedCylinder(shape, 0.5, 0.5, 1.2, 8, 1);
        glPopMatrix();

        //transform right lower arm
        glTranslatef(-0.5, -6.0, 0.3);
        //right lower arm
        {glPushMatrix();
          zglCuboid(1, 1, -0.6);
          
          glPushMatrix();
          glTranslatef(0.5, -2.6, -0.3);
          glRotatef(90, 0, 1, 0);
          zglHexaprism(1, 0.8, 90, 3);
          glPopMatrix();

          glPushMatrix();
          glTranslatef(0.5, -2.4, -0.3);
          glRotatef(90, 1, 0, 0);
          gluCylinder(shape, 0.4, 0.4, 0.6, 8, 1);
          glPopMatrix();

          //righthand transform
          glTranslatef(0.5, -3.6, -0.3);

          //right hand
          {glPushMatrix();
            zglHexaprism(1, sqrt(3) / 2, 120, 0.8);

            //put finger code here ?
          }glPopMatrix();
        }glPopMatrix();
      }glPopMatrix();
      //end of right arm
      glPopMatrix();

      glPushMatrix();
      //transform head

      //head
      {glPushMatrix();
        //no head :(
      }glPopMatrix();
      //end of head
      glPopMatrix();

    }glPopMatrix();
    //end of upper body
    glPopMatrix();

  }glPopMatrix();

  gluDeleteQuadric(shape);
  glPopMatrix();
}

void zglHexaprism(GLfloat len, GLfloat wid, GLfloat spreadAng, GLfloat hei){
  GLfloat tZ;

  if(spreadAng > 179)
    spreadAng = 179;
  if(spreadAng < 1)
    spreadAng = 1;

  tZ = len - (wid / tanDeg(spreadAng / 2));
  glBegin(GL_TRIANGLE_FAN);{//bottom
    glVertex3f(0, 0, len);
    glVertex3f(-wid, 0, tZ);
    glVertex3f(-wid, 0, -(tZ));
    glVertex3f(0, 0, -(len));
    glVertex3f(wid, 0, -(tZ));
    glVertex3f(wid, 0, tZ);
  }glEnd();
  glBegin(GL_TRIANGLE_FAN);{//top
    glVertex3f(0, hei, len);
    glVertex3f(wid, hei, tZ);
    glVertex3f(wid, hei, -(tZ));
    glVertex3f(0, hei, -(len));
    glVertex3f(-wid, hei, -(tZ));
    glVertex3f(-wid, hei, tZ);
  }glEnd();

  glBegin(GL_TRIANGLE_STRIP);{//sides diags
    glVertex3f(0, 0, len);
    glVertex3f(wid, 0, tZ);
    glVertex3f(0, hei, len);
    glVertex3f(wid, hei, tZ);
  }glEnd();
  glBegin(GL_TRIANGLE_STRIP);{
    glVertex3f(0, 0,-(len));
    glVertex3f(-(wid), 0, -(tZ));
    glVertex3f(0, hei, -(len));
    glVertex3f(-(wid), hei, -(tZ));
  }glEnd();

  glBegin(GL_TRIANGLE_STRIP);{
    glVertex3f(-(wid), 0, tZ);
    glVertex3f(0, 0, len);
    glVertex3f(-(wid), hei, tZ);
    glVertex3f(0, hei, len);
  }glEnd();
  glBegin(GL_TRIANGLE_STRIP);{
    glVertex3f(wid, 0, -(tZ));
    glVertex3f(0, 0, -(len));
    glVertex3f(wid, hei, -(tZ));
    glVertex3f(0, hei, -(len));
  }glEnd();

  glBegin(GL_TRIANGLE_STRIP);{//sides Z
    glVertex3f(wid, 0, tZ);
    glVertex3f(wid, 0, -(tZ));
    glVertex3f(wid, hei, tZ);
    glVertex3f(wid, hei, -(tZ));
  }glEnd();
  glBegin(GL_TRIANGLE_STRIP);{
    glVertex3f(-(wid), 0, -(tZ));
    glVertex3f(-(wid), 0, tZ);
    glVertex3f(-(wid), hei, -(tZ));
    glVertex3f(-(wid), hei, tZ);
  }glEnd();
}

//note: depth in opengl is negative
void zglCuboid(GLfloat wid, GLfloat hei, GLfloat dep){

  glBegin(GL_TRIANGLE_STRIP);{//front
    glVertex3f(0, 0, 0);
    glVertex3f(wid, 0, 0);
    glVertex3f(0, hei, 0);
    glVertex3f(wid, hei, 0);
  }glEnd();
  glBegin(GL_TRIANGLE_STRIP);{//right
    glVertex3f(wid, 0, 0);
    glVertex3f(wid, 0, dep);
    glVertex3f(wid, hei, 0);
    glVertex3f(wid, hei, dep);
  }glEnd();
  glBegin(GL_TRIANGLE_STRIP);{//back
    glVertex3f(wid, 0, dep);
    glVertex3f(0, 0, dep);
    glVertex3f(wid, hei, dep);
    glVertex3f(0, hei, dep);
  }glEnd();
  glBegin(GL_TRIANGLE_STRIP);{//left
    glVertex3f(0, 0, dep);
    glVertex3f(0, 0, 0);
    glVertex3f(0, hei, dep);
    glVertex3f(0, hei, 0);
  }glEnd();
  glBegin(GL_TRIANGLE_STRIP);{//top
    glVertex3f(0, hei, 0);
    glVertex3f(wid, hei, 0);
    glVertex3f(0, hei, dep);
    glVertex3f(wid, hei, dep);
  }glEnd();
  glBegin(GL_TRIANGLE_STRIP);{//bottom
    glVertex3f(0, 0, dep);
    glVertex3f(wid, 0, dep);
    glVertex3f(0, 0, 0);
    glVertex3f(wid, 0, 0);
  }glEnd();
}

void zgluCappedCylinder(GLUquadric *quad, GLdouble base, GLdouble top, GLdouble height,
  GLint slices, GLint stacks){
  
  gluCylinder(quad, base, top, height, slices, stacks);

  glPushMatrix();
  glRotatef(180, 0, 1, 0);
  gluDisk(quad, 0, base, slices, 2);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0, height);
  gluDisk(quad, 0, top, slices, 2);
  glPopMatrix();
}

void viewportDraw(GLFWwindow *win){
  int wid, hei;

  glfwGetFramebufferSize(win, &wid, &hei);
  glViewport(0, 0, wid, hei);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(35, (GLfloat) wid/hei, 1, 60);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void initDraw(GLFWwindow *win){
  const GLfloat lightWhite[] = {(float) 0x0d/0xff, (float) 0x0d/0xff, (float) 0x0d/0xff, 1};
  const GLfloat lightAmbient[] = {(float) 0x40/0xff, (float) 0x40/0xff, (float) 0x40/0xff, 1};
  const GLfloat lightPos[] = {-10, 5, 5, 1};
   
  glFrontFace(GL_CCW);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightWhite);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightAmbient);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  glEnable(GL_LIGHT0);

  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  //glClearColor((float) 0xdc/0xff , (float) 0x14/0xff, (float) 0x3c/0xff, 1);
  glClearColor((float) 0x40/0xff , (float) 0x40/0xff, (float) 0x80/0xff, 1);
}

void glinputHandlr(GLFWwindow *win, int key, int scancode, int action, int mods){
  switch(key){
    case GLFW_KEY_ESCAPE:{
      if(action == GLFW_PRESS)
        glfwSetWindowShouldClose(win, GLFW_TRUE);
      break;
    }
    case GLFW_KEY_RIGHT:
    case GLFW_KEY_D:{
      if(action == GLFW_REPEAT || action == GLFW_PRESS){
        if(mods && GLFW_MOD_CONTROL)
          panHor += 0.5;
        else
          rotTetha += 5.;
      }
      break;
    }
    case GLFW_KEY_LEFT:
    case GLFW_KEY_A:{
      if(action == GLFW_REPEAT || action == GLFW_PRESS){
        if(mods && GLFW_MOD_CONTROL)
          panHor -= 0.5;
        else
          rotTetha -= 5.;
      }    
      break;
    }
    case GLFW_KEY_UP:
    case GLFW_KEY_W:{
      if(action == GLFW_REPEAT || action == GLFW_PRESS){
        if(mods && GLFW_MOD_SHIFT)
          zoomR += 0.5;
        else{
          if(mods && GLFW_MOD_CONTROL)
            panVert += 0.5;
          else
            rotPhi += 5.;
        }          
      }
      break;
    }
    case GLFW_KEY_DOWN:
    case GLFW_KEY_S:{
      if(action == GLFW_REPEAT || action == GLFW_PRESS){
        if(mods && GLFW_MOD_SHIFT)
          zoomR -= 0.5;
        else{
           if(mods && GLFW_MOD_CONTROL)
            panVert -= 0.5;
          else
            rotPhi -= 5.;
        }  
      }      
      break;
    }
  }

  if(rotTetha > 360)
    rotTetha = 0;
   
  if(rotTetha < 0)
    rotTetha = 360;
  
  if(rotPhi > 360)
    rotPhi = 0;
  
  if(rotPhi < 0)
    rotPhi = 360;
    
  if(zoomR > -2)
    zoomR = -2;
}

void errHandlr(int errCode, char *errText, void *errData){
  fprintf(stderr, "ERROR (%d)> %s\n", errCode, errText);
}

float degToRad(float deg){
  return 2 * PI * (deg / 360);
}

float radToDeg(float rad){
  return 360 * (rad / (2 * PI));
}

float cosDeg(float deg){
  return cos(degToRad(deg));
}

float sinDeg(float deg){
  return sin(degToRad(deg));
}

float tanDeg(float deg){
  return tan(degToRad(deg));
}
