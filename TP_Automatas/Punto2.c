int convertirANumero(char caracter)
{
  return caracter -'0';
}

int caracterANumero(char* cadena){
    
    int i = 0;
    int acumulador = 0;
    int c = cadena[i];
    while(c != '\0'){
        int numeroAgregado = convertirANumero(c);
        acumulador = acumulador * 10 + numeroAgregado;
        i++;
        c = cadena[i];
    }
    return acumulador;
}

main(){
    char numero[100];
    printf("Introduzca un numero: ");
    scanf("%s", &numero);
    int numeroDado = caracterANumero(numero);
    printf("%i\n",numeroDado);
}