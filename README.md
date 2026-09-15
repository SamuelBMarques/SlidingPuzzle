
# 🧩 Sliding Puzzle

Um jogo de **Sliding Puzzle (Quebra-Cabeças Deslizante)** desenvolvido em **C** para execução no terminal.

O objetivo é organizar as peças em ordem crescente, utilizando o espaço vazio para movimentar as peças adjacentes.

O projeto foi desenvolvido como trabalho prático da disciplina de **Introdução à Programação (BCC201)**.

---

## 🎮 Funcionalidades

- Tabuleiros de `3 × 3` até `10 × 10`
- Três níveis de dificuldade: Fácil, Médio e Difícil
- Embaralhamento aleatório do tabuleiro
- Movimentação das peças pelo número correspondente
- Contagem de movimentos
- Verificação automática da solução
- Salvamento e carregamento de partidas
- Continuação de partidas em andamento
- Interface colorida no terminal

---

## 🕹️ Como jogar

Ao iniciar o programa, o menu principal apresenta as seguintes opções:

```text
N - Iniciar um novo jogo
C - Continuar o jogo atual
S - Carregar um jogo salvo
A - Exibir instruções
X - Sair
````

Ao iniciar um novo jogo, o jogador escolhe o tamanho do tabuleiro e o nível de dificuldade.

Durante a partida, basta informar o **número da peça** que deseja movimentar.

Exemplo:

```text
Digite um comando ou número da peça que quer mover: 5
```

Também é possível utilizar comandos como:

```text
salvar nome_do_arquivo
voltar
```

---

## 🎯 Objetivo

O jogador vence quando todas as peças estão organizadas em ordem crescente.

Exemplo de um tabuleiro `3 × 3` resolvido:

```text
┏━━┳━━┳━━┓
┃ 1┃ 2┃ 3┃
┣━━╋━━╋━━┫
┃ 4┃ 5┃ 6┃
┣━━╋━━╋━━┫
┃ 7┃ 8┃  ┃
┗━━┻━━┻━━┛
```

---

## 🛠️ Tecnologias

* **C**
* **GCC**
* Alocação dinâmica de memória
* Manipulação de matrizes
* Estruturas (`struct`)
* Manipulação de arquivos
* Geração de números aleatórios
* ANSI Escape Codes

---

## 📁 Estrutura

```text
SlidingPuzzle/
│
├── main_tp.c
├── quebracabecas_tp.c
├── quebracabecas_tp.h
└── README.md
```

* `main_tp.c` — fluxo principal e menu do jogo
* `quebracabecas_tp.c` — implementação das funcionalidades
* `quebracabecas_tp.h` — estruturas, constantes e protótipos

---

## 💻 Compilação

Compile utilizando o GCC:

```bash
gcc main_tp.c quebracabecas_tp.c -o sliding_puzzle -lm
```

Depois, execute:

```bash
./sliding_puzzle
```

> Recomenda-se utilizar um terminal com suporte a cores ANSI e caracteres Unicode.

---

## 📚 Contexto acadêmico

**Disciplina:** Introdução à Programação — BCC201
**Aluno:** Samuel Braga Marques
**Versão:** 1.4
**Data:** 01/10/2024

---

## 👨‍💻 Autor

**Samuel Braga Marques**

GitHub: [@SamuelBMarques](https://github.com/SamuelBMarques)
