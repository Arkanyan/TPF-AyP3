#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructura_materias.c"

typedef struct estructuraEstudiante{
    char nombre[64];
    int legajo;
    int edad;
    NodoMateria *materias;

} Estudiante;

typedef struct NodoEstudiante {
    Estudiante estudiante;
    struct NodoEstudiante *proximo;
    
} NodoEstudiante;

NodoEstudiante *agregarElemento(NodoEstudiante *lista, Estudiante estudiante) {
    NodoEstudiante *nodoNuevo = malloc(sizeof(NodoEstudiante));
    nodoNuevo->estudiante = estudiante;
    nodoNuevo->proximo = NULL;
    if (lista == NULL) {
        lista = nodoNuevo;
    } else {
        NodoEstudiante *cursor = lista;
        while (cursor->proximo != NULL) {
            cursor = cursor->proximo;
        }
        cursor->proximo = nodoNuevo;
    }
    return lista;
}

NodoEstudiante *agregarElementoPorEdad(NodoEstudiante *lista, Estudiante estudiante) {
    NodoEstudiante *nodoNuevo = malloc(sizeof(NodoEstudiante));
    nodoNuevo->estudiante = estudiante;
    nodoNuevo->proximo = NULL;
    if (lista == NULL || lista->estudiante.edad > nodoNuevo->estudiante.edad) {
        nodoNuevo->proximo = lista;
        lista = nodoNuevo;
    } else {
        NodoEstudiante *cursor = lista;
        while (cursor->proximo != NULL && cursor->proximo->estudiante.edad < nodoNuevo->estudiante.edad) {
            cursor = cursor->proximo;
        }
        if(cursor->proximo != NULL){
            nodoNuevo->proximo = cursor->proximo;
        }
        cursor->proximo = nodoNuevo;
    }
    return lista;
}

NodoEstudiante *agregarNuevoEstudiante(NodoEstudiante *lista, Estudiante estudiante) {
    NodoEstudiante *nodoNuevo = malloc(sizeof(NodoEstudiante));
    nodoNuevo->estudiante = estudiante;
    nodoNuevo->proximo = NULL;
    if (lista == NULL) {
        lista = nodoNuevo;
        nodoNuevo->estudiante.legajo = 1;
    } else {
        NodoEstudiante *cursor = lista;
        while (cursor->proximo != NULL) {
            cursor = cursor->proximo;
        }
        nodoNuevo->estudiante.legajo = cursor->estudiante.legajo+1;
        cursor->proximo = nodoNuevo;
    }
    return lista;
}

NodoEstudiante *altaEstudiante(char *nombre, int edad, NodoEstudiante *lista){
    Estudiante estudiante;
    strcpy(estudiante.nombre, nombre);
    estudiante.edad = edad;
    estudiante.materias = crearListaMaterias();
    lista = agregarNuevoEstudiante(lista, estudiante);
    return lista;
}

NodoEstudiante *crearLista() {
    NodoEstudiante *lista = malloc(sizeof(NodoEstudiante));
    lista = NULL;
    return lista;
}

int largoDeLista(NodoEstudiante *lista){
    if (lista == NULL) {
       return 0;
    } else {
        int contador = 0;
        NodoEstudiante *cursor = lista;
        while (cursor != NULL) {
            contador = contador+1;
            cursor = cursor->proximo;
        }
        return contador;
    }
    return 0;
}
bool verificarEstudiante(NodoEstudiante *lista, int legajo){
    if (lista == NULL) {
       return false;
    } else {
        NodoEstudiante *cursor = lista;
        while (cursor->proximo != NULL && cursor->estudiante.legajo != legajo) {
            cursor = cursor->proximo;
        }
        if(cursor->estudiante.legajo == legajo){
            return true;
        }
        return false;
    }
}

NodoEstudiante *modificarEstudianteActual(NodoEstudiante *lista, int legajo){
    if (lista == NULL) {
       return lista;
    } else {
        NodoEstudiante *cursor = lista;
        while (cursor->proximo != NULL && cursor->estudiante.legajo != legajo) {
            cursor = cursor->proximo;
        }
        if(cursor->estudiante.legajo == legajo){
            return cursor;
        }
    }
}

NodoEstudiante *obtenerEstudiante (NodoEstudiante *lista, char *nombre){
    NodoEstudiante *listaNueva = crearLista();
    if(lista == NULL){
        return listaNueva;
    } else{
        NodoEstudiante *cursor = lista;
        while(cursor != NULL){
            if(strcmp(cursor->estudiante.nombre, nombre) == 0){
                listaNueva = agregarElemento(listaNueva, cursor->estudiante);
            }
            cursor = cursor->proximo;
        }
        return listaNueva;  
    }
}

NodoEstudiante *obtenerEstudiantesPorEdad (NodoEstudiante *lista, int min, int max){
    NodoEstudiante *listaNueva = crearLista();
    if(lista == NULL){
        return listaNueva;
    } else{
        NodoEstudiante *cursor = lista;
        while(cursor != NULL){
            if(cursor->estudiante.edad >= min && cursor->estudiante.edad <= max){
                listaNueva = agregarElementoPorEdad(listaNueva, cursor->estudiante);
            }
            cursor = cursor->proximo;
        }
        return listaNueva;  
    }
}

void eliminarNodo (NodoEstudiante *lista, int posicion){
    if(lista == NULL || posicion >= largoDeLista(lista)){
        return;
    } else{
        NodoEstudiante *cursor = lista;
        for(int i = 0; i < posicion-1 ;i =i+1){
            cursor = cursor->proximo;
        }
        NodoEstudiante *proximo = cursor->proximo->proximo;
        free(cursor->proximo);
        cursor->proximo = proximo;
    }
}

void imprimirLista(NodoEstudiante *lista){
    if(lista == NULL){
        printf("La lista esta vacia\n");
    }else{
        NodoEstudiante *cursor = lista;
        int contador = 0;
        printf("    Nombre y Apellido      Edad  Legajo\n");
        while (cursor != NULL) {
            contador = contador + 1;
            printf("%i.  %s   %d     %d\n", contador, cursor->estudiante.nombre, cursor->estudiante.edad, cursor->estudiante.legajo);
            cursor = cursor->proximo;
        }
        printf("\n");
    }
}