#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

//Construir arbol k-ario con claves 
/*se  debe  construir  un   ́arbol   de  busqueda  k + 1-ario,  como  el  de  la  Figura.  Es  decir,  
que  cada  nodo  almacene  hasta  k  claves  (por  ejemplo,  con un pequeño array de largo k) y se almacenen 
hasta k + 1 punteros para ir a los nodos descendientes. La idea 
es la misma que en los BST, donde, por cada nodo, se almacenan k=1 claves y se tienen k + 1  =  2 punteros,
pero ahora generalizado a cualquier k que sea potencia de 2. 
*/
/*Adjunta  a  la  tarea  dispone  de  los  diccionarios  D1.txt  y  D2.txt,  los  cuales  contienen  una  palabra  por 
línea. El diccionario D1 le servira para crear las estructuras desde 0, sin realizar eliminaciones. luego 
utilizar ́a  el diccionario D2 para relizar inserciones y eliminaciones adicionales. La experimentacion pedida 
es la siguiente (desde luego puede agregar más experimentos si estima que es necesario para su analisis y 
presentacion clara de los resultados)
*/

//Estuctura del nodo del arbol k-ario

struct Nodo {
    vector<string> claves;
    vector<Nodo*> hijos;
    bool esHoja;
};

Nodo* crearNodo(bool esHoja);
Nodo* insertar(Nodo* raiz, const string& clave, int k);
Nodo* eliminar(Nodo* raiz, const string& clave, int k);
void liberar(Nodo* raiz);
void experimentoBusqueda(Nodo* raiz, const char* archivoBusqueda);
void experimentoInsercion(Nodo* raiz, const char* archivoInsertar, int k);
void experimentoEliminacion(Nodo* raiz, const char* archivoEliminar, int k);
vector<string> cargarDiccionario(const char* nombreArchivo);

int main(){
    int opcion;
    int k;
    do{
        cout << "\nMenu 3\n";
        cout << "1. Busqueda de 10000 palabras de D2\n";
        cout << "2. Insercion de 5000 palabras de D2\n";
        cout << "3. Eliminacion de 5000 ultimas palabras de D2\n";
        cout << "0. Salir\n";
        cout << "Seleccione opcion: ";
        cin >> opcion;
        if(opcion == 0) break;

        cout << "\nCargando D1.txt...\n";
        vector<string> D1 = cargarDiccionario("D1.txt");
        vector<string> D2 = cargarDiccionario("D2.txt");
        cout << "Cantidad inicial: " << D1.size() << "\n";

        cout << "Ingrese valor de k(8, 32, 128, 512): ";
        cin >> k;
    }
    while(opcion != 0);
    cout << "\nPrograma finalizado con exito";
    return 0;
}

Nodo* crearNodo(bool esHoja){
}

Nodo* insertar(Nodo* raiz, const string& clave, int k){
}

Nodo* eliminar(Nodo* raiz, const string& clave, int k){
}

void liberar(Nodo* raiz){
}

void experimentoBusqueda(Nodo* raiz, const char* archivoBusqueda){
}

void experimentoInsercion(Nodo* raiz, const char* archivoInsertar, int k){
}

void experimentoEliminacion(Nodo* raiz, const char* archivoEliminar, int k){
}

vector<string> cargarDiccionario(const char* nombreArchivo){
}