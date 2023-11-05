#include "vec3.h"

#define AMORTECIMENTO 0.01
#define TEMPO_ESCALONADO 0.5*0.5
#define LIMITE_INTERACAO 15

#define TRUE 1
#define FALSE 0

typedef struct particula
{
    int movel;

    GLfloat massa;

    Vec3 pos;
    Vec3 pos_antiga; 
    Vec3 aceleracao;
    Vec3 normal_acumulda;
}Particula;

typedef struct limitacao
{
    GLfloat distancia_descanso;
    Particula *p1, *p2;
}Limitacao;

typedef struct limitacoes
{
    int qtd;
    Limitacao *elem; // Elementos
}Limitacoes;

// Particula
Particula criaParticula(Vec3 pos);
void printParticula(Particula p);
Vec3 getPosParticula(Particula *p);
void setPosParticule(Particula *p, Vec3 v);
Vec3 getNormalParticula(Particula *p);
void setNormalParticula(Particula *p, Vec3 v);
void addNormalParticula(Particula *p, Vec3 normal);
void resetNormalParticula(Particula *p);
void addForcaParticula(Particula *p, Vec3 f);
void timeStepParticula(Particula *p);
void resetaAceleracaoParticula(Particula *p);
void desvioPosParticula(Particula *p, Vec3 v);
void imovelParticula(Particula *p);

// Limitacao
Limitacao criaLimitacao(Particula *p1, Particula *p2);
Particula* getP1Limitacao(Limitacao *l);
void setP1Limitacao(Limitacao *l, Particula *p1);
Particula* getP2Limitacao(Limitacao *l);
void setP2Limitacao(Limitacao *l, Particula *p2);
void satisfazRestricao(Limitacao *l);

// Limitações 
Limitacoes *criaLimitacoes();
void addLimitacoa(Limitacoes *limitacoes, Limitacao limitacao);
Limitacoes *destroiLimitacoes(Limitacoes *l);