#include <stdio.h>
#include <stdlib.h>

// Função para realizar o tratamento de bordas com zero
void zeroPadding(int **matriz, int linhas, int colunas, int **matrizExpandida) {
    // Preencher a matriz expandida com zeros nas bordas
    for (int i = 0; i < linhas + 2; i++) {
        for (int j = 0; j < colunas + 2; j++) {
            if (i == 0 || i == linhas + 1 || j == 0 || j == colunas + 1) {
                matrizExpandida[i][j] = 0;
            } else {
                matrizExpandida[i][j] = matriz[i - 1][j - 1];
            }
        }
    }
}

// Função para aplicar o filtro de média 3x3
void filtroMedia(int **matrizExpandida, int linhas, int colunas, int **resultado) {
    for (int i = 1; i <= linhas; i++) {
        for (int j = 1; j <= colunas; j++) {
            // Calcular a média dos valores vizinhos
            int soma = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    soma += matrizExpandida[i + k][j + l];
                }
            }
            resultado[i - 1][j - 1] = soma / 9; 
        }
    }
}

// Função para salvar a matriz em formato PGM
void salvarPGM(const char *diretorio, const char *nomeArquivo, int **matriz, int linhas, int colunas) {
    char caminhoCompleto[1000];  
    snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s/%s", diretorio, nomeArquivo);

    FILE *arquivo = fopen(caminhoCompleto, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(arquivo, "P2\n");
    fprintf(arquivo, "%d %d\n", colunas, linhas);
    fprintf(arquivo, "255\n");

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fprintf(arquivo, "%d ", matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

int main() {
    int linhas = 3;
    int colunas = 5;

    // Criar matriz original
    int **matrizOriginal = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matrizOriginal[i] = (int *)malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            matrizOriginal[i][j] = i * colunas + j + 1;
        }
    }

    // Criar matriz expandida com dimensões aumentadas
    int linhasExpandida = linhas + 2;
    int colunasExpandida = colunas + 2;
    int **matrizExpandida = (int **)malloc(linhasExpandida * sizeof(int *));
    for (int i = 0; i < linhasExpandida; i++) {
        matrizExpandida[i] = (int *)malloc(colunasExpandida * sizeof(int));
    }

    // Realizar o tratamento de bordas com zero
    zeroPadding(matrizOriginal, linhas, colunas, matrizExpandida);

    // Criar matriz para armazenar o resultado do filtro de média
    int **resultado = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        resultado[i] = (int *)malloc(colunas * sizeof(int));
    }

    // Aplicar o filtro de média 3x3
    filtroMedia(matrizExpandida, linhas, colunas, resultado);

    // Solicitar o diretório ao usuário
    char diretorio[1000];  
    printf("Digite o diretório de destino para salvar o arquivo: ");
    scanf("%s", diretorio);

    // Salvar a matriz resultado em formato PGM no diretório especificado
    salvarPGM(diretorio, "resultado.pgm", resultado, linhas, colunas);

    // Liberar a memória alocada
    for (int i = 0; i < linhas; i++) {
        free(matrizOriginal[i]);
        free(resultado[i]);
    }
    free(matrizOriginal);
    free(resultado);

    for (int i = 0; i < linhasExpandida; i++) {
        free(matrizExpandida[i]);
    }
    free(matrizExpandida);

    return 0;
}
