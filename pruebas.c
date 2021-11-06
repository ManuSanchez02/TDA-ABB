#include "src/abb.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "pa2mm.h"
#include "string.h"

typedef struct vector{
  void** elementos;
  size_t tamanio_maximo;
  size_t tamanio_actual;
} vector_t;


/*
 * Pre: _numero1 y _numero2 deben ser punteros a entero inicializados.
 * Post: - Devuelve un numero menor a 0 si numero1 < numero2.
 *       - Devuelve un numero mayor a 0 si numero1 > numero2.
 *       - Devuelve 0 si numero1 es igual a numero2.
 */
int comparador_de_enteros(void* _numero1, void* _numero2){
  int* numero1 = _numero1;
  int* numero2 = _numero2;

  return *numero1 - *numero2;
}

int _comparador_de_enteros(const void* numero1, const void* numero2){


  return *(int*)numero1 - *(int*)numero2;
}

/*
 * Pre: elemento debe ser un puntero a un int.
 * Post: Libera la memoria reservada para elemento.
 */
void destructor_de_enteros(void* elemento){
  free(elemento);
}

/*
 * Pre: elemento debe ser un puntero a un int y vector tiene que ser un vector de punteros.
 * Post: agrega elemento a vector si este es menor a 45.
 */
bool agregar_a_vector_si_es_menor_a_45(void* elemento, void* vector){
  vector_t* vector_aux = (vector_t*) vector;
  if(!vector_aux->elementos || vector_aux->tamanio_actual >= vector_aux->tamanio_maximo || *(int*)elemento >= 45)
    return false;

  vector_aux->elementos[vector_aux->tamanio_actual] = elemento;
  vector_aux->tamanio_actual++;

  return true;
}


void intentoCrearYDestruirUnABB(){
  abb_t* arbol = abb_crear(comparador_de_enteros);

  pa2m_afirmar((arbol != NULL), "El arbol se pudo crear con exito");

  abb_destruir(arbol);
}



void dadoUnArbolNULL_suEstadoEsCorrecto(){
  abb_t* arbol = NULL;
  int elemento = 3;

  pa2m_afirmar((abb_tamanio(arbol) == 0), "El abb NULL tiene tamaño 0");
  pa2m_afirmar((abb_vacio(arbol) == true), "El abb NULL esta vacio");
  pa2m_afirmar((abb_buscar(arbol, &elemento) == NULL), "Buscar un elemento en un arbol vacio devuelve NULL");
}

void dadoUnArbolNULL_noPuedoInsertarElementosNiQuitarElementos(){
  abb_t* arbol = NULL;
  int elemento1 = 12;
  int* elemento2 = malloc(sizeof(int));
  if(!elemento2)
    return;

  *elemento2 = 3;

  pa2m_afirmar((abb_insertar(arbol, &elemento1) == NULL), "El elemento del stack no pudo ser insertado");
  pa2m_afirmar((abb_insertar(arbol, elemento2) == NULL), "El elemento del heap no pudo ser insertado");
  pa2m_afirmar((abb_quitar(arbol, &elemento1) == NULL), "No puedo quitar elementos del stack");
  pa2m_afirmar((abb_quitar(arbol, elemento2) == NULL), "No puedo quitar elementos del heap");

  free(elemento2);
}



void dadoUnArbolVacio_suEstadoEsCorrecto(){
  abb_t* arbol = abb_crear(comparador_de_enteros);
  int elemento = 3;

  pa2m_afirmar((abb_tamanio(arbol) == 0), "El abb vacio tiene tamaño 0");
  pa2m_afirmar((abb_vacio(arbol) == true), "El abb vacio esta vacio");
  pa2m_afirmar((abb_buscar(arbol, &elemento) == NULL), "Buscar un elemento en un arbol vacio devuelve NULL");

  abb_destruir(arbol);
}

void dadoUnArbolVacio_noPuedoQuitarElementos(){
  abb_t* arbol = abb_crear(comparador_de_enteros);
  int elemento1 = 3;
  int* elemento2 = malloc(sizeof(int));
  if(!elemento2)
    return;

  *elemento2 = 18;

  pa2m_afirmar((abb_quitar(arbol, &elemento1) == NULL), "No puedo quitar elementos del stack");
  pa2m_afirmar((abb_quitar(arbol, elemento2) == NULL), "No puedo quitar elementos del heap");

  free(elemento2);
  abb_destruir(arbol);
}

void dadoUnArbolVacio_puedoInsertarElementosDelStack(){
  abb_t* arbol = abb_crear(comparador_de_enteros);
  int elemento1 = 12;
  int elemento2 = 2;
  int elemento3 = 23;
  int elemento4 = 16;
  int elemento5 = 1;

  pa2m_afirmar((abb_insertar(arbol, &elemento1) == arbol), "El elemento1 pudo ser insertado");
  pa2m_afirmar((abb_insertar(arbol, &elemento2) == arbol), "El elemento2 pudo ser insertado");
  pa2m_afirmar((abb_insertar(arbol, &elemento3) == arbol), "El elemento3 pudo ser insertado");
  pa2m_afirmar((abb_insertar(arbol, &elemento4) == arbol), "El elemento4 pudo ser insertado");
  pa2m_afirmar((abb_insertar(arbol, &elemento5) == arbol), "El elemento5 pudo ser insertado");

  abb_destruir(arbol);
}

void dadoUnArbolVacio_puedoInsertarMuchosElementosDelStack_ysuEstadoEsCorrecto(){
  abb_t* arbol = abb_crear(comparador_de_enteros);
  int elementos[1000];

  for(int i = 0; i < 1000; i++){
    elementos[i] = i;
    abb_insertar(arbol, &elementos[i]);
  }

  pa2m_afirmar((abb_tamanio(arbol) == 1000), "El abb con 1000 elementos tiene tamaño 1000");
  pa2m_afirmar((abb_vacio(arbol) == false), "El abb con 1000 elementos no esta vacio");
  pa2m_afirmar((abb_buscar(arbol, &elementos[743]) == &elementos[743]), "El abb con 1000 elementos puede buscar un elemento arbitrario");

  abb_destruir(arbol);
}

void dadoUnArbolVacio_puedoInsertarElementosDelHeap(){
  abb_t* arbol = abb_crear(comparador_de_enteros);
  int* elemento1 = malloc(sizeof(int));
  int* elemento2 = malloc(sizeof(int));
  int* elemento3 = malloc(sizeof(int));
  int* elemento4 = malloc(sizeof(int));
  int* elemento5 = malloc(sizeof(int));
  if(!elemento1 || !elemento2 || !elemento3 || !elemento4 || !elemento5)
    return;

  *elemento1 = 15;
  *elemento2 = 7;
  *elemento3 = 3;
  *elemento4 = 5;
  *elemento5 = 19;

  pa2m_afirmar((abb_insertar(arbol, elemento2) == arbol), "El elemento1 pudo ser insertado");
  pa2m_afirmar((abb_insertar(arbol, elemento1) == arbol), "El elemento2 pudo ser insertado");
  pa2m_afirmar((abb_insertar(arbol, elemento3) == arbol), "El elemento3 pudo ser insertado");
  pa2m_afirmar((abb_insertar(arbol, elemento4) == arbol), "El elemento4 pudo ser insertado");
  pa2m_afirmar((abb_insertar(arbol, elemento5) == arbol), "El elemento5 pudo ser insertado");


  abb_destruir_todo(arbol, destructor_de_enteros);
}



void dadoUnArbolConElementosDelStack_suEstadoEsCorrecto(){
  abb_t* arbol = abb_crear(comparador_de_enteros);
  int elemento1 = 12;
  int elemento2 = 2;
  int elemento3 = 23;
  int elemento4 = 34;

  abb_insertar(arbol, &elemento1);
  abb_insertar(arbol, &elemento2);
  abb_insertar(arbol, &elemento3);

  pa2m_afirmar((abb_tamanio(arbol) == 3), "El abb con 3 elementos tiene tamaño 3");
  pa2m_afirmar((abb_vacio(arbol) == false), "El abb con 3 elementos no esta vacio");
  pa2m_afirmar((abb_buscar(arbol, &elemento1) == &elemento1), "El abb con 3 elementos tiene el elemento1");
  pa2m_afirmar((abb_buscar(arbol, &elemento2) == &elemento2), "El abb con 3 elementos tiene el elemento2");
  pa2m_afirmar((abb_buscar(arbol, &elemento3) == &elemento3), "El abb con 3 elementos tiene el elemento3");
  pa2m_afirmar((abb_buscar(arbol, &elemento4) == NULL), "El abb con 3 elementos no tiene el elemento4");

  abb_destruir(arbol);
}

void dadoUnArbolConElementos_prueboQuitarElementos(){
  abb_t* arbol = abb_crear(comparador_de_enteros);

  int elemento1 = 42;
  int elemento2 = 34;
  int elemento3 = 15;
  int elemento4 = 36;
  int* elemento5 = malloc(sizeof(int)); 
  int* elemento6 = malloc(sizeof(int)); 
  int* elemento7 = malloc(sizeof(int)); 

  if(!elemento5 || !elemento6 || !elemento7){
    free(elemento5);
    free(elemento6);
    free(elemento7);
  }

  *elemento5 = 56;
  *elemento6 = 65;
  *elemento7 = 60;

  abb_insertar(arbol, &elemento1);
  abb_insertar(arbol, &elemento2);
  abb_insertar(arbol, &elemento3);
  abb_insertar(arbol, &elemento4);
  abb_insertar(arbol, elemento5);
  abb_insertar(arbol, elemento6);
  abb_insertar(arbol, elemento7);

  pa2m_afirmar((abb_quitar(arbol, elemento7) == elemento7), "Puedo quitar una hoja");
  pa2m_afirmar((abb_tamanio(arbol) == 6), "El tamaño del arbol es 6");
  pa2m_afirmar((abb_buscar(arbol, elemento7) == NULL), "El elemento eliminado no puede ser encontrado");


  pa2m_afirmar((abb_quitar(arbol, elemento5) == elemento5), "Puedo quitar una rama con un hijo");
  pa2m_afirmar((abb_tamanio(arbol) == 5), "El tamaño del arbol es 5");
  pa2m_afirmar((abb_buscar(arbol, elemento5) == NULL), "El elemento eliminado no puede ser encontrado");
  pa2m_afirmar((abb_buscar(arbol, elemento6) == elemento6), "El hijo del elemento eliminado puede ser encontrado");
  pa2m_afirmar((arbol->nodo_raiz->derecha->elemento == elemento6), "El hijo derecho de la raiz es el esperado");

  pa2m_afirmar((abb_quitar(arbol, &elemento2) == &elemento2), "Puedo quitar una rama con dos hijos");
  pa2m_afirmar((abb_tamanio(arbol) == 4), "El tamaño del arbol es 4");
  pa2m_afirmar((abb_buscar(arbol, &elemento2) == NULL), "El elemento eliminado no puede ser encontrado");
  pa2m_afirmar((abb_buscar(arbol, &elemento3) == &elemento3), "El hijo izquierdo del elemento eliminado puede ser encontrado");
  pa2m_afirmar((abb_buscar(arbol, &elemento4) == &elemento4), "El hijo derecho del elemento eliminado puede ser encontrado");
  pa2m_afirmar((arbol->nodo_raiz->izquierda->elemento == &elemento3), "El hijo izquierdo de la raiz es el esperado");



  pa2m_afirmar((abb_quitar(arbol, &elemento1) == &elemento1), "Puedo quitar la raiz del arbol");
  pa2m_afirmar((abb_tamanio(arbol) == 3), "El tamaño del arbol es 3");
  pa2m_afirmar((abb_buscar(arbol, &elemento1) == NULL), "El elemento eliminado no puede ser encontrado");
  pa2m_afirmar((abb_buscar(arbol, &elemento3) == &elemento3), "El hijo izquierdo del elemento eliminado puede ser encontrado");
  pa2m_afirmar((abb_buscar(arbol, elemento6) == elemento6), "El hijo derecho del elemento eliminado puede ser encontrado");
  pa2m_afirmar((arbol->nodo_raiz->elemento == &elemento4), "La raiz es la esperada");
  pa2m_afirmar((arbol->nodo_raiz->derecha->elemento == elemento6), "El hijo derecho de la raiz es el esperado");
  pa2m_afirmar((arbol->nodo_raiz->izquierda->elemento == &elemento3), "El hijo izquierdo de la raiz es el esperado");

  pa2m_afirmar((abb_quitar(arbol, &elemento3) == &elemento3), "Puedo quitar la hoja izquierda del arbol");
  pa2m_afirmar((abb_quitar(arbol, elemento6) == elemento6), "Puedo quitar la hoja derecha del arbol");
  pa2m_afirmar((abb_quitar(arbol, &elemento4) == &elemento4), "Puedo quitar la raiz del arbol");
  pa2m_afirmar((abb_tamanio(arbol) == 0), "El tamaño del arbol es 0");
  pa2m_afirmar((abb_vacio(arbol) == true), "El arbol esta vacio");
  pa2m_afirmar((abb_buscar(arbol, &elemento4) == NULL), "El elemento que era raiz no puede ser encontrado");
  pa2m_afirmar((abb_buscar(arbol, &elemento3) == NULL), "La hoja izquierda no puede ser encontrada");
  pa2m_afirmar((abb_buscar(arbol, elemento6) == NULL), "La hoja derecha no puede ser encontrada");
  pa2m_afirmar((arbol->nodo_raiz == NULL), "La raiz es la esperada");



  free(elemento5);
  free(elemento6);
  free(elemento7);
  abb_destruir(arbol);
}

void dadoUnArbolCon2Elementos_prueboQuitarElementos(){
  abb_t* arbol = abb_crear(comparador_de_enteros);

  int elemento1 = 75;
  int elemento2 = 12;
  int elemento3 = 100;

  abb_insertar(arbol, &elemento1);
  abb_insertar(arbol, &elemento2);
  abb_insertar(arbol, &elemento3);

  pa2m_afirmar((abb_quitar(arbol, &elemento1) == &elemento1), "Puedo quitar la raiz");
  pa2m_afirmar((arbol->nodo_raiz->derecha->elemento == &elemento3), "No hay hijo derecho");
  pa2m_afirmar((arbol->nodo_raiz->izquierda == NULL), "No hay hijo izquierdo");
  pa2m_afirmar((arbol->nodo_raiz->elemento == &elemento2), "La raiz es la esperada");

  abb_destruir(arbol);
}

void dadoUnArbolConElementos_prueboQuitarSuRaiz(){
  abb_t* arbol = abb_crear(comparador_de_enteros);

  int elemento1 = 42;
  int elemento2 = 34;
  int elemento3 = 15;
  int elemento4 = 36;
  int elemento5 = 56;
  int elemento6 = 65;
  int elemento7 = 60; 

  abb_insertar(arbol, &elemento1);
  abb_insertar(arbol, &elemento2);
  abb_insertar(arbol, &elemento3);
  abb_insertar(arbol, &elemento4);
  abb_insertar(arbol, &elemento5);
  abb_insertar(arbol, &elemento6);
  abb_insertar(arbol, &elemento7);

  pa2m_afirmar((abb_quitar(arbol, &elemento1) == &elemento1), "Puedo quitar la raiz");
  pa2m_afirmar((abb_tamanio(arbol) == 6), "El tamaño del arbol es 6");
  pa2m_afirmar((arbol->nodo_raiz->elemento == &elemento4), "La raiz es el elemento 36");
  
  pa2m_afirmar((abb_quitar(arbol, &elemento4) == &elemento4), "Puedo quitar la raiz");
  pa2m_afirmar((abb_tamanio(arbol) == 5), "El tamaño del arbol es 5");
  pa2m_afirmar((arbol->nodo_raiz->elemento == &elemento2), "La raiz es el elemento 34");

  pa2m_afirmar((abb_quitar(arbol, &elemento2) == &elemento2), "Puedo quitar la raiz");
  pa2m_afirmar((abb_tamanio(arbol) == 4), "El tamaño del arbol es 4");
  pa2m_afirmar((arbol->nodo_raiz->elemento == &elemento3), "La raiz es el elemento 15");

  pa2m_afirmar((abb_quitar(arbol, &elemento3) == &elemento3), "Puedo quitar la raiz");
  pa2m_afirmar((abb_tamanio(arbol) == 3), "El tamaño del arbol es 3");
  pa2m_afirmar((arbol->nodo_raiz->elemento == &elemento5), "La raiz es el elemento 56");
  
  pa2m_afirmar((abb_quitar(arbol, &elemento5) == &elemento5), "Puedo quitar la raiz");
  pa2m_afirmar((abb_tamanio(arbol) == 2), "El tamaño del arbol es 2");
  pa2m_afirmar((arbol->nodo_raiz->elemento == &elemento6), "La raiz es el elemento 65");

  pa2m_afirmar((abb_quitar(arbol, &elemento6) == &elemento6), "Puedo quitar la raiz");
  pa2m_afirmar((abb_tamanio(arbol) == 1), "El tamaño del arbol es 1");
  pa2m_afirmar((arbol->nodo_raiz->elemento == &elemento7), "La raiz es el elemento 60");

  pa2m_afirmar((abb_quitar(arbol, &elemento7) == &elemento7), "Puedo quitar la raiz");
  pa2m_afirmar((abb_tamanio(arbol) == 0), "El tamaño del arbol es 0");
  pa2m_afirmar((abb_vacio(arbol) == true), "El arbol esta vacio");
  pa2m_afirmar((arbol->nodo_raiz == NULL), "La raiz es NULL");
  
  abb_destruir(arbol);
}

void dadoUnArbolConElementosDelHeap_suEstadoEsCorrecto(){
  abb_t* arbol = abb_crear(comparador_de_enteros);
  int* elemento1 = malloc(sizeof(int));
  int* elemento2 = malloc(sizeof(int));
  int* elemento3 = malloc(sizeof(int));
  int* elemento4 = malloc(sizeof(int));
  int* elemento5 = malloc(sizeof(int));
  if(!elemento1 || !elemento2 || !elemento3 || !elemento4 || !elemento5)
    return;

  *elemento1 = 15;
  *elemento2 = 7;
  *elemento3 = 3;
  *elemento4 = 5;
  *elemento5 = 19;

  abb_insertar(arbol, elemento1);
  abb_insertar(arbol, elemento2);
  abb_insertar(arbol, elemento3);
  abb_insertar(arbol, elemento4);
  abb_insertar(arbol, elemento5);

  pa2m_afirmar((abb_tamanio(arbol) == 5), "El abb con 5 elementos del heap tiene tamaño 5");
  pa2m_afirmar((abb_vacio(arbol) == false), "El abb con 5 elementos no esta vacio");
  pa2m_afirmar((abb_buscar(arbol, elemento4) == elemento4), "El abb con 5 elementos puede buscar tiene al elemento4");


  abb_destruir_todo(arbol, destructor_de_enteros);
}

void dadoUnArbolConElementos_puedoAplicarFuncionACadaElementoYVerificoElOrdenDeAplicacion(){
  abb_t* arbol = abb_crear(comparador_de_enteros);
  vector_t vector;
  void* elementos[5];
  vector.elementos = elementos;
  vector.tamanio_maximo = 5;
  vector.tamanio_actual = 0;

  int elemento1 = 42;
  int elemento2 = 34;
  int elemento3 = 15;
  int elemento4 = 36;
  int elemento5 = 56;
  int elemento6 = 65;
  int elemento7 = 60;
  int elemento8 = 35;

  abb_insertar(arbol, &elemento1);
  abb_insertar(arbol, &elemento2);
  abb_insertar(arbol, &elemento3);
  abb_insertar(arbol, &elemento4);
  abb_insertar(arbol, &elemento5);
  abb_insertar(arbol, &elemento6);
  abb_insertar(arbol, &elemento7);
  abb_insertar(arbol, &elemento8);
  
  pa2m_afirmar((abb_con_cada_elemento(arbol, PREORDEN, agregar_a_vector_si_es_menor_a_45, &vector) == 6), "La funcion se invoco 6 veces");
  pa2m_afirmar((vector.elementos[0] == &elemento1), "La funcion se aplico sobre el primer elemento PREORDEN");
  pa2m_afirmar((vector.elementos[1] == &elemento2), "La funcion se aplico sobre el segundo elemento PREORDEN");
  pa2m_afirmar((vector.elementos[2] == &elemento3), "La funcion se aplico sobre el tercer elemento PREORDEN");
  pa2m_afirmar((vector.elementos[3] == &elemento4), "La funcion se aplico sobre el cuarto elemento PREORDEN");
  pa2m_afirmar((vector.elementos[4] == &elemento8), "La funcion se aplico sobre el quinto elemento PREORDEN");

  vector.tamanio_actual = 0;
  pa2m_afirmar((abb_con_cada_elemento(arbol, INORDEN, agregar_a_vector_si_es_menor_a_45, &vector) == 6), "La funcion se invoco 6 veces");
  pa2m_afirmar((vector.elementos[0] == &elemento3), "La funcion se aplico sobre el primer elemento INORDEN");
  pa2m_afirmar((vector.elementos[1] == &elemento2), "La funcion se aplico sobre el segundo elemento INORDEN");
  pa2m_afirmar((vector.elementos[2] == &elemento8), "La funcion se aplico sobre el tercer elemento INORDEN");
  pa2m_afirmar((vector.elementos[3] == &elemento4), "La funcion se aplico sobre el cuarto elemento INORDEN");
  pa2m_afirmar((vector.elementos[4] == &elemento1), "La funcion se aplico sobre el quinto elemento INORDEN");

  vector.tamanio_actual = 0;
  pa2m_afirmar((abb_con_cada_elemento(arbol, POSTORDEN, agregar_a_vector_si_es_menor_a_45, &vector) == 5), "La funcion se invoco 5 veces");
  pa2m_afirmar((vector.elementos[0] == &elemento3), "La funcion se aplico sobre el primer elemento POSTORDEN");
  pa2m_afirmar((vector.elementos[1] == &elemento8), "La funcion se aplico sobre el segundo elemento POSTORDEN");
  pa2m_afirmar((vector.elementos[2] == &elemento4), "La funcion se aplico sobre el tercer elemento POSTORDEN");
  pa2m_afirmar((vector.elementos[3] == &elemento2), "La funcion se aplico sobre el cuarto elemento POSTORDEN");

  abb_destruir(arbol);
}

void dadoUnArbolConElementos_puedoRecorrerYAgregarAVector(){
  abb_t* arbol = abb_crear(comparador_de_enteros);
  void* array_preorden[5];
  void* array_inorden[6];
  void* array_postorden[4];
  size_t tamanio_maximo_preorden = 5, tamanio_maximo_inorden = 6, tamanio_maximo_postorden = 4;

  int elemento1 = 42;
  int elemento2 = 34;
  int elemento3 = 15;
  int elemento4 = 36;
  int elemento5 = 56;
  int elemento6 = 65;
  int elemento7 = 60;
  int elemento8 = 35;

  abb_insertar(arbol, &elemento1);
  abb_insertar(arbol, &elemento2);
  abb_insertar(arbol, &elemento3);
  abb_insertar(arbol, &elemento4);
  abb_insertar(arbol, &elemento5);
  abb_insertar(arbol, &elemento6);
  abb_insertar(arbol, &elemento7);
  abb_insertar(arbol, &elemento8);

  pa2m_afirmar((abb_recorrer(arbol, PREORDEN, array_preorden, tamanio_maximo_preorden) == 5), "La cantidad de elementos PREORDEN agregados al array es 5");
  pa2m_afirmar((array_preorden[0] == &elemento1), "El primer elemento del array es correcto");
  pa2m_afirmar((array_preorden[1] == &elemento2), "El segundo elemento del array es correcto");
  pa2m_afirmar((array_preorden[2] == &elemento3), "El tercero elemento del array es correcto");
  pa2m_afirmar((array_preorden[3] == &elemento4), "El cuarto elemento del array es correcto");
  pa2m_afirmar((array_preorden[4] == &elemento8), "El quinto elemento del array es correcto");

  pa2m_afirmar((abb_recorrer(arbol, INORDEN, array_inorden, tamanio_maximo_inorden) == 6), "La cantidad de elementos INORDEN agregados al array es 6");
  pa2m_afirmar((array_inorden[0] == &elemento3), "El primer elemento del array es correcto");
  pa2m_afirmar((array_inorden[1] == &elemento2), "El segundo elemento del array es correcto");
  pa2m_afirmar((array_inorden[2] == &elemento8), "El tercero elemento del array es correcto");
  pa2m_afirmar((array_inorden[3] == &elemento4), "El cuarto elemento del array es correcto");
  pa2m_afirmar((array_inorden[4] == &elemento1), "El quinto elemento del array es correcto");
  pa2m_afirmar((array_inorden[5] == &elemento5), "El sexto elemento del array es correcto");

  pa2m_afirmar((abb_recorrer(arbol, POSTORDEN, array_postorden, tamanio_maximo_postorden) == 4), "La cantidad de elementos POSTORDEN agregados al array es 4");
  pa2m_afirmar((array_postorden[0] == &elemento3), "El primer elemento del array es correcto");
  pa2m_afirmar((array_postorden[1] == &elemento8), "El segundo elemento del array es correcto");
  pa2m_afirmar((array_postorden[2] == &elemento4), "El tercero elemento del array es correcto");
  pa2m_afirmar((array_postorden[3] == &elemento2), "El cuarto elemento del array es correcto");

  abb_destruir(arbol);
}

void dadoUnArbolVacio_insertoMuchosElementos_yComprueboSuEstado(){
  abb_t* arbol = abb_crear(comparador_de_enteros);
  int vector[10000];
  int vector_ordenado[10000];
  void* vector_recorrido[10000];
  for(size_t i = 0; i < 10000; i++){
    vector[i] = rand();
    arbol = abb_insertar(arbol, &vector[i]);
  }
  memcpy(vector_ordenado, vector, 10000*sizeof(int));
  qsort(vector_ordenado, 10000, sizeof(int), _comparador_de_enteros);
  

  pa2m_afirmar((arbol != NULL), "Puedo insertar muchos elementos en un arbol");
  pa2m_afirmar((arbol->nodo_raiz->elemento == &vector[0]), "El elemento del nodo raiz es el primer elemento agregado");
  pa2m_afirmar((abb_tamanio(arbol) == 10000), "El tamaño es correcto");
  pa2m_afirmar((abb_vacio(arbol) == false), "El abb no esta vacio");
  pa2m_afirmar((abb_buscar(arbol, &vector[4562]) == &vector[4562]), "El tamaño es correcto");


  pa2m_afirmar((abb_recorrer(arbol, INORDEN, vector_recorrido, 10000) == 10000), "La cantidad de elementos recorridos es la de todo el arbol");
  int i = 0;
  while(vector_recorrido[i] == &vector_ordenado[i])
    i++;
  pa2m_afirmar((*(int*)vector_recorrido[i] == vector_ordenado[i]), "Los elementos se recorrieron en el orden correcto");  


  for(size_t i = 0; i < 10000; i++){
    abb_quitar(arbol, &vector[i]);
  }
  pa2m_afirmar((arbol->nodo_raiz == NULL), "El nodo raiz es nulo");
  pa2m_afirmar((abb_tamanio(arbol) == 0), "El tamaño despues de quitar es correcto");
  pa2m_afirmar((abb_vacio(arbol) == true), "El abb esta vacio despues de quitar elementos");


  abb_destruir(arbol);
}

int main(){
  srand((unsigned int)time(NULL));
  pa2m_nuevo_grupo("Pruebas de creacion y destruccion de ABB");
  intentoCrearYDestruirUnABB();

  pa2m_nuevo_grupo("Pruebas con arbol nulo");
  dadoUnArbolNULL_suEstadoEsCorrecto();
  dadoUnArbolNULL_noPuedoInsertarElementosNiQuitarElementos();

  pa2m_nuevo_grupo("Pruebas con arbol vacio");
  dadoUnArbolVacio_suEstadoEsCorrecto();
  dadoUnArbolVacio_noPuedoQuitarElementos();
  dadoUnArbolVacio_puedoInsertarElementosDelStack();
  dadoUnArbolVacio_puedoInsertarMuchosElementosDelStack_ysuEstadoEsCorrecto();
  dadoUnArbolVacio_puedoInsertarElementosDelHeap();

  pa2m_nuevo_grupo("Pruebas con arbol con elementos");
  dadoUnArbolConElementosDelStack_suEstadoEsCorrecto();
  dadoUnArbolConElementosDelHeap_suEstadoEsCorrecto();
  dadoUnArbolConElementos_prueboQuitarElementos();
  dadoUnArbolCon2Elementos_prueboQuitarElementos();
  dadoUnArbolConElementos_prueboQuitarSuRaiz();

  pa2m_nuevo_grupo("Pruebas de recorrido de arbol");
  dadoUnArbolConElementos_puedoAplicarFuncionACadaElementoYVerificoElOrdenDeAplicacion();
  dadoUnArbolConElementos_puedoRecorrerYAgregarAVector();

  pa2m_nuevo_grupo("Pruebas de volumen");
  dadoUnArbolVacio_insertoMuchosElementos_yComprueboSuEstado();

  return pa2m_mostrar_reporte();
}
