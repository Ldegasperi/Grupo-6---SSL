/*
Incluyo librerías básicas
*/
#include <stdio.h>
#include <ctype.h>

int columna (char c) //{}
{
  if(perteneceAlGrupo(c, int grupo)) // podemos hacer una funcion que nos retorne el grupo directamente
  {
    return i;    
  }
  return 0;
}

int esPalabra(char* cadena)
{
  static int tt[fila][columna]= { {},
                                   {},
                                   {},
                                   {},
                                   {},
                                   {} };
  int e=0; // guarda estado
  int i=0; // puntero de cadena
  int c = cadena[i]; // guarda char de pos i en la cadena
  while (c!='\0')
  {
    e= tt[e][columna(c)];
    i++;
    c= cadena[i];
  }
  if (esEstadoDeAceptacion(e)) // usando paradigma funcional
    return 1;     // si e es estado de aceptacion, es valida
  return 0;
}

int verifica(char* cadena) // verifica que la cadena contenga solo caracteres de alguna de las columnas
{
  int i=0;
  int c = cadena[i];
  while (c!='\0')
  {
    if (pertenceAlAlfabeto(c))
      return 0;
    i++;
    c = cadena[i];
  }
  return 1;
}

// Función Punto 2)
/*
Recibe como caracter (char) un número y devuelve un número (int)
*/
int convertirANumero(char caracter)
{
  int numero;
  numero = caracter - '0';
  return numero;
}

int main(int longitud, char *cadena[])
{
  
  if (verifica(cadena))
  {
    if (esPalabra(cadena))
    {
      printf ("es palabra del lenguaje");      
    }
    else
    {
      printf ("no es palabra del lenguaje");      
    }
  }
  else
  {
    printf ("posee caracteres invalidos"); 
  }
}
