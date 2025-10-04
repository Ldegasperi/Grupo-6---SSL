#include <stdio.h>
#include <ctype.h>

int caracterANumero(char* cadena){
    
    int i = 0;
    int resultado = 0;
    int c = cadena[i];
    while(c != '\0'){
        int charAInt = c -'0';
        resultado = resultado * 10 + charAInt;
        i++;
        c = cadena[i];
    }
    return resultado;
}

main(){
    char numero[100];
    printf("Introduzca un numero: ");
    scanf("%s", &numero);
    int numeroDado = caracterANumero(numero);
    printf("%i\n",numeroDado);

}
