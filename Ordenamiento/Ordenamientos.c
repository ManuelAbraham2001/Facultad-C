#include <stdio.h>
#include <stdlib.h>

int posicion_maximo (float v[], int d){
    /* devuelve la posicion del elemento mayor del vector x */
    /* entrada: vector x, de tamanio efectivo n */
    /* salida : posicion entre 1 y n-1 */
    int mprov, pprov, i;

        mprov = v[0];
        pprov = 0;

    for (i = 1; i < d; i++){

        if (v[i]> mprov){

          mprov = v[i];
          pprov = i;

        }
    }

    return pprov;

}

void intercambia (int * px, int * py) {

    int n;

    n = *py;
    *py = *px;
    *px = n;

}

void coloca_el_ultimo (float v[], int d){
    /* intercambia los elementos maximo de x y ultimo de x
     colocando en ultimo lugar el maximo elemento */
    /* n es el tamanio efectivo de x */
    int p;

    p = posicion_maximo (v, d);

    if (v[p] !=  v[d-1]){

        intercambia (&v[d-1], &v[p]);

    }

}

void posicion(float v[], int d){
    int cont, i;
    /* Ordenamiento*/
    for (cont = d; cont > 1; cont--){
    /* tamanio desde el inicial hasta 2 */
        coloca_el_ultimo (v, cont);

    }
    /* Fin ordenamiento*/

    for (i = 0; i < d; i++){

        printf ("%.0f - ", v[i]);

    }

    printf("\n");

}

void burbujeo(float v[], int dim){

    int i,j, aux, cambio;

    /* Ordenamiento*/

    for (i = 0; i < dim-1 ; i++){

        cambio = 0;

           for (j = 0; j < dim-(i+1); j++){
                if (v[j] > v[j+1]){

                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
                cambio = 1;

                }
            }
        }
    /* Fin ordenamiento*/

    for (i = 0; i < dim; i++){

      printf ("%.0f - ", v[i]);

    }

    printf("\n");

}

void insercion(float v[], int d){

    int i,j, k, cont, aux;
	/* Ordenar y mostrar resultados intermedios*/
        for (cont = 1 ; cont < d ; cont++){
		/* Colocar v[cont] */
		aux = v[cont];
		k = cont-1; /* posicion del elemento a comparar */

		while ((v[k] > aux) && (k>0)){
	 		/* Desplazar elementos */
		v[k+1] = v[k];
		k--;

		}
        if (v[k] <= aux){
        /* posicion intermedia */
        v[k+1] = aux;

		}
		else{ /* colocar el primero */

		v[1] = v[0];
		v[0] = aux;

		}
    }

    for (i = 0; i < d; i++){

      printf ("%.0f - ", v[i]);

    }

}

int main(){

    const int dim = 5;
    float v[dim];
    int i;

    printf("Ingrese los valores a ordenar\n");

    for(i = 0 ; i <= dim-1 ; i++){

        scanf("%f", &v[i]);

    }

    printf("Por burbujeo\n");

    burbujeo(v, dim);

    printf("Por posicion\n");

    posicion(v, dim);

    printf("Por insercion\n");

    insercion(v, dim);

    return 0;
}
