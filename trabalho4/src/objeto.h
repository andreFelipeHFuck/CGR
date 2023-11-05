// Bibliotecas padão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Opengl
#include <GL/glut.h>


typedef struct face
{
    GLfloat x, y, z;
    GLfloat textX, textY, textZ;
    struct face *prox;
}Face;

typedef struct vec3
{
    GLfloat x, y, z;
    struct vec3 *prox;
}Vec3;

typedef struct vec2{
    GLfloat x, y;
    struct vec2 *prox;
}Vec2;

typedef struct objeto
{
    Face *face;
    Vec2 *vec2;
    Vec3 *vec3;
    Vec3 *normal;
}Objeto;


Vec2 *criaVec2(GLfloat x, GLfloat y);
Vec3 *criaVec3(GLfloat x, GLfloat y, GLfloat z);
Face *criaFace(GLfloat x, GLfloat y, GLfloat z, GLfloat textX, GLfloat textY, GLfloat textZ);
Objeto *criaObjeto();
Vec2 *addVec2(Vec2 *lista, float x, float y);
Vec3 *addVec3(Vec3 *lista, float x, float y, float z);
Face *addFace(Face *lista, float x, float y, float z, float textX, float textY, float textZ);
Objeto *getObejeto(char *arq);
void printV2(Vec2 *lista);
void printV3(Vec3 *lista);
void printObj(Objeto *obj);
Vec3 *getVertice3(Vec3 *lista, int index);
Vec2 *getVertice2(Vec2 *lista, int index);