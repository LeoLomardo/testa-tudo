#include <stdio.h>

int main()
{

     char command[] = "wget -A png,jpeg,jpg,gif -r https://en.wikipedia.org/wiki/Botafogo_de_Futebol_e_Regatas_%28basketball%29";  
     system(command); 
     return 0;
}