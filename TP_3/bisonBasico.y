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
   char* cadena;
   int num;
} 
%union{
  char cadena[32]; /* para IDs */ 
  int num;   /* para constantes */
}

%token ASIGNACION PYCOMA SUMA RESTA PARENIZQUIERDO PARENDERECHO COMA
%token <cadena> ID
%token <num> CONSTANTE
%token INICIO 
%token FIN
%token LEER
%token ESCRIBIR
%token FDT /* token de eof */
%%
objetivo: programa FDT
programa: INICIO sentencias FIN
sentencias: sentencias sentencia 
|sentencia
;
sentencia: ID {printf("el id es: %s de longitud: %d ",yytext,yyleng);if(yyleng>10) yyerror("metiste la pata");} ASIGNACION expresion PYCOMA
| LEER PARENIZQUIERDO listaIdentificadores PARENDERECHO PYCOMA
| ESCRIBIR PARENIZQUIERDO listaIdentificadores PARENDERECHO PYCOMA
;
listaIdentificadores: listaidentificadores COMA ID
| ID
expresiones: expresiones expresion
| expresion
expresion: primaria 
|expresion operadorAditivo primaria {$$ = $1 + $3}
; 
primaria: ID
|CONSTANTE {printf("valores %d ",atoi(yytext),$1); }
|PARENIZQUIERDO expresion PARENDERECHO
;
operadorAditivo: SUMA 
| RESTA
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