#ifndef MERGE_SORT
#define MERGE_SORT

#include <stdio.h>
#include <string.h>
#include "componentes.h"

void merge(void *arr, void *temp, int inicio, int meio, int fim, size_t tamanho_elem, int (*comparar)(const void *, const void *));
void mergesort_recursivo(void *arr, void *temp, int inicio, int fim, size_t tamanho_elem, int (*comparar)(const void *, const void *));
void mergesort(void *arr, int n, size_t tamanho_elem, int (*comparar)(const void *, const void *));

#endif