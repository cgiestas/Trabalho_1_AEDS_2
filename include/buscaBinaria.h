// buscabinaria.h

#ifndef BUSCA_BINARIA_H
#define BUSCA_BINARIA_H

#include <stdio.h>
#include <stddef.h> // Para size_t
#include "componentes.h"
#include "buscaSequencial.h"

// Protótipo da função genérica de busca binária
void *buscaBinariaGenerica(int chave, FILE *in, FILE *log, int (*compara)(const void *elemento, int chave), size_t tamanho_struct);
TComp *buscaComputadorBinario(int chave, FILE *in, FILE *log);
TClie *buscaClienteBinario(int chave, FILE *in, FILE *log);
TLoca *buscaLocacaoBinaria(int chave, FILE *in, FILE *log);

#endif // BUSCA_BINARIA_H
