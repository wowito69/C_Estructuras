#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int dato;
    struct Nodo *siguiente;
};

void agregarNodo(struct Nodo **inicio, int dato);
void buscarValor(struct Nodo *inicio, int dato);
void eliminarValor(struct Nodo **inicio, int dato);
void modificarValor(struct Nodo *inicio, int dato);
void mostrar(struct Nodo *inicio);

int main() {
    struct Nodo *inicio = NULL;
    int seleccion, dato;

    while (1) {
        printf("\n¿Que deseas hacer?\n1.-Agregar Nodo\n2.-Buscar Valor\n3.-Eliminar Valor\n4.-Modificar valor\n5.-Mostrar\n6.-Salir\n");
        scanf("%i", &seleccion);

        switch (seleccion) {
            case 1:
                printf("Que numero deseas agregar:\n");
                scanf("%d", &dato);
                agregarNodo(&inicio, dato);
                break;
            case 2:
                printf("Que numero deseas buscar:\n");
                scanf("%d", &dato);
                buscarValor(inicio, dato);
                break;
            case 3:
                printf("Que numero deseas eliminar:\n");
                scanf("%d", &dato);
                eliminarValor(&inicio, dato);
                break;
            case 4:
                printf("Que numero deseas modificar:\n");
                scanf("%d", &dato);
                modificarValor(inicio, dato);
                break;
            case 5:
                mostrar(inicio);
                break;
            case 6:
                printf("Saliendo...\n");
                free;
                return 0;
            default:
                printf("Opción no válida. Intenta de nuevo.\n");
        }
    }

    return 0;
}

void agregarNodo(struct Nodo **inicio, int dato) {
    // Crear un nuevo nodo y asignarle memoria
    struct Nodo *nuevoNodo = (struct Nodo *)malloc(sizeof(struct Nodo));

    // Verificar si se asignó correctamente la memoria
    if (nuevoNodo == NULL) {
        printf("Error al asignar memoria para el nuevo nodo.\n");
        exit(1);
    }

    // Asignar el dato al nuevo nodo
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;  // Establecer el siguiente del nuevo nodo como NULL

    // Verificar si la lista está vacía
    if (*inicio == NULL) {
        *inicio = nuevoNodo;
    } else {
        // Encontrar el último nodo en la lista
        struct Nodo *ultimo = *inicio;
        while (ultimo->siguiente != NULL) {
            ultimo = ultimo->siguiente;
        }

        // Agregar el nuevo nodo al final de la lista
        ultimo->siguiente = nuevoNodo;
    }

    // Mostrar la lista actualizada
    mostrar(*inicio);
}


void buscarValor(struct Nodo *inicio, int dato) {
    struct Nodo *actual = inicio;

    while (actual != NULL) {
        if (actual->dato == dato) {
            printf("Valor encontrado: %d\n", dato);
            return;
        }
        actual = actual->siguiente;
    }

    printf("Valor no encontrado.\n");
}

void eliminarValor(struct Nodo **inicio, int dato) {
    struct Nodo *actual = *inicio;
    struct Nodo *anterior = NULL;

    while (actual != NULL) {
        if (actual->dato == dato) {
            if (anterior == NULL) {
                *inicio = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }

            free(actual);
            printf("Valor eliminado: %d\n", dato);
            return;
        }

        anterior = actual;
        actual = actual->siguiente;
    }

    printf("Valor no encontrado para eliminar.\n");
}

void modificarValor(struct Nodo *inicio, int dato) {
    struct Nodo *actual = inicio;

    while (actual != NULL) {
        if (actual->dato == dato) {
            printf("Ingresa el nuevo valor para %d: ", dato);
            scanf("%d", &(actual->dato));
            printf("Valor modificado con éxito.\n");
            return;
        }
        actual = actual->siguiente;
    }

    printf("Valor no encontrado para modificar.\n");
}

void mostrar(struct Nodo *inicio) {
    struct Nodo *actual = inicio;

    printf("Contenido de la lista:\n");
    while (actual != NULL) {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}



