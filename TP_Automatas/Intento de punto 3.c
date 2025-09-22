#include <stdio.h>
#include <string.h>

int esOperador(char c){
     return (c == '+' || c == '-' || c == '*' || c == '/');
}


int esValido(char c) {
    return (isdigit(c) || esOperador(c));
}

int validarCadena (char *expresion){
    int i = strlen (expresion);
    if (i==0) return 0;
    if(esOperador(expresion[0]|| esOperador(expresion[i-1])))return 0;

    for(int j=0; j<i;i++){
        if(!esValido(expresion[i])) return 0;
    }
    if (esOperador(expresion[j]) && esOperador(expresion[j+1]))return 0;

return 1;
}
