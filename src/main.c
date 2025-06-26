#include "buscaBinaria.h"
#include "buscaSequencial.h"
#include "componentes.h"
#include "merge.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <interacoes.h>

int main()
{
    FILE *computadores;
    FILE *clientes;
    FILE *locacoes;
    FILE *log;

    if ((log = fopen("log.txt", "a+")) == NULL)
    {
        printf("Erro ao abrir arquivo log\n");
        exit(1);
    }

    if ((computadores = fopen("computadores.dat", "w+b")) == NULL ||
        (locacoes = fopen("locacoes.dat", "w+b")) == NULL || // Adicionado parênteses para a atribuição
        (clientes = fopen("clientes.dat", "w+b")) == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else
    {

        criarBase(computadores, 5, 1);
        rewind(computadores);
        imprimirBase(computadores, 1);

        criarBase(clientes, 5, 2);
        rewind(clientes);
        imprimirBase(clientes, 2);

        criarBase(locacoes, 5, 3);
        rewind(locacoes);
        imprimirBase(locacoes, 3);
    }

    int qtd_comp;
    int qtd_clie;
    int qtd_loca;

    TComp *comp = carregaComp(computadores, &qtd_comp);
    TClie *clie = carregaClie(clientes, &qtd_clie);
    TLoca *loca = carregaLoca(locacoes, &qtd_loca);

    //---- Busca Sequencial ----
    // Exemplo de busca por um computador
    int chave_comp = 4;
    TComp *computador_encontrado = (TComp *)buscaSequencialGenerica(
        chave_comp, computadores, log, comparaTComp, sizeof(TComp));

    if (computador_encontrado != NULL)
    {
        printf("Computador encontrado: ID %d, Marca %s, Modelo %s, Processador %s, Valor %f, Disponível %d\n", computador_encontrado->cod, computador_encontrado->marca, computador_encontrado->modelo, computador_encontrado->processador, computador_encontrado->valor, computador_encontrado->disponivel);
        free(computador_encontrado);
    }
    else
    {
        printf("Computador com ID %d nao encontrado.\n", chave_comp);
    }

    // Exemplo de busca por um cliente
    int chave_clie = 3;
    TClie *cliente_encontrado = (TClie *)buscaSequencialGenerica(
        chave_clie, clientes, log, comparaTClie, sizeof(TClie));

    if (cliente_encontrado != NULL)
    {
        printf("Cliente encontrado: ID %d, Nome %s, CNPJ/CPF %s, Telefone %d, Email %s\n", cliente_encontrado->cod, cliente_encontrado->nome, cliente_encontrado->cpf_cnpj, cliente_encontrado->telefone, cliente_encontrado->email);
        free(cliente_encontrado);
    }
    else
    {
        printf("Cliente com ID %d nao encontrado.\n", chave_clie);
    }

    // Exemplo de busca por uma locação
    int chave_loca = 2; // ID da locação que você quer buscar
    TLoca *locacao_encontrada = (TLoca *)buscaSequencialGenerica(
        chave_loca, locacoes, log, comparaTLoca, sizeof(TLoca));

    if (locacao_encontrada != NULL)
    {
        printf("Locacao encontrada: ID %d, com data de inicio %s e data de fim %s, e ativa %d\n", locacao_encontrada->cod, locacao_encontrada->data_inicial, locacao_encontrada->data_final, locacao_encontrada->ativa);
        // 1. Buscar o Cliente
        int id_cliente_da_locacao = locacao_encontrada->cod_clie;
        TClie *cliente_da_locacao = (TClie *)buscaSequencialGenerica(
            id_cliente_da_locacao, clientes, log, comparaTClie, sizeof(TClie));

        if (cliente_da_locacao != NULL)
        {
            printf("Cliente: ID %d, Nome: %s\n", cliente_da_locacao->cod, cliente_da_locacao->nome);
            free(cliente_da_locacao); // Lembre-se de liberar a memória
        }
        else
        {
            printf("Cliente com ID %d nao encontrado para esta locacao.\n", id_cliente_da_locacao);
        }

        // 2. Buscar o Computador
        int id_computador_da_locacao = locacao_encontrada->cod_comp;
        TComp *computador_da_locacao = (TComp *)buscaSequencialGenerica(
            id_computador_da_locacao, computadores, log, comparaTComp, sizeof(TComp));

        if (computador_da_locacao != NULL)
        {
            // Supondo que Tcomp tenha campos para marca e modelo
            printf(" Computador: ID %d, Marca: %s, Modelo: %s, Processador: %s, Valor Unitario: %f, Quantidade Locada: %d, Valor Total Locacao: %f\n", computador_da_locacao->cod, computador_da_locacao->marca, computador_da_locacao->modelo, computador_da_locacao->processador, computador_da_locacao->valor, locacao_encontrada->quantidade, locacao_encontrada->valor_total);
            free(computador_da_locacao); // libera a memoria
        }
        else
        {
            printf(" Computador com ID %d nao encontrado para esta locacao.\n", id_computador_da_locacao);
        }

        free(locacao_encontrada); // Lembre-se de liberar a memória da locação
    }
    else
    {
        printf("Locacao com ID %d nao encontrada.\n", chave_loca);
    }

    // chamando a função de ordenção
    mergesort(comp, qtd_comp, sizeof(TComp), compara_comp);
    mergesort(clie, qtd_clie, sizeof(TClie), compara_clie);
    mergesort(loca, qtd_loca, sizeof(TLoca), compara_loca);

    printf("\n=== COMPUTADORES ORDENADOS ===\n");
    for (int i = 0; i < qtd_comp; i++) {
        imprimecomp(&comp[i]);
    }

    printf("\n=== CLIENTES ORDENADOS ===\n");
    for (int i = 0; i < qtd_clie; i++) {
        imprimeclie(&clie[i]);
    }

    printf("\n=== LOCAÇÕES ORDENADAS ===\n");
    for (int i = 0; i < qtd_loca; i++) {
        imprimeloca(&loca[i]);
    }


    //---Busca Binaria---
    // Exemplo de busca por um computador
    int chave_comp_bin = 2;
    TComp *computador_encontrado_bin = buscaComputadorBinario(chave_comp_bin, computadores, log);

    if (computador_encontrado_bin != NULL)
    {
        printf("Computador encontrado (Binaria): ID %d, Marca %s, Modelo %s, Processador %s, Valor unitario %f, disponivel %d\n", computador_encontrado_bin->cod, computador_encontrado_bin->marca,
               computador_encontrado_bin->modelo, computador_encontrado_bin->processador, computador_encontrado_bin->valor, computador_encontrado_bin->disponivel);
        free(computador_encontrado_bin);
    }
    else
    {
        printf("Computador com ID %d nao encontrado (Binaria).\n", chave_comp_bin);
    }

    printf("\n");

    // Exemplo de busca por uma locação, e depois buscando detalhes do cliente e computador
    int chave_loca_bin = 2;
    TLoca *locacao_encontrada_bin = buscaLocacaoBinaria(chave_loca_bin, locacoes, log);

    if (locacao_encontrada_bin != NULL)
    {
        printf("Locacao encontrada (Binaria): ID %d\n", locacao_encontrada_bin->cod);

        TClie *cliente_da_locacao = buscaClienteBinario(locacao_encontrada_bin->cod_clie, clientes, log);
        if (cliente_da_locacao != NULL)
        {
            printf("  Cliente: ID %d, Nome: %s\n", cliente_da_locacao->cod, cliente_da_locacao->nome);
            free(cliente_da_locacao);
        }
        else
        {
            printf("  Cliente com ID %d (associado a locacao) nao encontrado.\n", locacao_encontrada_bin->cod_clie);
        }

        TComp *computador_da_locacao = buscaComputadorBinario(locacao_encontrada_bin->cod_comp, computadores, log);
        if (computador_da_locacao != NULL)
        {
            printf("  Computador: ID %d, Marca: %s, Modelo: %s\n",
                   computador_da_locacao->cod,
                   computador_da_locacao->marca,
                   computador_da_locacao->modelo);
            free(computador_da_locacao);
        }
        else
        {
            printf("  Computador com ID %d (associado a locacao) nao encontrado.\n", locacao_encontrada_bin->cod_comp);
        }

        free(locacao_encontrada_bin);
    }
    else
    {
        printf("Locacao com ID %d nao encontrada (Binaria).\n", chave_loca_bin);
    }

    fclose(computadores);
    fclose(clientes);
    fclose(locacoes);
    fclose(log);

    return 0;
}