#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// TOP DOWN
/* int es_palabra(char* cadena, int tt[][], columna [])
   typedef struct { char caracter, int valor } columna;
   int columna (int c, columna []) {
        algoritmo que busca el valor q le corresponde a ese caracter recorriendo la lista de columnas
        return num_columna;
   }
*/

/* PUNTO 1 */
int es_palabra(char* cadena, int* cant_hexadecimales, int* cant_octales, int* cant_decimales)
{
	static int tt[8][8] = 	{	// alfabeto ampliado, teniendo como ultima fila el estado de rechazo y como ultima columna a todo caracter que no pertenezca al lenguaje
								{1,2,7,7,1,1,7,7},
								{7,7,7,7,3,3,7,7},
								{7,4,5,0,4,7,7,7},
								{7,3,7,0,3,3,7,7},
								{7,4,7,0,4,7,7,7},
								{7,6,7,7,6,6,6,7},
								{7,6,7,0,6,6,6,7},
								{7,7,7,7,7,7,7,7}							
							};
	
	int e = 0;						
	int i = 0;					
	char c = cadena[i];
	
	// Para saber si tengo que seguir reconociendo o esperar al siguiente #
	int contador = 1;
	
	while(c != '\0' && e != 7){
		e = tt[e][columna(c)];	
		contar_tipo(e, &contador, cant_hexadecimales, cant_octales, cant_decimales);
		i++;
		c = cadena[i];
	}
	
	if(e == 2 || e == 3 || e == 4 || e == 6) return 1;
	
	return 0;
}

int columna(int c)
{
	if(c == '-' || c == '+') return 0;
	if(c == '0') return 1;
	if(c == 'x') return 2;
	if(c == '#') return 3;
	if(c >= '1' && c <= '7') return 4;
	if(c == '8' || c == '9') return 5;
	if(c >= 'A' && c <= 'F') return 6;
	return 7;
}

void contar_tipo(int e, int* contador, int* cant_hexadecimales, int* cant_octales, int* cant_decimales)
{	
	if(*contador){
		if(e == 1 || e == 3){
			(*cant_decimales)++;	
			(*contador) = 0;
		}
		if(e == 2) (*cant_octales)++;
		if(e == 5) {
			(*cant_hexadecimales)++;	
			(*cant_octales)--;			
		}
	}
	
	if(e == 0) (*contador) = 1;

}

/*FIN PUNTO 1*/

/*PUNTO 2*/

int caracterANumero(char caracter)
{
  return caracter -'0';
}

int convertirANumero(char* cadena){
    
    int i = 0;
    int acumulador = 0;
    int c = cadena[i];
    while(c != '\0'){
        int numeroAgregado = caracterANumero(c);
        acumulador = acumulador * 10 + numeroAgregado;
        i++;
        c = cadena[i];
    }
    return acumulador;
}

/*FIN PUNTO 2*/

/*PUNTO 3*/
int es_palabra_p3(char* cadena)
{
	static int tt[3][3] =  {
                            {2,1,2},
                            {1,1,0}, // Cambie estado 4 por 2 por simplicidad 
                            {2,2,2}
                            }; 
    int e=0;
    int i=0;
    int c = cadena[i];
    while(c!='\0')
    {
        e = tt[0][columna(c)];
        i++;
        c=cadena[i];
    }
    if(e==1)
        return 1; // Chequea que el estado en el cual termino se uno de aceptación
    return 0;
}

int columna_p3(char c)
{
	if(c=='0')
        return 0;
    if(c=='-' || c == '+' || c=='*' || c=='/')
        return 2;
	if(c>='1' && c <= '9')
		return 1;
}

int calculo(char* cadena)
{
	if(es_palabra_p3(cadena))
	{
		int resultado;
		int numeros[length(cadena)];
		char operadores[length(cadena)/2;] // creo q no es necesario pero maximo va a haber largoCadena/2 division entera 
		int i=0;
		int operador=0;
		int numero = 0;
		while(i!=length(cadena))
		{
			if(cadena[i] == '+'|| cadena[i] == '-'||cadena[i] == '/'||cadena[i] == '*')
				operadores[operador]= cadena[i];
			else
			{
				char* cadena_intermedia;
				int j=i;
				int k= 0;
				while(j!=length(cadena) && cadena[j+1]<='9' && cadena[j+1]>='0') // corre mientras el siguiente caracter sea un numero
				{
					*(cadena_intermedia[k])=cadena[j]; // tengo q buscarlo p0rque no me acuerdo
					j++;
				}
				numeros[numero]= convertirANumero(*cadena_intermedia); // Pongo un else directamente porque ya fue chequeado que fuese palabra				
			} 
			i++;
		}
		i=0;
		while(i!= length(operadores) && operadores[0]!= 0){ // Se saca de encima todos los */ para luego resolver todos los + -
			if(operadores[i]=='*' || operadores[i]=='/')
			{
				calcular(); // Desarrollar
			}
		}
		i=0;
		while(i!= length(operadores) && operadores[0]!= 0){
			if(operadores[i]=='+' || operadores[i]=='-')
			{
				calcular();
			}
		}
			return resultado;
	}
	return 0; // ERROR
}

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
/*FIN PUNTO 3*/

/*FUNCIONES DE INTERACIÓN CON EL USUARIO*/
void imprimir_titulo()
{
	printf("+-----------------------------------+\n");
	printf("|   TP AUTOMATAS - SYSL - PUNTO 1   |\n");
	printf("+-----------------------------------+\n");	
}

void imprimir_opciones_menu()
{
	printf("\n+---------------MENU----------------+\n");
	printf("| De que forma ingresara la cadena? |\n");
	printf("|                                   |\n");
	printf("| 1 - Por linea de comando          |\n");
	printf("| 2 - Por archivo                   |\n");
	printf("+-----------------------------------+\n");
}

int pedir_opcion_menu(int* opc)
{
	do{
		printf("\nIngrese la opcion correspondiente: ");
		scanf("%d", opc); 
		while (getchar() != '\n'); 
	}while(*opc != 1 && *opc != 2);
}

void* seguir_flujo_menu(int opc, char* cadena)
{
	char directorio_cadena[] = "./cadena.txt";
	
	if (opc == 1){
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

void imprimir_resultados(char* cadena)
{
	int cant_hexadecimales = 0;
	int cant_octales = 0;
	int cant_decimales = 0;
	
	printf("\n+----------------------------------------RESUMEN--------------------------------------+\n");
	printf("| Cadena testeada: "); printf("%-*s |\n", 66, cadena);
	printf("|                                                                                     |\n");
	printf("| Resultado: ");
		
	
		if(es_palabra(cadena, &cant_hexadecimales, &cant_octales, &cant_decimales)) {
			printf("%-*s |\n", 72, "Es palabra del lenguaje");
			printf("|                                                                                     |\n");
			printf("| Cantidad de decimales: "); printf("%-*d |\n", 60, cant_decimales);
			printf("| Cantidad de octales: "); printf("%-*d |\n", 62, cant_octales);
			printf("| Cantidad de hexadecimales: "); printf("%-*d |\n", 56, cant_hexadecimales);
		} 
		else{
			printf("%-*s |\n", 72, "No es palabra del lenguaje");
		} 
	
	
	printf("+-------------------------------------------------------------------------------------+\n");
}

void pedir_opcion_seguir(int* seguir)
{
	do{
		printf("Ingrese la opcion correspondiente: ");
		scanf("%d", seguir); 
		while (getchar() != '\n'); 
	}while(*seguir != 0 && *seguir != 1);
}
/*FIN FUNCIONES DE INTERACIÓN CON EL USUARIO*/


/*Main*/
int main()
{
	int opc;
	int seguir;
	char cadena[100];
	
	imprimir_titulo();
	
	do{
		
		imprimir_opciones_menu();
		
		pedir_opcion_menu(&opc);
		
		seguir_flujo_menu(opc, cadena);
	
		imprimir_resultados(cadena);
		
		printf("\nTestear otra cadena? 1 = SI | 0 = NO\n\n");
			
		pedir_opcion_seguir(&seguir);
		
	}while(seguir);
	
}