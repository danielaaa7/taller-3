#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;

//estructura del nodo
struct Node{
    string clave;
    Node* sig;
    Node* abajo;
    Node(string c) : clave(c), sig(nullptr), abajo(nullptr) {}
};

Node* construirLista(const vector<string>& claves); //lista enlazada simple
Node* construirMuestra(Node* nivelInferior, int k); //muestra cada k-enesimo nodo
vector<Node*> construirGrilla(const vector<string>& claves, int k); //grilla multinivel
Node* buscarClave(vector<Node*>& niveles, const string& clave);
void insertarClave(vector<Node*>& niveles, const string& clave, int k);
void eliminarClave(vector<Node*>& niveles,const string& clave, int k);
void liberarLista(Node* head);
int contarNodos(Node* head);
vector<string> cargarDiccionario(const string& nombreArchivo);
void enlazarNiveles(Node* superior, Node* inferior);

int main(){
    int opcion;
    int k;
    do{
        cout << "\nMENU \n";
        cout << "1. Busqueda de 10000 palabras de D2\n";
        cout << "2. Insercion de 5000 palabras de D2\n";
        cout << "3. Eliminacion de 5000 ultimas palabras de D2\n";
        cout << "0. Salir\n";
        cout << "Seleccione opcion: ";
        cin >> opcion;

        if(opcion == 0)
            break;
        
        cout << "\nCargando D1.txt...\n";
        vector<string> D1 = cargarDiccionario("D1.txt");
        vector<string> D2 = cargarDiccionario("D2.txt");
        cout << "Cantidad inicial: " << D1.size() << "\n";

        cout << "Ingrese valor de k(8, 32, 128, 512): ";
        cin >> k;

        clock_t inicio,fin;
        inicio = clock();
        vector<Node*> grilla = construirGrilla(D1, k);
        fin = clock();

        switch (opcion)
        {
        case 1:{ //busqueda
            cout << "\nEXPERIMENTO BUSQUEDA:\n";
            int n = min(10000, ( int)D2.size());
            int encontrados = 0;
            inicio = clock();
            for(int i = 0; i < n; i++){
                Node* resultado = buscarClave(grilla,D2[i]);
                if(resultado)
                    encontrados ++;
            }
            fin = clock();
            double tiempoTotal = double(fin - inicio) / CLOCKS_PER_SEC;
            double tiempoPromedio = tiempoTotal / n;
            cout << "Palabras buscadas: " << n << "\n";
            cout << "Palabras encontradas: " << encontrados << "\n";
            cout << "Tiempo total: " << tiempoTotal << " segundos\n";
            cout << "Tiempo promedio: " << tiempoPromedio << " segundos\n";
            break;
        }
        case 2:{ //insercion
            cout << "\nEXPERIMENTO INSERCION: \n";
            int n = min(5000, ( int)D2.size());
            inicio = clock();
            for(int i = 0; i < n; i++){
                insertarClave(grilla, D2[i], k);
            }
            fin = clock();
            double tiempoTotal = double(fin - inicio) / CLOCKS_PER_SEC;
            double tiempoPromedio = tiempoTotal / n;
            cout << "Palabras insertadas: " << n << "\n";
            cout << "Cantidad final: " << D1.size() + n << "\n";
            cout << "Tiempo total: " << tiempoTotal << " segundos\n";
            cout << "Tiempo promedio: " << tiempoPromedio << " segundos\n";
            break;
        }
        case 3:{ //eliminacion
            cout << "\nEXPERIMENTO ELIMINACION: \n";
            int n = min(5000, ( int)D2.size());
            inicio = clock();
            for(int i = 0; i < n; i++){
                eliminarClave(grilla, D2[D2.size() -1 -i], k);
            }
            fin = clock();
            double tiempoTotal = double(fin - inicio) / CLOCKS_PER_SEC;
            double tiempoPromedio = tiempoTotal / n;
            cout << "Palabras eliminadas: " << n << "\n";
            cout << "Cantidad final exitosa: " << D1.size() - n << "\n";
            cout << "Tiempo total: " << tiempoTotal << " segundos\n";
            cout << "Tiempo promedio: " << tiempoPromedio << " segundos\n";
            break;
        }    
        default:
            cout << "Opcion invalida.\n";  
        }
    }
    while (opcion != 0);

    cout << "\nPrograma finalizado con exito\n";
    return 0;
}

Node* construirLista(const vector<string>& claves){
    if(claves.empty())
        return nullptr;
    Node* head = new Node(claves[0]);
    Node* actual = head;
    for(size_t i = 1; i < claves.size(); i++){
        actual->sig = new Node(claves[i]);
        actual = actual->sig;
    }
    return head;
}
Node* construirMuestra(Node* nivelInferior, int k){
    if(!nivelInferior)
        return nullptr;
    vector<string> muestras;
    Node* actual = nivelInferior;
    int contador = 0;
    while(actual){
        if (contador % k == 0)
            muestras.push_back(actual->clave);
        actual = actual->sig;
        contador++;
    }
    return construirLista(muestras);
}
vector<Node*> construirGrilla(const vector<string>& claves, int k){
    vector<Node*> niveles;
    Node* L1 = construirLista(claves);
    niveles.push_back(L1);

    Node* anterior = L1;
    while(true){
        Node* nuevoNivel = construirMuestra(anterior,k);
        if(!nuevoNivel)
            break;
        niveles.push_back(nuevoNivel);

        //enlazar punteros abajo
        enlazarNiveles(nuevoNivel, anterior);

        anterior = nuevoNivel;

        int cuenta = 0;
        Node* temp = nuevoNivel;
        while(temp){
            cuenta++;
            temp = temp->sig;
        }
        if(cuenta <= k)
            break;
    }
    return niveles;
}
Node* buscarClave(vector<Node*>& niveles, const string& clave){
    if(niveles.empty())
        return nullptr;
    Node* nodo = niveles.back();
    while(nodo){
        // avanzar horizontalmente
        while(nodo->sig && nodo->sig->clave <= clave){
            nodo = nodo->sig;
        }
        // encontrado
        if(nodo->clave == clave){
            return nodo;
        }
        // bajar nivel
        nodo = nodo->abajo;
    }
    return nullptr;
}
void insertarClave(vector<Node*>& niveles, const string& clave, int k){
    if(niveles.empty())
        return;
    Node* head = niveles[0];
    Node* nuevo = new Node(clave);
    //caso: insertar al inicio
    if(clave < head->clave){
        nuevo->sig = head;
        niveles[0] = nuevo;
    }
    else{
        Node* actual = head;
        while(actual->sig && actual->sig->clave < clave){
            actual = actual->sig;
        }
        nuevo->sig = actual->sig;
        actual->sig = nuevo;
    }
    for(size_t nivel = 1; nivel < niveles.size(); ++nivel){
    liberarLista(niveles[nivel]);
    niveles[nivel] = construirMuestra(niveles[nivel - 1], k);
    enlazarNiveles(niveles[nivel], niveles[nivel - 1]);
    } 
}
void eliminarClave(vector<Node*>& niveles,const string& clave, int k){
    if(niveles.empty())
        return;
    Node* head = niveles[0];
    if(!head)
        return;
    //caso: eliminar al inicio
    if(head->clave == clave){
        niveles[0] = head->sig;
        delete head;
        return;
    }
    Node* actual = head;
    while(actual->sig && actual->sig->clave != clave){
        actual = actual->sig;    
    }
    if(actual->sig){
        Node* temp = actual->sig;
        actual->sig = temp->sig;
        delete temp;
    }
    for(size_t nivel = 1; nivel < niveles.size(); ++nivel){
    liberarLista(niveles[nivel]);
    // reconstruir
    niveles[nivel] = construirMuestra(niveles[nivel - 1], k);
    // volver a enlazar
    enlazarNiveles(niveles[nivel], niveles[nivel - 1]);
    }
}
int contarNodos(Node* head){
    int c = 0;
    while(head)
        c++; head = head->sig;
    return c;
}

void liberarLista(Node* head){
    while(head){
        Node* temp = head;
        head = head->sig;
        delete temp;
    }
}

vector<string> cargarDiccionario(const string& nombreArchivo){
    vector<string> palabras;
    ifstream archivo(nombreArchivo);
    string palabra;

    if(!archivo.is_open()){
        cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << endl;
        return palabras;
    }
    while(archivo >> palabra){
        palabras.push_back(palabra);
    }
    archivo.close();
    sort(palabras.begin(), palabras.end());
    return palabras;
}

void enlazarNiveles(Node* superior, Node* inferior){
    Node* sup = superior;
    Node* inf = inferior;
    while(sup && inf){
        while(inf && inf->clave < sup->clave){
            inf = inf->sig;
        }
        if(inf && inf->clave == sup->clave){
            sup->abajo = inf;
        }
        sup = sup->sig;
    }
}