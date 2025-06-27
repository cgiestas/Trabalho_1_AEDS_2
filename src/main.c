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

    int opcao;
    int dados_ordenados = 0; //para saber se precisa ordenar

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                realizarLocacaoUI(computadores, clientes, locacoes, log);
                dados_ordenados = 0; // Modificou dados, precisa reordenar
                break;
            case 2:
                finalizarLocacaoUI(computadores, locacoes, log);
                dados_ordenados = 0; // Modificou dados, precisa reordenar
                break;
            case 3:
                visualizarLocacoesClienteUI(locacoes, log);
                break;
            case 4:
                menuBuscaSequencial(computadores, clientes, locacoes, log);
                break;
            case 5:
                if (dados_ordenados) {
                menuBuscaBinaria(computadores, clientes, locacoes, log);
                } else {
                    printf("\nERRO: Os dados precisam ser ordenados primeiro!\n");
                    printf("Por favor, execute a Opcao 6 antes de tentar uma busca binaria.\n");
                }
        break;
                break;
            case 6: {
                int qtd_comp, qtd_clie, qtd_loca;
                
                // Carrega os dados dos arquivos para a memória
                TComp *comp = carregaComp(computadores, &qtd_comp);
                TClie *clie = carregaClie(clientes, &qtd_clie);
                TLoca *loca = carregaLoca(locacoes, &qtd_loca);

                // Ordena os vetores em memória
                // chamando a função de ordenção
                mergesort(comp, qtd_comp, sizeof(TComp), compara_comp);
                mergesort(clie, qtd_clie, sizeof(TClie), compara_clie);
                mergesort(loca, qtd_loca, sizeof(TLoca), compara_loca);

                // Reescreve os arquivos com os dados ordenados
                freopen("computadores.dat", "w+b", computadores);
                for(int i = 0; i < qtd_comp; i++) salvacomp(&comp[i], computadores);
                
                freopen("clientes.dat", "w+b", clientes);
                for(int i = 0; i < qtd_clie; i++) salvaclie(&clie[i], clientes);

                freopen("locacoes.dat", "w+b", locacoes);
                for(int i = 0; i < qtd_loca; i++) salvaloca(&loca[i], locacoes);

                printf("\n--- DADOS ORDENADOS ---\n");
                printf("\n--- COMPUTADORES ORDENADOS ---\n");
                imprimirBase(computadores, 1);
                printf("\n--- CLIENTES ORDENADOS ---\n");
                imprimirBase(clientes, 2);
                printf("\n--- LOCACOES ORDENADAS ---\n");
                imprimirBase(locacoes, 3);
                
                dados_ordenados = 1; // Marca que os dados agora estão ordenados

                // Libera a memória dos vetores
                free(comp);
                free(clie);
                free(loca);
                break;
            }
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0);


    // printf("\n=== COMPUTADORES ORDENADOS ===\n");
    // for (int i = 0; i < qtd_comp; i++) {
    //     imprimecomp(&comp[i]);
    // }

    // printf("\n=== CLIENTES ORDENADOS ===\n");
    // for (int i = 0; i < qtd_clie; i++) {
    //     imprimeclie(&clie[i]);
    // }

    // printf("\n=== LOCACOES ORDENADAS ===\n");
    // for (int i = 0; i < qtd_loca; i++) {
    //     imprimeloca(&loca[i]);
    // }

    fclose(computadores);
    fclose(clientes);
    fclose(locacoes);
    fclose(log);

    return 0;
}