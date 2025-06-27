#include "buscaBinaria.h"
#include "buscaSequencial.h"
#include "componentes.h"
#include "interacoes.h"
#include "merge.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    FILE *computadores, *clientes, *locacoes, *log;

    if ((log = fopen("log.txt", "a+")) == NULL)
    {
        printf("Erro ao abrir arquivo log\n");
        exit(1);
    }

    if ((computadores = fopen("computadores.dat", "w+b")) == NULL ||
        (locacoes = fopen("locacoes.dat", "w+b")) == NULL ||
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

        // criarBase(locacoes, 5, 3);
        // rewind(locacoes);
        // imprimirBase(locacoes, 3);
    }

    int opcao;
    int dados_ordenados = 0;

    TComp *comp = NULL;
    TClie *clie = NULL;
    TLoca *loca = NULL;
    int qtd_comp = 0, qtd_clie = 0, qtd_loca = 0;

    do
    {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            realizarLocacaoUI(computadores, clientes, locacoes, log);
            dados_ordenados = 0;

            if (comp)
                free(comp);
            if (clie)
                free(clie);
            if (loca)
                free(loca);
            comp = NULL;
            clie = NULL;
            loca = NULL;
            break;

        case 2:
            finalizarLocacaoUI(computadores, locacoes, log);
            dados_ordenados = 0;

            if (comp)
                free(comp);
            if (clie)
                free(clie);
            if (loca)
                free(loca);
            comp = NULL;
            clie = NULL;
            loca = NULL;
            break;

        case 3:
            visualizarLocacoesClienteUI(locacoes, log);
            break;

        case 4:
            imprimirBase(computadores, 1);
            break;

        case 5:
            menuBuscaSequencial(computadores, clientes, locacoes, log);
            break;

        case 6:
        {
            if (dados_ordenados)
            {
                menuBuscaBinaria(comp, qtd_comp, clie, qtd_clie, loca, qtd_loca, log);
            }
            else
            {
                printf("\nERRO: Os dados precisam ser ordenados primeiro!\n");
                printf("Por favor, execute a Opcao 7 antes de tentar uma busca binaria.\n");
            }
            break;
        }
        case 7:
            if (comp)
                free(comp);
            if (clie)
                free(clie);
            if (loca)
                free(loca);

            // Carrega os dados dos arquivos para a memória
            comp = carregaComp(computadores, &qtd_comp);
            clie = carregaClie(clientes, &qtd_clie);
            loca = carregaLoca(locacoes, &qtd_loca);

            // Ordena os vetores em memória
            mergesort(comp, qtd_comp, sizeof(TComp), compara_comp);
            mergesort(clie, qtd_clie, sizeof(TClie), compara_clie);
            mergesort(loca, qtd_loca, sizeof(TLoca), compara_loca);

            // Reescreve os arquivos com os dados ordenados
            freopen("computadores.dat", "w+b", computadores);
            for (int i = 0; i < qtd_comp; i++)
                salvacomp(&comp[i], computadores);

            freopen("clientes.dat", "w+b", clientes);
            for (int i = 0; i < qtd_clie; i++)
                salvaclie(&clie[i], clientes);

            freopen("locacoes.dat", "w+b", locacoes);
            for (int i = 0; i < qtd_loca; i++)
                salvaloca(&loca[i], locacoes);

            printf("\n--- DADOS ORDENADOS ---\n");
            imprimirBase(computadores, 1);
            imprimirBase(clientes, 2);
            imprimirBase(locacoes, 3);

            dados_ordenados = 1; // Marca que os dados agora estão ordenados
            break;
        case 0:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
            break;
        }

    } while (opcao != 0);

    if (comp)
        free(comp);
    if (clie)
        free(clie);
    if (loca)
        free(loca);

    fclose(computadores);
    fclose(clientes);
    fclose(locacoes);
    fclose(log);

    return 0;
}