#include "interacoes.h"
#include "componentes.h"
#include "buscaSequencial.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Locar computador, finalizar locação, lista de computadores e locações feitas por cliente

TComp *carregaComp(FILE *arquivo, int *qtd) {
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell(arquivo);
    *qtd = tamanho / sizeof(TComp);
    rewind(arquivo);

    if (*qtd == 0) return NULL;

    TComp *vetor = malloc(tamanho);
    if (!vetor) {
        printf("Erro ao alocar memoria!!!!!\n");
        exit(1);
    }

    fread(vetor, sizeof(TComp), *qtd, arquivo);
    return vetor;
}

TClie *carregaClie(FILE *arquivo, int *qtd){
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell (arquivo);
    *qtd = tamanho /sizeof(TClie);
    rewind(arquivo);

    if(*qtd == 0) return NULL;

    TClie *vetor = malloc(tamanho);
    if(!vetor){
        printf("Erro ao alocar memoria!!!!!");
        exit(1);
    }

    fread(vetor, sizeof(TClie), *qtd, arquivo);
    return vetor;
}

TLoca*carregaLoca(FILE *arquivo, int *qtd){
    fseek(arquivo, 0, SEEK_END);
    long tamanho = ftell (arquivo);
    *qtd = tamanho /sizeof(TLoca);
    rewind(arquivo);

    if(*qtd == 0) return NULL;

    TLoca *vetor = malloc(tamanho);
    if(!vetor){
        printf("Erro ao alocar memoria!!!!!");
        exit(1);
    }

    fread(vetor, sizeof(TLoca), *qtd, arquivo);
    return vetor;
}

