# 📊 Sistema de Ordenação e Manipulação de Arquivos em C

Trabalho prático desenvolvido para unir conceitos de **manipulação de arquivos** e **algoritmos de ordenação** utilizando a linguagem C, no âmbito do curso de Engenharia de Software da UNICID.

---

## 👥 Equipe, RGMs e Divisão de Tarefas

O desenvolvimento das funcionalidades e algoritmos foi distribuído entre os integrantes do grupo:

* **Jonathan Nery Lacerda** (RGM: `47734213`)  
  — Módulo de Manipulação de Arquivos (`dados.txt` e `temp.txt`) e Função de Alteração/Edição de Valores.

* **Ruan Sousa Silva** (RGM: `47347805`)  
  — Implementação do Algoritmo Avançado (*Quick Sort*) e Estruturação do Menu Principal (`switch/case`).

* **Kayke Queriquieri da Silva** (RGM: `47556897`)  
  — Implementação dos Algoritmos Intermediários (*Insertion Sort* e *Selection Sort*).

* **Vinicius de Oliveira** (RGM: `47710608`)  
  — Implementação do Algoritmo Avançado (*Merge Sort* - Divisão e Conquista com alocação dinâmica).

* **Leonardo Augusto** (RGM: `47733497`)  
  — Implementação do Algoritmo Básico (*Bubble Sort*) e Função de Salvamento do Arquivo Ordenado (`ordenado.txt`).

---

## ⚙️ Funcionalidades do Sistema

O programa funciona por meio de um menu interativo e executa as seguintes operações:
1. **Criar e Gravar Dados (`dados.txt`)**: Permite inserir números desordenados gerando o arquivo de entrada.
2. **Leitura e Ordenação**: Lê os dados do arquivo para um vetor na memória RAM e permite escolher entre **5 algoritmos de ordenação**:
   * *Bubble Sort*
   * *Insertion Sort*
   * *Selection Sort*
   * *Merge Sort*
   * *Quick Sort*
3. **Salvar Resultado (`ordenado.txt`)**: Grava automaticamente os dados já ordenados em um novo arquivo.
4. **Alteração de Valores**: Permite editar um valor específico dentro do arquivo original utilizando uma estratégia de arquivo temporário (`temp.txt`).

---

## 📂 Estrutura dos Arquivos Gerados

* `dados.txt` — Contém os valores numéricos originais inseridos pelo usuário (entrada).
* `ordenado.txt` — Contém os valores organizados após a execução do algoritmo de ordenação escolhido.
* `temp.txt` — Arquivo auxiliar utilizado temporariamente para atualizar valores no arquivo original.

---

## 🚀 Como Compilar e Executar

Certifique-se de que você tem um compilador de C instalado (como o **GCC**). Você pode compilar e executar o programa através do terminal com os seguintes comandos:

```bash
# Compilar o código fonte
gcc Main.c -o programa_ordenacao

# Executar o programa
# No Linux / macOS:
./programa_ordenacao

# No Windows:
programa_ordenacao.exe
