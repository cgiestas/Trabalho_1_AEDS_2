#include "buscaBinaria.h"
#include "buscaSequencial.h"
#include "componentes.h"
#include <stdlib.h>     
#include <string.h>     

// Implementação da busca binária genérica
void *buscaBinariaGenerica(int chave, FILE *in, FILE *log,
                           int (*compara)(const void *elemento, int chave),
                           size_t tamanho_struct) {
    if (in == NULL) {
        fprintf(log, "Erro: Arquivo de entrada nulo na busca binaria.\n");
        return NULL;
    }

    void *elemento = malloc(tamanho_struct);
    if (elemento == NULL) {
        fprintf(log, "Erro de alocacao de memoria na busca binaria.\n");
        return NULL;
    }

    fseek(in, 0, SEEK_END);
    long tamanho_arquivo = ftell(in);
    long num_registros = tamanho_arquivo / tamanho_struct;

    long esquerda = 0;
    long direita = num_registros - 1;
    long meio;

    fprintf(log, "Iniciando busca binaria por chave %d. Total de registros: %ld\n", chave, num_registros);

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;

        fseek(in, meio * tamanho_struct, SEEK_SET);

        if (fread(elemento, tamanho_struct, 1, in) != 1) {
            fprintf(log, "Erro de leitura no arquivo durante busca binaria.\n");
            free(elemento);
            return NULL;
        }

        int resultado_comparacao = compara(elemento, chave);

        if (resultado_comparacao == 0) {
            fprintf(log, "Elemento com chave %d encontrado na posicao %ld.\n", chave, meio);
            return elemento;
        } else if (resultado_comparacao < 0) {
            esquerda = meio + 1;
            fprintf(log, "Chave %d maior que elemento em %ld. Nova faixa: [%ld, %ld]\n", chave, meio, esquerda, direita);
        } else {
            direita = meio - 1;
            fprintf(log, "Chave %d menor que elemento em %ld. Nova faixa: [%ld, %ld]\n", chave, meio, esquerda, direita);
        }
    }

    fprintf(log, "Elemento com chave %d nao encontrado.\n", chave);
    free(elemento);
    return NULL;
}

// Funções auxiliares de busca específicas que a main vai chamar
TComp *buscaComputadorBinario(int chave, FILE *in, FILE *log) {
    return (TComp *)buscaBinariaGenerica(chave, in, log, comparaTComp, sizeof(TComp));
}

TClie *buscaClienteBinario(int chave, FILE *in, FILE *log) {
    return (TClie *)buscaBinariaGenerica(chave, in, log, comparaTClie, sizeof(TClie));
}

TLoca *buscaLocacaoBinaria(int chave, FILE *in, FILE *log) {
    return (TLoca *)buscaBinariaGenerica(chave, in, log, comparaTLoca, sizeof(TLoca));
}