#include "particula.h"

// Particula
Particula criaParticula(Vec3 pos){
    Particula novo;

    novo.pos = pos;
    novo.pos_antiga = pos;
    novo.aceleracao = criaVec3(0, 0, 0);
    novo.massa = 1;
    novo.movel = TRUE;
    novo.normal_acumulda = criaVec3(0, 0 , 0);

    return novo;
}

void printParticula(Particula p){
    printf("Pos: ");
    printVec3(p.pos);

    // printf("\nPos antiga: ");
    // printVec3(p.pos_antiga);

    // printf("\nAceleração: ");
    // printVec3(p.aceleracao);

    // printf("\nMassa: %f", p.massa);

    // printf("\nMovel: %d", p.movel);

    // printf("\nNormal acumulada: ");
    // printVec3(p.normal_acumulda);

    // printf("\n");
}

Vec3 getPosParticula(Particula *p){
    return p->pos;
}

void setPosParticule(Particula *p, Vec3 v){
    p->pos = v;
}


Vec3 getNormalParticula(Particula *p){
    return p->normal_acumulda;
}

void setNormalParticula(Particula *p, Vec3 v){
    p->normal_acumulda = v;
}

void addNormalParticula(Particula *p, Vec3 normal){
    somaIgualVec3(&p->normal_acumulda, normalizar(normal));
}

void resetNormalParticula(Particula *p){
    p->normal_acumulda = criaVec3(0, 0, 0);
}

void addForcaParticula(Particula *p, Vec3 f){
    somaIgualVec3(&p->aceleracao, divisaoVec3(f, p->massa));
}

void timeStepParticula(Particula *p){
    if(p->movel){
        Vec3 temp = p->pos;
        p->pos = somaVec3(
                    somaVec3(p->pos, 
                                multiplicacaoVec3(
                                        subtracaoVec3(p->pos, p->pos_antiga), 
                                        1.0 - AMORTECIMENTO
                                    )
                                    
                            ),
                    multiplicacaoVec3(p->aceleracao, TEMPO_ESCALONADO)
                );
        p->pos_antiga = temp;
        p->aceleracao = criaVec3(0, 0, 0);
        
    }
}

void resetaAceleracaoParticula(Particula *p){
    p->aceleracao = criaVec3(0, 0, 0);
}

void desvioPosParticula(Particula *p, Vec3 v){
    if(p->movel)
        somaIgualVec3(&p->pos, v);
}

void imovelParticula(Particula *p){
    p->movel = FALSE;
}

// Limitacao
Limitacao criaLimitacao(Particula *p1, Particula *p2){
    Limitacao novo;
    novo.p1 = p1;
    novo.p2 = p2;

    Vec3 vec = subtracaoVec3(getPosParticula(p1), getPosParticula(p2));
    novo.distancia_descanso = comprimento(vec);

}

Particula* getP1Limitacao(Limitacao *l){
    return l->p1;
}
void setP1Limitacao(Limitacao *l, Particula *p1){
    l->p1 = p1;
}

Particula* getP2Limitacao(Limitacao *l){
    return l->p2;
}

void setP2Limitacao(Limitacao *l, Particula *p2){
    l->p2;
}

void satisfazRestricao(Limitacao *l){
    Vec3 p1_para_p2 = subtracaoVec3(getPosParticula(l->p2), getPosParticula(l->p1));
    GLfloat distancia_atual = comprimento(p1_para_p2);
    Vec3 vetorDeCorrecao = multiplicacaoVec3(p1_para_p2, (1 - l->distancia_descanso/distancia_atual));
    Vec3 vetorDeCorrecaoMetade = multiplicacaoVec3(vetorDeCorrecao, 0.5);
    desvioPosParticula(l->p1, vetorDeCorrecaoMetade);
    desvioPosParticula(l->p2, inverteSinalVec3(vetorDeCorrecaoMetade));
}

// Limitacoes
Limitacoes *criaLimitacoes(){
    Limitacoes *novo;
    novo = (Limitacoes*) malloc(sizeof(Limitacoes));
    
    novo->qtd = 0;
    novo->elem = NULL;
}

void addLimitacoa(Limitacoes *limitacoes, Limitacao limitacao){
    limitacoes->elem = (Limitacao *) realloc(limitacoes->elem,
                        (limitacoes->qtd + 1) * sizeof(Limitacao));
    limitacoes->qtd++;
    limitacoes->elem[limitacoes->qtd - 1] = limitacao;
}

Limitacoes *destroiLimitacoes(Limitacoes *l){
    free(l->elem);
    free(l);
    return NULL;
}

// int main(){
//     Vec3 pos = criaVec3(1, 2, 3);
//     Particula p = criaParticula(pos);

//     printParticula(p);

//     addForcaParticula(&p, criaVec3(1, 2, 3));

//     printParticula(p);

//     timeStepParticula(&p);
//     printParticula(p);

// }
