//A horrible worlist generator to test and inform the vulnerability at my univesity site

//The site only verifies the first 8 characters in the password, the site doesnt have captch verification neither a limit amout of tries
/*
Implementacoes:
    -Escrever em arquivo binario
    -Criar condições para evitar arquivo mt grande: +1 espaço por senha

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 126
void vetorCaracteres(char* vetorDados);

int main(void){
    unsigned char caracteres[MAX_LEN];
    unsigned char aux[8];

    FILE *arq;
    arq = fopen("wordlistArq", "wb");
    if(arq == NULL){
        printf("Deu ruim");
        exit(1);
    }
    caracteres[0] = 32;
    vetorCaracteres(caracteres);

// i z l j u h t

    for(int i = 0; i < 34; i++){
        for(int z = 0; z < 34; z++){
            for(int l = 0; l < 34;l++){   
                for(int j = 0; j <34; j++){
                    for(int u = 0; u < 34; u++){
                        for(int h = 0; h< 34;h++){
                            for(int t = 0; t < 34; t++){
                                for(int b = 0; b<34; b++){
                                    aux[0] = caracteres[i];
                                    aux[1] = caracteres[z];
                                    aux[2] = caracteres[l];
                                    aux[3] = caracteres[j];
                                    aux[4] = caracteres[u];
                                    aux[5] = caracteres[h];
                                    aux[6] = caracteres[t];
                                    aux[7] = caracteres[b];
                                    fwrite(aux,sizeof(char),8,arq);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    free(arq);
    return 0;
}
//2020201
//0018930
void vetorCaracteres(char* vetorDados){
       for(int i = 1; i<=MAX_LEN - 32  ;i++){
        vetorDados[i] = i+32;
        printf("%c\n",vetorDados[i]);
    }
}



