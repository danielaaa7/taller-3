#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;
//Estuctura del nodo del arbol k-ario
struct NodoK{
    vector<string> claves;
    vector<NodoK*> hijos;
    bool esHoja;

    NodoK(int k, bool hoja = true){
        hijos.resize(k + 1, nullptr);
        esHoja = hoja;
    }
};

void DividirHijos(NodoK *padre, int IndiceHijo, int k);
NodoK* insertar(NodoK* raiz, const string& clave, int k);
void fusionarNodos(NodoK* padre, int indice, int k);
NodoK* eliminar(NodoK* raiz, const string& clave, int k);
bool buscarClave(NodoK* nodo, const string& clave, int k);
void liberar(NodoK* raiz);
vector<string> cargarDiccionario(const char* nombreArchivo);

int main(){
    int opcion, k;
    do{
        cout << "\nMenu 3\n";
        cout << "1. Construcción desde D1.txt\n";
        cout << "2. Búsqueda repetida de palabras\n";
        cout << "3. Eliminación / Inserción intercaladas\n";
        cout << "0. Salir\n";
        cout << "Seleccione opción: ";
        cin >> opcion;
        if (opcion == 0) break;
        // Cargar diccionarios
        vector<string> D1 = cargarDiccionario("D1.txt");
        vector<string> D2 = cargarDiccionario("D2.txt");

        cout << "Ingrese valor de k (8, 32, 128, 512): ";
        cin >> k;
        NodoK* raiz = nullptr;

        // ---------------- Opción 1: Construcción ----------------
        if(opcion == 1){
            clock_t inicio = clock();
            for (const string& palabra : D1) {
                raiz = insertar(raiz, palabra, k);
            }
            clock_t fin = clock();
            double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;
            cout << "Construcción completa en " << tiempo << " segundos.\n";
        }
        // ---------------- Opción 2: Búsqueda ----------------
        else if (opcion == 2){
            // Primero construir el árbol
            for (const string& palabra : D1) {
                raiz = insertar(raiz, palabra, k);
            }
            int REP;
            cout << "Ingrese número de repeticiones de búsqueda: ";
            cin >> REP;
            srand(time(nullptr));
            clock_t inicio = clock();
            for (int i = 0; i < REP; i++) {
                string clave = D1[rand() % D1.size()];
                bool encontrado = buscarClave(raiz, clave, k);
                // Puedes comentar esta línea si no quieres imprimir cada búsqueda
                cout << "Buscando '" << clave << "': "
                     << (encontrado ? "Encontrada" : "No encontrada") << endl;
            }
            clock_t fin = clock();
            double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;
            cout << "Tiempo total de búsqueda: " << tiempo << " segundos.\n";
        }

        // ---------------- Opción 3: Eliminación / Inserción ----------------
        else if (opcion == 3){
            // Primero construir el árbol
            for (const string& palabra : D1) {
                raiz = insertar(raiz, palabra, k);
            }
            cout << "Procesando inserciones y eliminaciones de D2...\n";
            for (size_t i = 0; i < D2.size(); i++) {
                if (i % 2 == 0) {
                    raiz = insertar(raiz, D2[i], k);
                } else {
                    raiz = eliminar(raiz, D2[i], k);
                }
            }
            cout << "Inserciones y eliminaciones completadas.\n";
        }
        liberar(raiz);
    }while(opcion != 0);
    cout << "\nPrograma finalizado con éxito\n";
    return 0;
}

//divide el hijo en la posicion  'indice hijo' del nodo padre
void DividirHijos(NodoK *padre, int indiceHijo, int k){
    NodoK* hijo = padre->hijos[indiceHijo];
    int medio = k / 2;
    // Crear nuevo nodo hermano derecho
    NodoK* nuevo = new NodoK(k, hijo->esHoja);

    // Copiar la mitad derecha de las claves al nuevo nodo
    for (int i = medio + 1; i < hijo->claves.size(); i++) {
        nuevo->claves.push_back(hijo->claves[i]);
    }
    // Si no es hoja, copiar también los hijos derechos
    if (!hijo->esHoja) {
        for (int i = medio + 1; i < hijo->hijos.size(); i++) {
            nuevo->hijos[i - (medio + 1)] = hijo->hijos[i];
        }
    }
    // Reducir el hijo original a la mitad izquierda
    string ClaveMedio = hijo->claves[medio];
    hijo->claves.resize(medio);
    padre->claves.insert(padre->claves.begin() + indiceHijo,
    ClaveMedio);
}

NodoK* insertar(NodoK* raiz, const string& clave, int k){
    //caso base: arbol vacio
    if(!raiz){
        NodoK *nuevo = new NodoK(k, true);
        nuevo->claves.push_back(clave);
        return nuevo;
    }
    //si la raiz esta llena, dividirla
    if(raiz->claves.size() == k){
        NodoK *nuevoPadre = new NodoK(k, false);
        nuevoPadre->hijos[0] = raiz;
        DividirHijos(nuevoPadre, 0, k);
        raiz = nuevoPadre;
    }
    NodoK* nodo = raiz;
    while (!nodo->esHoja) {
        int i = nodo->claves.size() - 1;
        while (i >= 0 && clave < nodo->claves[i]) i--;
        i++; // posición donde debe ir la clave
        // Si el hijo está lleno, dividirlo antes de descender
        if(nodo->hijos[i] && nodo->hijos[i]->claves.size() == k) {
            DividirHijos(nodo, i, k);
            if (clave > nodo->claves[i]) i++;
        }
        if (!nodo->hijos[i]) {
            nodo->hijos[i] = new NodoK(k, true);
        }
        nodo = nodo->hijos[i];
    }
    // Insertar en el nodo hoja en orden
    auto it = lower_bound(nodo->claves.begin(), nodo->claves.end(), clave);
    if (it == nodo->claves.end() || *it != clave) {
        nodo->claves.insert(it, clave);
    }
    return raiz;
}

void fusionarNodos(NodoK* padre, int indice, int k) {
    NodoK* hijoIzq = padre->hijos[indice];
    NodoK* hijoDer = padre->hijos[indice + 1];

    // Bajar la clave del padre al hijo izquierdo
    hijoIzq->claves.push_back(padre->claves[indice]);

    // Copiar las claves del hijo derecho al hijo izquierdo
    for (const string& clave : hijoDer->claves) {
        hijoIzq->claves.push_back(clave);
    }
    // Copiar los hijos del hijo derecho
    if (!hijoDer->esHoja) {
        for (NodoK* subHijo : hijoDer->hijos) {
            hijoIzq->hijos.push_back(subHijo);
        }
    }
    // Eliminar la clave del padre que bajó
    padre->claves.erase(padre->claves.begin() + indice);

    // Eliminar el hijo derecho del padre
    padre->hijos.erase(padre->hijos.begin() + indice + 1);

    // Liberar memoria del hijo derecho
    delete hijoDer;
}

NodoK* eliminar(NodoK* raiz, const string& clave, int k){ 
    if(raiz == nullptr) return nullptr;

    int i = 0;
    //busca la posicion correcta en el nodo
    while(i < raiz->claves.size() && clave > raiz->claves[i]) i++;
    
    //Caso 1: clave encontrada en el nodo
    if(i < raiz->claves.size() && raiz->claves[i] == clave){
        if (raiz->esHoja){
            // Si es hoja, borrar directamente
            raiz->claves.erase(raiz->claves.begin() + i);
        }else{
            // Si es interno, reemplazar con sucesor
            NodoK* sucesor = raiz->hijos[i+1];
            while (sucesor && !sucesor->esHoja) {
                sucesor = sucesor->hijos[0];
            }
            if (sucesor && !sucesor->claves.empty()) {
                raiz->claves[i] = sucesor->claves[0];
                raiz->hijos[i+1] = eliminar(raiz->hijos[i+1], sucesor->claves[0], k);
            }
        }
    }else{
        // Caso 2: la clave no está en este nodo
        if (raiz->esHoja)  return raiz; // No encontrada
        else raiz->hijos[i] = eliminar(raiz->hijos[i], clave, k);
    }
    // Si el hijo tiene menos de ⌈k/2⌉ claves, fusionar
    if(raiz->hijos[i] && raiz->hijos[i]->claves.size() < (k / 2)){
        if (i < raiz->claves.size())
            fusionarNodos(raiz, i, k);
        else
            fusionarNodos(raiz, i - 1, k);
    }
    return raiz;
}

bool buscarClave(NodoK* nodo, const string& clave, int k){
    if(nodo == nullptr) return false;
    int i = 0;
    // Buscar la posición donde debería estar la clave
    while(i <nodo->claves.size() && clave > nodo->claves[i]) i++;

    // Caso 1: la clave está en el nodo actual
    if (i < nodo->claves.size() && nodo->claves[i] == clave) return true;
    
    // Caso 2: si es hoja, no está
    if(nodo->esHoja) return false;

    // Caso 3: descender al hijo correspondiente
    return buscarClave(nodo->hijos[i], clave, k);
}

void liberar(NodoK* raiz){
    //caso base: Arbol vacio
    if (raiz == nullptr) return;
    for (NodoK* hijo : raiz->hijos){
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
