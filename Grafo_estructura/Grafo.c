//
// Created by wowo on 14/11/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// defino todas las funciones para poder usarlas aunque esten despues del main
void liberar_matriz(int filas, int **matriz);
void imprimir_grafo_punteros(int filas, int columnas, int **grafo);
void imprimir_camino(int *camino, int longitud);
void encontrar_todos_los_caminos_recursivo(int **grafo, int filas, int *visitado, int *camino, int pos, int destino,int longitud);
void encontrar_todos_los_caminos(int **grafo, int filas, int inicio, int destino);
void crear_grafo_aleatorio(int filas, int columnas, int **grafo);

int main() {
    //para crear una semilla aleatoria dependiendo la hora
    srand(time(NULL));
    int seleccion, filas, columnas;
    // dos matrices inicializadas en null
    int **grafo_insertado = NULL;
    int **grafo_aleatoria = NULL;

    while (1) {
        printf("¿Que deseas hacer?\n1.-Crear mi propio Grafo\n2.-Crear un grafo aleatorio\n3.-Imprimir el grafo\n4.-Salir\n");
        scanf("%i", &seleccion);

        switch (seleccion) {
            case 1:
                printf("¿Cuantos vertices deseas que tenga tu grafo?\n");
                scanf("%d", &filas);
                columnas = filas;

                //asignamos memoria dinamicamente a nuestro puntero de punteros del tamaño filas por el tamaño de punteros a enteros
                //el puntero grafo_insertado apunta al puntero filas que apunta a cada columna
                grafo_insertado = malloc(filas * sizeof(int *));
                for (int i = 0; i < filas; i++) {
                    //ahora cada fila le asignamos memoria para que almacene tantos datos enteros como sea indicado
                    grafo_insertado[i] = malloc(columnas * sizeof(int));
                }
                //recorremos toda nuestra matriz
                for (int i = 0; i < filas; i++) {
                    for (int j = 0; j < columnas; j++) {
                        //si i es igual a j es como si dijeramos que vertice 1 apunta a vertice 1 entonces toda la
                        //diagonal la llenamos de 0
                        if (i == j) {
                            grafo_insertado[i][j] = 0;
                            //sino preguntamos si quiere unir el vertice x a el vertice x asignando 1 y 0 respectivamente
                        } else {
                            printf("¿Quieres que el vertice (%d) este conectado con el vertice (%d)?\n1.-Si\n0.-No\n ", i + 1, j + 1);
                            scanf("%d", &grafo_insertado[i][j]);
                        }
                    }
                    printf("\n");
                }
                printf("Vamos a encontrar todos las rutas que podemos tomar para llegar de vertice (1) a vertice (%d) en el siguiente grafo:\n", filas);
                //llamamos a la funcion imprimir
                imprimir_grafo_punteros(filas, columnas, grafo_insertado);
                //llamamos a la funcion encontrar todos los caminos le enviamos de inicio 0 y destino nuestro ultimo vertice
                encontrar_todos_los_caminos(grafo_insertado, filas, 0, filas-1);
                break;
                case 2:
                //si queremos uno aleatorio definimos el numero de vertices
                printf("¿Cuantos vertices deseas que tenga tu grafo?\n");
                scanf("%d", &filas);
                columnas = filas;
                //como no sabemos cuando va a medir la matriz tenemos que usar punteros y asignar memoria dinamica
                grafo_aleatoria = malloc(filas * sizeof(int *));
                for (int i = 0; i < filas; i++) {
                    grafo_aleatoria[i] = malloc(columnas * sizeof(int));
                }
                // llamamos a nuestro algoritmo aleatorio
                crear_grafo_aleatorio(filas, columnas, grafo_aleatoria);
                //esto es lo mismo que en los anteriores
                printf("Vamos a encontrar todos las rutas que podemos tomar para llegar de vertice (1) a vertice (%d) en el siguiente grafo:\n", filas);
                imprimir_grafo_punteros(filas, columnas, grafo_aleatoria);
                encontrar_todos_los_caminos(grafo_aleatoria, filas, 0, filas-1);
                break;
            case 3:
                //todo esto solo sirve para imprimir
                printf("¿Cual grafo deseas imprimir?\n1.-El que creaste\n2.-El aleatorio\n");
                scanf("%d", &seleccion);
                switch (seleccion) {

                    case 1:
                        imprimir_grafo_punteros(filas, columnas, grafo_insertado);
                        break;
                    case 2:
                        imprimir_grafo_punteros(filas, columnas, grafo_aleatoria);
                        break;
                }
                break;
            case 4:
                printf("Saliendo...\n");
                //aqui nos aseguramos que si creamos algun nodo insertado o aleatorio liberemos la memoria asignada
                if (grafo_insertado != NULL) {
                    liberar_matriz(filas, grafo_insertado);
                }
                if (grafo_aleatoria != NULL) {
                    liberar_matriz(filas, grafo_aleatoria);
                }

                return 0;
            default:
                printf("Elige una opcion válida.\n");
                break;
        }
    }
    return 0;
}

void liberar_matriz(int filas, int **matriz) {
    for (int i = 0; i < filas; ++i) {
        //libero cada puntero fila a columna
        free(matriz[i]);
    }
    //libero puntero matriz a fila
    free(matriz);
}

void imprimir_grafo_punteros(int filas, int columnas, int **grafo) {
    //solo imprime
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            printf("%d\t", grafo[i][j]);
        }
        printf("\n");
    }
}

void imprimir_camino(int *camino, int longitud) {
    printf("Camino: ");
    for (int i = 0; i < longitud; ++i) {
        printf("%d ", camino[i] + 1);  // sumo 1 para mostrar el vértice en lugar del índice
    }
    printf("\n");
}

void encontrar_todos_los_caminos_recursivo(int **grafo, int filas, int *visitado, int *camino, int pos, int destino, int longitud) {
    // marcamos como visitado la posición en la que estamos
    visitado[pos] = 1;
    // aquí vamos a ir guardando nuestros pasos
    camino[longitud] = pos; // usamos la variable longitud para saber el índice actual del camino
    // si la posición es igual al destino
    if (pos == destino) {
        // llamamos a nuestra función imprimir_camino
        imprimir_camino(camino, longitud + 1); // longitud + 1 porque los índices van de 0 a longitud
    }
    else {
        for (int i = 0; i < filas; i++) {
            // ahora checamos si el vértice (pos) tiene una conexión con el vértice (i) y si además no lo hemos visitado
            if (grafo[pos][i] == 1 && !visitado[i]) {
                // si se cumple, llamamos recursivamente y avanzamos a i (vértice con el que verificamos si el actual-anterior tenía conexión)
                encontrar_todos_los_caminos_recursivo(grafo, filas, visitado, camino, i, destino, longitud + 1);
            }
        }
    }
    // esto nos asegura que cuando regresemos en la recursión, ese vértice que visitamos pueda ser visitado
    // una segunda vez en un camino diferente
    visitado[pos] = 0;
}




void encontrar_todos_los_caminos(int **grafo, int filas, int inicio, int destino) {
    //necesito saber que ya visite por lo que asigno memoria para tantos enteros como filas haya
    int *visitado = malloc(filas * sizeof(int));
    //tambien necesito saber que camino recorri que tambien sera tan largo como vertices haya
    int *camino = malloc(filas * sizeof(int));

    //visitado es un array que nos indica con 0 o 1 que vertice ya hemos visitado asi que lo iniciamos
    // todo en 0
    for (int i = 0; i < filas; i++) {
        visitado[i] = 0;
    }

    // inicializar el camino igual todo en 0
    for (int i = 0; i < filas; i++) {
        camino[i] = 0;
    }

    //ya que vamos a llamar a la funcion recursiva que a su vez llama a imprimir los caminos
    //dejamos indicado este mensaje
    printf("Todos los caminos de %d a %d:\n", inicio + 1, destino + 1);
    //a nuestra funcion recursiva mandamos nuestro grafo, numero de filas y nuestro camino visitado
    //asi como donde nos encontramos y a donde debemos llegar
    encontrar_todos_los_caminos_recursivo(grafo, filas, visitado, camino, inicio, destino, 0);

    free(visitado);
    free(camino);
}



void crear_grafo_aleatorio(int filas, int columnas, int **grafo) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (i == j) {
                grafo[i][j] = 0;
            } else {
                int num = rand() % 10 + 1;
                if (num <7) {
                    grafo[i][j] = 1;
                } else {
                    grafo[i][j] = 0;
                }
            }
        }
    }
}
