#include "tecido.h"

Tecido *criaTecido(GLfloat largura, GLfloat comprimento,  int num_particulas_largura, int num_particulas_comprimento){
    Tecido *novo = (Tecido*) malloc(sizeof(Tecido));
    novo->num_particulas = num_particulas_comprimento*num_particulas_largura;

    novo->num_particulas_largura = num_particulas_largura;
    novo->num_particulas_comprimento = num_particulas_comprimento;

    novo->particulas = (Particula*) malloc(novo->num_particulas * sizeof(Particula));

    for(int i=0; i<num_particulas_largura; i++){
        for(int j=0; j<num_particulas_comprimento; j++){
            Vec3 pos = criaVec3(
                largura * i/(GLfloat) num_particulas_largura,
                -comprimento * (j/(GLfloat)num_particulas_comprimento),
                0
            );
            novo->particulas[j * num_particulas_largura +i ] = criaParticula(pos);
        }
    }

    novo->limitacoes = criaLimitacoes();

    for(int i=0; i<num_particulas_largura; i++){
        for(int j=0; j<num_particulas_comprimento; j++){
            if(i < num_particulas_largura-1)
                addLimitacaoTecido(
                    novo,
                    getParticula(novo, i, j),
                    getParticula(novo, i+1, j)
                );
            if(j < num_particulas_comprimento-1){
                addLimitacaoTecido(
                    novo,
                    getParticula(novo, i, j),
                    getParticula(novo, i, j+1)
                );
            }
            if(i<num_particulas_largura-1 && j<num_particulas_comprimento-1){
                addLimitacaoTecido(
                    novo,
                    getParticula(novo, i, j),
                    getParticula(novo, i+1, j+1)
                );
            }
             if(i<num_particulas_largura-1 && j<num_particulas_comprimento-1){
                addLimitacaoTecido(
                    novo,
                    getParticula(novo, i+1, j),
                    getParticula(novo, i, j+1)
                );
            }
        }
    }

   for(int i=0; i<num_particulas_largura; i++){
        for(int j=0; j<num_particulas_comprimento; j++){
            if(i < num_particulas_largura-2)
                addLimitacaoTecido(
                    novo,
                    getParticula(novo, i, j),
                    getParticula(novo, i+2, j)
                );
            if(j < num_particulas_comprimento-2){
                addLimitacaoTecido(
                    novo,
                    getParticula(novo, i, j),
                    getParticula(novo, i, j+2)
                );
            }
            if(i<num_particulas_largura-2 && j<num_particulas_comprimento-2){
                addLimitacaoTecido(
                    novo,
                    getParticula(novo, i, j),
                    getParticula(novo, i+2, j+2)
                );
            }
             if(i<num_particulas_largura-2 && j<num_particulas_comprimento-2){
                addLimitacaoTecido(
                    novo,
                    getParticula(novo, i+2, j),
                    getParticula(novo, i, j+2)
                );
            }
        }
    }

    for(int i=0; i<3; i++){
        desvioPosParticula(getParticula(novo, 0+i, 0), criaVec3(-0.5, 0.0, 0.0));
        imovelParticula(getParticula(novo, 0+i, 0));

        desvioPosParticula(getParticula(novo, 0+i, 0), criaVec3(-0.5, 0.0, 0.0));
        imovelParticula(getParticula(novo, num_particulas_largura-1-i, 0));
    }

    return novo;
}

Particula* getParticula(Tecido *t, int x, int y){
    return &t->particulas[y * t->num_particulas_largura + x];
}

void addLimitacaoTecido(Tecido *t, Particula *p1, Particula *p2){
    addLimitacoa(t->limitacoes, criaLimitacao(p1, p2));
}

void printTecido(Tecido *t){
    for(int i=0; i<t->num_particulas_largura; i++){
        for(int j=0; j<t->num_particulas_comprimento; j++){
            printParticula(&t->particulas[j * t->num_particulas_largura + i]);
        }
    }
}

void addForcasDoVentoPorTriangulo(Particula *p1, Particula *p2, Particula *p3, Vec3 direcao){
    Vec3 normal = calTrianguloNormal(p1, p2, p3);
    Vec3 d = normalizar(normal);
    Vec3 forca = multiplicacaoVec3(normal, pontoVec3(d, direcao));
    addForcaParticula(p1, forca);
    addForcaParticula(p2, forca);
    addForcaParticula(p3, forca);
}

void timeStepTecido(Tecido *t){
    for(int i=0; i<LIMITE_INTERACAO; i++){
        for(int j=0; j< t->limitacoes->qtd; j++){    
            satisfazRestricao(&t->limitacoes->elem[j]);
        }
    }

    for(int i=0; i<t->num_particulas; i++){
        timeStepParticula(&t->particulas[i]);
    }
}

void addForcaTecido(Tecido *t, Vec3 direcao){
    for(int i=0; i<t->num_particulas; i++){
        addForcaParticula(&t->particulas[i], direcao);
    }
}

void forcaVentoTecido(Tecido *t, Vec3 direcao){
    printf("Força do Vento\n");
    for(int i=0; i<t->num_particulas_largura-1; i++){
        for(int j=0; j<t->num_particulas_comprimento; j++){
            addForcasDoVentoPorTriangulo(
                getParticula(t, i+1, j),
                getParticula(t, i, j),
                getParticula(t, i, j+1),
                direcao
            );
            
            addForcasDoVentoPorTriangulo(
                getParticula(t, i+1, j+1),
                getParticula(t, i+1, j),
                getParticula(t, i, j+1),
                direcao
            );
        }
    }
}

Vec3 calTrianguloNormal(Particula *p1, Particula *p2, Particula *p3){
    Vec3 pos1 = getPosParticula(p1);
    Vec3 pos2 = getPosParticula(p2);
    Vec3 pos3 = getPosParticula(p3);

    Vec3 v1 = subtracaoVec3(pos2, pos1);
    Vec3 v2 = subtracaoVec3(pos3, pos1);

    return produtoCruzadoVec3(v1, v2);
}

void desenhaTrianguloTecido(Particula *p1, Particula *p2, Particula *p3, Color color){
    glColor3f(color.r, color.g, color.b);
    
    Vec3 normalP1 = normalizar(getNormalParticula(p1));
    glNormal3f(normalP1.x, normalP1.y, normalP1.z);
    Vec3 posP1 = getPosParticula(p1);
    glVertex3f(posP1.x, posP1.y, posP1.z);

    Vec3 normalP2 = normalizar(getNormalParticula(p2));
    glNormal3f(normalP2.x, normalP2.y, normalP2.z);
    Vec3 posP2 = getPosParticula(p2);
    glVertex3f(posP2.x, posP2.y, posP2.z);


    Vec3 normalP3 = normalizar(getNormalParticula(p3));
    glNormal3f(normalP3.x, normalP3.y, normalP3.z);
    Vec3 posP3 = getPosParticula(p3);
    glVertex3f(posP3.x, posP3.y, posP3.z);

}

void resetaNormalTecido(Tecido *t){
    for(int i=0; i<t->num_particulas; i++)
      resetNormalParticula(&t->particulas[i]);
}

void colisaoBolaTecido(Tecido *t, Vec3 center, GLfloat radius){
    for(int i=0; i<t->num_particulas; i++){
        Vec3 v = subtracaoVec3(getPosParticula(&t->particulas[i]), center);
        float l = comprimento(v);
        if(comprimento(v) < radius)
            desvioPosParticula(&t->particulas[i], multiplicacaoVec3(normalizar(v), (radius-l)));
    }
}

void desenhaShadedTecido(Tecido *t){
    resetaNormalTecido(t);

    for(int i=0; i<t->num_particulas_largura-1; i++){
        for(int j=0; j<t->num_particulas_comprimento-1; j++){
            Vec3 normal = calTrianguloNormal(
                getParticula(t, i+1, j),
                getParticula(t, i, j),
                getParticula(t, i, j+1)
            );
            addNormalParticula(getParticula(t, i+1, j), normal);
            addNormalParticula(getParticula(t, i, j), normal);
            addNormalParticula(getParticula(t, i, j+1), normal);

            normal = calTrianguloNormal(
                getParticula(t, i+1, j+1),
                getParticula(t, i+1, j),
                getParticula(t, i, j+1)
            );
            addNormalParticula(getParticula(t, i+1, j+1), normal);
            addNormalParticula(getParticula(t, i+1, j), normal);
            addNormalParticula(getParticula(t, i, j+1), normal);
        }
    }

    glBegin(GL_TRIANGLES);
    for(int i=0; i<t->num_particulas_largura-1; i++){
        for(int j=0; j<t->num_particulas_comprimento-1; j++){
            Color color;
            color.r = 1;
            color.g = 0;
            color.b = 0;

            desenhaTrianguloTecido(
                getParticula(t, i+1, j),
                getParticula(t, i, j),
                getParticula(t, i, j+1),
                color
            );
            desenhaTrianguloTecido(
                getParticula(t, i+1, j+1),
                getParticula(t, i+1, j),
                getParticula(t, i, j+1),
                color               
            );
        }
    }
    glEnd();
}


int main(){
    Tecido *tecido = criaTecido(14, 10, 55, 45);

   while (1)
   {
    forcaVentoTecido(tecido, multiplicacaoVec3(criaVec3(0, -0.2, 0), TEMPO_ESCALONADO));
   }
   
   
}