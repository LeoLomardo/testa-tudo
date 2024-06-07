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
            fprintf(arquivo, "Passo %d:\n", step);
            fprintf(arquivo, "%s <--- entrada atualizada\n", dividend);
            fprintf(arquivo, "%*s%s <--- divisor\n", i, "", generator);
            fprintf(arquivo, "-------------------------------------\n");

            for (int k = 0; k < genLen; k++) {
                dividend[i + k] = (dividend[i + k] == generator[k]) ? '0' : '1';
            }
            fprintf(arquivo, "%s <--- resultado\n", dividend);
            step++;
        } else if (dividend[i] == '0') {
            fprintf(arquivo, "Passo %d:\n", step);
            fprintf(arquivo, "%s <--- entrada atualizada\n", dividend);
            fprintf(arquivo, "%*s%s <--- divisor\n", i, "", generator);
            fprintf(arquivo, "-------------------------------------\n");
            fprintf(arquivo, "%s <--- resultado - sem alterações\n", dividend);
            step++;
        } else {
            printf("Caractere inválido\n");
            exit(1);
        }
    }
    
    fprintf(arquivo, "Resto: %s\n", dividend + msgLen);
    printf("Resto: %s\n", dividend + msgLen);
    strcpy(resultado, dividend + msgLen);
    fprintf(arquivo, "Quociente: %s\n", quotient);
    printf("Quociente: %s\n", quotient);
    fprintf(arquivo, "\nNumero de Passos:%d\n",step - 1);
}

void calculateLFSR(char *message, char *generator, FILE *arquivo) {
    int msgLen = strlen(message);
    int genLen = strlen(generator);

    int lfsr[genLen - 1];
    for (int i = 0; i < genLen - 1; i++) {
        lfsr[i] = 0;
    }
    fprintf(arquivo, "\\begin{table}[h!]\n\\centering\n\\begin{tabular}{|c|c|c|c|c|c|c|c|l|}\n");
    fprintf(arquivo, "\\hline\n");
    fprintf(arquivo, "Passo & R5 & R4 & R3 & R2 & R1 & R0 & Feedback & Bits Restantes \\\\ \\hline\n");

    fprintf(arquivo, "%4d & ", 0);
    for (int j = genLen - 2; j >= 0; j--) {
        fprintf(arquivo, "0 & ");
    }
    fprintf(arquivo, "0 &  ");
    for (int j = 0; j < msgLen; j++) {
        fprintf(arquivo, "%c", message[j]);
    }
    fprintf(arquivo, " \\\\\n\\hline\n");

    for (int i = 0; i < msgLen; i++) {
        int feedback = lfsr[genLen - 2] ^ (message[i] - '0');
        for (int j = genLen - 2; j > 0; j--) {
            lfsr[j] = lfsr[j - 1] ^ (feedback & (generator[j] - '0'));
        }
        lfsr[0] = feedback;
        
        fprintf(arquivo, "%4d & ", i + 1);
        for (int j = genLen - 2; j >= 0; j--) {
            fprintf(arquivo, "%d & ", lfsr[j]);
        }
        fprintf(arquivo, "%d &  ", feedback);
        if (i == (msgLen - 1)) {
            fprintf(arquivo, "-");
        } else {
            for (int j = i + 1; j < msgLen; j++) {
                fprintf(arquivo, "%c", message[j]);
            }
        }
        fprintf(arquivo, " \\\\\n\\hline\n");
    }

    for (int i = 0; i < genLen - 1; i++) {
        int feedback = lfsr[genLen - 2]; 
        for (int j = genLen - 2; j > 0; j--) {
            lfsr[j] = lfsr[j - 1] ^ (feedback & (generator[j] - '0'));
        }
        lfsr[0] = feedback;

        fprintf(arquivo, "%4d & ", msgLen + i + 1);
        for (int j = genLen - 2; j >= 0; j--) {
            fprintf(arquivo, "%d & ", lfsr[j]);
        }
        fprintf(arquivo, "%d & - \\\\\n\\hline\n", feedback);
    }

    fprintf(arquivo, "\\end{tabular}\n\\caption{Evolução do LFSR}\n\\end{table}\n");
}




int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    // Mensagem de entrada de 32 bits
    char message[] = "11001110110110101010101110110101";
    char messageAumentada[] = "110011101101101010101011101101010000000";
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

    FILE *arquivoLFSRmsgnNormal = fopen("lfsrMsgnNormal.tex", "w");

    calculateLFSR(message, generator, arquivoLFSRmsgnNormal);
    
    fclose(arquivoLFSRmsgnNormal);
    return 0;
}

