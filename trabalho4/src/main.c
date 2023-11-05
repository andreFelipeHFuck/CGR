#include "objeto.h"
#include <SOIL/SOIL.h>
#define STB_IMAGE_IMPLEMENTATION
#define TEXTURE_COUNT 2;

static GLfloat yRot = 0.0f;
static GLfloat xRot = 0.0f;
static GLfloat zDist = -10.0f;
static GLfloat yDist = 0.0f;

char *arq = "../assets/cube_teste.obj";
GLuint textureID;

void loadTexture() {
    textureID = SOIL_load_OGL_texture(
        "../assets/cube.png", 
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (textureID == 0) {
        printf("Erro ao carregar a textura: %s\n", SOIL_last_result());
    }
}

void init() {
   glClearColor(0.0, 0.0, 0.0, 0.0); // Define a cor de fundo
//    glShadeModel(GL_SMOOTH); // Define o modo de shading como suave
//    glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade para cálculo de sombra
//    glEnable(GL_LIGHTING); // Habilita o sombreamento
//    glEnable(GL_LIGHT0); // Habilita a primeira fonte de luz
//    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0}; // Posição da luz
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Define a posição da luz
}

void SpecialKeys(unsigned char key, int x, int y){  

    if(key == 'a')  
        yRot -= 5.0f;  
  
    if(key == 'd')  
        yRot += 5.0f;  
                  
    yRot = (GLfloat)((const int)yRot % 360);  

    if(key == 'w')  
        xRot -= 5.0f;  
  
    if(key == 's')  
        xRot += 5.0f;  
                  
    xRot = (GLfloat)((const int)xRot % 360);  

    if(key == 'z')
        zDist += 1.0f;
    
    if(key == 'x')
        zDist -= 1.0f;

    if(key == '-')
        yDist += .5f;
    
    if(key == '=')
        yDist -= .5f;

    if(key == 'q' || key == 'Q')
        exit(0);
  
    // Refresh the Window  
    glutPostRedisplay();  
}

void ChangeSize(int width, int height) {  
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
}

void SetupRC(){  

   // Light values and coordinates  
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess = { 100.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	glEnable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
  
    // Black blue background  
    glClearColor(.0, .0, .25, 1.0);
	glColor3f(1.0, 0.0, 0.0);

}  

void RenderScene(void){
 glClearColor(0.0, 0.0, 0.0, 0.0); // Define a cor de fundo
   glShadeModel(GL_SMOOTH); // Define o modo de shading como suave
   glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade para cálculo de sombra
   glEnable(GL_LIGHTING); // Habilita o sombreamento
   glEnable(GL_LIGHT0); // Habilita a primeira fonte de luz
   GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0}; // Posição da luz
   glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Define a posição da luz
}

void desenharObj() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cores e de profundidade

    // Define as propriedades do material
    GLfloat mat_ambient[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat mat_diffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    Vec2 *v2 = (Vec2*)malloc(sizeof(Vec2));
    v2 = NULL;
    Vec3 *v3 = (Vec3*)malloc(sizeof(Vec3));
    v3 = NULL;
    Vec3 *normal = (Vec3*)malloc(sizeof(Vec3));
    normal = NULL;
    Face *faces = (Face*)malloc(sizeof(Face));
    faces = NULL;

    FILE * file = fopen(arq, "r");
    if( file == NULL ){
        printf("Impossible to open the file !\n");
        return;
    }

    float x, y, z;
    int trash, xInt, yInt, zInt, temVt = 0, temVn = 0;
    int textX=0, textY=0, textZ=0;

    GLUquadricObj *pObj;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH); 

    while( 1 ){

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader
        if ( strcmp( lineHeader, "v" ) == 0 ){
            fscanf(file, "%f %f %f\n", &x, &y, &z );
            v3 = addVec3(v3, x, y, z);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            fscanf(file, "%f %f\n", &x, &y );
            v2 = addVec2(v2, x, y);
            temVt = 1;
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
            fscanf(file, "%f %f %f\n", &x, &y, &z );
            normal = addVec3(normal, x, y, z);
            temVn = 1;
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            if(temVt == 1 && temVn == 1){
                fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &xInt, &textX, &trash, &yInt, &textY, &trash, &zInt, &textZ, &trash);
                faces = addFace(faces, xInt, yInt, zInt, textX, textY, textZ);
            }else if(temVt == 1 && temVn == 0 || temVt == 0 && temVn == 1){
                fscanf(file, "%d/%d/%d %d/%d/%d\n", &xInt, &textX, &yInt, &textY, &zInt, &textZ);
                faces = addFace(faces, xInt, yInt, zInt, textX, textY, textZ);
            }else {
                fscanf(file, "%d/%d/%d\n", &xInt, &yInt, &zInt);
                faces = addFace(faces, xInt, yInt, zInt, textX, textY, textZ);
            }
        }
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glColor3f(.0f, .0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.0f, yDist, zDist);  
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        glRotatef(xRot, 1.0f, 0.0f, 0.0f); 
        glColor3f(.0f, .0f, 1.0f);
        //glTranslatef(0.0f, 0.0f, zDist);  
        Face *p = faces;
        Vec3 *vertice;
        Vec2 *textures;
        while(p!=NULL){
            glBegin(GL_TRIANGLES);
                vertice = getVertice3(v3, p->x);
                textures = getVertice2(v2, p->textX);
                glTexCoord2f(textures->x, textures->y);
                glVertex3f(vertice->x, vertice->y, vertice->z);

                vertice = getVertice3(v3, p->y);
                textures = getVertice2(v2, p->textY);
                glTexCoord2f(textures->x, textures->y);
                glVertex3f(vertice->x, vertice->y, vertice->z);
                
                vertice = getVertice3(v3, p->z);
                textures = getVertice2(v2, p->textZ);
                glTexCoord2f(textures->x, textures->y);
                glVertex3f(vertice->x, vertice->y, vertice->z);
            glEnd();
            p=p->prox;
        }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();  

}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    init();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Objeto");
    loadTexture();
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(SpecialKeys);
    glutDisplayFunc(desenharObj);
    SetupRC();
    glutMainLoop();

    return 0;
}
