#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void copiar_vetor(int *origem, int *destino, int n) {
    memcpy(destino, origem, n * sizeof(int));
}

void gerar_vetor(int *v, int n) {
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 100000;
    }
}

// BUBBLE SORT
void bubbleSort(int *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// SELECTION SORT
void selectionSort(int *v, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min])
                min = j;
        }
        int temp = v[i];
        v[i] = v[min];
        v[min] = temp;
    }
}

// INSERTION SORT 
void insertionSort(int *v, int n) {
    for (int i = 1; i < n; i++) {
        int key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

// MERGE SORT
void merge(int *v, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = v[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = v[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            v[k++] = L[i++];
        else
            v[k++] = R[j++];
    }

    while (i < n1)
        v[k++] = L[i++];

    while (j < n2)
        v[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int *v, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(v, l, m);
        mergeSort(v, m + 1, r);
        merge(v, l, m, r);
    }
}

// QUICK SORT
int particiona(int *v, int low, int high) {
    int pivot = v[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (v[j] < pivot) {
            i++;
            int temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
    }

    int temp = v[i + 1];
    v[i + 1] = v[high];
    v[high] = temp;

    return i + 1;
}

void quickSort(int *v, int low, int high) {
    if (low < high) {
        int pi = particiona(v, low, high);
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

// COUNTING SORT
void countingSort(int *v, int n) {
    int max = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > max)
            max = v[i];

    int *count = calloc(max + 1, sizeof(int));

    for (int i = 0; i < n; i++)
        count[v[i]]++;

    int index = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i]-- > 0) {
            v[index++] = i;
        }
    }

    free(count);
}

int main() {
    srand(time(NULL));

    int tamanhos[] = {100, 500, 1000, 5000, 30000, 80000, 100000, 150000, 200000};
    int qtd = sizeof(tamanhos) / sizeof(int);

    for (int i = 0; i < qtd; i++) {
        int n = tamanhos[i];

        int *original = malloc(n * sizeof(int));
        int *vetor = malloc(n * sizeof(int));

        gerar_vetor(original, n);

        printf("\nTamanho do vetor: %d\n", n);

        clock_t inicio, fim;

        copiar_vetor(original, vetor, n);
        inicio = clock();
        bubbleSort(vetor, n);
        fim = clock();
        printf("Bubble Sort: %.4f s\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

        copiar_vetor(original, vetor, n);
        inicio = clock();
        selectionSort(vetor, n);
        fim = clock();
        printf("Selection Sort: %.4f s\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

        copiar_vetor(original, vetor, n);
        inicio = clock();
        insertionSort(vetor, n);
        fim = clock();
        printf("Insertion Sort: %.4f s\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

        copiar_vetor(original, vetor, n);
        inicio = clock();
        mergeSort(vetor, 0, n - 1);
        fim = clock();
        printf("Merge Sort: %.4f s\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

        copiar_vetor(original, vetor, n);
        inicio = clock();
        quickSort(vetor, 0, n - 1);
        fim = clock();
        printf("Quick Sort: %.4f s\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

        copiar_vetor(original, vetor, n);
        inicio = clock();
        countingSort(vetor, n);
        fim = clock();
        printf("Counting Sort: %.4f s\n", (double)(fim - inicio) / CLOCKS_PER_SEC);

        free(original);
        free(vetor);
    }

    return 0;
}
