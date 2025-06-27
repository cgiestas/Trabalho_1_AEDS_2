// buscabinaria.h

#ifndef BUSCA_BINARIA_H
#define BUSCA_BINARIA_H

#include <stdio.h>
#include <stddef.h>
#include "componentes.h"
#include "buscaSequencial.h"

void *buscaBinariaGenerica(void *vetor, long num_registros, size_t tamanho_struct, int chave, int (*compara)(const void *elemento, int chave), FILE *log);

TComp *buscaComputadorBinario(TComp *vetor_comp, int qtd_comp, int chave, FILE *log);
TClie *buscaClienteBinario(TClie *vetor_clie, int qtd_clie, int chave, FILE *log);
TLoca *buscaLocacaoBinaria(TLoca *vetor_loca, int qtd_loca, int chave, FILE *log);

#endif // BUSCA_BINARIA_H