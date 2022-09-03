#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINK 200

int main(){
     char command[] = "wget --output-document=saida.jpg -nd -r -P /media/HD/DOCUMENTOS/Github/testa-tudo -A jpeg,jpg,bmp,gif,png ";  
     char link[MAX_LINK];

     printf("Insira o link da imagem que deseja inserir:");
     scanf("%s", link);

     strcat(command,link);

     system(command); 
     system("gsettings set org.gnome.desktop.background picture-uri file://///media/HD/DOCUMENTOS/Github/testa-tudo/saida.jpg");
     return 0;
}