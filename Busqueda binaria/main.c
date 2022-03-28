#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(){

    const int dim = 5;
    int v[dim], i;
    char nombres[30];
    char buscar[30];
    char resultado[30];

    for(i = 0 ; i <= dim ; i++){

        printf("Ingrese los nombres\n");
        gets(nombres[i]);
        fflush();

    }

    printf("Ingrese el nombre que quiere buscar\n");
    gets(buscar);

    resultado = busquedaBinaria(v, buscar, 0, dim - 1, dim );

}

int busquedaBinaria( const int b[], int claveDeBusqueda, int bajo, int alto, int d ){

    int izquierda = 0, derecha = longitudDelArreglo - 1;

    while(izquierda <= derecha){

        int indiceDeLaMitad = floor((izquierda + derecha) / 2);
        char *elementoDeLaMitad = arreglo[indiceDeLaMitad];

        int resultadoDeLaComparacion = strcmp(busqueda, elementoDeLaMitad);
        // Si son iguales hemos encontrado el elemento
        if (resultadoDeLaComparacion == 0) return indiceDeLaMitad;

        // Si no, vemos en cual mitad podria estar

        // A la izquierda?
        if (resultadoDeLaComparacion < 0){
            derecha = indiceDeLaMitad - 1;
        }else{
            // A la derecha
            izquierda = indiceDeLaMitad + 1;
        }
    }
    // Si termina el ciclo y no encontramos nada, regresamos -1
    return -1;
}
