#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

struct NodoK{
    vector<string> claves;
    vector<NodoK*> hijos;

    NodoK(int k) {
        hijos.resize(k + 1, nullptr);
    }
};

int posicion(NodoK* nodo, const string& clave);
bool buscarClave(NodoK* nodo, const string& clave);
void insertarEnNodo(NodoK* nodo, const string& clave);
void insertarClave(NodoK* nodo,const string& clave,int k);
bool eliminarClave(NodoK* nodo, const string& clave);
void liberarArbol(NodoK* nodo);
int contarNodos(NodoK* nodo);
long long memoriaArbol( NodoK* nodo, int k);
vector<string> cargarDiccionario(const string& archivo);


int main() {
    int opcion;
    do {
        cout << "\nMENU\n";
        cout << "1. Busqueda de 10000 palabras de D2\n";
        cout << "2. Insercion de 5000 palabras de D2\n";
        cout << "3. Eliminacion de 5000 ultimas palabras de D2\n";
        cout << "0. Salir\n";
        cout << "Seleccione opcion: ";

        cin >> opcion;
        if(opcion == 0) break;

        cout << "\nCargando D1.txt...\n";

        vector<string> D1 =cargarDiccionario("D1.txt");
        vector<string> D2 =cargarDiccionario("D2.txt");

        cout << "Cantidad inicial: " << D1.size()<< endl;
        int k;
        cout << "Ingrese k (8,32,128,512): ";
        cin >> k;
        NodoK* raiz = new NodoK(k);
        clock_t inicio = clock();

        for(size_t i=0; i<D1.size();i++) {
            insertarClave(raiz,D1[i],k);
        }
        clock_t fin =
            clock();
        double tiempoConstruccion = double(fin-inicio) / CLOCKS_PER_SEC;

        cout << "Tiempo construccion: "
             << tiempoConstruccion
             << " segundos\n";

        switch(opcion){
        case 1:
        {
            int encontrados = 0;
            int n = min(10000,(int)D2.size());
            inicio = clock();
            for(int i=0;i<n;i++) {
                if(buscarClave(raiz,D2[i])) encontrados++;
            }
            fin = clock();
            double total = double(fin-inicio) / CLOCKS_PER_SEC;

            cout << "\nEXPERIMENTO BUSQUEDA\n";
            cout << "Busquedas: " << n << endl;
            cout << "Encontradas: " << encontrados << endl;
            cout << "Tiempo total: " << total << endl;
            cout << "Tiempo promedio: "<< total/n << endl;
            break;
        }
        case 2: {
            int n = min(5000, (int)D2.size());
            inicio = clock();
            for(int i=0; i<n;i++) {
                insertarClave(raiz, D2[i], k);
            }
            fin = clock();
            double total = double(fin-inicio) / CLOCKS_PER_SEC;
            cout << "\nEXPERIMENTO INSERCION\n";
            cout << "Insertadas: " << n << endl;
            cout << "Tiempo total: " << total << endl;
            cout << "Tiempo promedio: " << total/n << endl;
            break;
        }
        case 3: {
            int n = min( 5000, (int)D2.size());
            inicio = clock();
            for(int i=0;i<n; i++){
                eliminarClave(raiz, D2[D2.size()-1-i]);
            }
            fin = clock();
            double total = double(fin-inicio) / CLOCKS_PER_SEC;
            cout << "\nEXPERIMENTO ELIMINACION\n";
            cout << "Eliminadas: " << n << endl;
            cout << "Tiempo total: " << total << endl;
            cout << "Tiempo promedio: " << total/n << endl;
            break;
        }
        default:
            cout << "Opcion invalida\n";
        }
        cout << "\nNodos del arbol: " << contarNodos(raiz) << endl;
        cout << "Memoria aproximada: " << memoriaArbol(raiz, k) / 1024.0 << " KB\n";

        liberarArbol(raiz);
    }while(opcion != 0);
    cout << "\nPrograma finalizado con exito\n";
    return 0;
}

int posicion(NodoK* nodo, const string& clave) {

    int i = 0;

    while(i < (int)nodo->claves.size() &&
          clave > nodo->claves[i]) {
        i++;
    }
    return i;
}

bool buscarClave(NodoK* nodo, const string& clave) {
    if(nodo == nullptr) return false;
    int pos = posicion(nodo, clave);

    if(pos < (int)nodo->claves.size() && nodo->claves[pos] == clave){
        return true;
    }
    return buscarClave(nodo->hijos[pos],clave);
}

void insertarEnNodo(NodoK* nodo, const string& clave){
    nodo->claves.push_back(clave);
    int i = nodo->claves.size() - 1;
    while(i > 0 && nodo->claves[i] < nodo->claves[i-1]) {
        swap(nodo->claves[i],nodo->claves[i-1] );
        i--;
    }
}

void insertarClave(NodoK* nodo,const string& clave,int k){
    int pos = posicion(nodo, clave);
    if(pos < (int)nodo->claves.size() && nodo->claves[pos] == clave) return;
    
    if((int)nodo->claves.size() < k){
        insertarEnNodo(nodo,clave);
        return;
    }
    if(nodo->hijos[pos] == nullptr) {
        nodo->hijos[pos] = new NodoK(k);
    }
    insertarClave(nodo->hijos[pos], clave, k);
}

bool eliminarClave(NodoK* nodo, const string& clave) {
    if(nodo == nullptr) return false;

    int pos = posicion(nodo, clave);
    if(pos < (int)nodo->claves.size() &&
       nodo->claves[pos] == clave) {
        nodo->claves.erase(nodo->claves.begin() + pos);
        return true;
    }
    return eliminarClave(
        nodo->hijos[pos],
        clave
    );
}

void liberarArbol(NodoK* nodo){
    if(nodo == nullptr) return;
    for(size_t i=0; i<nodo->hijos.size(); i++){
        liberarArbol(nodo->hijos[i]);
    }
    delete nodo;
}

int contarNodos(NodoK* nodo){
    if(nodo == nullptr) return 0;
    int total = 1;
    for(size_t i=0; i<nodo->hijos.size(); i++){
        total += contarNodos(nodo->hijos[i]);
    }
    return total;
}

// MEMORIA APROXIMADA
long long memoriaArbol( NodoK* nodo, int k) {
    if(nodo == nullptr) return 0;
    long long memoria = sizeof(NodoK);
    memoria += nodo->claves.capacity() * sizeof(string);
    memoria += nodo->hijos.capacity() * sizeof(NodoK*);
    for(size_t i=0; i<nodo->hijos.size(); i++){
        memoria += memoriaArbol(nodo->hijos[i],k);
    }
    return memoria;
}

vector<string> cargarDiccionario(const string& archivo){
    vector<string> palabras;
    ifstream in(archivo);
    string palabra;

    if(!in.is_open()){
        cerr << "Error al abrir " << archivo << endl;
        return palabras;
    }
    while(in >> palabra){ 
        palabras.push_back(palabra);
    }
    in.close();
    sort(palabras.begin(),palabras.end());
    return palabras;
}

