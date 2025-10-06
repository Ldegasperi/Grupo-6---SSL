#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int retornar_columna(int c, int consigna_seleccionada)
{
	if(consigna_seleccionada == 1){
		if(c == '-' || c == '+') return 0;
		if(c == '0') return 1;
		if(c == 'x' || c=='X') return 2;
		if(c == '#') return 3;
		if(c >= '1' && c <= '7') return 4;
		if(c == '8' || c == '9') return 5;
		if((c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) return 6;
		return 7;
	}else{
		if(c>='0' && c <= '9') return 0;
		if(c=='-' || c == '+' || c=='*' || c=='/') return 1;
		return 2;
	}
	
}

int es_palabra(char* cadena, int filas, int columnas, int tt[filas][columnas], int consigna_seleccionada)
{
	int e = 0;						
	int i = 0;					
	char c = cadena[i];

	int contador = 1;
	
	if(consigna_seleccionada == 1)
	{
		while(c != '\0' && e != 8){
			e = tt[e][retornar_columna(c, consigna_seleccionada)];	
			i++;
			c = cadena[i];
		}
		if(e == 2 || e == 3 || e == 5|| e == 6 || e == 7) return 1; // Chequea que haya terminado en un estado final, en ese caso devuelve 1 (verdadero)
		return 0;
	} else if (consigna_seleccionada == 2)
	{
		while(c != '\0' && e != 2)
		{
			e = tt[e][retornar_columna(c, consigna_seleccionada)];
			i++;
			c=cadena[i];
		}
		if(e==1) return 1; // Chequea que el estado en el cual termino se uno de aceptación
		return 0;
	}
}

/* PUNTO 1 */
void contar_tipos(char* cadena, int* cant_hexadecimales, int* cant_octales, int* cant_decimales)
{	
	int i = 0;
	char c = cadena[i]; 
	int analizar = 1; // Pseudo booleano	
	
	while(c != '\0'){
		
		if(analizar == 1){
			if(c != '0' || (c == '0' && (cadena[i+1] == '#' || cadena[i+1] == '\0' ))){ // Decimales NO empiezan por cero
				(*cant_decimales)++;
			}else if(cadena[i+1] == 'x' || cadena[i+1] == 'X'){ // Si empieza por cero y ademas el caracter siguiente es una x
				(*cant_hexadecimales)++;
			}else{	 // Si empieza por cero y el caracter siguiente no es una x
				(*cant_octales)++;
			}
			analizar = 0;	
		}
		
		if(c == '#') analizar = 1;
		
		i++;
		c = cadena[i]; 
	}
}
/*FIN PUNTO 1*/

/*PUNTO 2*/
int caracter_a_numero(char caracter)
{
  return caracter - '0';
}
/*FIN PUNTO 2*/

/*PUNTO 3*/

// CODIGO PARA RESOLVER PRECEDENCIA DE OPERACIONES
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

int esOperador(char c) {
    return (c == '*' || c == '/' || c == '+' || c == '-');
}

int evaluarPostfijo(char* cadena) {
    Nodo *pila = NULL;
	int i = 0;
    while (cadena[i] != '\0') {
      
        // si es operador
        if (esOperador(cadena[i])) {
            int b = pop(&pila);
            int a = pop(&pila);

            int resultado = 0;
            switch (cadena[i]) {
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
                    printf("Operador no válido: %s\n", cadena);
                    return 0;
            }
            push(&pila, resultado); 
        }
        // si es numero
        else {
        	push(&pila, caracter_a_numero(cadena[i]));
        }
        i++;
    }

    int resultado = pop(&pila);
    return resultado;
}
// FIN DE CODIGO PARA RESOLVER PRECEDENCIA DE OPERACIONES

// CODIGO PARA PASAR DE INFIJA A POSFIJA
int prec(char c) {
    if (c == '^')
    return 3;
    else if (c == '/' || c == '*')
    return 2;
    else if (c == '+' || c == '-')
    return 1;
    else
    return -1;
}

// Check if operator is right-associative
int isRightAssociative(char c) {
    return c == '^';
}

char* infixToPostfix(char* exp) {
    int len = strlen(exp);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    char* stack = (char*)malloc(len * sizeof(char));
    int j = 0;
    int top = -1;
    
    for (int i = 0; i < len; i++) {
        char c = exp[i];
        
        if (isalnum(c)) {
            result[j++] = c;
        }
        else if (c == '(') {
            stack[++top] = '(';
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                result[j++] = stack[top--];
            }
            top--; 
        }
        else {
            while (top != -1 && stack[top] != '(' &&
                (prec(stack[top]) > prec(c) ||
                (prec(stack[top]) == prec(c) && !isRightAssociative(c)))) {
                result[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }
    
    while (top != -1) {
        result[j++] = stack[top--];
    }
    
    result[j] = '\0';
    free(stack);
    return result;  // ahora es válido
}

// FIN DE CODIGO PARA PASAR DE INFIJA A POSFIJA

/*FUNCIONES DE INTERACCIÓN CON EL USUARIO*/
void imprimir_titulo()
{
	printf("+-----------------------------------+\n");
	printf("|   TP AUTOMATAS - SYSL - GRUPO 6   |\n");
	printf("+-----------------------------------+\n");	
}

void imprimir_consigna_seleccionada(int consigna)
{
	printf("\n+-----------------------------------+\n");
	printf("|    SELECCIONASTE LA CONSIGNA %d    |\n", consigna);
	printf("+-----------------------------------+\n");	
}

void pedir_opcion_menu(int cota_inferior, int cota_superior, int* opc)
{
	do{
		printf("\nIngrese la opcion correspondiente: ");
		scanf("%d", opc); 
		while (getchar() != '\n'); 
	}while(*opc < cota_inferior || *opc > cota_superior);
}

void activar_opciones_consigna_uno(int* opc)
{
	printf("\n+------------CONSIGNA 1-------------+\n");
	printf("| De que forma ingresara la cadena? |\n");
	printf("|                                   |\n");
	printf("| 1 - Por linea de comando          |\n");
	printf("| 2 - Por archivo                   |\n");
	printf("+-----------------------------------+\n");

	pedir_opcion_menu(1, 2, opc);

}

void activar_opciones_consignas(int* opc)
{
	printf("\n+-------------CONSIGNAS-------------+\n");
	printf("| Que consigna del TP desea probar? |\n");
	printf("|                                   |\n");
	printf("| 1 - Tipos de numeros              |\n");
	printf("| 2 - Operaciones                   |\n");
	printf("+-----------------------------------+\n");

	pedir_opcion_menu(1, 2, opc);
}

void* pedir_cadena(int consigna_seleccionada, int opc, char* cadena)
{
	char directorio_cadena[] = "./cadena.txt";
	
	if (consigna_seleccionada == 2 || opc == 1){
		printf("\nIngrese la cadena a continuacion: ");
		scanf("%s", cadena); 
	}else{
		FILE *fp = fopen(directorio_cadena, "r");
		if (fp == NULL) {
    		printf("No se encontro el archivo en la ruta especificada! Saliendo...\n");
    		exit(EXIT_FAILURE);
		} else {
    		fgets(cadena, 100, fp);
		}
	}
}

void ejecutar_consigna(int consigna_seleccionada, char* cadena, int filas, int columnas, int tt[filas][columnas])
{
	int cant_hexadecimales = 0;
	int cant_octales = 0;
	int cant_decimales = 0;
	
	printf("\n+--------------------------------------RESULTADO--------------------------------------+\n");
	printf("| Cadena testeada: "); printf("%-*s |\n", 66, cadena);
	printf("|                                                                                     |\n");
	printf("| Resultado: ");
	if(es_palabra(cadena, filas, columnas, tt, consigna_seleccionada)) {
		printf("%-*s |\n", 72, "Es palabra del lenguaje");
		printf("|                                                                                     |\n");
		if(consigna_seleccionada == 1){
			contar_tipos(cadena, &cant_hexadecimales, &cant_octales, &cant_decimales);
			printf("| Cantidad de decimales: "); printf("%-*d |\n", 60, cant_decimales);
			printf("| Cantidad de octales: "); printf("%-*d |\n", 62, cant_octales);
			printf("| Cantidad de hexadecimales: "); printf("%-*d |\n", 56, cant_hexadecimales);
		}else if (consigna_seleccionada == 2){
			char* posfijo = infixToPostfix(cadena);	
			printf("| Resultado de la operacion: "); printf("%-*d |\n", 56, evaluarPostfijo(posfijo));
    		free(posfijo); // liberar memoria
		}
	}else{
		printf("%-*s |\n", 72, "No es palabra del lenguaje");
	}
	printf("+-------------------------------------------------------------------------------------+\n");
}

void activar_opciones_seguir(int* seguir)
{
	printf("\nProbar otra vez? 1 = SI | 0 = NO\n");

	pedir_opcion_menu(0, 1, seguir);
}
/*FIN FUNCIONES DE INTERACCIÓN CON EL USUARIO*/

/*Main*/
int main()
{
	static int tt_punto_1[9][8] = 	{	
							{1,	7,	8,	8,	2,	2,	8,	8},
							{8,	8,	8,	8,	2,	2,	8,	8},
							{8,	2,	8,	0,	2,	2,	8,	8},
							{8,	8,	8,	0,	8,	8,	8,	8},
							{8,	3,	8,	8,	6,	6,	6,	8},
							{8,	5,	8,	0,	5,	8,	8,	8},
							{8,	6,	8,	0,	6,	6,	6,	8},
							{8,	3,	4,	0,	5,	8,	8,	8},
							{8,	8,	8,	8,	8,	8,	8,	8}
						};

	static int tt_punto_3[4][3] =  {
                            {1,	2,	2},
                            {2,	0,	2},
                            {2,	2,	2}
                            }; 

	int consigna_seleccionada;
	int opc;
	int seguir;
	char cadena[100];
	
	do{
		imprimir_titulo();
		
		activar_opciones_consignas(&consigna_seleccionada);
		
		imprimir_consigna_seleccionada(consigna_seleccionada);

		if(consigna_seleccionada == 1) activar_opciones_consigna_uno(&opc);
		 
		pedir_cadena(consigna_seleccionada, opc, cadena);

		if(consigna_seleccionada == 1){
			ejecutar_consigna(consigna_seleccionada, cadena, 9, 8, tt_punto_1);
		}else if (consigna_seleccionada == 2){
			ejecutar_consigna(consigna_seleccionada, cadena, 4, 3, tt_punto_3);
		}
			
		activar_opciones_seguir(&seguir);
		
	}while(seguir);
	
}