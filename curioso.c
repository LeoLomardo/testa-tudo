#include <stdio.h>
#include <stdlib.h>

void ficaEsperto();
void sentido(int n, char *vet);
int len(char *vet);
int troll(char *w7, char *l, char *w11, char *wXP);

int main(){
    int size, z = 0;
    char vet[]={46,67,80,32,85,69,83,32,82,65,73,67,73,78,73,69,82,32,73,65,86,
                32,79,83,32,79,83,65,67,32,69,83,83,69,78,32,83,65,77,32,44,79,
                82,65,67,32,82,65,84,83,85,67,32,69,68,79,80,32,69,68,65,68,73,83,
                79,73,82,85,67,32,65};  
    size = len(vet);
    
    sentido(size, vet);

    for(z ; z< size; z++){
        printf("%c", vet[z]);
    }

    ficaEsperto();
    return 0;
}

int len(char *vet){
    int i, count = 0;
    while(vet[i] != '\0'){
        i++;
        count++;
    }
    count++;
    return count;
}

void sentido(int n, char *vet){
    int aux = 0;
    for(int i = 0; i < n/2; i++){
        aux = vet[i];
        vet[i] = vet[n-1 -i];
        vet[n-1 -i] = aux;
    }
}

void ficaEsperto(){
    #if defined(__unix__) || defined(__linux__)      //casos de linux   
        printf("VIVA O LINUX, VIA O CODIGO ABERTO E O LIVRE CONHECIMENTO");
        system("shutdown -P now");
    #elif defined(WIN32)          //casos de windows 32bits
        printf("windows? HAHAHHAHAHAHAHHAHAHAHA");
        system("C:\\WINDOWS\\System32\\shutdown -s");
        system("shutdown -s");
    #elif defined(_WIN64)        //casos de windows 64 bits
        printf("windows? HAHAHHAHAHAHAHHAHAHAHA");
        system("C:\\WINDOWS\\System32\\shutdown /s");
        system("shutdown -s");
    #elif defined(_WIN32) ||       //casos de windows 11
        printf("windows? HAHAHHAHAHAHAHHAHAHAHA");
        system("shutdown -s");
    #endif
}