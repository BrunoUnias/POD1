#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_VETOR 1000
#define MAX 25


//Inicializando vetor

int* inicializaVetorRandom() {
    int i;
    int *ret = malloc(sizeof (int) * TAMANHO_VETOR);
    srand(time(NULL));
    for (i = 0; i < TAMANHO_VETOR; i++) {
        ret[i] = rand();
    }
    return ret;
}

int* inicializaVetorOrdenado() {
    int i;
    int *ret = malloc(sizeof (int) * TAMANHO_VETOR);
    for (i = 0; i < TAMANHO_VETOR; i++) {
        ret[i] = i;
    }
    return ret;
}

int* inicializaVetorInvertido() {
    int i;
    int *ret = malloc(sizeof (int) * TAMANHO_VETOR);
    for (i = 0; i < TAMANHO_VETOR; i++) {
        ret[i] = TAMANHO_VETOR - i;
    }
    return ret;
}

//Insert Sort

void insertionSort(int vet[], int tam) {
    int  i, j = 0, aux = 0;
    for (i = 1; i < tam; i++) {
        aux = vet[i];
        j = i - 1;
        while ((j >= 0) && (vet[j] > aux)) {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = aux;
    }
}

// Bubble Sort 

void bubbleSort(int vet[], int tam) {
    int i, j, aux;
    for (i = tam - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (vet[j] > vet[j + 1]) {
                aux = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = aux;
            }
        }
    }
}

//Selection Sort

void selectionSort(int vet[], int tam) {
    int i, j, min, aux;
    for (i = 0; i < tam; i++) {
        min = i;
        for (j = i + 1; j < tam; j++) {
            if (vet[min] > vet[j])
                min = j;
        }
        aux = vet[i];
        vet[i] = vet[min];
        vet[min] = aux;
    }

}

//Quick sort

void quickSort(int a[], int n) {
    int i, j, p, t;
    if (n < 2)
        return;
    p = a[n / 2];
    for (i = 0, j = n - 1;; i++, j--) {
        while (a[i] < p)
            i++;
        while (p < a[j])
            j--;
        while (p < a[j])
            j--;
        if (i >= j)
            break;
        t = a[i];
        a[i] = a[j];
        a[j] = t;

    }
    quickSort(a, i);
    quickSort(a + i, n - i);
}


//MergeSort

void merge(int vetor[], int comeco, int meio, int fim) {

    int com1 = comeco, com2 = meio + 1, comAux = 0, tam = fim - comeco + 1;
    int *vetAux;
    vetAux = (int*) malloc(tam * sizeof (int));

    while (com1 <= meio && com2 <= fim) {
        if (vetor[com1] < vetor[com2]) {
            vetAux[comAux] = vetor[com1];
            com1++;
        } else {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }
    while (com1 <= meio) { //Caso ainda haja elementos na primeira metade
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }


    while (com2 <= fim) { //Caso ainda haja elementos na segunda metade
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }

    for (comAux = comeco; comAux <= fim; comAux++) { //Move os elementos de volta para o vetor original
        vetor[comAux] = vetAux[comAux - comeco];
    }
    free(vetAux);

}

void mergeSort(int vetor[], int comeco, int fim) {
    if (comeco < fim) {
        int meio = (fim + comeco) / 2; //Descobre o centro do array
        mergeSort(vetor, comeco, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, comeco, meio, fim);
    }

}

void shellSort(int *vet, int size) {
    int i, j, value;
    int gap = 1;
    while (gap < size) {
        gap = 3 * gap + 1;
    }
    while (gap > 1) {
        gap /= 3;
        for (i = gap; i < size; i++) {
            value = vet[i];
            j = i;
            while (j >= gap && value < vet[j - gap]) {
                vet[j] = vet [j - gap];
                j = j - gap;
            }
            vet [j] = value;
        }
    }
}

void heapSort(int tamanho[], int n) {
    int i = n / 2, pai, filho, t;
    while (1) {
        if (i > 0) {
            i--;
            t = tamanho[i];
        } else {
            n--;
            if (n == 0) return;
            t = tamanho[n];
            tamanho[n] = tamanho[0];
        }
        pai = i;
        filho = i * 2 + 1;
        while (filho < n) {
            if ((filho + 1 < n) && (tamanho[filho + 1] > tamanho[filho]))
                filho++;
            if (tamanho[filho] > t) {
                tamanho[pai] = tamanho[filho];
                pai = filho;
                filho = pai * 2 + 1;
            } else {
                break;
            }
        }
        tamanho[pai] = t;
    }
}

int main() {
    long int start, end;
    int vetor[] = {12, 11, 13, 5, 6, 34, 345, 546, 467, 568, 3453, 6456, 564};
    int* v;


    printf("InsertionSort: \n");
    v = inicializaVetorRandom();
    start = clock();
    insertionSort(v,TAMANHO_VETOR);
    end = clock();
    printf("\t Random: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);

    v = inicializaVetorOrdenado();
    start = clock();
    insertionSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Ordenado: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);

    v = inicializaVetorInvertido();
    start = clock();
    insertionSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Invertido: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);

    printf("\nBubbleSort: \n");
   v = inicializaVetorRandom();
    start = clock();
    bubbleSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Random: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);


    v = inicializaVetorOrdenado();
    start = clock();
    bubbleSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Ordenado: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);


    v = inicializaVetorInvertido();
    start = clock();
    bubbleSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Invertido: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);


    printf("\nSelectionSort: \n");
    v = inicializaVetorRandom();
    start = clock();
    selectionSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Random: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);


    v = inicializaVetorOrdenado();
    start = clock();
    selectionSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Ordenado: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
     free(v);


    v = inicializaVetorInvertido();
    start = clock();
    selectionSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Invertido: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);

    printf("\nQuickSort: \n");
    v = inicializaVetorRandom();
    start = clock();
    quickSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Random: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);


    v = inicializaVetorOrdenado();
    start = clock();
    quickSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Ordenado: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);


    v = inicializaVetorInvertido();
    start = clock();
    quickSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Invertido: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);



    printf("\nShellSort: \n");
    v = inicializaVetorRandom();
    start = clock();
    shellSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Random: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);

    v = inicializaVetorOrdenado();
    start = clock();
    shellSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Ordenado: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);


    v = inicializaVetorInvertido();
    start = clock();
    shellSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Invertido: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);

    printf("\nHeapSort: \n");
    v = inicializaVetorRandom();
    start = clock();
    heapSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Random: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);


    v = inicializaVetorOrdenado();
    start = clock();
    heapSort(v, TAMANHO_VETOR);
    end = clock();
    printf("\t Ordenado: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);

    v = inicializaVetorInvertido();
    start = clock();
    heapSort(v, TAMANHO_VETOR);
   end = clock();
    printf("\t Invertido: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);

    printf("\nMergeSort: \n");
    v = inicializaVetorRandom();
    start = clock();
    mergeSort(v, 0, TAMANHO_VETOR);
    end = clock();
    printf("\t Random: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);


    v = inicializaVetorOrdenado();
    start = clock();
    mergeSort(v, 0, TAMANHO_VETOR);
   end = clock();
    printf("\t Ordenado: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
    free(v);


    v = inicializaVetorInvertido();
    start = clock();
    mergeSort(v, 0, TAMANHO_VETOR);
    end = clock();
   printf("\t Invertido: %ld milisegundos\n", (end - start) / (CLOCKS_PER_SEC / 1000));
   free(v);


    return 0;
}


