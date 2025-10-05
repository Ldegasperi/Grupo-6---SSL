#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Nodo {
    int info;
    struct Nodo* sgte;
} Nodo;


void push(Nodo **pila, int valor) {
    Nodo *nuevo = (Nodo*) malloc(sizeof(Nodo));
    if (!nuevo) {
        printf("Error: no se pudo asignar memoria\n");
        return;
    }
    nuevo->info = valor;
    nuevo->sgte = *pila;
    *pila = nuevo;
}

int pop(Nodo **pila) {
    int ret = (*pila)->info;
    Nodo *aux = *pila;
    *pila = aux->sgte;
    free(aux);
    return ret;
}


int evaluarPostfijo() {
    Nodo *pila = NULL;
    char token[50];

    printf("Ingrese la expresion en notacion postfija (termine con '='):\n");

    while (1) {
        scanf("%s", token);

        // condición de corte
        if (token[0] == '=') {
            break;
        }

        // si es número (positivo o negativo)
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&pila, atoi(token));
        }
        // si es operador
        else {
            int b = pop(&pila);
            int a = pop(&pila);

            int resultado = 0;
            switch (token[0]) {
                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/':
                    if (b == 0) {
                        printf("Error: división por cero\n");
                        return 0;
                    }
                    resultado = a / b; 
                    break;
                default:
                printf("Operador no válido: %s\n", token);
                    return 0;
            }
            push(&pila, resultado);
        }
    }

    int resultado = pop(&pila);
    return resultado;
}


int main() {
    int resultado = evaluarPostfijo();
    printf("Resultado: %d\n", resultado);
    return 0;
}
