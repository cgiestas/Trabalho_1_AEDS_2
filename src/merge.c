#include <stdio.h>
#include "componentes.h"
#include <string.h>

// Função auxiliar "merge" para o mergesort
void merge(void *arr, void *temp, int inicio, int meio, int fim, size_t tamanho_elem, int (*comparar)(const void *, const void *)) {
    int i = inicio;
    int j = meio + 1;
    int k = inicio;
    char *arr_char = (char *)arr;
    char *temp_char = (char *)temp;

    // Copia para o array temporário
    memcpy(temp_char + inicio * tamanho_elem, arr_char + inicio * tamanho_elem, (fim - inicio + 1) * tamanho_elem);

    // Combina os dois subarrays de volta para o array original
    while (i <= meio && j <= fim) {
        if (comparar(temp_char + i * tamanho_elem, temp_char + j * tamanho_elem) <= 0) {
            memcpy(arr_char + k * tamanho_elem, temp_char + i * tamanho_elem, tamanho_elem);
            i++;
        } else {
            memcpy(arr_char + k * tamanho_elem, temp_char + j * tamanho_elem, tamanho_elem);
            j++;
        }
        k++;
    }

    // Copia os elementos restantes da primeira metade, se houver
    while (i <= meio) {
        memcpy(arr_char + k * tamanho_elem, temp_char + i * tamanho_elem, tamanho_elem);
        i++;
        k++;
    }

    // Copia os elementos restantes da segunda metade, se houver
    while (j <= fim) {
        memcpy(arr_char + k * tamanho_elem, temp_char + j * tamanho_elem, tamanho_elem);
        j++;
        k++;
    }
}

// Função mergesort recursiva
void mergesort_recursivo(void *arr, void *temp, int inicio, int fim, size_t tamanho_elem, int (*comparar)(const void *, const void *)) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergesort_recursivo(arr, temp, inicio, meio, tamanho_elem, comparar);
        mergesort_recursivo(arr, temp, meio + 1, fim, tamanho_elem, comparar);
        merge(arr, temp, inicio, meio, fim, tamanho_elem, comparar);
    }
}

// Função principal do mergesort genérico (wrapper)
void mergesort(void *arr, int n, size_t tamanho_elem, int (*comparar)(const void *, const void *)) {
    if (n < 2) return; // Array já está ordenado

    void *temp = malloc(n * tamanho_elem);
    if (temp == NULL) {
        perror("Falha ao alocar memória para o array temporário");
        return;
    }

    mergesort_recursivo(arr, temp, 0, n - 1, tamanho_elem, comparar);

    free(temp);
}

// void ordenar_base_em_disco(const char* nome_arquivo, size_t tamanho_registro, int (*comparar_fn)(const void*, const void*)) {
//     FILE *f = fopen(nome_arquivo, "rb");
//     if (f == NULL) {
//         perror("Erro ao abrir arquivo para ordenação");
//         return;
//     }

//     fseek(f, 0, SEEK_END);
//     long num_registros = ftell(f) / tamanho_registro;
//     fseek(f, 0, SEEK_SET);

//     if (num_registros == 0) {
//         fclose(f);
//         printf("Arquivo %s está vazio, nada para ordenar.\n", nome_arquivo);
//         return;
//     }

//     // Carrega todos os registros para a memória RAM
//     void* buffer = malloc(num_registros * tamanho_registro);
//     if (buffer == NULL) {
//         fprintf(stderr, "Erro de alocação de memória para ordenação.\n");
//         fclose(f);
//         return;
//     }

//     fread(buffer, tamanho_registro, num_registros, f);
//     fclose(f);

//     // Ordena o buffer na memória usando qsort (que geralmente é implementado com quicksort ou mergesort otimizado)
//     qsort(buffer, num_registros, tamanho_registro, comparar_fn);

//     // Grava os registros ordenados de volta no arquivo
//     f = fopen(nome_arquivo, "wb"); // Abre em modo de escrita para sobrescrever
//     if (f == NULL) {
//         perror("Erro ao abrir arquivo para escrita após ordenação");
//         free(buffer);
//         return;
//     }

//     fwrite(buffer, tamanho_registro, num_registros, f);
//     fclose(f);
//     free(buffer);

//     printf("Arquivo '%s' ordenado com sucesso por ID.\n", nome_arquivo);
// }

