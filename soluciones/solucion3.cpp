#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

//Construir arbol k-ario con claves 
/*se  debe  construir  un   ́arbol   de  busqueda  k + 1-ario,  como  el  de  la  Figura.  Es  decir,  
que  cada  NodoK  almacene  hasta  k  claves  (por  ejemplo,  con un pequeño array de largo k) y se almacenen 
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

/*Considere el parámetro K para la tercera solución, además de un parámetro REP para el número de 
repeticiones de la búsqueda de claves. 
1. Tiempo y espacio para la construcción desde cero. Construya, con el dicionario D1, la tercera 
EDs y calcule el tiempo de construcción y la memoria total utilizada por cada solución. Grafique 
adecuadamente. 
2. Tiempo de busqueda de claves existentes. Tome REP claves aleatorios de D1 y busquelas en la 
estructura. Pruebe con diferentes tamanños para k, k ∈ {8, 32, 128, 512}. 
Obtenga el tiempo promedio de CPU que tarda cada solución en encontrar una clave. 
3. Eliminación e Inserción. Tome el diccionario D2. Recorra desde la primera palabra de D2 hasta 
la última e intercaladamente inserte y elimine la palabra leída desde D2; por tanto habrán |D2|/2 
inserciones y |D2|/2 eliminaciones, estas últimas pueden ser no existosas ya que es posible que la 
palabra que se desea eliminar no exista en las estructuras.
*/

//Estuctura del nodo del arbol k-ario

struct NodoK{
    vector<string> claves;
    vector<NodoK*> hijos;

    NodoK(int k){
        hijos.resize(k + 1, nullptr);
    }
};

NodoK* insertar(NodoK* raiz, const string& clave, int k);
NodoK* eliminar(NodoK* raiz, const string& clave, int k);
bool buscarClave(NodoK* nodo, const string& clave, int k);
void liberar(NodoK* raiz);
vector<string> cargarDiccionario(const char* nombreArchivo);

int main(){
    int opcion;
    int k;
    do{
        cout << "\nMenu 3\n";
        cout << "1. Construccion desde D1.txt\n";
        cout << "2. Busqueda repetidas palabras\n";
        cout << "3. Eliminacion / Insercion de palabras intercaladas\n";
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

        clock_t inicio,fin;
        inicio = clock();
        NodoK *raiz = nullptr;
        for(const string& palabra : D1){
            raiz  = insertar(raiz, palabra, k);
        }
        fin = clock();

    }
    while(opcion != 0);
    cout << "\nPrograma finalizado con exito";
    return 0;
}

NodoK* insertar(NodoK* raiz, const string& clave, int k){
    // Implementar la insercion en el arbol k-ario
    if(!raiz) return crearNodoK({clave}, {}, true);
    
    NodoK* nodo = raiz;
    while(!nodo->esHoja){
        size_t i = 0;

        //Encontrar la posición correcta para descender
        while(i < nodo->claves.size() && clave > nodo->claves[i]) i++;
        
        if(i < nodo->claves.size() && nodo->claves[i] == clave){
            return raiz; // La clave ya existe, no insertar
        }

        //Descender al hijo correspondiente
        if(i < nodo->hijos.size() && nodo->hijos[i]){
            nodo = nodo->hijos[i];
        } else {
            // Si el hijo no existe, crear un nuevo nodo hoja
             if(i < nodo->hijos.size()){
                nodo->hijos[i] = crearNodoK({clave}, {}, true);
            }
            return raiz;
        }

    }
}

NodoK* eliminar(NodoK* raiz, const string& clave, int k){ 
    if(raiz == nullptr)
        return nullptr;
    int i = 0;
    while(i < raiz->claves.size() && raiz->claves[i]){
        i++:
    }
    //Caso 1: clave encontrada en el nodo
    if(i < raiz->claves.size() && raiz->claves[i] == clave){
        //Si es hoja entonces borra directamente
        bool esHoja = true;
        for(int j = 0; j < raiz->hijos.size(); j++){
            if(raiz->hijos[j] != nullptr){ //si existe algun hijo
                esHoja = false;
                break; 
            }
        }
        //Si es hoja se borra la clave
        if(esHoja){
            raiz->claves.erase(raiz->claves.begin() + i);
            return raiz;
        }
        else{
            //Caso 2: el nodo es interno y se debe remplazar con el sucesor
            NodoK* sucesor = raiz->hijos[i+1];
            while(sucesor && sucesor->hijos[0]){
                sucesor = sucesor->hijos[0];
            }
            if(sucesor != nullptr && sucesor->claves.empty() == false){
                raiz->claves[i] = sucesor->claves[0];
                raiz->hijos[i+1] = eliminar(raiz->hijos[i+1], sucesor->claves[0], k);
            }
        }   
    }
    else{
        //Caso 3: la clave no esta en este nodo
        if(i < raiz->hijos.size()){
            raiz->hijos[i] = eliminar(raiz->hijos[i], clave, k);
        } 
    }
    return raiz;
}



bool buscarClave(NodoK* nodo, const string& clave, int k){
    //Diego
}

void liberar(NodoK* raiz){
    //caso base: Arbol vacio
    if (raiz == nullptr)
        return;
    for (NodoK hijo : raiz->hijos){
        liberar(hijo);
    }
    delete raiz; //libera nodo actual
}


vector<string> cargarDiccionario(const char* nombreArchivo){
    vector<string> palabras;
    ifstream archivo(nombreArchivo);
    string palabra;

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return palabras;
    }
    while (getline(archivo, palabra)) {
        palabras.push_back(palabra);
    }
    archivo.close();
    sort(palabras.begin(), palabras.end());

    return palabras;
}
