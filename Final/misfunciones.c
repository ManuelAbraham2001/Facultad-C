#include "misfunciones.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct cliente{

    int id;
    char apellido[30];
    char nombre[30];
    char categoria;
    float facturacion;
	int activo;

};

int idCorroborar(int idActual, FILE * aC){

    aC = fopen("clientes.dat","r+b");

    int i, cantidadRegistros;
    i = 0;

    fseek(aC, 0, SEEK_END);
    cantidadRegistros = ftell(aC) / sizeof(struct cliente);// calculo la cantidad de clientes registrados para el ciclo

    struct cliente clientes[cantidadRegistros];

    fseek(aC,0,SEEK_SET);

    while(i < cantidadRegistros){

        fseek(aC, i*sizeof(struct cliente), SEEK_SET);
        fread(&clientes[i], sizeof(struct cliente), 1, aC);

        i++;
    }

            for (i = 0; i < cantidadRegistros; i++){

            if (clientes[i].id == idActual){

                return 1;
            }

        }

    fclose(aC);
    return 0;
}

int leerId(){

    int buscarId;

    printf("Ingresar la id del cliente: \n");
    scanf("%d", &buscarId);
    fflush(stdin);

    return buscarId;

}

void leerApellido(char* apellido){

    printf("Ingresar el apellido del cliente: \n");
    gets(apellido);
    fflush(stdin);
    convertirMayusculas(apellido);

}

void listarDatos(FILE *aC){

    struct cliente datos;
    int i, cantidadRegistros, opcion; //i es el contador, cantidadRegistros se utiliza para guardar el numero de registros del archivo
                                 //opcion guarda la opcion para utilizar el menu
    i = 0;

    aC = fopen("clientes.dat","rb");

    fseek(aC, 0, SEEK_END);

    cantidadRegistros = ftell(aC)/sizeof(struct cliente);// calculo la cantidad de clientes registrados para el ciclo

    printf("1 - Listar Todos\n");
    printf("2 - Listar Activos\n");
    printf("3 - Listar Pasivos\n");
    scanf("%d",&opcion);
    fflush(stdin);

    while(opcion < 1 || opcion > 3){

        printf("Por favor ingrese una opcion valida\n");
        printf("1 - Listar Todos\n");
        printf("2 - Listar Activos\n");
        printf("3 - Listar Pasivos\n");
        scanf("%d",&opcion);
        fflush(stdin);

    }

    fseek(aC, 0, SEEK_SET);

    while(i < cantidadRegistros){

        fseek(aC, i*sizeof(struct cliente), SEEK_SET);
        fread(&datos, sizeof(struct cliente), 1, aC);

        if (opcion == 1){

        printf("ID: %d || Apellido: %s || Nombre: %s || Categoria: %c  || Factutacion: %.2f$  || Activo: %d \n", datos.id, datos.apellido, datos.nombre, datos.categoria, datos.facturacion, datos.activo);

        }

        if (opcion == 2  && datos.activo == 1 ){

        printf("ID: %d || Apellido: %s || Nombre: %s || Categoria: %c  || Factutacion: %.2f$  || Activo: %d \n", datos.id, datos.apellido, datos.nombre, datos.categoria, datos.facturacion, datos.activo);

        }

        if (opcion == 3  && datos.activo == 0 ){

        printf("ID: %d || Apellido: %s || Nombre: %s || Categoria: %c  || Factutacion: %.2f$  || Activo: %d \n", datos.id, datos.apellido, datos.nombre, datos.categoria, datos.facturacion, datos.activo);

        }

        i++;
    }

fclose(aC);

}

void busqueda(FILE *aC){

    struct cliente datos;
    int opcion, buscarId; //opcion recibe la opcion de busqueda, buscarId recibe la id a buscar
    char apellido[30]; //apellido guarda el apellido a buscar

    printf("A continuacion indique como quiere hacer la busqueda del cliente\n");
    printf("1 - Buscar cliente por Apellido\n");
    printf("2 - Buscar cliente por ID\n");
    scanf("%d", &opcion);
    fflush(stdin);

    while(opcion < 1 || opcion > 2){

        printf("Por favor ingrese una opcion valida\n");
        printf("1 - Buscar cliente por Apellido\n");
        printf("2 - Buscar cliente por ID\n");
        scanf("%d", &opcion);
        fflush(stdin);

    }

    if (opcion == 1){

        leerApellido(apellido);

    }

    if (opcion == 2){

        buscarId = leerId();

    }

    aC = fopen("clientes.dat", "rb");

    while(!feof(aC)){

         if (fread(&datos, sizeof(struct cliente), 1, aC) == 1){

            if(opcion == 1 && strcmp(datos.apellido, apellido) == 0){

            printf("ID: %d || Apellido: %s || Nombre: %s || Categoria: %c  || Factutacion: %.2f$  || Activo: %d \n", datos.id, datos.apellido, datos.nombre, datos.categoria, datos.facturacion, datos.activo);
            break;

            }

            if(opcion == 1 && strcmp(datos.apellido, apellido) != 0){

            printf("No se encontro el cliente\n");
            break;

            }

            if(opcion == 2 && buscarId == datos.id){

            printf("ID: %d || Apellido: %s || Nombre: %s || Categoria: %c  || Factutacion: %.2f$  || Activo: %d \n", datos.id, datos.apellido, datos.nombre, datos.categoria, datos.facturacion, datos.activo);
            break;

            }

            if(opcion == 2 && buscarId != datos.id){

            printf("No se encontro el cliente\n");
            break;

            }

        }

    }

    fclose(aC);

}

