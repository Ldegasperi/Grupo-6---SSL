%{
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
extern char *yytext;
extern int yyleng;
extern int yylex(void);
extern void yyerror(char*);
int variable=0;
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

%%

objetivo: programa FDT /* #terminar */
;
programa: INICIO sentencias FIN /* #comenzar */
;
sentencias: sentencias sentencia 
|sentencia
;
sentencia: ID {printf("el id es: %s de longitud: %d ",yytext,yyleng);if(yyleng>10) yyerror("metiste la pata");} ASIGNACION expresion PYCOMA
| LEER PARENIZQUIERDO listaIdentificadores PARENDERECHO PYCOMA
| ESCRIBIR PARENIZQUIERDO listaIdentificadores PARENDERECHO PYCOMA
;
listaIdentificadores: listaidentificadores COMA identificador
| identificador /* #leerID */
;
identificador: ID {printf("id %d ",atoi(yytext),$1); }/* #procesarID */
;
expresiones: expresiones expresion /* #escribirExpresion */
| expresion /* #escribirExpresion */
;
expresion: primaria 
| expresion operadorAditivo primaria {$$ = $1 + $3} /* #genInfijo */
; 
primaria: ID
| CONSTANTE {printf("valores %d ",atoi(yytext),$1); } /* #procesarConstante */
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
printf ("mi error es %s\n",s);
}
int yywrap()  {
  return 1;  
} 