#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "misfunciones.h"

struct cliente{

    int id;
    char apellido[30];
    char nombre[30];
    char categoria;
    float facturacion;
	int activo;

};


// creo el archivo
void crearArchivo(FILE * aC){

    if ((aC = fopen("clientes.dat", "w+b")) == NULL){ // abro el archivo en modo lectura y escritura si es NULL no se abre

        printf("No se pudo abrir el archivo\n");

    }

    else{

        printf("El archivo se creo correctamente\n"); // si no es NULL se crea
        fclose(aC);

    }
}

// menu de opciones
int Menu(){

    char opcion;

    printf("A - Crear archivo\n");
    printf("B - Alta de cliente\n");
    printf("C - Listar clientes\n");
    printf("D - Buscar datos de un cliente\n");
    printf("E - Modificar categoria\n");
    printf("F - Modificar facturacion\n");
    printf("G - Ordenar alfabeticamente\n");
    printf("H - Dar Baja logica a un cliente\n");
    printf("I - Actualizar archivo eliminando bajas de clientes (Baja fisica)\n");
    printf("S - Salir\n");
    scanf("%c", &opcion);
    fflush(stdin);
    toupper(opcion);

    return toupper(opcion); //devuelvo la opcion en mayuscula

}

void convertirMayusculas(char* cadenas){

    int i, x;

    x = strlen(cadenas);

        for(i = 0 ; i <= x ; i++){

            cadenas[i] = toupper(cadenas[i]);

        }

}

// alta del cliente
void altaCliente(FILE * aC){ //recibo el archivo para cargar el cliente

    struct cliente datos;
    int idActual; // guarda el ID del cliente

    aC = fopen("clientes.dat","r+b");
    printf("Ingrese la id del cliente: \n");
    scanf("%d", &idActual);
    fflush(stdin);

    while(idActual <= 0){

        printf("El id no puede ser una letra o un numero negativo\nPor favor ingrese un valor correcto...\n");
        printf("Ingrese la id del cliente: \n");
        scanf("%d", &idActual);
        fflush(stdin);

    }

    int corroborarId = idCorroborar(idActual, aC); // chequeo que la id ingresada no sea la misma que la de otro cliente

    while(corroborarId){ // si el id esta ocupado, lo pide de nuevo

        printf("Este id ya esta siendo utilizado por otro cliente\nIngrese un id diferente\n");
        printf("Ingrese la id del cliente: \n");
        scanf("%d", &idActual);
        fflush(stdin);
        corroborarId = idCorroborar(idActual, aC);

    }

    datos.id = idActual; // actualizo el struct

    printf("Ingrese el nombre del cliente: \n");
    gets(datos.nombre);
    fflush(stdin);

	convertirMayusculas(datos.nombre); // convierto las cadenas a mayusculas

    printf("Ingrese el apellido del cliente: \n");
    gets(datos.apellido);
    fflush(stdin);

	convertirMayusculas(datos.apellido); // convierto las cadenas a mayusculas

    printf("Ingrese la categoria del cliente, A B o C: \n");
    scanf("%c",&datos.categoria);
    fflush(stdin);

    if(datos.categoria == 'a'){

        datos.categoria = 'A';

    }

    if(datos.categoria == 'b'){

        datos.categoria = 'B';

    }

    if(datos.categoria == 'c'){

        datos.categoria = 'C';

    }

    while((datos.categoria != 'A') && (datos.categoria != 'B') && (datos.categoria != 'C')){

        printf("Ingrese una categoria valida, A B o C\n");
        printf("Ingresar categoria nuevamente: \n");
        scanf("%c", &datos.categoria);
        fflush(stdin);

        if(datos.categoria == 'a'){

            datos.categoria = 'A';

        }

        if(datos.categoria == 'b'){

            datos.categoria = 'B';

        }

        if(datos.categoria == 'c'){

            datos.categoria = 'C';

        }

    }

    printf("Ingresar la facturacion del cliente: \n");
    scanf("%f", &datos.facturacion);
    fflush(stdin);


    while(datos.facturacion <= 0){ //si la facturacion es menor o igual a 0 se pide ingresarla nuevamente

        printf("La facturacion del cliente no puede ser 0, por favor ingrese la facturacion nuevamente\n");
        printf("Ingresar la facturacion del cliente: \n");
        scanf("%f", &datos.facturacion);

    }

    datos.activo = 1;
    fflush(stdin);

    if(datos.id == 1){

        fseek(aC, 0, SEEK_SET);
        fwrite(&datos, sizeof(struct cliente), 1, aC);

    }

    else{

        fseek(aC, (datos.id-1)*sizeof(struct cliente), SEEK_SET);
        fwrite(&datos, sizeof(struct cliente), 1, aC);

    }

    fclose(aC);

}

int buscarIdApellido(char* apellido, FILE *aC){

    struct cliente datos;
    int id;

    aC = fopen("clientes.dat", "rb");

        while(!feof(aC)){
        // las funciones en c devuelven un valor entero lo que permite usar ese valor para las operaciones
         if (fread(&datos, sizeof(struct cliente), 1, aC) == 1){

             if(strcmp(datos.apellido, apellido) == 0){

                id = datos.id;
                break;

             }

         }

    }

    fclose(aC);

    return id;

}

// modifico la categoria
void modificarcategoria(FILE * aC){

    struct cliente datos;
    char cambioCategoria;    //guardo la nueva categoria
    char guardarApellido[30]; //guardo el apellido para buscar
    int confirmar, opcion, buscarId, corroborarId; //opcion es para elegir como buscar el cliente
                                    //buscarId guarda el id del cliente para buscarlo

    printf("1 - Buscar cliente por id\n");
    printf("2 - Buscar cliente por apellido\n");
    scanf("%d", &opcion);
    fflush(stdin);

    while(opcion < 1 || opcion > 2){

        printf("Por favor ingrese una opcion valida\n");
        printf("1 - Buscar cliente por id\n");
        printf("2 - Buscar cliente por apellido\n");
        scanf("%d", &opcion);
        fflush(stdin);

    }

    if(opcion == 1){

        buscarId = leerId();

        corroborarId = idCorroborar(buscarId, aC);

        if(corroborarId == 1){

        }

        else{
            printf("No se encuentra el cliente\n");
            return;
        }

    }

    if(opcion == 2){

        leerApellido(guardarApellido);
        buscarId = buscarIdApellido(guardarApellido, aC);
        corroborarId = idCorroborar(buscarId, aC);

        if(corroborarId == 1){

        }

        else{
            printf("No se encuentra el cliente\n");
            return;
        }

    }

    aC = fopen("clientes.dat", "r+b");
    fseek(aC, 0, SEEK_SET);
    fseek(aC, (buscarId-1)*sizeof(struct cliente), SEEK_SET);
    fread(&datos, sizeof(struct cliente ), 1, aC);

    printf("Cliente a modificar:\n");
    printf("ID: %d || Apellido: %s || Nombre: %s || Categoria: %c  || Factutacion: %.2f$  || Activo: %d \n", datos.id, datos.apellido, datos.nombre, datos.categoria, datos.facturacion, datos.activo);

    printf("Ingrese la nueva categoria del cliente\n");
    scanf("%c", &cambioCategoria);
    fflush(stdin);

    if(cambioCategoria == 'a'){

        cambioCategoria = 'A';

    }

    if(cambioCategoria == 'b'){

        cambioCategoria = 'B';

    }

    if(cambioCategoria == 'c'){

        cambioCategoria = 'C';

    }

    while((cambioCategoria != 'A') && (cambioCategoria != 'B') && (cambioCategoria != 'C') && (cambioCategoria != 'a') && (cambioCategoria != 'b') && (cambioCategoria != 'c')){

        printf("Ingrese una categoria valida, A B o C\n");
        printf("Ingresar categoria nuevamente: \n");
        scanf("%c", &cambioCategoria);
        fflush(stdin);

    }

    printf("Esta seguro que desea modificar la categoria?\n");
    printf("1 - Aceptar\n");
    printf("2 - Cancelar\n");
    scanf("%d", &opcion);
    fflush(stdin);

    while(opcion < 1 || opcion > 2){

        printf("Por favor ingrese una opcion valida\n");
        printf("1 - Aceptar\n");
        printf("2 - Cancelar\n");
        scanf("%d", &opcion);
        fflush(stdin);

    }

    if(opcion == 1){ //si se confirma el cambio se escribe en el archivo

    toupper(cambioCategoria);
    datos.categoria = cambioCategoria;
    fseek(aC, -sizeof(struct cliente), SEEK_CUR);
    fwrite(&datos, sizeof(struct cliente), 1, aC);

    printf("\n***LA CATEGORIA FUE MODIFICADA EXITOSAMENTE***\n");

    }

    if(opcion == 2){ //si se cancela la operacion no se hace el cambio y vuelve al menu

    printf("\n***LA OPERACION HA SIDO CANCELADA***\n");

    }

    fclose(aC);

}

// modifico la facturacion
void actualizarFacturacion(FILE * aC){

    struct cliente datos;
    float nuevofacturacion; //guarda la facturacion a modificar
    char guardarApellido[30]; //guarda el apellido para buscarlo
    int buscarId, opcion, corroborarId; //guarda la id para buscarla
                            //opcion es para elegir si modificar por apellido o id
    printf("1 - Buscar cliente por ID\n");
    printf("2 - Buscar cliente por Apellido\n");
    scanf("%d", &opcion);
    fflush(stdin);

    while(opcion < 1 || opcion > 2){

        printf("Por favor ingrese una opcion valida\n");
        printf("1 - Buscar cliente por ID\n");
        printf("2 - Buscar cliente por Apellido\n");
        scanf("%d", &opcion);
        fflush(stdin);

    }

        if(opcion == 1){

        buscarId = leerId();

        corroborarId = idCorroborar(buscarId, aC);

        if(corroborarId == 1){

        }

        else{
            printf("No se encuentra el cliente\n");
            return;
        }

    }

    if(opcion == 2){

        leerApellido(guardarApellido);
        buscarId = buscarIdApellido(guardarApellido, aC);
        corroborarId = idCorroborar(buscarId, aC);

        if(corroborarId == 1){

        }

        else{
            printf("No se encuentra el cliente\n");
            return;
        }

    }


    aC = fopen("clientes.dat", "r+b");
    fseek(aC, 0, SEEK_SET);
    fseek(aC,(buscarId-1)*sizeof(struct cliente), SEEK_SET);
    fread(&datos, sizeof(struct cliente), 1, aC);

    printf("Cliente a modificar:\n");
    printf("ID: %d || Apellido: %s || Nombre: %s || Categoria: %c  || Factutacion: %.2f$  || Activo: %d \n", datos.id, datos.apellido, datos.nombre, datos.categoria, datos.facturacion, datos.activo);

    printf("Ingrese la nueva facturacion del cliente\n");
    scanf("%f", &nuevofacturacion);
    fflush(stdin);

    printf("Esta seguro que desea modificar la facturacion?\n");
    printf("1 - Aceptar\n");
    printf("2 - Cancelar\n");
    scanf("%d", &opcion);
    fflush(stdin);

    while(opcion < 1 || opcion > 2){

        printf("Por favor ingrese una opcion valida\n");
        printf("1 - Aceptar\n");
        printf("2 - Cancelar\n");
        scanf("%d", &opcion);
        fflush(stdin);

    }

   if(opcion == 1){//si se confirma la operacion escribo la nueva facturacion

    datos.facturacion = nuevofacturacion;
    fseek(aC, -sizeof(struct cliente), SEEK_CUR);
    fwrite(&datos, sizeof(struct cliente), 1, aC);

    printf("\n***LA FACTURACION FUE MODIFICADA EXITOSAMENTE***\n");

   }

    if(opcion == 2){//si se cancela la operacion, no se cambia y se vuelve al menu

    printf("\n***LA OPERACION HA SIDO CANCELADA***\n");

    return;

   }

    fclose(aC);

}
// baja logica
void bajaLogica(FILE * aC){

    struct cliente datos;
    int buscarId = leerId(); //buscarId escanea la id y la guarda
    int opcion; //opcion es para confirmar si se quiere dar la baja logica

    aC = fopen("clientes.dat","r+b");

    fseek(aC, 0, SEEK_SET);
    fseek(aC, (buscarId-1)*sizeof(struct cliente ), SEEK_SET);
    fread(&datos, sizeof(struct cliente ), 1, aC);

    printf("Usted dara de baja a:\n");
    printf("ID: %d || Apellido: %s || Nombre: %s || Categoria: %c  || Factutacion: %.2f$  || Activo: %d \n", datos.id, datos.apellido, datos.nombre, datos.categoria, datos.facturacion, datos.activo);

    printf("Esta seguro que desea darle de baja al cliente?\n");
    printf("1 - Aceptar\n");
    printf("2 - Cancelar\n");
    scanf("%d", &opcion);
    fflush(stdin);

    while(opcion < 1 || opcion > 2){

        printf("Por favor ingrese una opcion valida\n");
        printf("1 - Aceptar\n");
        printf("2 - Cancelar\n");
        scanf("%d", &opcion);
        fflush(stdin);

    }

    if(opcion == 1){

        datos.activo = 0;
        fseek(aC, -sizeof(struct cliente), SEEK_CUR);
        fwrite(&datos, sizeof(struct cliente), 1, aC);
        printf("\n***EL CLIENTE FUE DADO DE BAJA EXITOSAMENTE***\n", buscarId);

    }

    if(opcion == 2){

    printf("\n***LA OPERACION HA SIDO CANCELADA***\n");

    return;

    }

    fclose(aC);

}

//baja fisica
void bajaFisica(FILE * aC){

    FILE *temp;
    struct  cliente datos;

        aC = fopen("clientes.dat", "rb");
        temp = fopen("clientes.temp", "w+b");
        fseek(aC, 0, SEEK_SET);

        while(fread(&datos ,sizeof(struct cliente), 1, aC) == 1){

            if(datos.activo == 1){

                fwrite(&datos ,sizeof(struct cliente), 1, temp);

            }
        }

        fclose(temp);
        fclose(aC);

        remove("clientes.dat");
        rename("clientes.temp","clientes.dat");
        remove("clientes.temp");

    printf("\n**ARCHIVO ACTUALIZADO***\n");

}

void ordenar(FILE * aC){

    aC = fopen("clientes.dat","r+b");

    int i, j, flag, cantidadRegistros;

    i = 0;

    fseek(aC, 0, SEEK_END);
    cantidadRegistros = ftell(aC) /sizeof(struct cliente);// calculo la cantidad de clientes registrados para el ciclo

    struct cliente clientes[cantidadRegistros];

    fseek(aC, 0, SEEK_SET);

    while(i < cantidadRegistros){

        fseek(aC, i*sizeof(struct cliente), SEEK_SET);
        fread(&clientes[i], sizeof(struct cliente), 1, aC);
        i++;

    }

    for (i = 0 ; i < cantidadRegistros-1 ; i++){

        flag = 0;

        for (j = 0 ; j < cantidadRegistros-(i+1) ; j++){

            if (strcmp(clientes[j].apellido,clientes[j+1].apellido) > 0){

                struct cliente aux = clientes[j];
                clientes[j] = clientes[j+1];
                clientes[j+1] = aux;
                flag = 1;

            }
        }
    }

        for (j = 0 ; j < cantidadRegistros ; j++){

            printf("ID: %d || Apellido: %s || Nombre: %s || Categoria: %c  || Factutacion: %.2f  || Activo: %d \n", clientes[j].id, clientes[j].apellido, clientes[j].nombre, clientes[j].categoria, clientes[j].facturacion, clientes[j].activo);

            }

    fclose(aC);

}

int main(){

    char opcion;
    FILE * archivoCliente;

    do{

     opcion = Menu();

         switch(opcion){
            case 'A': crearArchivo(archivoCliente);
            printf("\n");
            break;

            case 'B': altaCliente(archivoCliente);
            printf("\n");
            break;

            case 'C': listarDatos(archivoCliente);
            printf("\n");
            break;

            case 'D': busqueda(archivoCliente);
            printf("\n");
            break;

            case 'E': modificarcategoria(archivoCliente);
            printf("\n");
            break;

            case 'F': actualizarFacturacion(archivoCliente);
            printf("\n");
            break;

            case 'G': ordenar(archivoCliente);
            printf("\n");
            break;

            case 'H': bajaLogica(archivoCliente);
            printf("\n");
            break;

            case 'I': bajaFisica(archivoCliente);
            printf("\n");
            break;

        }

    }while(opcion != 'S');

    printf("Programa finalizado\n");

}


