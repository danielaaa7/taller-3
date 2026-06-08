#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;
struct NodoArregloDinamico{
    char** datos;
    int cantidad;
    int capacidad;
};

int comparar(const char* a, const char* b);
void inicializar(NodoArregloDinamico& arr, int capacidadInicial);
void agregarFinal(NodoArregloDinamico& arr, const char* palabra);
void cargarArchivo(NodoArregloDinamico& arr, const char* nombreArchivo);
int buscar(NodoArregloDinamico& arr, const char* palabra);
void experimentoBusqueda(NodoArregloDinamico& arr, const char* archivoBusqueda);
char* copiarPalabra(const char* palabra);
bool eliminar(NodoArregloDinamico& arr, const char* palabra);
void redimensionar(NodoArregloDinamico& arr);
void insertarOrdenado(NodoArregloDinamico& arr, const char* palabra);
void experimentoInsercion(NodoArregloDinamico& arr, const char* archivoInsertar);
void liberar(NodoArregloDinamico& arr);
void experimentoEliminacion(NodoArregloDinamico& arr, const char* archivoEliminar);

int main() {
    int opcion;
    do {
        cout << "MENU 1" << endl;
        cout << "1. Busqueda de 10000 palabras de D2" << endl;
        cout << "2. Insercion de 5000 palabras de D2" << endl;
        cout << "3. Eliminacion de 5000 ultimas palabras de D2" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione opcion: ";
        cin >> opcion;
        if (opcion >= 1 && opcion <= 3) {
            NodoArregloDinamico diccionario;
            inicializar(diccionario, 1000);

            cout << "\nCargando D1.txt...\n";
            cargarArchivo(diccionario, "D1.txt");
            cout << "Cantidad inicial: " << diccionario.cantidad << endl;
            switch (opcion) {
                case 1:
                    experimentoBusqueda(diccionario, "D2.txt");
                    break;

                case 2:
                    experimentoInsercion(diccionario, "D2.txt");
                    break;

                case 3:
                    experimentoEliminacion(diccionario, "D2.txt");
                    break;
                case 4:
                cout << "Cantidad actual de palabras: "
                     << diccionario.cantidad << endl;
                break;

                case 0:
                    cout << "Finalizando programa..." << endl;
                break;

                 default:
                    cout << "Opcion invalida :(" << endl;
            }
            liberar(diccionario);
        }
        else if (opcion == 0) {
            cout << "\n¡¡¡Programa finalizado con exito!!!" << endl;
        }
        else {
            cout << "\nOpcion invalida. :(\n";
        }
    } while (opcion != 0);
    return 0;
}

int comparar(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') { 
        if (a[i] < b[i]) return -1; 
        if (a[i] > b[i]) return 1; i++;
    }
    if (a[i] == '\0' && b[i] == '\0') return 0; 
    if (a[i] == '\0') return -1; 
    return 1;
}

char* copiarPalabra(const char* palabra) { 
    int largo = 0;
    while (palabra[largo] != '\0') largo++; 
    char* nueva = new char[largo + 1]; 
    for (int i = 0; i <= largo; i++) 
        nueva[i] = palabra[i]; 
    return nueva; 
}

void inicializar(NodoArregloDinamico& arr, int capacidadInicial) {
    // asignar capacidad inicial y reservar memoria para el arreglo de punteros
    arr.capacidad = capacidadInicial;
    arr.cantidad = 0;
    arr.datos = new char*[capacidadInicial];
}

void redimensionar(NodoArregloDinamico& arr) {
    //Duplica el tamaño del arreglo cuando se llena.
    int nuevaCapacidad = arr.capacidad * 2; 
    // Crear nuevo arreglo de punteros con la nueva capacidad
    char** nuevo = new char*[nuevaCapacidad]; 
    // Copiar los punteros del arreglo antiguo al nuevo
    for (int i = 0; i < arr.cantidad; i++) 
        nuevo[i] = arr.datos[i];
    delete[] arr.datos; 
    arr.datos = nuevo; 
    arr.capacidad = nuevaCapacidad; 
}

void agregarFinal(NodoArregloDinamico& arr, const char* palabra) { 
    if (arr.cantidad == arr.capacidad)
        redimensionar(arr);
    arr.datos[arr.cantidad] = copiarPalabra(palabra);
    arr.cantidad++;
}

void cargarArchivo(NodoArregloDinamico& arr, const char* nombreArchivo) { 
    ifstream archivo(nombreArchivo); 
    if (!archivo.is_open()){
        cout << "Error al abrir archivo: " << nombreArchivo << endl;
        return;
    }
    char palabra[100];
    while (archivo.getline(palabra, 100)) {
        agregarFinal(arr, palabra);
    }
    archivo.close();
}

int buscar(NodoArregloDinamico& arr, const char* palabra) {
    //T(n)=O(logn), Búsqueda binaria en el arreglo ordenado de punteros a palabras 
    int izq = 0;
    int der = arr.cantidad - 1;
    while (izq <= der) {
        int medio = (izq + der) / 2; 
        int cmp = comparar(arr.datos[medio], palabra);

        if (cmp == 0) return medio;
        else if (cmp < 0)
            izq = medio + 1;
        else
            der = medio - 1;
    }
    return -1;
}

bool eliminar(NodoArregloDinamico& arr, const char* palabra) {
    //T(n)=O(n) porque desplaza, Elimina una palabra del arreglo dinámico si existe, 
    int pos = buscar(arr, palabra); 
    if (pos == -1)
        return false;
    delete[] arr.datos[pos]; 
    for (int i = pos; i < arr.cantidad - 1; i++) {
        // Desplazar las palabras a la izquierda para llenar el espacio vacío
        arr.datos[i] = arr.datos[i + 1];
    }
    arr.cantidad--; 
    return true;
}

void experimentoEliminacion(NodoArregloDinamico& arr, const char* archivoNombre) {
    ifstream archivo(archivoNombre);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir archivo: " << archivoNombre << endl;
        return;
    }
    char* ultimas[5000]; 
    int contador = 0;
    char palabra[100];

    while (archivo.getline(palabra, 100)) {
        //Guardar las últimas 5000 palabras leídas para luego eliminarlas
        if (contador < 5000) { 
            ultimas[contador] = copiarPalabra(palabra);
        }else{
            delete[] ultimas[contador % 5000];
            ultimas[contador % 5000] = copiarPalabra(palabra);
        }

        contador++;
    }
    archivo.close();
    clock_t inicio = clock();
    for (int i = 0; i < 5000; i++) {
        eliminar(arr, ultimas[i]);
    }
    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    // Calcular el tiempo total en segundos
    cout << "\nEXPERIMENTO ELIMINACION:\n";
    cout << "Palabras eliminadas: 5000\n";
    cout << "Cantidad final exitosa: " << arr.cantidad << endl;  
    cout << "Tiempo total: " << tiempo << " segundos\n";
    cout << "Tiempo promedio: " << tiempo / 5000 << " segundos\n";

    for (int i = 0; i < 5000; i++) {
        delete[] ultimas[i];
    }
}

void liberar(NodoArregloDinamico& arr) {
    for (int i = 0; i < arr.cantidad; i++) {
        delete[] arr.datos[i];
    }
    delete[] arr.datos;
}

void experimentoBusqueda(NodoArregloDinamico& arr, const char* archivoBusqueda) {
    ifstream archivo(archivoBusqueda);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir archivo\n";
        return;
    }

    char palabra[100];
    int contadorEncontrados = 0;
    int totalBuscadas = 0;
    clock_t inicio = clock();

    while (archivo.getline(palabra, 100) && totalBuscadas < 10000) {
        if (buscar(arr, palabra) != -1) {
            contadorEncontrados++;
        }
        totalBuscadas++;
    }
    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    cout << "\nEXPERIMENTO BUSQUEDA: \n";
    cout << "Palabras buscadas: " << totalBuscadas << endl;
    cout << "Palabras encontradas: " << contadorEncontrados << endl;
    cout << "Tiempo total: " << tiempo << " segundos\n";
    cout << "Tiempo promedio: " << tiempo / totalBuscadas << " segundos\n";

    archivo.close();
}

void insertarOrdenado(NodoArregloDinamico& arr, const char* palabra) {
    //Complejidad T(n)=O(n) porque desplaza.
    if (arr.cantidad == arr.capacidad)
        redimensionar(arr); 

    int pos = 0;
    while (pos < arr.cantidad && comparar(arr.datos[pos], palabra) < 0) {
        pos++;
    }
    for (int i = arr.cantidad; i > pos; i--) {
        arr.datos[i] = arr.datos[i - 1];
    }
    arr.datos[pos] = copiarPalabra(palabra);
    arr.cantidad++;
}

void experimentoInsercion(NodoArregloDinamico& arr, const char* archivoInsertar) {
    ifstream archivo(archivoInsertar);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir archivo" << endl;
        return;
    }

    char palabra[100];
    int contadorInsertados = 0;
    clock_t inicio = clock();

    while (archivo.getline(palabra, 100) && contadorInsertados < 5000) {
        insertarOrdenado(arr, palabra);
        contadorInsertados++;
    }

    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    cout << "\nEXPERIMENTO INSERCION:\n";
    cout << "Palabras insertadas: " << contadorInsertados << endl;
    cout << "Cantidad final: " << arr.cantidad << endl;
    cout << "Tiempo total: " << tiempo << " segundos\n";
    cout << "Tiempo promedio: " << tiempo / contadorInsertados << " segundos\n";

    archivo.close();
}
