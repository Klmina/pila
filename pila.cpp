#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct nodo
{
    char val[40]; // Almacenar número de teléfono
    char nombre[40]; // Almacenar el nombre del contacto
    nodo* sig;
};

nodo* cab = NULL;
void push()
{
    system("cls");
    char telefono[40];

    cout << "Ingrese el numero de telefono: ";
    cin >> telefono;

    // Buscar si el número ya existe en la pila
    for (nodo* aux = cab; aux != NULL; aux = aux->sig)
    {
        if (strcmp(aux->val, telefono) == 0)
        {
            // El número ya existe, moverlo al top
            nodo* nuevo = (nodo*)malloc(sizeof(nodo));

            if (strcpy_s(nuevo->val, sizeof(nuevo->val), aux->val) != 0)
            {
                cout << "Error al copiar el número de teléfono." << endl;
                return;
            }

            if (strcpy_s(nuevo->nombre, sizeof(nuevo->nombre), aux->nombre) != 0)
            {
                cout << "Error al copiar el nombre del contacto." << endl;
                return;
            }

            nuevo->sig = cab;
            cab = nuevo;

            // Eliminar el nodo original
            nodo* temp = cab;
            while (temp->sig != aux)
            {
                temp = temp->sig;
            }
            temp->sig = aux->sig;
            free(aux);

            cout << "Numero existente, se movio al top de la pila." << endl;
            return;
        }
    }

    // El número no existe, solicitar el nombre del contacto
    nodo* nuevo = (nodo*)malloc(sizeof(nodo));

    if (strcpy_s(nuevo->val, sizeof(nuevo->val), telefono) != 0)
    {
        cout << "Error al copiar el numero de telefono." << endl;
        return;
    }

    cout << "Ingrese el nombre del contacto: ";
    cin >> nuevo->nombre;

    nuevo->sig = cab;
    cab = nuevo;

    cout << "Numero registrado exitosamente." << endl;
}

void viewer()
{
    system("cls");
    int i = 1;

    cout << "<<<LLAMADAS REALIZADAS>>>" << endl;
    cout << endl;

    for (nodo* aux = cab; aux != NULL; aux = aux->sig)
    {
        cout << "Llamada #" << i << endl;
        cout << "Numero de telefono: " << aux->val << endl;
        cout << "Nombre del contacto: " << aux->nombre << endl;
        cout << endl;
        i++;
    }

    if (cab == NULL)
    {
        cout << "La pila esta vacia." << endl;
    }
}

void pop()
{
    system("cls");

    if (cab == NULL)
    {
        cout << "La pila esta vacia. No se pueden eliminar llamadas." << endl;
        return;
    }

    // Eliminar el nodo en el top de la pila
    nodo* temp = cab;
    cab = cab->sig;
    free(temp);

    cout << "Llamada eliminada exitosamente." << endl;
}

int main()
{
    int opc = 0;

    do
    {
        cout << "<<<MENU>>>" << endl;
        cout << "1. Registrar Llamada" << endl;
        cout << "2. Mostrar Llamadas" << endl;
        cout << "3. Eliminar Ultima Llamada" << endl;
        cout << "4. Salir" << endl;
        cin >> opc;

        switch (opc)
        {
        case 1:
            push();
            system("pause");
            system("cls");
            break;
        case 2:
            viewer();
            system("pause");
            system("cls");
            break;
        case 3:
            pop();
            system("pause");
            system("cls");
            break;
        case 4:
            cout << "Adios" << endl;
            break;
        default:
            break;
        }
    } while (opc != 4);

    return 0;
}
