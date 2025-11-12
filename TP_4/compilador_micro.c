/* Compilador del Lenguaje Micro (Fischer) */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define NUMESTADOS 15
#define NUMCOLS 13
#define TAMLEX 32+1
#define TAMNOM 20+1
/******************Declaraciones Globales*************************/
FILE * in;
typedef enum {
INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO, PARENDERECHO, PUNTOYCOMA,
COMA, ASIGNACION, SUMA, RESTA, FDT, ERRORLEXICO
} TOKEN;
typedef struct {
char identifi[TAMLEX];
TOKEN t; /* t=0, 1, 2, 3 Palabra Reservada, t=ID=4 Identificador (ver enum) */
} RegTS;
RegTS TS[1000] = { {"inicio", INICIO}, {"fin", FIN}, {"leer", LEER}, {"escribir", ESCRIBIR}, {"$", 99} };

/**********************Prototipos de Funciones************************/
TOKEN scanner(); // el scanner
int columna(int c);
int estadoFinal(int e);
void Objetivo(void); // del PAS
void Programa(void);
void ListaSentencias(void);
void Sentencia(void);
void ListaIdentificadores(void);
void Identificador(REG_EXPRESION * presul);
void ListaExpresiones(void);
void Expresion(REG_EXPRESION * presul);
void Primaria(REG_EXPRESION * presul);
void OperadorAditivo(char * presul);

1
/* Compilador del Lenguaje Micro (Fischer) */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define NUMESTADOS 15
#define NUMCOLS 13
#define TAMLEX 32+1
#define TAMNOM 20+1
/******************Declaraciones Globales*************************/
FILE * in;
typedef enum {
INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO, PARENDERECHO, PUNTOYCOMA,
COMA, ASIGNACION, SUMA, RESTA, FDT, ERRORLEXICO
} TOKEN;
typedef struct {
char identifi[TAMLEX];
TOKEN t; /* t=0, 1, 2, 3 Palabra Reservada, t=ID=4 Identificador (ver enum) */
} RegTS;
RegTS TS[1000] = { {"inicio", INICIO}, {"fin", FIN}, {"leer", LEER}, {"escribir", ESCRIBIR}, {"$", 99} };
typedef struct{
TOKEN clase;
char nombre[TAMLEX];
int valor;
} REG_EXPRESION;
char buffer[TAMLEX];
TOKEN tokenActual;
int flagToken = 0;
/**********************Prototipos de Funciones************************/
TOKEN scanner(); // el scanner
int columna(int c);
int estadoFinal(int e);
void Objetivo(void); // del PAS
void Programa(void);
void ListaSentencias(void);
void Sentencia(void);
void ListaIdentificadores(void);
void Identificador(REG_EXPRESION * presul);
void ListaExpresiones(void);
void Expresion(REG_EXPRESION * presul);
void Primaria(REG_EXPRESION * presul);
void OperadorAditivo(char * presul);
REG_EXPRESION ProcesarCte(void);
REG_EXPRESION ProcesarId(void);
char * ProcesarOp(void);
void Leer(REG_EXPRESION in);
void Escribir(REG_EXPRESION out);
REG_EXPRESION GenInfijo(REG_EXPRESION e1, char * op, REG_EXPRESION e2);

void Match(TOKEN t);
TOKEN ProximoToken();
void ErrorLexico();
void ErrorSintactico();
void Generar(char * co, char * a, char * b, char * c);
char * Extraer(REG_EXPRESION * preg);
int Buscar(char * id, RegTS * TS, TOKEN * t);
void Colocar(char * id, RegTS * TS);
void Chequear(char * s);
void Comenzar(void);
void Terminar(void);
void Asignar(REG_EXPRESION izq, REG_EXPRESION der)

/***************************Programa Principal************************/
int main(int argc, char * argv[]){
TOKEN tok;
char nomArchi[TAMNOM];
int l;
/***************************Se abre el Archivo Fuente******************/
// verifica errores posibles
if (argc== 1) {
printf("Debe ingresar el nombre del archivo fuente (en lenguaje Micro) en la linea de comandos\n"); return -1; }// no puso nombre de archivo fuente
if (argc != 2) {
printf("Numero incorrecto de argumentos\n"); return -1; }//los argumentos deben ser 2
strcpy(nomArchi, argv[1]);
l = strlen(nomArchi);
if ( l > TAMNOM ) {
printf("Nombre incorrecto del Archivo Fuente\n"); return -1; }
// requiere para compilar un archivo de extensión.m archivo.m
if ( nomArchi[l-1] != 'm' || nomArchi[l-2] != '.' ) {
printf("Nombre incorrecto del Archivo Fuente\n"); return -1; }
if ( (in = fopen(nomArchi, "r") ) == NULL ) {
printf("No se pudo abrir archivo fuente\n"); return -1;//no pudo abrir archivo
}
}

