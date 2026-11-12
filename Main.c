#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Estrutura principal que representa os produtos da loja
typedef struct {
    int id;
    char produto[50];
    char categoria[30];
    float preco;
    int quantidade;
    char fornecedor[50];
} Produto;

// Jonathan - Cadastra um novo produto e grava no final do arquivo de texto
void criarArquivoDados() {
    FILE *f = fopen("dados.txt", "a");

    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Produto p;

    printf("\n--- NOVO PRODUTO ---\n");
    printf("ID: ");
    scanf("%d", &p.id);

    int c; while ((c = getchar()) != '\n' && c != EOF);

    printf("Nome do produto: ");
    fgets(p.produto, 50, stdin);
    p.produto[strcspn(p.produto, "\n")] = '\0';

    printf("Categoria: ");
    fgets(p.categoria, 30, stdin);
    p.categoria[strcspn(p.categoria, "\n")] = '\0';

    printf("Preco (R$): ");
    scanf("%f", &p.preco);

    printf("Quantidade: ");
    scanf("%d", &p.quantidade);

    while ((c = getchar()) != '\n' && c != EOF);

    printf("Fornecedor: ");
    fgets(p.fornecedor, 50, stdin);
    p.fornecedor[strcspn(p.fornecedor, "\n")] = '\0';

    // Grava os dados formatados com ponto e vírgula delimitando os campos
    fprintf(f, "%d;%s;%s;%.2f;%d;%s\n", p.id, p.produto, p.categoria, p.preco, p.quantidade, p.fornecedor);

    fclose(f);
    printf("Cadastrado com sucesso!\n");
}

// Jonathan - Lê o arquivo linha por linha e preenche o vetor de structs
int lerArquivoDados(Produto v[]) {
    FILE *f = fopen("dados.txt", "r");

    if (f == NULL) {
        printf("Arquivo 'dados.txt' nao encontrado!\n");
        return 0;
    }

    int i = 0;
    char linha[256];

    // sscanf faz o parsing da linha dividindo pelos separadores ponto e vírgula
    while (i < MAX && fgets(linha, sizeof(linha), f) != NULL) {
        if (sscanf(linha, "%d;%49[^;];%29[^;];%f;%d;%49[^\n]", 
                   &v[i].id, v[i].produto, v[i].categoria, &v[i].preco, &v[i].quantidade, v[i].fornecedor) == 6) {
            i++;
        }
    }

    fclose(f);
    return i; 
}

// Jonathan - Altera ou exclui um registro usando a técnica do arquivo temporário para evitar corrupção
void alterarValorArquivo() {
    FILE *f = fopen("dados.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    int idAlvo, achou = 0;
    printf("Digite o ID do produto que deseja alterar/excluir: ");
    scanf("%d", &idAlvo);

    int acao;
    printf("[1] Alterar | [2] Excluir: ");
    scanf("%d", &acao);

    char linha[256];
    while (fgets(linha, sizeof(linha), f) != NULL) {
        Produto p;
        if (sscanf(linha, "%d;%49[^;];%29[^;];%f;%d;%49[^\n]", 
                   &p.id, p.produto, p.categoria, &p.preco, &p.quantidade, p.fornecedor) == 6) {
            
            if (p.id == idAlvo) {
                achou = 1;
                if (acao == 1) {
                    printf("\n--- ALTERANDO ID %d ---\n", p.id);
                    int c; while ((c = getchar()) != '\n' && c != EOF);
                    
                    printf("Novo nome: ");
                    fgets(p.produto, 50, stdin);
                    p.produto[strcspn(p.produto, "\n")] = '\0';

                    printf("Nova categoria: ");
                    fgets(p.categoria, 30, stdin);
                    p.categoria[strcspn(p.categoria, "\n")] = '\0';

                    printf("Novo preco: ");
                    scanf("%f", &p.preco);

                    printf("Nova quantidade: ");
                    scanf("%d", &p.quantidade);

                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("Novo fornecedor: ");
                    fgets(p.fornecedor, 50, stdin);
                    p.fornecedor[strcspn(p.fornecedor, "\n")] = '\0';

                    // Escreve os dados novos no arquivo temporário
                    fprintf(temp, "%d;%s;%s;%.2f;%d;%s\n", p.id, p.produto, p.categoria, p.preco, p.quantidade, p.fornecedor);
                    printf("Atualizado com sucesso!\n");
                } else {
                    // Se for exclusão, pulamos a escrita no temp (o registro é apagado)
                    printf("Produto removido!\n");
                }
            } else {
                // Mantém os outros registros intactos copiando para o temp
                fprintf(temp, "%s", linha);
            }
        }
    }

    fclose(f);
    fclose(temp);

    // Substitui o arquivo original pelo temporário atualizado
    remove("dados.txt");
    rename("temp.txt", "dados.txt");

    if (!achou) {
        printf("ID nao encontrado.\n");
    }
}


// Kayke - Insertion Sort adaptado para ordenar o vetor de structs por ID
void insertionSort(Produto v[], int n) {
    for (int i = 1; i < n; i++) {
        Produto atual = v[i];
        int j = i - 1;

        while (j >= 0 && v[j].id > atual.id) {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = atual;
    }
}

// Kayke - Selection Sort adaptado para struct
void selectionSort(Produto v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            if (v[j].id < v[menor].id) {
                menor = j;
            }
        }

        if (menor != i) {
            Produto temp = v[i];
            v[i] = v[menor];
            v[menor] = temp;
        }
    }
}

// Kayke - Exibe os produtos formatados em uma tabela organizada no terminal
void mostrarVetor(Produto v[], int n) {
    printf("\n---------------------------------------------------------------------------\n");
    printf("| ID  | Produto              | Categoria       | Preco    | Qtd | Fornecedor  |\n");
    printf("---------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        // Alinhamento de colunas usando largura fixa de caracteres no printf
        printf("| %-3d | %-20s | %-15s | R$%-6.2f | %-3d | %-11s |\n", 
               v[i].id, v[i].produto, v[i].categoria, v[i].preco, v[i].quantidade, v[i].fornecedor);
    }
    printf("---------------------------------------------------------------------------\n");
}


// Leonardo - Bubble Sort adaptado para struct e salvamento do relatório
void bubbleSort(Produto v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;

        for (int j = 0; j < n - i - 1; j++) {
            if (v[j].id > v[j + 1].id) {
                Produto temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                trocou = 1;
            }
        }

        if (!trocou) break;
    }
}

int salvarOrdenado(Produto v[], int n) {
    FILE *arquivo = fopen("ordenado.txt", "w");

    if (arquivo == NULL) {
        printf("Nao foi possivel criar o arquivo.\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%d;%s;%s;%.2f;%d;%s\n", v[i].id, v[i].produto, v[i].categoria, v[i].preco, v[i].quantidade, v[i].fornecedor);
    }

    fclose(arquivo);
    printf("Dados salvos em ordenado.txt.\n");
    return 1;
}


// Vinicius - Merge Sort com alocação dinâmica adaptado para struct
void merge(Produto v[], Produto temp[], int inicio, int meio, int fim) {
    int i = inicio;
    int j = meio + 1;
    int k = inicio;

    while (i <= meio && j <= fim) {
        if (v[i].id <= v[j].id) {
            temp[k++] = v[i++];
        } else {
            temp[k++] = v[j++];
        }
    }

    while (i <= meio) temp[k++] = v[i++];
    while (j <= fim) temp[k++] = v[j++];

    for (i = inicio; i <= fim; i++) {
        v[i] = temp[i];
    }
}

void mergeSortRec(Produto v[], Produto temp[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSortRec(v, temp, inicio, meio);
        mergeSortRec(v, temp, meio + 1, fim);
        merge(v, temp, inicio, meio, fim);
    }
}

void mergeSort(Produto v[], int n) {
    if (n <= 1) return;

    Produto *temp = malloc(n * sizeof(Produto));
    if (temp == NULL) {
        printf("Erro de memoria!\n");
        return;
    }

    mergeSortRec(v, temp, 0, n - 1);
    free(temp);
}


// Ruan - Quick Sort adaptado para struct e gerenciamento do menu principal
void quickSort(Produto vetor[], int inicio, int fim) {
    int i = inicio;
    int j = fim;
    int pivo = vetor[(inicio + fim) / 2].id;

    while (i <= j) {
        while (vetor[i].id < pivo) i++;
        while (vetor[j].id > pivo) j--;

        if (i <= j) {
            Produto auxiliar = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = auxiliar;
            i++;
            j--;
        }
    }

    if (inicio < j) quickSort(vetor, inicio, j);
    if (i < fim) quickSort(vetor, i, fim);
}

void executarOrdenacao(int opcao) {
    Produto vetor[MAX];
    int quantidade = lerArquivoDados(vetor);

    if (quantidade == 0) {
        printf("Nao existem dados para ordenar.\n");
        return;
    }

    printf("\nProdutos originais:");
    mostrarVetor(vetor, quantidade);

    switch (opcao) {
        case 2:
            bubbleSort(vetor, quantidade);
            printf("\n--- Ordenado por Bubble Sort ---");
            break;
        case 3:
            insertionSort(vetor, quantidade);
            printf("\n--- Ordenado por Insertion Sort ---");
            break;
        case 4:
            selectionSort(vetor, quantidade);
            printf("\n--- Ordenado por Selection Sort ---");
            break;
        case 5:
            mergeSort(vetor, quantidade);
            printf("\n--- Ordenado por Merge Sort ---");
            break;
        case 6:
            quickSort(vetor, 0, quantidade - 1);
            printf("\n--- Ordenado por Quick Sort ---");
            break;
    }

    mostrarVetor(vetor, quantidade);
    salvarOrdenado(vetor, quantidade);
}

void menuPrincipal(void) {
    int opcao;

    do {
        printf("\n====================================\n");
        printf(" SISTEMA DE CADASTRO E LOJA\n");
        printf("====================================\n");
        printf("1 - Cadastrar novo produto\n");
        printf("2 - Bubble Sort\n");
        printf("3 - Insertion Sort\n");
        printf("4 - Selection Sort\n");
        printf("5 - Merge Sort\n");
        printf("6 - Quick Sort\n");
        printf("7 - Alterar ou excluir produto\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            int caractere;
            while ((caractere = getchar()) != '\n' && caractere != EOF);
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

int main(void) {
    menuPrincipal();
    return 0;
}
