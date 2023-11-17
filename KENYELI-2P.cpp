#include <iostream>
#include <string>

using namespace std;

struct Vuelo {
  string codigo; 
  double combustible; 
  double distancia; 
  double prioridad; 
  Vuelo* izq; 
  Vuelo* der; 
};


Vuelo* crearVuelo(string codigo, double combustible, double distancia) {
  Vuelo* nuevo = new Vuelo; 
  nuevo->codigo = codigo; 
  nuevo->combustible = combustible; 
  nuevo->distancia = distancia; 
  nuevo->prioridad = 0; 
  nuevo->izq = NULL; 
  nuevo->der = NULL; 
  return nuevo; 
}

void calcularPrioridad(Vuelo* vuelo) {
  
  double rendimiento = 0.5;
  double consumido = vuelo->distancia / rendimiento;
  double restante = vuelo->combustible - consumido;
  vuelo->prioridad = restante;
}

void insertarVuelo(Vuelo* &raiz, Vuelo* vuelo) {

  if (raiz == NULL) {
    raiz = vuelo;
  }
  else {
    
    if (vuelo->prioridad < raiz->prioridad) {
      insertarVuelo(raiz->izq, vuelo);
    }
    else {
      insertarVuelo(raiz->der, vuelo);
    }
  }
}

void mostrarVuelos(Vuelo* raiz) {
  
  if (raiz != NULL) {
    mostrarVuelos(raiz->izq); 
    cout << "Codigo: " << raiz->codigo << endl; 
    cout << "Combustible: " << raiz->combustible << " galones" << endl; 
    cout << "Distancia: " << raiz->distancia << " millas nauticas" << endl; 
    cout << "Prioridad: " << raiz->prioridad << " galones restantes" << endl; 
    cout << "--------------------------" << endl; 
    mostrarVuelos(raiz->der); 
  }
}

void eliminarVuelo(Vuelo* &raiz) {
  
  if (raiz->izq == NULL) {
    Vuelo* aux = raiz; 
    raiz = raiz->der; 
    delete aux; 
  }
  else {
    eliminarVuelo(raiz->izq); 
  }
}

void liberarArbol(Vuelo* &raiz) {

  if (raiz != NULL) {
    liberarArbol(raiz->izq); 
    liberarArbol(raiz->der); 
    delete raiz; 
    raiz = NULL;
  }
}

int main() {
  
  Vuelo* raiz = NULL;

  Vuelo* v1 = crearVuelo("AA123", 100, 500); 
  Vuelo* v2 = crearVuelo("BB456", 150, 600); 
  Vuelo* v3 = crearVuelo("CC789", 120, 400); 
  Vuelo* v4 = crearVuelo("DD101", 80, 300); 
  
  calcularPrioridad(v1);
  calcularPrioridad(v2);
  calcularPrioridad(v3);
  calcularPrioridad(v4);
  
  insertarVuelo(raiz, v1);
  insertarVuelo(raiz, v2);
  insertarVuelo(raiz, v3);
  insertarVuelo(raiz, v4);
  
  cout << "Los vuelos por su prioridad son:" << endl;
  mostrarVuelos(raiz);
  cout << "Se elimina el vuelo con menor prioridad:" << endl;
  eliminarVuelo(raiz);
  cout << "Los vuelos por su prioridad son:" << endl;
  mostrarVuelos(raiz);

  liberarArbol(raiz);
  return 0;
}
