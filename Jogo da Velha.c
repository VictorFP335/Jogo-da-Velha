#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<locale.h>

#define SIZE 4
#define SIMULATIONS 3000


char board[SIZE][SIZE];


typedef struct {
    int row;
    int col;
} Move;


void printBoard() {
    printf("\n-------------\n");
    for (int i = 1; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n-------------\n");
    }
}

//chance de vitoria
int checkWin(char player) {
    for (int i = 1; i < SIZE; i++) {
        if ((board[i][1] == player && board[i][2] == player && board[i][3] == player) ||
            (board[1][i] == player && board[2][i] == player && board[3][i] == player)) {
            return 1;
        }
    }


    if ((board[1][1] == player && board[2][2] == player && board[3][3] == player) ||
        (board[1][3] == player && board[2][2] == player && board[3][1] == player)) {
        return 1; // O jogador ganhou
    }

    return 0;
}

//empate com quadro completo
int isBoardFull() {
    for (int i = 1; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1; // Tabuleiro cheio
}

//  A jogada do Humano
void playerMove() {
    int row, col;
    printf("Digite a linha (1 a 3): ");
    scanf("%d", &row);
    printf("Digite a coluna (1 a 3): ");
    scanf("%d", &col);

    // Verificar se esta vazia o quadrante
    if (board[row][col] == ' ') {
        board[row][col] = 'X';
    } else {
        printf("Célula ocupada. Tente novamente.\n");
        playerMove();
    }
}

// A jogada da IA usando Monte Carlo
Move monteCarloMove() {
    Move move;
    do {
        move.row = rand() % SIZE;
        move.col = rand() % SIZE;
    } while (board[move.row][move.col] != ' '); // Continua escolhendo até encontrar uma célula vazia

    return move;
}

int main() {
    setlocale(LC_ALL,"portuguese");
    // Inicia o tabuleiro
    for (int i = 1; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }

    srand(time(NULL)); // Inicia os números aleatórios

    while (1) {
        printBoard();
        playerMove();

        if (checkWin('X')) {
            printBoard();
            printf("Você ganhou! Parabéns!\n");
            break;
        }

        if (isBoardFull()) {




            printBoard();
            printf("Empate! O tabuleiro está cheio.\n"); //Empate
            break;
        }

        printBoard();
        printf("Vez da IA...\n");

        Move aiMove = monteCarloMove();
        board[aiMove.row][aiMove.col] = 'O';

        if (checkWin('O')) {
            printBoard();
            printf("A IA ganhou! Tente novamente.\n"); //IA ganhou do jogador Humano
            break;
        }

        if (isBoardFull()) {
            printBoard();
            printf("Empate! O tabuleiro está cheio.\n"); //Empate
            break;
        }
    }

    return 0;
}
