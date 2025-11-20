%{
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
extern char *yytext;
extern int yyleng;
extern int yylex(void);
int yywrap();
extern void yyerror(char*);
void guardarIdentificadorEnTS(char*);
void precargarTS();
void imprimirTS();

int constanteProcesada;

#define TAM_MAX_ID 32

int posicionArray = 0;

enum tipoEntradaTS {
  IDENTIFICADOR,
  PR
};
 
typedef struct{
  char* cadena;
  int tipo;
}entradaTS;

entradaTS TS[100];

%}
%union{
  char* cadena[32];  
  int num;   
}

%token ASIGNACION PYCOMA SUMA RESTA PARENIZQUIERDO PARENDERECHO COMA
%token <cadena> ID
%token <num> CONSTANTE
%token INICIO 
%token FIN
%token LEER
%token ESCRIBIR
%token FDT 
%token TOKEN_ERROR

%%

objetivo: programa {imprimirTS(); yywrap();}/* #terminar */
;
programa:  {precargarTS();}/* #comenzar */ INICIO sentencias FIN
;
sentencias: sentencias sentencia 
|sentencia
;
sentencia: identificador ASIGNACION expresion PYCOMA /* #asignar */
| LEER PARENIZQUIERDO listaIdentificadores PARENDERECHO PYCOMA
| ESCRIBIR PARENIZQUIERDO expresiones PARENDERECHO PYCOMA
;
listaIdentificadores: listaIdentificadores COMA identificador /* #leerID */
| identificador /* #leerID */
;
identificador: ID {printf("Se hayo el id %d ",atoi(yytext),$1);if(yyleng>TAM_MAX_ID) yyerror("El identificador excede la cantidad de caracteres"); else{guardarIdentificadorEnTS(yytext);} }
;
espurio: TOKEN_ERROR {yyerror("Error de tipo lexico - Caracter espurio al lenguaje"); return 1;}
;
expresiones: expresiones expresion  /* #escribirExpresion */
| expresion /* #escribirExpresion */
;
expresion: primaria 
| expresion operadorAditivo primaria /* #genInfijo */
; 
primaria: identificador
| CONSTANTE {printf("valores %d ",atoi(yytext),$1); constanteProcesada = atoi(yytext);} /* #procesarConstante */
| PARENIZQUIERDO expresion PARENDERECHO 
;
operadorAditivo: SUMA /* #procesarOperador */
| RESTA /* #procesarOperador */
;
%%
int main() {
yyparse();
}
void yyerror (char *s){
printf ("Se hayo un error: %s\n",s);
}
int yywrap()  {
  return 1;  
} 

void guardarIdentificadorEnTS(char* nombreDelID){
  if(posicionArray<100){
    TS[posicionArray].tipo = ID;
    TS[posicionArray].cadena =nombreDelID;
    posicionArray++;
  }else{
    yyerror("La tabla de simbolos esta llena");
  }
}

void imprimirTS(){
  while(posicionArray>0){
    printf("[Entrada TS Nro %d] Tipo: %d - Cadena %s", posicionArray, TS[posicionArray].tipo, TS[posicionArray].cadena);
    posicionArray--;
  }
}

void precargarTS(){
  char* palabrasReservadas[] = {"inicio", "fin", "leer", "escribir"};
  while(posicionArray<4) {
    TS[posicionArray].tipo = PR;
    TS[posicionArray].cadena = palabrasReservadas[posicionArray];
    posicionArray++;
  }
  printf("TS precargada");
}
