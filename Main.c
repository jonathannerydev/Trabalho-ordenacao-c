#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Função para criar o arquivo e gravar os números desordenados fornecidos pelo usuário
void criarArquivoDados() {
    FILE *arquivo = fopen("dados.txt", "w");
    
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo dados.txt!\n");
        return;
    }
    
    int quantidade, numero;
    printf("Quantos numeros deseja inserir? ");
    scanf("%d", &quantidade);
    
    printf("Digite os %d valores:\n", quantidade);
    for (int i = 0; i < quantidade; i++) {
        scanf("%d", &numero);
        fprintf(arquivo, "%d\n", numero);
    }
    
    fclose(arquivo);
    printf("Dados gravados com sucesso em 'dados.txt'!\n");
}

// Função para ler os números do arquivo e jogá-los para um vetor na memória
int lerArquivoDados(int v[]) {
    FILE *arquivo = fopen("dados.txt", "r");
    
    if (arquivo == NULL) {
        printf("Arquivo 'dados.txt' nao encontrado!\n");
        return 0;
    }
    
    int i = 0;
    while (fscanf(arquivo, "%d", &v[i]) == 1 && i < MAX) {
        i++;
    }
    
    fclose(arquivo);
    return i; // Retorna quantos elementos foram lidos
}

// Função para alterar um valor específico dentro do arquivo usando um arquivo temporário
void alterarValorArquivo() {
    FILE *arquivo = fopen("dados.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos para edicao!\n");
        return;
    }
    
    int valorAntigo, valorNovo;
    int encontrado = 0;
    int atual;
    
    printf("Qual valor deseja alterar? ");
    scanf("%d", &valorAntigo);
    printf("Digite o novo valor: ");
    scanf("%d", &valorNovo);
    
    // Lê o arquivo original linha por linha e passa pro temporário, alterando o valor desejado
    while (fscanf(arquivo, "%d", &atual) == 1) {
        if (atual == valorAntigo && !encontrado) {
            fprintf(temp, "%d\n", valorNovo);
            encontrado = 1; // Altera apenas a primeira ocorrência
        } else {
            fprintf(temp, "%d\n", atual);
        }
    }
    
    fclose(arquivo);
    fclose(temp);
    
    // Substitui o arquivo antigo pelo novo atualizado
    remove("dados.txt");
    rename("temp.txt", "dados.txt");
    
    if (encontrado) {
        printf("Valor alterado com sucesso!\n");
    } else {
        printf("O valor informado nao foi encontrado no arquivo.\n");
    }
}


// Kayke Queriquieri
#include <stdio.h>

// Insertion Sort
void insertionSort(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int atual = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > atual) {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = atual;
    }
}

// Selection Sort
void selectionSort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[menor]) {
                menor = j;
            }
        }

        if (menor != i) {
            int temp = v[i];
            v[i] = v[menor];
            v[menor] = temp;
        }
    }
}

// Mostrar numeros
void mostrarVetor(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main(void) {
    int original[] = {64, 25, 12, 22, 11};
    int insertion[5], selection[5];
    int n = 5;

    for (int i = 0; i < n; i++) {
        insertion[i] = original[i];
        selection[i] = original[i];
    }

    printf("Vetor original: ");
    mostrarVetor(original, n);

    insertionSort(insertion, n);
    printf("Insertion Sort: ");
    mostrarVetor(insertion, n);

    selectionSort(selection, n);
    printf("Selection Sort: ");
    mostrarVetor(selection, n);

    return 0;
}

// Leonardo
#include <stdio.h>

// Bubble Sort
void bubbleSort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;

        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                trocou = 1;
            }
        }

        if (!trocou) {
            break;
        }
    }
}

// Salvar numeros no arquivo
int salvarOrdenado(int v[], int n) {
    FILE *arquivo = fopen("ordenado.txt", "w");

    if (arquivo == NULL) {
        printf("Nao foi possivel criar o arquivo.\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (fprintf(arquivo, "%d\n", v[i]) < 0) {
            printf("Erro ao escrever no arquivo.\n");
            fclose(arquivo);
            return 0;
        }
    }

    if (fclose(arquivo) != 0) {
        printf("Erro ao fechar o arquivo.\n");
        return 0;
    }

    printf("Dados salvos em ordenado.txt.\n");
    return 1;
}

// Mostrar numeros
void mostrarVetor(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main(void) {
    int numeros[] = {64, 25, 12, 22, 11};
    int n = sizeof(numeros) / sizeof(numeros[0]);

    printf("Vetor original: ");
    mostrarVetor(numeros, n);

    bubbleSort(numeros, n);

    printf("Bubble Sort: ");
    mostrarVetor(numeros, n);

    salvarOrdenado(numeros, n);

    return 0;
}
