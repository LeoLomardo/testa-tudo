#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Função para calcular o CRC
void calculateCRC(char *message, char *generator, FILE *arquivo, char *resultado) {
    int msgLen = strlen(message);
    int genLen = strlen(generator);

    char dividend[msgLen + genLen];
    char quotient[msgLen + 1];

    strcpy(dividend, message);
    for (int i = 0; i < genLen - 1; i++) {
        strcat(dividend, "0");
    }
    memset(quotient, '0', msgLen);
    quotient[msgLen] = '\0';
    fprintf(arquivo, "Mensagem aumentada: %s\n\n", dividend);
    printf("Mensagem aumentada: %s\n", dividend);

    int step = 1;
    for (int i = 0; i < msgLen; i++) {
        if (dividend[i] == '1') {
            quotient[i] = '1';
            fprintf(arquivo, "\\underline{Passo %d:}\n\n", step);
            fprintf(arquivo, "\\begin{verbatim}\n");
            fprintf(arquivo, "%s <--- entrada atualizada\n", dividend);
            fprintf(arquivo, "%*s%s <--- divisor\n", i, "", generator);
            fprintf(arquivo, "-------------------------------------\n");

            for (int k = 0; k < genLen; k++) {
                dividend[i + k] = (dividend[i + k] == generator[k]) ? '0' : '1';
            }
            fprintf(arquivo, "%s <--- resultado\n", dividend);
            fprintf(arquivo, "\\end{verbatim}\n\n");
            step++;
        } else if (dividend[i] == '0') {
            fprintf(arquivo, "\\underline{Passo %d:}\n\n", step);
            fprintf(arquivo, "\\begin{verbatim}\n");
            fprintf(arquivo, "%s <--- entrada atualizada\n", dividend);
            fprintf(arquivo, "%*s%s <--- divisor\n", i, "", generator);
            fprintf(arquivo, "-------------------------------------\n");
            fprintf(arquivo, "%s <--- resultado - sem alterações\n", dividend);
            fprintf(arquivo, "\\end{verbatim}\n\n");
            step++;
        } else {
            printf("Caractere inválido\n");
            exit(1);
        }
    }
    fprintf(arquivo, "\\textbf{Resto: }\n\n");
    fprintf(arquivo, "\\begin{verbatim}\n");
    fprintf(arquivo, "%s <--- resultado após %d passos de execução\n", dividend, step);
    fprintf(arquivo, "\\end{verbatim}\n\n");

    fprintf(arquivo, "Resto: %s\n", dividend + msgLen);
    printf("Resto: %s\n", dividend + msgLen);
    strcpy(resultado, dividend + msgLen);
    fprintf(arquivo, "Quociente: %s\n", quotient);
    printf("Quociente: %s\n", quotient);
}

// Função para evoluir o LFSR ao percorrer a mensagem e gerar o conteúdo LaTeX
void lfsrWithMessage(char *initialState, char *message, FILE *arquivo) {
    int stateLen = strlen(initialState);
    int msgLen = strlen(message);
    char state[stateLen + 1];
    strcpy(state, initialState);

    fprintf(arquivo, "Estado inicial do LFSR: %s\n", state);
    printf("Estado inicial do LFSR: %s\n", state);

    // LaTeX table header
    fprintf(arquivo, "\\begin{table}[h!]\n");
    fprintf(arquivo, "\\centering\n");
    fprintf(arquivo, "\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|}\n");
    fprintf(arquivo, "\\hline\n");
    fprintf(arquivo, "$t$ & $R_6$ & $R_5$ & $R_4$ & $R_3$ & $R_2$ & $R_1$ & $R_0$ & $I(t)$ & $O(t)$ \\\\\n");
    fprintf(arquivo, "\\hline\n");

    for (int i = 0; i < msgLen; i++) {
        // Bit de saída é o bit mais à direita do registro
        char bitSaida = state[stateLen - 1];

        // Calcular o novo bit de feedback
        char feedback = (state[stateLen - 1] - '0') ^ (state[stateLen - 2] - '0') ^ (state[stateLen - 4] - '0') ^ (message[i] - '0');
        feedback = feedback ? '1' : '0'; // Assegurar que o feedback seja '1' ou '0'

        // Deslocar os bits do registro para a direita
        for (int j = stateLen - 1; j > 0; j--) {
            state[j] = state[j - 1];
        }
        state[0] = feedback; // Inserir o novo bit de feedback na posição mais à esquerda

        // Escrever estado atual na tabela LaTeX
        fprintf(arquivo, "%d & ", i + 1);
        for (int j = 0; j < stateLen; j++) {
            fprintf(arquivo, "%c & ", state[j]);
        }
        fprintf(arquivo, "%c & %c \\\\\n", message[i], bitSaida);  // Incluir I(t) e O(t)
        fprintf(arquivo, "\\hline\n");

        printf("Passo %d: %s, I(t): %c, O(t): %c\n", i + 1, state, message[i], bitSaida);
    }

    // LaTeX table footer
    fprintf(arquivo, "\\end{tabular}\n");
    fprintf(arquivo, "\\caption{Evolução do LFSR}\n");
    fprintf(arquivo, "\\label{tab:lfsr}\n");
    fprintf(arquivo, "\\end{table}\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    // Mensagem de entrada de 32 bits
    char message[] = "11001110110110101010101110110101";

    // Polinômio gerador: X^6 + X^5 + X^3 + X + 1
    char generator[] = "1101011";
    int lenGen = strlen(generator);
    int lenMsg = strlen(message);

    char resultado[lenGen + 1];
    char resultadoFinal[lenGen + lenMsg]; // Inicializar com string vazia

    FILE *arquivoCRC = fopen("crc.txt", "w");
    if (arquivoCRC == NULL) {
        perror("Erro na abertura do arquivo!");
        exit(1);
    }
    fprintf(arquivoCRC, "Mensagem original: %s\n", message);
    fprintf(arquivoCRC, "Polinômio gerador: %s\n", generator);
    printf("Mensagem original: %s\n", message);
    printf("Polinômio gerador: %s\n", generator);

    calculateCRC(message, generator, arquivoCRC, resultado);

    strcat(resultadoFinal, message);
    strcat(resultadoFinal, resultado);
    printf("Resultado final: %s\n", resultadoFinal);
    fprintf(arquivoCRC, "Resultado final: %s\n", resultadoFinal);
    fclose(arquivoCRC);

    // LFSR
    char initialState[7] = "000000";  // Definir estado inicial
    FILE *arquivoLFSR = fopen("lfsr.txt", "w");
    if (arquivoLFSR == NULL) {
        perror("Erro na abertura do arquivo!");
        exit(1);
    }

    lfsrWithMessage(initialState, message, arquivoLFSR); // Evoluir o LFSR percorrendo a mensagem
    fclose(arquivoLFSR);

    return 0;
}
