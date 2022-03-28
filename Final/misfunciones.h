#ifndef _MISFUNCIONES_H_
#define _MISFUNCIONES_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int idCorroborar(int idActual, FILE* aC);

void leerApellido(char* apellido);

int leerId();

void listarDatos(FILE *aC);

struct cliente;

void busqueda(FILE *aC);

#endif

