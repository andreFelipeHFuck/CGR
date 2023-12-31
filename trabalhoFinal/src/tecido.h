#include "particula.h"
#include "formas.h"

typedef struct tecido
{
    int num_particulas;
    int num_particulas_largura;
    int num_particulas_comprimento;
    Particula *particulas;
    Limitacoes *limitacoes;
}Tecido;

Tecido *criaTecido(GLfloat width, GLfloat height,  int num_particulas_largura, int num_particulas_comprimento);
Particula* getParticula(Tecido *t, int x, int y);
void addLimitacaoTecido(Tecido *t, Particula *p1, Particula *p2);
void printTecido(Tecido *t);
Vec3 calTrianguloNormal(Particula *p1, Particula *p2, Particula *p3);
void addForcasDoVentoPorTriangulo(Particula *p1, Particula *p2, Particula *p3, Vec3 direcao);
void timeStepTecido(Tecido *t);
void addForcaTecido(Tecido *t, Vec3 direcao);
void forcaVentoTecido(Tecido *t, Vec3 direcao);
void desenhaTrianguloTecido(Particula *p1, Particula *p2, Particula *p3, Color color);
void colisaoBolaTecido(Tecido *t, Vec3 center, GLfloat radius);
void desenhaShadedTecido(Tecido *t);


