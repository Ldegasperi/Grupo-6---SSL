%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
	#include "string.h"
	char* devolver_copia(char* cadena, int largo){
		char* copia = malloc((largo+1) * sizeof(char));
		strcpy(copia, cadena);
		return copia; 
	}
%}

DIGITO [0-9]
LETRA [a-zA-Z]
IDENTIFICADOR {LETRA}({LETRA}|{DIGITO})*
CONSTANTE {DIGITO}({DIGITO})*

%%
":=" {return ASIGNACION;}
"inicio" {return INICIO;}
"fin" {return FIN;}
"leer" {return LEER;}
"escribir" {return ESCRIBIR;}
{CONSTANTE} {yylval.cadena = devolver_copia(yytext, yyleng); return CONSTANTE;}
{IDENTIFICADOR} {yylval.cadena = devolver_copia(yytext, yyleng); return ID; }
";" {return PYCOMA;}
"," {return COMA;}
"(" {return PIZQ;}
")" {return PDER;}
"+" {return SUMA;}
"-" {return RESTA;}
"=:" {fprintf(stderr, "[ERROR: Quizá quisiste poner := ...?]\n" );}
[ \t\n] {}
. {fprintf(stderr, "[ERROR: Caracter espurio al lenguaje: %s]\n", yytext );}
<<EOF>> {return 0;}
%%