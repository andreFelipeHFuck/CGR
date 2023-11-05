#include "vec3.h"

// Vec3
Vec3 criaVec3(GLfloat x, GLfloat y, GLfloat z){
    Vec3  novo;
    novo.x = x;
    novo.y = y;
    novo.z = z;

    return novo;
}

void printVec3(Vec3 v){
    printf("%f, %f, %f\n",
        v.x,
        v.y,
        v.z
    );
}

GLfloat comprimento(Vec3 v){
   return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

Vec3 normalizar(Vec3 v){
    GLfloat l = comprimento(v);
    return criaVec3(
        v.x/l,
        v.y/l,
        v.z/l
    );
}

void somaIgualVec3(Vec3 *v1, Vec3 v2){
    v1->x += v2.x;
    v1->y += v2.y;
    v1->z += v2.z;
}

Vec3 divisaoVec3(Vec3 v, GLfloat a){
    return criaVec3(
        v.x/a,
        v.y/a,
        v.z/a
    );
}

Vec3 subtracaoVec3(Vec3 v1, Vec3 v2){
    return criaVec3(
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z
    );
}

Vec3 somaVec3(Vec3 v1, Vec3 v2){
     return criaVec3(
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z
    );
}

Vec3 multiplicacaoVec3(Vec3 v, GLfloat a){
     return criaVec3(
        v.x*a,
        v.y*a,
        v.z*a
    );
}

Vec3 inverteSinalVec3(Vec3 v){
    return criaVec3(
        -v.x,
        -v.y,
        -v.z
    );
}

Vec3 produtoCruzadoVec3(Vec3 v1, Vec3 v2){
    return criaVec3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

GLfloat pontoVec3(Vec3 v1, Vec3 v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

// int main(){
//     Vec3 v1 = criaVec3(1, 2, 3);
//     Vec3 v2 = criaVec3(1, 2, 3);

//     printVec3(v1);
//     printVec3(v2);
//     printf("%f\n", comprimento(v1));
//     printVec3(normalizar(v1));

//     somaIgualVec3(&v1, v2);
//     printVec3(v1);

//     printVec3(divisaoVec3(v1, 2.0));

//     printVec3(subtracaoVec3(v1, v2));
//     printVec3(multiplicacaoVec3(v1, 2));

//     printVec3(inverteSinalVec3(v1));

//     printVec3(produtoCruzadoVec3(v1, v2));

//     printf("%f\n", pontoVec3(v1, v2));


//     return 0;
// }