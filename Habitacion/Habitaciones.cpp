#include <iostream>

using namespace std;

struct Habitacion {
    int numero;
    int categoria;
    Habitacion* izq;
    Habitacion* der;
};

Habitacion* raiz = NULL;

bool Exhabitacion(Habitacion* nodo, int numero) {
    if (nodo == NULL) {
        return false;
    } else if (numero == nodo->numero) {
        return true;
    } else if (numero < nodo->numero) {
        return Exhabitacion(nodo->izq, numero);
    } else {
        return Exhabitacion(nodo->der, numero);
    }
}

void Inserhabitacion(Habitacion*& nodo, int numero, int categoria) {
    if (nodo == NULL) {
        nodo = new Habitacion;
        nodo->numero = numero;
        nodo->categoria = categoria;
        nodo->izq = NULL;
        nodo->der = NULL;
    } else {
        if (categoria <= nodo->categoria) {
            Inserhabitacion(nodo->izq, numero, categoria);
        } else {
            Inserhabitacion(nodo->der, numero, categoria);
        }
    }
}

int AsignarC(Habitacion*& nodo, int categoria) {
    if (nodo == NULL) {
        return categoria;  
    } else if (categoria == nodo->categoria) {
        return AsignarC(nodo->izq, categoria - 1);
    } else if (categoria < nodo->categoria) {
        int categoriaAsignada = AsignarC(nodo->izq, categoria);
        if (categoriaAsignada == categoria) {
            nodo->categoria = categoria;  
        }
        return categoriaAsignada;
    } else {
        return AsignarC(nodo->der, categoria);
    }
}

Habitacion* EncontrarC(Habitacion* nodo) {
    if (nodo->izq == NULL) {
        return nodo;
    }
    return EncontrarC(nodo->izq);
}

Habitacion* EliminarH(Habitacion* nodo, int numero) {
    if (nodo == NULL) {
        return nodo;
    }

    if (numero < nodo->numero) {
        nodo->izq = EliminarH(nodo->izq, numero);
    } else if (numero > nodo->numero) {
        nodo->der = EliminarH(nodo->der, numero);
    } else {
        if (nodo->izq == NULL && nodo->der == NULL) {
            delete nodo;
            nodo = NULL;
        } else if (nodo->izq == NULL) {
            Habitacion* temp = nodo;
            nodo = nodo->der;
            delete temp;
        } else if (nodo->der == NULL) {
            Habitacion* temp = nodo;
            nodo = nodo->izq;
            delete temp;
        } else {
            Habitacion* temp = EncontrarC(nodo->der);
            nodo->numero = temp->numero;
            nodo->categoria = temp->categoria;
            nodo->der = EliminarH(nodo->der, temp->numero);
        }
    }
    return nodo;
}

void MostrarCategorias(Habitacion* nodo) {
    if (nodo != NULL) {
        MostrarCategorias(nodo->der); 
        cout << "Habitacion #" << nodo->numero << " - Categoria " << nodo->categoria << endl;
        MostrarCategorias(nodo->izq);
    }
}

int main() {
    int opcion = 0;

    do {
        cout << "1. Registrar Habitacion" << endl;
        cout << "2. Mostrar Habitaciones" << endl;
        cout << "3. Eliminar Habitacion" << endl;
        cout << "4. Salir" << endl;
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                int categoria, numeroHabitacion;
                cout << "Ingrese el numero de habitacion (del 1 al 50): ";
                cin >> numeroHabitacion;

                if (numeroHabitacion >= 1 && numeroHabitacion <= 50) {
                    if (!Exhabitacion(raiz, numeroHabitacion)) {
                        cout << "Ingrese la categoria de la habitacion: ";
                        cin >> categoria;

                        if (categoria >= 1) {
                            categoria = AsignarC(raiz, categoria);

                            if (categoria >= 1) {
                                Inserhabitacion(raiz, numeroHabitacion, categoria);
                                cout << "Habitacion #" << numeroHabitacion << " registrada con exito " << categoria << endl;
                            } else {
                                cout << "La categoria no esta disponible." << endl;
                            }
                        } else {
                            cout << "Categoria no valida." << endl;
                        }
                    } else {
                        cout << "La habitacion #" << numeroHabitacion << " ya esta registrada." << endl;
                    }
                } else {
                    cout << "Numero de habitacion no valido." << endl;
                }
                break;
            case 2:
                if (raiz != NULL) {
                    cout << "Habitaciones del hotel:" << endl;
                    MostrarCategorias(raiz);
                } else {
                    cout << "Habitacion no registrada." << endl;
                }
                break;
            case 3:
                int numeroEliminar;
                cout << "Ingrese el numero de la habitacion que quiere eliminar: ";
                cin >> numeroEliminar;
                raiz = EliminarH(raiz, numeroEliminar);
                cout << "Habitacion #" << numeroEliminar << " eliminada." << endl;
                break;
            case 4:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 4);

    return 0;
}
