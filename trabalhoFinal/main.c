#include "src/tecido.h"

Tecido *tecido;
Vec3 posicao_bola;
GLfloat raio_bola = 2;

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

GLfloat tempo_bola = 0;

// Scene
void RenderScene(void){
    posicao_bola =  criaVec3(7, -5, 0);

    tempo_bola++;
    posicao_bola.z = cos(tempo_bola/50.0) * 7;

   addForcaTecido(tecido, multiplicacaoVec3(criaVec3(0, -0.2, 0), TEMPO_ESCALONADO));
   forcaVentoTecido(tecido, multiplicacaoVec3(criaVec3(0, -1.5, 0), TEMPO_ESCALONADO));
   timeStepTecido(tecido);
   colisaoBolaTecido(tecido, posicao_bola, raio_bola);

    GLUquadricObj *pObj;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

    glPushMatrix();

    glTranslatef(0.0f, -1.0f, -18.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 1.0f, 0.0f, 0.0f);


    // pObj = gluNewQuadric();  
	// gluQuadricNormals(pObj, GLU_SMOOTH);  
   
    glTranslatef(-6.5,6,-9.0f); // move ca
	glRotatef(25,0,1,0);
    desenhaShadedTecido(tecido);

    glPushMatrix();
    glTranslatef(posicao_bola.x, posicao_bola.y, posicao_bola.z);
    glColor3f(0.4f, 0.8f, 0.5f);
    glutSolidSphere(raio_bola-0.1, 50, 50);
    glPopMatrix();
     
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char *argv[]){
    tecido = criaTecido(14, 10, 55, 45);

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Tecido");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();  
      
    return 0; 
}