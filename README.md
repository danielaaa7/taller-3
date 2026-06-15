# PROYECTO TALLER 3: ESTRUCTURAS DE DATOS Y ALGORITMOS

    Este proyecto tiene como objetivo analizar y comparar el rendimiento de diferentes 
    estructuras de datos aplicadas a la gestión de un diccionario de palabras:

   -En la solución 1: basada en un 'arreglo dinámico ordenado de palabras', donde cada palabra es
    almacenada como una cadena de caracteres (char*) y se mantiene ordenada lexicográficamente.
    Se realizaron experimentos de búsqueda (10000 palabras), inserción (5000 palabras) y eliminación
    (5000 palabras), midiendo tiempos totales y promedios.

   -En la solución 2:  se desarrolló una grilla multinivel de listas enlazadas, que mejora la eficiencia
    de las operaciones al permitir saltos entre niveles. Con esta estructura se realizaron experimento
    de búsqueda (10000 palabras), inserción (5000 palabras) y eliminación (5000 palabras), midiendo
    tiempos totales y promedios.
    
    -En la solución 3: Basado en un árbol k-ario, que mejora mas la eficiencia de las operaciones. Permite 
     que cada nodo almacene múltiples claves ordenadas y disponga de hasta k+1 hijos. Esto reduce la altura del árbol.
     
    Objetivo general:
    Evaluar cómo cambia el rendimiento al pasar de una solución básica a una optimizada, relacionando los 
    resultados experimentales con el análisis teórico en notación O. De esta forma, se busca comprender mejor 
    la importancia de elegir estructuras de datos adecuadas para trabajar con grandes volúmenes de información.

## Solución 1: Arreglo Dinámico Ordenado

Descripción:
    El programa carga un diccionario inicial desde el archivo D1.txt y realiza experimentos de busqueda,
    inserción y eliminación hecho en un arreglo dinamico utilizando palabras provenientes del archivo
    D2.txt. Donde se miden los tiempos de cada uno con su respectivo promedio.

Componentes de la estructura:
    datos → arreglo de punteros a palabras.
    cantidad → número actual de palabras almacenadas.
    capacidad → tamaño reservado del arreglo.

Archivos necesarios:
    -solucion1.cpp -> código fuente principal.
    -D1.txt -> diccionario base.
    -D2.txt -> conjunto de palabras para pruebas.

Como compilar y ejecutar:
    g++ -Wall -std=c++17 -o solucion1 solucion1.cpp
    ./solucion1

Funcionamiento del programa:
    1.- Carga los archivos D1.txt y D2.txt
    2.- Muestra un "menu" con 4 opciones:
        1- búsqueda: Buscar las 100000 palabras de D2.txt
        2- inserción: Inserta 5000 palabras
        3- eliminación: Elimina las ultimas 5000 palabras
        4- Salir del programa
    3.- Libera la memoria.
    En cada opción muestra el tiempo que se demoro y el tiempo promedio.

Estructura del código:
    -comparar(): Sirve para comparar dos palabras alfabéticamente.
    -inicializar(): Prepara la estructura antes de usarla.
    -agregarFinal(): Agrega una palabra al final del arreglo dinámico, redimensionando si es necesario.
    -cargarArchivo(): Lee todas las palabras desde D1.txt.
    -Buscar(): Busca una palabra usando búsqueda binaria.
    -experimentoBusqueda(): Ejecuta la prueba de busqueda comparando rendimientos de tiempo.
    -copiarPalabra(): Crea un copia dinamica de una palabra.
    -eliminar(): Borra una palabra.
    -redimensionar(): Duplica el tamaño del arreglo cuando se llena.
    -insertarOrdenado(): Inserta una nueva palabra manteniendo orden.
    -experimentoInsercion(): Lee las 5000 palabras de D2 las inserta y mide el tiempo.
    -liberar(): Limpia toda la memoria dinámica.
    -experimentoEliminacion(): Lee las últimas 5000 palabras de D2 las elimina y mide el tiempo.

Analisis de complejidad (notacion O):
    -Búsqueda: O(log n)
    -inserción: O(n)
    -eliminación: O(n)

## Solucion 2: Grilla multinivel de listas enlazadas

Descripción:
    Este programa implementa una estructura de datos basada en listas enlazadas multinivel.
    Permite realizar operaciones de búsqueda, inserción y eliminación sobre un diccionario de
    palabras (D1.txt y D2.txt), midiendo los tiempos de ejecución para analizar el rendimiento según distintos valores de k.

archivos necesarios:
    -solucion2.cpp -> código fuente principal.
    -D1.txt -> diccionario base.
    -D2.txt -> conjunto de palabras para pruebas.

Como compilar y ejecutar:
    g++ -Wall -std=c++17 -o solucion2 solucion2.cpp
    ./solucion2

Funcionamiento del programa:
    1.- Carga los archivos D1.txt y D2.txt.
    2.- Construye una grilla multinivel con salto k.
    3.- Muestra un menú con 3 opciones:
        -1: Buscar 10000 palabras de D2.
        -2: Insertar 5000 palabras de D2.
        -3: Eliminar 5000 últimas palabras de D2.
        -0: Salir.
    4.- Calcula y muestra:
        -Cantidad inicial y final de palabras.
        -Tiempo total y promedio por palabras.

Estructura del código:
    -struct Node: define cada nodo con su clave y punteros sig y abajo.
    -construirLista (): crea una lista enlazada simple.
    -construirMuestra (): genera un nivel superior tomando cada k-enésimo nodo.
    -construirGrilla (): arma la grilla para encontrar una palabra.
    -insertarClave () y eliminarClave (): modifica la lista base y reconstruyen niveles.
    -cargarDiccionario (): lee y ordena las palabras desde archivo.
    -enlazar Niveles (): conecta nodos entre niveles.

Análisis de complejidad (notación O):
    -Construcción: O(n)
    -Búsqueda: O(m*log_k(n))
    -Inserción: O(n)
    -Eliminación: O(n)

## Solución 3: Arbol k_ario
Descripcion:
    implementa un árbol k-ario de búsqueda para almacenar y gestionar las palabras contenidas en los diccionarios D1.txt
    y D2.txt. El objetivo principal es evaluar el comportamiento de una estructura jerárquica capaz de almacenar grandes 
    cantidades de palabras y analizar experimentalmente el costo de las operaciones de búsqueda, inserción y eliminación
    para distintos valores de k.

Archivos necesarios:
    -solucion3.cpp -> código fuente principal.
    -D1.txt -> diccionario base.
    -D2.txt -> conjunto de palabras para pruebas.

Como compilar y ejecutar:
    g++ -Wall -std=c++17 -O2 -o solucion3.cpp solucion3
    ./solucion3

Funcionamiento del programa:
    1.- Se cargan las palabras contenidas en D1.txt y D2.txt.
    2.- Seleccionar un valor para k.
    3.- Se construye un árbol k-ario utilizando todas las palabras de D1.
    4.- Se ejecuta el experimento correspondiente.
    5.- Se mide el tiempo de ejecución.
    6.- Se muestran estadísticas del experimento.
    7.- Se libera toda la memoria utilizada por la estructura.

Estructura del código:
    -posicion(): Determina la posición donde debería encontrarse una palabra dentro de un nodo.
    -buscarClave(): Busca una palabra dentro del árbol k-ario. Compara la palabra con las claves del nodo actual y, si no la  
    encuentra, continúa la búsqueda en el hijo correspondiente hasta encontrarla o llegar a un nodo nulo.
    -insertarEnNodo(): Inserta una palabra dentro de un nodo manteniendo el orden lexicográfico de las claves almacenadas.
    -insertarClave(): Inserta una nueva palabra en el árbol. Si el nodo actual tiene espacio disponible, la almacena allí; de lo contrario, continúa descendiendo 
    hacia el hijo correspondiente hasta encontrar una ubicación adecuada.
    -eliminarClave(): Busca una palabra dentro del árbol y la elimina cuando es encontrada. Si la palabra no se encuentra en el
    nodo actual, continúa la búsqueda en el subárbol correspondiente.
    -liberarArbol(): Libera toda la memoria dinámica utilizada por la estructura, recorriendo el árbol desde las hojas hasta la raíz. 
    -contarNodos(): Recorre recursivamente todo el árbol y contabiliza la cantidad total de nodos existentes
    -memoriaArbol(): Calcula una estimación de la memoria utilizada por el árbol considerando la memoria ocupada por los nodos, las claves almacenadas y los 
    punteros a hijos.
    -cargardiccionario(): Lee todas las palabras desde un archivo de texto y las almacena en un vector ordenado.

Análisis de complejidad (notación O):
    -Busqueda:
    -Inserción:
    -Eliminación:
    Descripcion:
