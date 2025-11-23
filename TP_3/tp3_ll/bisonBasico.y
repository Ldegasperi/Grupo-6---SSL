%{
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#define MAXIMO_CARACTERES_ID 32
extern char *yytext;
extern int yyleng;
extern int yylex(void);
extern void yyerror(char*);

/* IMPLEMENTACION TABLA DE SIMBOLOS PARA MICRO */

enum {
    RESERVADA,
    IDENTIFICADOR,
    TEMPORAL
};

typedef struct {
    char* cadena;
    int tipo;
}TS;

TS tabla_simbolos[100];

char* operacion = "";
char* operando_izq = "";
char* operando_der = "";
char* registro_expresion ="";
int numero_temporales = 1;
int indice_ts = 0;
int constante_procesada = 0;

int buscar(char* cadena){
    for(int i = 0; i < indice_ts; i++){
        if(strcmp(tabla_simbolos[i].cadena, cadena) == 0) return 1;
    }
    return 0;
}

void colocar(char* cadena, int tipo){
    if(indice_ts < 100){ /* esta en la ts? */
      TS nuevoRegistro;
      nuevoRegistro.cadena = strdup(cadena);
      nuevoRegistro.tipo = tipo;
      tabla_simbolos[indice_ts] = nuevoRegistro;
      indice_ts++;
    }else{
      yyerror("Tabla de simbolos llena");
    }
}

void chequear(char* cadena, int tipo){
     if(!buscar(cadena)){ /* esta en la ts? */
        colocar(cadena, tipo);
        printf("Declara %s, Entera\n", cadena);
    }
}

void procesar_id(char* cadena){
  if (strlen(cadena) > MAXIMO_CARACTERES_ID){
    yyerror("Identificador supera largo maximo");
    cadena[MAXIMO_CARACTERES_ID] = '\0';
  } 
  chequear(cadena, IDENTIFICADOR);
}

char* gen_infijo(){
  char temp[50] = "Temp&";
  char destino[50]; 
  itoa(numero_temporales++, destino, 10);
  strcat(temp, destino);
  chequear(temp, TEMPORAL);
  registro_expresion = strdup(temp);
  printf("%s, %s, %s, %s\n", operacion, operando_izq, operando_der, temp);
  return registro_expresion;
}

void asignar(char* id){
    printf("Almacena, %s, %s\n", registro_expresion, id);
}

void cargar_prs_en_ts(){
  char* palabras_reservadas[] = {"leer", "escribir", "inicio", "fin"};
  while(indice_ts < 4){
      colocar(palabras_reservadas[indice_ts], RESERVADA);
  }
}

char* manejar_tipo(int tipo){
    switch(tipo){
        case RESERVADA:
            return "RESERVADA";
        case IDENTIFICADOR:
            return "IDENTIFICADOR";
        case TEMPORAL:
            return "TEMPORAL";
        default:
            yyerror("Tipo desconocido en la tabla de simbolos");
            return "DESCONOCIDO";
    }
}

void finalizar(){
    printf("Detiene");
    printf("\n\n--- TABLA DE SIMBOLOS FINAL ---\n");
    for(int i = 0; i < indice_ts; i++){
        char* tipo_identificador = manejar_tipo(tabla_simbolos[i].tipo);
        printf("[ENTRADA N%d] Cadena: %s, Tipo: %s\n", i, tabla_simbolos[i].cadena, tipo_identificador);
    }
}

void leer_id(char* id){
    printf("Read, %s, Entera\n", id);
}

void escribir_exp(char* exp){
    printf("Write, %s, Entera\n", exp);
}
int pr_en_yytext(){
  return (strcmp(yytext, "inicio") == 0 || strcmp(yytext, "fin") == 0 || strcmp(yytext, "leer") == 0 || strcmp(yytext, "escribir") == 0);
}
%}

%union{
   char* cadena;
}

%token ASIGNACION PYCOMA SUMA RESTA INICIO FIN LEER ESCRIBIR COMA FDT
%token <cadena> ID CONSTANTE PIZQ PDER
%type <cadena> primaria identificador expresion

%%

objetivo: programa {finalizar();}
;
programa: { cargar_prs_en_ts(); /* esto ya lo hace flex */} INICIO sentencias FIN 
;
sentencias: sentencias sentencia 
|sentencia
;
sentencia: identificador ASIGNACION expresion {asignar($1);} PYCOMA
         | LEER PIZQ identificadores PDER PYCOMA
         | ESCRIBIR PIZQ expresiones PDER PYCOMA
;
identificadores: identificador {leer_id($1);} 
               | identificadores COMA identificador {leer_id($3);} 
;
expresiones: expresion {escribir_exp($1);} 
           | expresiones COMA expresion {escribir_exp($3);} 
;
expresion: primaria {operando_izq = $1;}
         | expresion operadorAditivo primaria {operando_der = $3; $$ = gen_infijo();} 
;
primaria: identificador
        | CONSTANTE {constante_procesada = atoi($1);}
        | PIZQ expresion PDER
;
operadorAditivo: SUMA {operacion = "Sumar";} 
| RESTA  {operacion = "Restar";} 
;
identificador: ID {procesar_id($1);}
;

%%

int main() {
yyparse();
}

void yyerror (char *s){
    printf ("[ERROR: %s]\n",s);
}

int yywrap()  {
  return 1;  
} 