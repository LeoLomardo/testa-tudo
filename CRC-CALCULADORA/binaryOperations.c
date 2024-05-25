#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para inverter uma string
char* reverse(const char *text) {
    int len = strlen(text);
    char *reversed = (char *)malloc(len + 1);
    for (int i = 0; i < len; i++) {
        reversed[i] = text[len - 1 - i];
    }
    reversed[len] = '\0';
    return reversed;
}

// Função para exibir o polinômio correspondente à string binária
void showpoly(const char *a, FILE *file) {
    int nobits = strlen(a);
    char str1[1024] = "";

    for (int x = 0; x < nobits - 2; x++) {
        if (a[x] == '1') {
            char term[50];
            if (strlen(str1) == 0) {
                sprintf(term, "x**%d", nobits - x - 1);
            } else {
                sprintf(term, "+x**%d", nobits - x - 1);
            }
            strcat(str1, term);
        }
    }

    if (a[nobits - 2] == '1') {
        if (strlen(str1) == 0) {
            strcat(str1, "x");
        } else {
            strcat(str1, "+x");
        }
    }

    if (a[nobits - 1] == '1') {
        strcat(str1, "+1");
    }

    fprintf(file, "%s\n", str1);
}

// Função personalizada para converter um inteiro em uma string binária
void intToBinaryString(unsigned long int value, char *str,  int strSize) {
    str[strSize - 1] = '\0';
    for (int i = strSize - 2; i >= 0; i--) {
        str[i] = (value % 2) ? '1' : '0';
        value /= 2;
    }
}

// Função para realizar a multiplicação binária e imprimir cada etapa no arquivo
unsigned int multiply(const char *a, const char *b, FILE *file) {
    unsigned long int bit1 = strtoul(a, NULL, 2);
    unsigned long int bit2 = strtoul(b, NULL, 2);
    unsigned int g[50];
    long int nobits = strlen(b);
    long int maxLen = strlen(a) + strlen(b);

    char formatStr[100];
    sprintf(formatStr, "%%%ds\n", 50);

    fprintf(file, formatStr, a);
    fprintf(file, formatStr, b);
    fprintf(file, "%s\n", "x");

    char *reversed = reverse(b);
    for (int i = 0; i < nobits; i++) {
        if (reversed[i] == '0') {
            g[i] = 0;
        } else {
            g[i] = bit1 << i;
        }

        char binStr[maxLen + 1];
        intToBinaryString(g[i], binStr, maxLen + 1);
        fprintf(file, formatStr, binStr);
    }
    free(reversed);

    unsigned long int res = g[0];
    for (int i = 1; i < nobits; i++) {
        res ^= g[i];
    }

    char binStr[maxLen + 1];
    intToBinaryString(res, binStr, maxLen + 1);
    fprintf(file, "%s\n", binStr);
    fprintf(file, "%s\n", "=");

    return res;
}

int main(int argc, char *argv[]) {
    char val1[] = "10010011101010000111101101001101";
    char val2[] = "1101011";

    if (argc > 1) {
        strcpy(val1, argv[1]);
    }
    if (argc > 2) {
        strcpy(val2, argv[2]);
    }

    FILE *file = fopen("output.txt", "w");
    if (!file) {
        perror("Could not open file");
        return 1;
    }

    fprintf(file, "Binary form:\t%s x %s\n", val1, val2);
    fprintf(file, "Decimal form:\t%ld x %ld\n", strtoul(val1, NULL, 2), strtoul(val2, NULL, 2));
    fprintf(file, "\n");

    showpoly(val1, file);
    showpoly(val2, file);

    fprintf(file, "\nWorking out:\n\n");
    unsigned long int res = multiply(val1, val2, file);

    fprintf(file, "\nResult: %u\n", res);

    fclose(file);

    return 0;
}
