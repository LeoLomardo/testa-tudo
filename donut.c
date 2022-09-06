#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

# define PIPI           3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006  /* pi */
# define EVER ;;
#define _BSD_SOURCE
int main() {
    float A = 1000, B = 10; //sentido de rotacao
    float i, j;
    int k;
    float z[2000]; //manter 2000 para ambos 
    char b[2000];
    printf("\x1b[2J"); //ASCII Escape code, nesse caso ele limpa a tela 
    for(EVER) {
        memset(b,32,2000); //coordenada da tela
        memset(z,0,8000);
        for(j=0; j < 2*PIPI; j += 0.07) {
            for(i=0; i < 2*PIPI; i += 0.01) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;  // basicamente a distancia de visao e tamanho do donut manter + 2
                float D = 0.9 / (c * h * e + f * g + 5); //essa ultima adicao define a distancia do centro do donut q esta o espectador 
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y= 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 3 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n); //indice de luz, quanto maior o primeiro multiplicador, mais densa sera a imagem 
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".'`^,:;Il!i><~+_-?][}{1)(|tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$"[N > 0 ? N : 0];
                }
            }
        }
        printf("\x1b[H");
        for(k = 0; k < 2000; k++) { //2000 envolve taxa de atulaizacao da img, manter 2000
            putchar(k % 80 ? b[k] : 10);
            A += 0.00004; //velocidade
            B += 0.00002; //velocidade
        }
        usleep(30);
    }
    return 0;
}