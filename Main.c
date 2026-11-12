
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Estrutura que guarda os dados de cada produto
typedef struct {
    int id;
    char produto[50];
    char categoria[30];
    float preco;
    int quantidade;
    char fornecedor[50];
} Produto;


// Le os produtos salvos no arquivo dados.txt
int lerProdutos(Produto v[]) {
    FILE *f = fopen("dados.txt", "r");
    int n = 0;

    if (f == NULL) {
        return 0;
    }

    while (n < MAX &&
        fscanf(f, "%d;%49[^;];%29[^;];%f;%d;%49[^\n]",
        &v[n].id, v[n].produto, v[n].categoria,
        &v[n].preco, &v[n].quantidade, v[n].fornecedor) == 6) {
        n++;
    }

    fclose(f);
    return n;
}


// Verifica se um ID ja existe
int idExiste(Produto v[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (v[i].id == id) {
            return 1;
        }
    }

    return 0;
}


// Cadastra um produto
void cadastrar() {
    Produto v[MAX];
    Produto p;
    int n = lerProdutos(v);

    // Gera um ID automatico
    p.id = 1;

    for (int i = 0; i < n; i++) {
        if (v[i].id >= p.id) {
            p.id = v[i].id + 1;
        }
    }

    if (idExiste(v, n, p.id)) {
        printf("ID ja existe!\n");
        return;
    }

    printf("Nome do produto: ");
    scanf(" %49[^\n]", p.produto);

    printf("Categoria: ");
    scanf(" %29[^\n]", p.categoria);

    printf("Preco: ");
    scanf("%f", &p.preco);

    printf("Quantidade: ");
    scanf("%d", &p.quantidade);

    printf("Fornecedor: ");
    scanf(" %49[^\n]", p.fornecedor);

    FILE *f = fopen("dados.txt", "a");

    if (f == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    fprintf(f, "%d;%s;%s;%.2f;%d;%s\n",
        p.id, p.produto, p.categoria,
        p.preco, p.quantidade, p.fornecedor);

    fclose(f);

    printf("Produto cadastrado! ID: %d\n", p.id);
}


// Mostra o cabecalho da tabela
void cabecalho() {
    printf("\n%-4s %-20s %-15s %-8s %-5s %-15s\n",
        "ID", "Produto", "Categoria", "Preco", "Qtd", "Fornecedor");

    printf("-------------------------------------------------------------------\n");
}


// Mostra um produto
void linha(Produto p) {
    printf("%-4d %-20.20s %-15.15s %-8.2f %-5d %-15.15s\n",
        p.id, p.produto, p.categoria,
        p.preco, p.quantidade, p.fornecedor);
}


// Lista todos os produtos
void listar() {
    Produto v[MAX];
    int n = lerProdutos(v);

    if (n == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    cabecalho();

    for (int i = 0; i < n; i++) {
        linha(v[i]);
    }
}


// Transforma um texto em letras minusculas
void minusculo(char texto[]) {
    for (int i = 0; texto[i] != '\0'; i++) {
        texto[i] = tolower((unsigned char)texto[i]);
    }
}


// Busca um produto pelo nome ou categoria
void buscar() {
    Produto v[MAX];
    int n = lerProdutos(v);

    char busca[50];
    char nome[50];
    char categoria[30];

    int achou = 0;

    printf("Digite o nome ou categoria: ");
    scanf(" %49[^\n]", busca);

    minusculo(busca);

    for (int i = 0; i < n; i++) {

        strcpy(nome, v[i].produto);
        strcpy(categoria, v[i].categoria);

        minusculo(nome);
        minusculo(categoria);

        if (strstr(nome, busca) != NULL ||
            strstr(categoria, busca) != NULL) {

            if (achou == 0) {
                cabecalho();
            }

            linha(v[i]);
            achou = 1;
        }
    }

    if (achou == 0) {
        printf("Nenhum produto encontrado.\n");
    }
}


// Altera ou exclui um produto
void alterarExcluir() {
    Produto v[MAX];
    int n = lerProdutos(v);

    int idAlvo;
    int acao;
    int achou = 0;

    printf("ID do produto: ");
    scanf("%d", &idAlvo);

    printf("1 - Alterar\n");
    printf("2 - Excluir\n");
    scanf("%d", &acao);

    if (acao != 1 && acao != 2) {
        printf("Opcao invalida!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");

    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario!\n");
        return;
    }

    for (int i = 0; i < n; i++) {

        if (v[i].id == idAlvo) {
            achou = 1;

            if (acao == 1) {
                printf("Novo nome: ");
                scanf(" %49[^\n]", v[i].produto);

                printf("Nova categoria: ");
                scanf(" %29[^\n]", v[i].categoria);

                printf("Novo preco: ");
                scanf("%f", &v[i].preco);

                printf("Nova quantidade: ");
                scanf("%d", &v[i].quantidade);

                printf("Novo fornecedor: ");
                scanf(" %49[^\n]", v[i].fornecedor);
            }

            if (acao == 2) {
                continue;
            }
        }

        fprintf(temp, "%d;%s;%s;%.2f;%d;%s\n",
            v[i].id, v[i].produto, v[i].categoria,
            v[i].preco, v[i].quantidade, v[i].fornecedor);
    }

    fclose(temp);

    if (achou == 0) {
        remove("temp.txt");
        printf("ID nao encontrado.\n");
        return;
    }

    remove("dados.txt");
    rename("temp.txt", "dados.txt");

    printf("Operacao realizada com sucesso!\n");
}


// Exporta os produtos para um arquivo CSV
void exportarCSV() {
    Produto v[MAX];
    int n = lerProdutos(v);

    if (n == 0) {
        printf("Nada para exportar.\n");
        return;
    }

    FILE *f = fopen("dados.csv", "w");

    if (f == NULL) {
        printf("Erro ao criar arquivo CSV!\n");
        return;
    }

    // Cabecalho da planilha
    fprintf(f, "ID,Produto,Categoria,Preco,Quantidade,Fornecedor\n");

    // Escreve os produtos no arquivo
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d,%s,%s,%.2f,%d,%s\n",
            v[i].id, v[i].produto, v[i].categoria,
            v[i].preco, v[i].quantidade, v[i].fornecedor);
    }

    fclose(f);

    printf("Arquivo dados.csv criado!\n");
}


// Ordena os produtos pelo preco
void bubbleSort(Produto v[], int n) {

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - 1 - i; j++) {

            if (v[j].preco > v[j + 1].preco) {

                Produto aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}


// Mostra e salva os produtos ordenados
void ordenar() {
    Produto v[MAX];
    int n = lerProdutos(v);

    if (n == 0) {
        printf("Nada para ordenar.\n");
        return;
    }

    bubbleSort(v, n);

    cabecalho();

    for (int i = 0; i < n; i++) {
        linha(v[i]);
    }

    FILE *f = fopen("ordenado.txt", "w");

    if (f == NULL) {
        printf("Erro ao criar arquivo!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d;%s;%s;%.2f;%d;%s\n",
            v[i].id, v[i].produto, v[i].categoria,
            v[i].preco, v[i].quantidade, v[i].fornecedor);
    }

    fclose(f);

    printf("Relatorio salvo em ordenado.txt\n");
}


// Menu principal
int main() {
    int opcao;

    do {
        printf("\n===== CADASTRO DE LOJA =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Buscar produto\n");
        printf("4 - Alterar ou excluir produto\n");
        printf("5 - Ordenar por preco\n");
        printf("6 - Exportar para CSV\n");
        printf("0 - Sair\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                cadastrar();
                break;

            case 2:
                listar();
                break;

            case 3:
                buscar();
                break;

            case 4:
                alterarExcluir();
                break;

            case 5:
                ordenar();
                break;

            case 6:
                exportarCSV();
                break;

            case 0:
                printf("Ate logo!\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
