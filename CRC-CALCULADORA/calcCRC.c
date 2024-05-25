#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void calculateCRC(char *message, char *generator, FILE *arquivo, char *resultado) {

    int msgLen = strlen(message);
    int genLen = strlen(generator);

    char dividend[msgLen + genLen]; 
    char quotient[msgLen + 1]; 

    strcpy(dividend, message);

    for (int i = 0; i < genLen - 1; i++) {
        strcat(dividend, "0");
    }

    memset(quotient, '0', msgLen); // Inicializa o quociente com '0's
    quotient[msgLen] = '\0'; // Termina a string do quociente

    fprintf(arquivo, "Mensagem aumentada: %s\n\n", dividend);
    printf("Mensagem aumentada: %s\n", dividend);

   
    int step = 1;
    
    for (int i = 0; i <= msgLen; i++) {
        // Realizar a operação XOR se o bit atual for '1'
        if (dividend[i] == '1') {
            quotient[i] = '1';

            fprintf(arquivo, "Passo %d:\n", step);
            fprintf(arquivo, "%s <--- entrada deslocada para a direita com %d zeros\n", dividend, i);
            fprintf(arquivo, "%*s%s <--- divisor\n", i, "", generator); // Alinha o divisor com a parte do dividendo
            fprintf(arquivo, "-------------------------------------\n");

            for (int k = 0; k < genLen; k++) {
                dividend[i + k] = (dividend[i + k] == generator[k]) ? '0' : '1';
            }

            // Imprimir o resultado da operação XOR
            fprintf(arquivo, "%s <--- resultado\n\n", dividend);

            step++;
        }
    }

    fprintf(arquivo, "Resto : %s\n", dividend + msgLen);
    printf("Resto: %s\n", dividend + msgLen);
    strcpy(resultado, dividend + msgLen);

    fprintf(arquivo, "Quociente: %s\n", quotient);
    printf("Quociente: %s\n", quotient);

}

int main() {
    // Mensagem de entrada de 32 bits
    char message[] = "11001110110110101010101110110101"; 

    // Polinômio gerador: X^6 + X^5 + X^3 + X + 1
    char generator[] = "1101011";
    int lenGen = strlen(generator);
    int lenMsg = strlen(message);

    char resultado[lenGen+1];

    char resultadoFinal[lenGen+lenMsg];  // Inicializar com string vazia
    memset(resultadoFinal, 0x00, sizeof(resultadoFinal));
    // Limpar o conteúdo do arquivo antes de iniciar o cálculo
    FILE *arquivo = fopen("crc.txt", "w");
    if (arquivo == NULL) {
        perror("Erro na abertura do arquivo!");
        exit(1);
    }
    fclose(arquivo);
    
    // Reabrir o arquivo no modo de adição
    arquivo = fopen("crc.txt", "a+");
    if (arquivo == NULL) {
        perror("Erro na abertura do arquivo!");
        exit(1);
    }

    fprintf(arquivo, "Mensagem original: %s\n", message);
    fprintf(arquivo, "Polinomio gerador: %s\n", generator);
    printf("Mensagem original: %s\n", message);
    printf("Polinomio gerador: %s\n", generator);
    
    calculateCRC(message, generator, arquivo, resultado);

    strcat(resultadoFinal, message);
    strcat(resultadoFinal, resultado);
    printf("Resultado final: %s\n", resultadoFinal);
    fprintf(arquivo,"Resultado final: %s\n", resultadoFinal);
    fclose(arquivo);
    return 0;
}
