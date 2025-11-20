%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
%}
DIGITO [0-9]

LETRA [a-zA-Z]

IDENTIFICADOR {LETRA}({LETRA}|{DIGITO})*

constEntera {DIGITO}({DIGITO})*
%%
<<EOF>> {return 0;}
":=" {return ASIGNACION;}
{constEntera} {yylval.num=atoi(yytext);return CONSTANTE;}
"inicio" {return INICIO;}
"fin" {return FIN;}
"escribir" {return ESCRIBIR;}
"leer" {return LEER;}

{IDENTIFICADOR} { return ID; }
";" {return PYCOMA;}
"," {return COMA;}
"(" {return PARENIZQUIERDO;}
")" {return PARENDERECHO;}
"+" {return SUMA;}
"-" {return RESTA;}
. {return TOKEN_ERROR;}
%%