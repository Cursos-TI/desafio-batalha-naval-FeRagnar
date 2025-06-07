#include <stdio.h>

#define TAB_SIZE 10
#define HABILIDADE_SIZE 7

// Função para calcular valor absoluto (em C puro)
int valorAbsoluto(int x) {
    return (x < 0) ? -x : x;
}

// Função para aplicar a habilidade no tabuleiro
void aplicaHabilidade(int tabuleiro[TAB_SIZE][TAB_SIZE], int habilidade[HABILIDADE_SIZE][HABILIDADE_SIZE], int origemLinha, int origemColuna) {
    int meio = HABILIDADE_SIZE / 2;

    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = origemLinha + (i - meio);
                int colTab = origemColuna + (j - meio);
                // Verifica se está dentro do tabuleiro
                if (linhaTab >= 0 && linhaTab < TAB_SIZE && colTab >= 0 && colTab < TAB_SIZE) {
                    // Só marca se não for navio (3)
                    if (tabuleiro[linhaTab][colTab] != 3) {
                        tabuleiro[linhaTab][colTab] = 5; // Marca área de habilidade
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE] = {0};

    // Posiciona alguns navios (exemplo simples)
    // Navio horizontal tamanho 3
    int navio1Linha = 1, navio1Coluna = 1;
    for (int i = 0; i < 3; i++) {
        tabuleiro[navio1Linha][navio1Coluna + i] = 3;
    }

    // Navio vertical tamanho 3
    int navio2Linha = 5, navio2Coluna = 4;
    for (int i = 0; i < 3; i++) {
        tabuleiro[navio2Linha + i][navio2Coluna] = 3;
    }

    // Matriz para habilidade Cone (7x7)
    int cone[HABILIDADE_SIZE][HABILIDADE_SIZE] = {0};
    int meio = HABILIDADE_SIZE / 2;
    // Construindo cone - triângulo invertido (ponta no topo)
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        int largura = i * 2 + 1;
        int inicio = meio - i;
        int fim = meio + i;
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            if (j >= inicio && j <= fim) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }

    // Matriz para habilidade Cruz (7x7)
    int cruz[HABILIDADE_SIZE][HABILIDADE_SIZE] = {0};
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            if (i == meio || j == meio) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }

    // Matriz para habilidade Octaedro (7x7)
    int octaedro[HABILIDADE_SIZE][HABILIDADE_SIZE] = {0};
    for (int i = 0; i < HABILIDADE_SIZE; i++) {
        for (int j = 0; j < HABILIDADE_SIZE; j++) {
            int dist = valorAbsoluto(i - meio) + valorAbsoluto(j - meio);
            if (dist <= 3) {
                octaedro[i][j] = 1;
            } else {
                octaedro[i][j] = 0;
            }
        }
    }

    // Define pontos de origem das habilidades no tabuleiro
    int origemConeLinha = 2, origemConeColuna = 2;
    int origemCruzLinha = 7, origemCruzColuna = 7;
    int origemOctaedroLinha = 5, origemOctaedroColuna = 5;

    // Aplica habilidades no tabuleiro
    aplicaHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    aplicaHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    aplicaHabilidade(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    // Imprime o tabuleiro final
    // 0 = água, 3 = navio, 5 = área afetada por habilidade
    printf("Tabuleiro com navios e habilidades especiais (0=agua, 3=navio, 5=habilidade):\n\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}