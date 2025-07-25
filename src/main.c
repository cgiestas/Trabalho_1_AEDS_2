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
                FILE *f_comp = fopen("computadores.dat", "rb");
                FILE *f_clie = fopen("clientes.dat", "rb");
                FILE *f_loca = fopen("locacoes.dat", "rb");
                FILE *log = fopen("log.txt", "a");

                menuBuscaBinaria(f_comp, f_clie, f_loca, log);

                fclose(f_comp);
                fclose(f_clie);
                fclose(f_loca);
                fclose(log);
            }
            else
            {
                printf("\nERRO: Os dados precisam ser ordenados primeiro!\n");
                printf("Por favor, execute a Opcao 7 antes de tentar uma busca binaria.\n");
            }
            break;
        }
        case 7:
            int tam_bloco = 100; //tamanho máximo de indices de cada bloco na ram
            merge_externo_comp("computadores.dat", tam_bloco);
            merge_externo_clie("clientes.dat", tam_bloco);
            merge_externo_loca("locacoes.dat", tam_bloco);
            // reabre os arquivos para leitura após ordenação 
            FILE *computadores = fopen("computadores.dat", "rb");
            FILE *clientes = fopen("clientes.dat", "rb");
            FILE *locacoes = fopen("locacoes.dat", "rb");

            imprimirBase(computadores, 1);
            imprimirBase(clientes, 2);
            imprimirBase(locacoes, 3);

            fclose(computadores);
            fclose(clientes);
            fclose(locacoes);
            dados_ordenados = 1; //marca que os dados agora estão ordenados
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