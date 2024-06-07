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

void calculateLFSR(char *message, char *generator, FILE *arquivo) {
    int msgLen = strlen(message);
    int genLen = strlen(generator);

    // Inicializa o LFSR com todos os flip-flops em 0
    int lfsr[genLen - 1];
    for (int i = 0; i < genLen - 1; i++) {
        lfsr[i] = 0;
    }

    // Imprime o cabeçalho da tabela
    fprintf(arquivo, "Passo\tI\t");
    for (int i = genLen - 1; i >= 0; i--) {
        fprintf(arquivo, "R%d\t", i);
    }
    fprintf(arquivo, "\n");

    // Processa cada bit da mensagem
    for (int i = 0; i < msgLen; i++) {
        int input_bit = message[i] - '0';
        int feedback = lfsr[genLen - 2] ^ input_bit;

        fprintf(arquivo, "Passo %d\t%d\t", i + 1, input_bit);

        // Atualiza os estados do LFSR
        for (int j = genLen - 2; j > 0; j--) {
            lfsr[j] = lfsr[j - 1];
        }
        lfsr[0] = feedback;

        // Realiza o XOR com o polinômio gerador
        for (int j = 0; j < genLen - 1; j++) {
            if (generator[j] == '1') {
                lfsr[j] ^= feedback;
            }
        }

        // Imprime o estado atual do LFSR
        for (int j = genLen - 2; j >= 0; j--) {
            fprintf(arquivo, "%d\t", lfsr[j]);
        }
        fprintf(arquivo, "\n");
    }

    // Imprime o estado final
    fprintf(arquivo, "Final\t");
    for (int i = genLen - 2; i >= 0; i--) {
        fprintf(arquivo, "%d\t", lfsr[i]);
    }
    fprintf(arquivo, "\n");
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
    char resultadoFinal[lenGen + lenMsg];

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

    FILE *arquivoLFSR = fopen("lfsr2.txt", "w");
    FILE *arquivoLFRSmsnAumentada = fopen("lfsrMsgAumentada.txt", "w");
    FILE *arquivoLFSRres = fopen("lfsrRes.txt", "w");   
    if (arquivoLFSR == NULL) {
        perror("Erro na abertura do arquivo!");
        exit(1);
    }
    calculateLFSR(message, generator, arquivoLFSR);
    fclose(arquivoLFSR);

    return 0;
}
