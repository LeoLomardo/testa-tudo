#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void calculateCRC(char *message, char *generator, FILE *arquivo, char *resultado) {
    int msgLen = strlen(message);
    int genLen = strlen(generator);
    char dividend[msgLen + genLen]; // Alocar espa�o suficiente para a mensagem aumentada
    char quotient[msgLen + 1]; // Quociente ter� o mesmo tamanho da mensagem original

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
        // Realizar a opera��o XOR se o bit atual for '1'
        if (dividend[i] == '1') {
            quotient[i] = '1'; // Define o bit do quociente como '1'
            
            // Imprimir o estado atual do dividendo
            fprintf(arquivo, "Passo %d:\n", step);
            fprintf(arquivo, "%s <--- entrada deslocada para a direita com %d zeros\n", dividend, i);
            fprintf(arquivo, "%*s%s <--- divisor\n", i, "", generator); // Alinha o divisor com a parte do dividendo
            fprintf(arquivo, "------------------\n");

            for (int k = 0; k < genLen; k++) {
                dividend[i + k] = (dividend[i + k] == generator[k]) ? '0' : '1';
            }

            // Imprimir o resultado da opera��o XOR
            fprintf(arquivo, "%s <--- resultado\n\n", dividend);

            step++;
        }
    }

    // Copiar o resto final para a vari�vel resultado
    fprintf(arquivo, "Resto final: %s\n", dividend + msgLen);
    printf("Resto final: %s\n", dividend + msgLen);
    strcpy(resultado, dividend + msgLen);

    // Imprimir o quociente
    fprintf(arquivo, "Quociente: %s\n", quotient);
    printf("Quociente: %s\n", quotient);
}

int main() {
    // Mensagem de entrada de 32 bits
    char message[] = "101011"; 

    // Polin�mio gerador: X^6 + X^5 + X^3 + X + 1
    char generator[] = "1101";
    int msgLen = strlen(message);
    int genLen = strlen(generator);
    char resultado[genLen+1];
    char resultadoFinal[genLen+msgLen+1];  // Inicializar com string vazia

    // Limpar o conte�do do arquivo antes de iniciar o c�lculo
    FILE *arquivo = fopen("crc2.txt", "w+");
    if (arquivo == NULL) {
        perror("Erro na abertura do arquivo!");
        exit(1);
    }

    
    // Reabrir o arquivo no modo de adi��o


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
