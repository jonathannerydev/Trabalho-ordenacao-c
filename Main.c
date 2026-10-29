
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

    if (quantidade < 1 || quantidade > MAX) {
        printf("Quantidade invalida! Digite de 1 a 100.\n");
        fclose(arquivo);
        return;
    }

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

    while (i < MAX && fscanf(arquivo, "%d", &v[i]) == 1) {
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

        if (arquivo != NULL) {
            fclose(arquivo);
        }

        if (temp != NULL) {
            fclose(temp);
        }

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


// Leonardo
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


// Vinicius
void merge(int v[], int temp[], int inicio, int meio, int fim) {
    int i = inicio;
    int j = meio + 1;
    int k = inicio;

    while (i <= meio && j <= fim) {
        if (v[i] <= v[j]) {
            temp[k] = v[i];
            i++;
        } else {
            temp[k] = v[j];
            j++;
        }
        k++;
    }

    while (i <= meio) {
        temp[k] = v[i];
        i++;
        k++;
    }

    while (j <= fim) {
        temp[k] = v[j];
        j++;
        k++;
    }

    for (i = inicio; i <= fim; i++) {
        v[i] = temp[i];
    }
}

void mergeSortRec(int v[], int temp[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;

        mergeSortRec(v, temp, inicio, meio);
        mergeSortRec(v, temp, meio + 1, fim);

        merge(v, temp, inicio, meio, fim);
    }
}

void mergeSort(int v[], int n) {
    if (n <= 1) {
        return;
    }

    int *temp = malloc(n * sizeof(int));

    if (temp == NULL) {
        printf("Erro de memoria!\n");
        return;
    }

    mergeSortRec(v, temp, 0, n - 1);

    free(temp);
}


// Ruan
// Quick Sort
void quickSort(int vetor[], int inicio, int fim) {
    int i = inicio;
    int j = fim;
    int pivo = vetor[(inicio + fim) / 2];
    int auxiliar;

    while (i <= j) {
        while (vetor[i] < pivo) {
            i++;
        }

        while (vetor[j] > pivo) {
            j--;
        }

        if (i <= j) {
            auxiliar = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = auxiliar;

            i++;
            j--;
        }
    }

    if (inicio < j) {
        quickSort(vetor, inicio, j);
    }

    if (i < fim) {
        quickSort(vetor, i, fim);
    }
}

// Executar ordenacao
void executarOrdenacao(int opcao) {
    int vetor[MAX];
    int quantidade = lerArquivoDados(vetor);

    if (quantidade == 0) {
        printf("Nao existem dados para ordenar.\n");
        return;
    }

    printf("\nNumeros originais: ");
    mostrarVetor(vetor, quantidade);

    switch (opcao) {
        case 2:
            bubbleSort(vetor, quantidade);
            printf("Bubble Sort: ");
            break;

        case 3:
            insertionSort(vetor, quantidade);
            printf("Insertion Sort: ");
            break;

        case 4:
            selectionSort(vetor, quantidade);
            printf("Selection Sort: ");
            break;

        case 5:
            mergeSort(vetor, quantidade);
            printf("Merge Sort: ");
            break;

        case 6:
            quickSort(vetor, 0, quantidade - 1);
            printf("Quick Sort: ");
            break;

        default:
            printf("Opcao invalida!\n");
            return;
    }

    mostrarVetor(vetor, quantidade);
    salvarOrdenado(vetor, quantidade);
}

// Menu principal
void menuPrincipal(void) {
    int opcao;

    do {
        printf("\n====================================\n");
        printf(" SISTEMA DE ORDENACAO DE ARQUIVOS\n");
        printf("====================================\n");
        printf("1 - Criar arquivo de dados\n");
        printf("2 - Bubble Sort\n");
        printf("3 - Insertion Sort\n");
        printf("4 - Selection Sort\n");
        printf("5 - Merge Sort\n");
        printf("6 - Quick Sort\n");
        printf("7 - Alterar valor no arquivo\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            int caractere;

            while ((caractere = getchar()) != '\n' &&
                   caractere != EOF) {
            }

            printf("Digite uma opcao valida!\n");
            continue;
        }

        switch (opcao) {
            case 1:
                criarArquivoDados();
                break;

            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                executarOrdenacao(opcao);
                break;

            case 7:
                alterarValorArquivo();
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);
}

// Main
int main(void) {
    menuPrincipal();
    return 0;
}

