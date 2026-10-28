# 📊 Sistema de Ordenação e Manipulação de Arquivos em C

Trabalho prático desenvolvido para unir conceitos de **manipulação de arquivos** e **algoritmos de ordenação** utilizando a linguagem C, no âmbito do curso de Engenharia de Software.

---

## 👥 Equipa do Projeto

O desenvolvimento das funcionalidades e algoritmos foi distribuído entre os elementos do grupo:

* **Jonathan** — Implementação do *Quick Sort* e Estruturação do Menu Principal (`switch/case`).
* **Leonardo** — Implementação do *Bubble Sort* e Função de Salvamento do Ficheiro Ordenado (`ordenado.txt`).
* **Ruan** — Módulo de Manipulação de Ficheiros de Entrada (`dados.txt`) e Função de Alteração/Substituição de Valores.
* **Kayke** — Implementação do *Insertion Sort* e do *Selection Sort*.
* **Vinicius** — Implementação do *Merge Sort* (Divisão e Conquista com alocação dinâmica).

---

## ⚙️ Funcionalidades do Sistema

O programa funciona através de um menu interativo e executa as seguintes operações:
1. **Criar e Gravar Dados (`dados.txt`)**: Permite inserir números desordenados gerando o ficheiro de entrada.
2. **Leitura e Ordenação**: Lê os dados do ficheiro para um vetor na memória RAM e permite escolher entre **5 algoritmos de ordenação**:
   * *Bubble Sort*
   * *Insertion Sort*
   * *Selection Sort*
   * *Merge Sort*
   * *Quick Sort*
3. **Guardar Resultado (`ordenado.txt`)**: Grava automaticamente os dados já ordenados num novo ficheiro.
4. **Alteração de Valores**: Permite editar um valor específico dentro do ficheiro original utilizando uma estratégia de ficheiro temporário (`temp.txt`).

---

## 📂 Estrutura dos Ficheiros Gerados

* `dados.txt` — Contém os valores numéricos originais inseridos pelo utilizador (entrada).
* `ordenado.txt` — Contém os valores organizados após a execução do algoritmo de ordenação escolhido.
* `temp.txt` — Ficheiro auxiliar utilizado temporariamente para atualizar valores no ficheiro original.

---

## 🚀 Como Compilar e Executar

Certifica-te de que tens um compilador de C instalado (como o **GCC**). Podes compilar e executar o programa através do terminal com os seguintes comandos:

```bash
# Compilar o código fonte
gcc main.c -o programa_ordenacao

# Executar o programa
# No Linux / macOS:
./programa_ordenacao

# No Windows:
programa_ordenacao.exe
