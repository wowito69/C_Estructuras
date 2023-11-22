#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura del nodo
struct Nodo {
    //campo dato
    int dato;
    //apuntador izquierdo y derecho
    struct Nodo *izquierda;
    struct Nodo *derecha;
};

// Función para crear un nuevo nodo
struct Nodo* crearNodo(int dato) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->izquierda = nuevoNodo->derecha = NULL;
    return nuevoNodo;
}

// Función para insertar un nodo en el árbol
struct Nodo* insertar(struct Nodo* raiz, int dato) {
    if (raiz == NULL) {
        return crearNodo(dato);
    }

    if (dato < raiz->dato) {
        raiz->izquierda = insertar(raiz->izquierda, dato);
    } else if (dato > raiz->dato) {
        raiz->derecha = insertar(raiz->derecha, dato);
    }

    return raiz;
}

// Función para realizar un recorrido en orden (in-order) del árbol
void inOrder(struct Nodo* raiz) {
    if (raiz != NULL) {
        inOrder(raiz->izquierda);
        printf("%d ", raiz->dato);
        inOrder(raiz->derecha);
    }
}

// Función principal
int main() {
    // Crear una raíz vacía
    struct Nodo* raiz = NULL;

    // Insertar elementos en el árbol
    raiz = insertar(raiz, 50);
    raiz = insertar(raiz, 30);
    raiz = insertar(raiz, 20);
    raiz = insertar(raiz, 40);
    raiz = insertar(raiz, 70);
    raiz = insertar(raiz, 60);
    raiz = insertar(raiz, 80);

    // Realizar un recorrido in-order e imprimir los nodos
    printf("Recorrido In-Order: ");
    inOrder(raiz);

    // Liberar la memoria al finalizar el programa
    // En una implementación completa, podrías tener funciones para liberar la memoria
    // asociada con los nodos del árbol.

    return 0;
}
