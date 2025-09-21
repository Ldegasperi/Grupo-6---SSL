#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

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


// De aca para abajo no hay nada que tenga que ver con la funcionalidad del automata sino con la interaccion con el usuario y la impresion de los datos relevantes

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

