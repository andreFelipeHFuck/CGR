#include "objeto.h"

Vec2 *criaVec2(GLfloat x, GLfloat y){
    Vec2 *novo = (Vec2*) malloc(sizeof(Vec2));

    novo->x = x;
    novo->y = y;
    novo->prox = NULL;

    return novo;
}

Vec3 *criaVec3(GLfloat x, GLfloat y, GLfloat z){
    Vec3 *novo = (Vec3*) malloc(sizeof(Vec3));

    novo->x = x;
    novo->y = y;
    novo->z = z;
    novo->prox = NULL;

    return novo;
}

Face *criaFace(GLfloat x, GLfloat y, GLfloat z, GLfloat textX, GLfloat textY, GLfloat textZ){
    Face *novo = (Face*) malloc(sizeof(Face));

    novo->x = x;
    novo->y = y;
    novo->z = z;
    novo->textX = textX;
    novo->textY = textY;
    novo->textZ = textZ;
    novo->prox = NULL;

    return novo;
}

Objeto *criaObjeto(){
    Objeto *novo = (Objeto*) malloc(sizeof(Objeto));

    novo->face = (Face*) malloc(sizeof(Face));
    novo->vec2 = (Vec2*) malloc(sizeof(Vec2));
    novo->vec3 = (Vec3*) malloc(sizeof(Vec3));
    novo->normal = (Vec3*) malloc(sizeof(Vec3));

    return novo;
}

Vec2 *addVec2(Vec2 *lista, float x, float y){
    Vec2 *p = lista;
    Vec2 *novo = criaVec2(x, y);

    if(p == NULL){
        return novo;
    }

    while(p->prox != NULL){
        p = p->prox;
    }
    p->prox = novo;
    return lista;
}

Vec3 *addVec3(Vec3 *lista, float x, float y, float z){
    Vec3 *p = lista;
    Vec3 *novo = criaVec3(x, y, z);

    if(p == NULL){
        return novo;
    }

    while(p->prox != NULL){
        p = p->prox;
    }
    p->prox = novo;
    return lista;
}

Face *addFace(Face *lista, float x, float y, float z, float textX, float textY, float textZ){
    Face *p = lista;
    Face *novo = criaFace(x, y, z, textX, textY, textZ);

    if(p == NULL){
        return novo;
    }

    while(p->prox != NULL){
        p = p->prox;
    }
    p->prox = novo;
    return lista;
}

Objeto *leituraObjeto(FILE *file){
    Objeto *obj = criaObjeto();

    float x, y, z;
    int trash, xInt, yInt, zInt, temVt = 0, temVn = 0;
    int textX=0, textY=0, textZ=0;

    while (1)
    {
        char lineHeader[128];

        int res = fscanf(file, "%s", lineHeader);
        if(res == EOF)
            break;

        if ( strcmp( lineHeader, "v" ) == 0 ){
            fscanf(file, "%f %f %f\n", &x, &y, &z );
            obj->vec3 = addVec3(obj->vec3, x, y, z);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            fscanf(file, "%f %f\n", &x, &y );
            obj->vec2 = addVec2(obj->vec2, x, y);
            temVt = 1;
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
            fscanf(file, "%f %f %f\n", &x, &y, &z );
            obj->normal = addVec3(obj->normal, x, y, z);
            temVn = 1;
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            if(temVt == 1 && temVn == 1){
                fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &xInt, &textX, &trash, &yInt, &textY, &trash, &zInt, &textZ, &trash);
                obj->face = addFace(obj->face, xInt, yInt, zInt, textX, textY, textZ);
            }else if(temVt == 1 && temVn == 0 || temVt == 0 && temVn == 1){
                fscanf(file, "%d/%d/%d %d/%d/%d\n", &xInt, &textX, &yInt, &textY, &zInt, &textZ);
                obj->face = addFace(obj->face, xInt, yInt, zInt, textX, textY, textZ);
            }else {
                fscanf(file, "%d/%d/%d\n", &xInt, &yInt, &zInt);
                obj->face = addFace(obj->face, xInt, yInt, zInt, textX, textY, textZ);
            }
        }
    }

    return obj;
    
}

Objeto *getObejeto(char *arq){

    FILE *file = fopen(arq, "r");
    if(file == NULL){
        printf("Erro ao abrir o arquivo! \n");
        return NULL;
    }

    return leituraObjeto(file);
}

void printV2(Vec2 *lista){
    Vec2 *p = lista;
    while(p != NULL){
        printf("%.6f, %.6f\n", p->x, p->y);
        p = p->prox;
    }
}

void printV3(Vec3 *lista){
    Vec3 *p = lista;
    while(p != NULL){
        printf("%.6f, %.6f, %.6f\n", p->x, p->y, p->z);
        p = p->prox;
    }
}

void printObj(Objeto *obj){
    printf("Vertices\n");
    printV3(obj->vec3);
    printf("Vertices Normal\n");
    printV2(obj->vec2);
}

Vec3 *getVertice3(Vec3 *lista, int index){
    Vec3 *p = lista;
    for(int i = 1; i < index; i++){
        p = p->prox;
    }
    return p;
}

Vec2 *getVertice2(Vec2 *lista, int index) {
    Vec2 *p = lista;
    for(int i = 1; i < index; i++) {
        p = p->prox;
    }
    return p;
}

// int main(){
//     char *arq = "../assets/cube.obj";
//     Objeto *obj = getObejeto(arq);

//     printObj(obj);
// }