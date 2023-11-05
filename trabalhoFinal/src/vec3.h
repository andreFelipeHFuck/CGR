//Bibliote padão
#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
#include <math.h>

// Biblioteca OpenGl
#include <GL/glut.h>

// Struct do vetor R3
typedef struct vec3
{
    GLfloat x, y, z;
}Vec3;

// Vec3
Vec3 criaVec3(GLfloat x, GLfloat y, GLfloat z);
void printVec3(Vec3 v);
GLfloat comprimento(Vec3 v);
Vec3 normalizar(Vec3 v);
void somaIgualVec3(Vec3 *v1, Vec3 v2);
Vec3 divisaoVec3(Vec3 v, GLfloat a);
Vec3 subtracaoVec3(Vec3 v1, Vec3 v2);
Vec3 somaVec3(Vec3 v1, Vec3 v2);
Vec3 multiplicacaoVec3(Vec3 v, GLfloat a);
Vec3 inverteSinalVec3(Vec3 v);
Vec3 produtoCruzadoVec3(Vec3 v1, Vec3 v2);
GLfloat pontoVec3(Vec3 v1, Vec3 v2);
