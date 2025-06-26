#ifndef INTERACOES_H
#define INTERACOES_H

#include <stdio.h>
#include "componentes.h"

TComp *carregaComp(FILE *arquivo, int *qtd);
TClie *carregaClie(FILE *arquivo, int *qtd);
TLoca *carregaLoca(FILE *arquivo, int *qtd);

#endif