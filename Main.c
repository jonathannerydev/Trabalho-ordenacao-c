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

# Responsável: Kayke
# Algoritmos: Insertion Sort e Selection Sort

# Algoritmo Insertion Sort
def insertion_sort(vetor):
    for i in range(1, len(vetor)):
        chave = vetor[i]
        j = i - 1

        while j >= 0 and vetor[j] > chave:
            vetor[j + 1] = vetor[j]
            j -= 1

        vetor[j + 1] = chave

    return vetor


# Algoritmo Selection Sort
def selection_sort(vetor):
    n = len(vetor)

    for i in range(n - 1):
        indice_menor = i

        for j in range(i + 1, n):
            if vetor[j] < vetor[indice_menor]:
                indice_menor = j

        vetor[i], vetor[indice_menor] = (
            vetor[indice_menor], vetor[i]
        )

    return vetor


# Programa principal
def main():
    numeros = [64, 25, 12, 22, 11]

    print("===== ALGORITMOS DE ORDENAÇÃO =====")
    print("Vetor original:", numeros)

    resultado_insertion = insertion_sort(numeros.copy())
    resultado_selection = selection_sort(numeros.copy())

    print("\nInsertion Sort:", resultado_insertion)
    print("Selection Sort:", resultado_selection)

    # Verificação dos resultados
    esperado = sorted(numeros)

    assert resultado_insertion == esperado
    assert resultado_selection == esperado

    print("\nTodos os testes passaram!")


if __name__ == "__main__":
    main()
