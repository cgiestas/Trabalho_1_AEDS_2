#ifndef INTERACOES_H
#define INTERACOES_H

#include <stdio.h>
#include "componentes.h"

TComp *carregaComp(FILE *arquivo, int *qtd);
TClie *carregaClie(FILE *arquivo, int *qtd);
TLoca *carregaLoca(FILE *arquivo, int *qtd);

void alugarComputador(FILE *f_comp, FILE *f_clie, FILE *f_loca, FILE *f_log, int cod_clie, int cod_comp, int quantidade, const char *data_inicial, const char *data_final);

void exibirMenu();
void realizarLocacaoUI(FILE *f_comp, FILE *f_clie, FILE *f_loca, FILE *f_log);
void finalizarLocacaoUI(FILE *f_comp, FILE *f_loca, FILE *f_log);
void visualizarLocacoesClienteUI(FILE *f_loca, FILE *f_log);
void menuBuscaSequencial(FILE *f_comp, FILE *f_clie, FILE *f_loca, FILE *f_log);
void menuBuscaBinaria(TComp *vetor_comp, int qtd_comp, TClie *vetor_clie, int qtd_clie, TLoca *vetor_loca, int qtd_loca, FILE *log);

#endif