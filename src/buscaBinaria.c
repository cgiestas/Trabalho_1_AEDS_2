#include "buscaBinaria.h"
#include "buscaSequencial.h"
#include "componentes.h"
#include <stdlib.h>
#include <string.h> 

void *buscaBinariaGenerica(void *vetor,long num_registros,size_t tamanho_struct, int chave, int (*compara)(const void *elemento, int chave), FILE *log) {
    if (vetor == NULL) {
        fprintf(log, "Erro: Vetor de entrada nulo na busca binaria.\n");
        return NULL;
    }

    long esquerda = 0;
    long direita = num_registros - 1;
    long meio;

    fprintf(log, "Iniciando busca binaria por chave %d. Total de registros: %ld\n", chave, num_registros);

    while (esquerda <= direita) {
        meio = esquerda + (direita - esquerda) / 2;
        void *elemento_meio = (char *)vetor + (meio * tamanho_struct);

        int resultado_comparacao = compara(elemento_meio, chave);

        if (resultado_comparacao == 0) {
            fprintf(log, "Elemento com chave %d encontrado na posicao %ld.\n", chave, meio);
            return elemento_meio;
        } else if (resultado_comparacao < 0) {
            esquerda = meio + 1;
            fprintf(log, "Chave %d maior que elemento em %ld. Nova faixa: [%ld, %ld]\n", chave, meio, esquerda, direita);
        } else {
            direita = meio - 1;
            fprintf(log, "Chave %d menor que elemento em %ld. Nova faixa: [%ld, %ld]\n", chave, meio, esquerda, direita);
        }
    }

    fprintf(log, "Elemento com chave %d nao encontrado.\n", chave);
    return NULL;
}

TComp *buscaComputadorBinario(TComp *vetor_comp, int qtd_comp, int chave, FILE *log) {
    return (TComp *)buscaBinariaGenerica(vetor_comp, qtd_comp, sizeof(TComp), chave, comparaTComp, log);
}

TClie *buscaClienteBinario(TClie *vetor_clie, int qtd_clie, int chave, FILE *log) {
    return (TClie *)buscaBinariaGenerica(vetor_clie, qtd_clie, sizeof(TClie), chave, comparaTClie, log);
}

TLoca *buscaLocacaoBinaria(TLoca *vetor_loca, int qtd_loca, int chave, FILE *log) {
    return (TLoca *)buscaBinariaGenerica(vetor_loca, qtd_loca, sizeof(TLoca), chave, comparaTLoca, log);
}