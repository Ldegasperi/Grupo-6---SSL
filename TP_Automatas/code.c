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
int retornar_columna(int c, int consigna_seleccionada)
{
	if(consigna_seleccionada == 1){
		if(c == '-' || c == '+') return 0;
		if(c == '0') return 1;
		if(c == 'x') return 2;
		if(c == '#') return 3;
		if(c >= '1' && c <= '7') return 4;
		if(c == '8' || c == '9') return 5;
		if(c >= 'A' && c <= 'F') return 6;
		return 7;
	}else{
		if(c=='0') return 0;
		if(c=='-' || c == '+' || c=='*' || c=='/') return 2;
		if(c>='1' && c <= '9') return 1;
		return 3;
	}

}


/* PUNTO 1 */
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

int es_palabra_punto_uno(char* cadena, int* cant_hexadecimales, int* cant_octales, int* cant_decimales, int consigna_seleccionada)
{
	int e = 0;						
	int i = 0;					
	char c = cadena[i];

	static int tt[7][10] = 	{	// alfabeto ampliado, teniendo como ultima fila el estado de rechazo y como ultima columna a todo caracter que no pertenezca al lenguaje
								{1,2,9,9,3,3,9},
								{9,9,9,9,3,3,9},
								{9,3,4,5,3,3,9},
								{9,3,9,5,3,3,9},
								{9,6,9,9,7,7,7},
								{1,8,9,9,3,3,9},
								{9,9,9,5,9,9,9},
								{9,7,9,5,7,7,7},
								{9,6,4,9,3,3,9},
								{9,9,9,9,9,9,9}
							};
	
	
	// Para saber si tengo que seguir reconociendo o esperar al siguiente #
	int contador = 1;
	
	while(c != '\0' && e != 7){
		e = tt[e][retornar_columna(c, consigna_seleccionada)];	
		contar_tipo(e, &contador, cant_hexadecimales, cant_octales, cant_decimales);
		i++;
		c = cadena[i];
	}
	
	if(e == 2 || e == 3 || e == 4 || e == 6) return 1;
	
	return 0;
}



/*FIN PUNTO 1*/

/*PUNTO 2*/
int caracter_a_numero(char caracter)
{
  return caracter - '0';
}

void limpiar_cadena(int longitud, char* cadena){
	for(int i = 0; i < longitud; i++){
		cadena[i] = '\0';
	}
}
int convertir_a_numero(char* cadena){
    int i = 0;
    int acumulador = 0;
    int c = cadena[i];
    while(c != '\0' ){
        acumulador = acumulador * 10 + caracter_a_numero(c);
        i++;
        c = cadena[i];
    }
	/* printf("Numero convertido: %d\n", acumulador); // debug */
	limpiar_cadena(i, cadena); // Limpio la cadena para que no queden digitos de algun otro numero anterior
    return acumulador;
}

/*FIN PUNTO 2*/


/*PUNTO 3*/

int es_palabra_punto_tres(char* cadena, int consigna_seleccionada)
{
	static int tt[4][4] =  {
                            {2,1,2,2},
                            {1,1,0,2}, // Cambie estado 4 por 2 por simplicidad 
                            {2,2,2,2}
                            }; 
    int e=0;
    int i=0;
    int c = cadena[i];
    while(c != '\0' && e != 2)
    {
        e = tt[e][retornar_columna(c, consigna_seleccionada)];
        i++;
        c=cadena[i];
    }
    if(e==1) return 1; // Chequea que el estado en el cual termino se uno de aceptación
    return 0;
}


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


int realizar_multiplicaciones_y_divisiones(char* operadores, int* operandos){
	int i = 0;
	while(operadores[i] != '\0'){
		if(operadores[i] == '*' || operadores[i] == '/'){
		//	printf("Realizando operacion %c entre %d y %d\n", operadores[i], operandos[i], operandos[i+1]); // debug
			if(operadores[i] == '*'){
				operandos[i] = operandos[i] * operandos[i+1];
			}else{
				operandos[i] = operandos[i] / operandos[i+1];
			}

			// Una vez que hice la operacion muevo todos los elementos desde el resultado una posicion a la izquierda incluido el fin de cadena para que me sirva de corte en la proxima iteracion
			for(int j = i; operadores[j] != '\0'; j++){
				operandos[j+1] = operandos[j+2];
				operadores[j] = operadores[j+1];
			}
		}else{
			i++;
		}
	}
}

int realizar_sumas_y_restas(char* operadores, int* operandos){
	int i = 0;
	while(operadores[i] != '\0'){
		//	printf("Realizando operacion %c entre %d y %d\n", operadores[i], operandos[i], operandos[i+1]); // debug
			if(operadores[i] == '+' || operadores[i] == '-'){
			if(operadores[i] == '+'){
				operandos[i] = operandos[i] + operandos[i+1];
			}else{
				operandos[i] = operandos[i] - operandos[i+1];
			}
			for(int j = i; operadores[j] != '\0'; j++){
				operandos[j+1] = operandos[j+2];
				operadores[j] = operadores[j+1];
			}
		}else{
			i++;
		}
	}
}

int resolver_segun_precedencia(char* operadores, int* operandos){
	realizar_multiplicaciones_y_divisiones(operadores, operandos);
	realizar_sumas_y_restas(operadores, operandos);

	return operandos[0];
}

int es_operador(char c){
	 return (c == '+' || c == '-' || c == '*' || c == '/');
}

void separar_operadores_de_operandos(char* operadores, int* operandos, char* cadena){

	int cant_operadores = 0;
	int cant_operandos = 0;
	int i = 0; // Recorre la cadena
	int n = 0; // Para guardar los numeros char en la cadena que va a ser transformada a entero
	char numero[100]; // Caso limite es que sea un numero de 100 digitos
	while(cadena[i] != '\0'){
		
		if(es_operador(cadena[i])){
			operadores[cant_operadores] = cadena[i];
			cant_operadores++;
			i++;
		}else if(cadena[i] >= '0' && cadena[i] <= '9'){
			n = 0; // Muevo iterador a posicion 0

			// Avanzando hasta recuperarlo todos los digitos
			do{
				numero[n] = cadena[i]; // Guardo las cifras en formato char
				i++; n++; // Avanzo ambas cadenas
			}while(!es_operador(cadena[i]) && cadena[i] != '\0'); // Hasta encontrarme un operador o el final de la cadena
			
			operandos[cant_operandos] = convertir_a_numero(numero); // Guardo en los operandos el numero char convertido a entero
			cant_operandos++;	
		}
	}
}


int realizar_operacion(char* cadena){
	int i = 0;
	// El caso limite es de 49 operandos y 51 operadores si es que admitimos cadenas de 100 caracteres (ver si se puede hacer dinamico)
	char operadores[49]; 
	int operandos[51];

	separar_operadores_de_operandos(operadores, operandos, cadena);

	return resolver_segun_precedencia(operadores, operandos);
}

void ejecutar_consigna(int consigna_seleccionada, char* cadena)
{
	int cant_hexadecimales = 0;
	int cant_octales = 0;
	int cant_decimales = 0;
	
	printf("\n+--------------------------------------RESULTADO--------------------------------------+\n");
	printf("| Cadena testeada: "); printf("%-*s |\n", 66, cadena);
	printf("|                                                                                     |\n");
	printf("| Resultado: ");
	if(consigna_seleccionada == 1){
		if(es_palabra_punto_uno(cadena, &cant_hexadecimales, &cant_octales, &cant_decimales, consigna_seleccionada)) {
			printf("%-*s |\n", 72, "Es palabra del lenguaje");
			printf("|                                                                                     |\n");
			printf("| Cantidad de decimales: "); printf("%-*d |\n", 60, cant_decimales);
			printf("| Cantidad de octales: "); printf("%-*d |\n", 62, cant_octales);
			printf("| Cantidad de hexadecimales: "); printf("%-*d |\n", 56, cant_hexadecimales);
		} 
		else{
			printf("%-*s |\n", 72, "No es palabra del lenguaje");
		} 
	}else{
		if(es_palabra_punto_tres(cadena, consigna_seleccionada)){
			printf("%-*s |\n", 72, "Es palabra del lenguaje");
			printf("|                                                                                     |\n");
			printf("| Resultado de la operacion: "); printf("%-*d |\n", 56, realizar_operacion(cadena));
		}else{
			printf("%-*s |\n", 72, "No es palabra del lenguaje");
		}
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

		ejecutar_consigna(consigna_seleccionada, cadena);
			
		activar_opciones_seguir(&seguir);
		
	}while(seguir);
	
}