#include <iostream>
#include <string>
#include <limits> // Para manejar errores de entrada

using namespace std;

const int MAX_ITEMS = 50;

struct Item {
    string nombre;
    int rareza;
};

Item items[MAX_ITEMS];
int cantidad = 0;

// Función para mostrar el nombre de la rareza basado en el número
string obtenerRareza(int rareza) {
    switch (rareza) {
        case 1: return "Rareza 1";
        case 2: return "Rareza 2";
        case 3: return "Rareza 3";
        case 4: return "Rareza 4";
        default: return "Desconocida";
    }
}

// Función para agregar múltiples items con los mismos datos
void agregarItems(int n, const string& nombre, int rareza) {
    if (cantidad + n > MAX_ITEMS) {
        cout << "No hay suficiente espacio en el inventario para agregar " << n << " items.\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        items[cantidad].nombre = nombre;
        items[cantidad].rareza = rareza;
        cantidad++;
    }
    cout << "Se han agregado " << n << " items con nombre '" << nombre 
         << "' y rareza " << obtenerRareza(rareza) << " exitosamente.\n";
}

// Función para contar items con el mismo nombre
int contarItems(const string& nombre) {
    int contador = 0;
    for (int i = 0; i < cantidad; i++) {
        if (items[i].nombre == nombre) {
            contador++;
        }
    }
    return contador;
}

// Función para eliminar n items por nombre
void eliminarItems(const string& nombre, int n) {
    int disponibles = contarItems(nombre);

    if (disponibles == 0) {
        cout << "No se encontraron items con el nombre '" << nombre << "'.\n";
        return;
    }

    if (n > disponibles) {
        cout << "Solo hay " << disponibles << " items disponibles con el nombre '" << nombre << "'. Eliminando todos ellos.\n";
        n = disponibles;
    } else {
        cout << "Eliminando " << n << " items con el nombre '" << nombre << "'.\n";
    }

    int eliminados = 0;
    for (int i = 0; i < cantidad && eliminados < n; i++) {
        if (items[i].nombre == nombre) {
            // Mover los items hacia atrás para llenar el espacio eliminado
            for (int j = i; j < cantidad - 1; j++) {
                items[j] = items[j + 1];
            }
            cantidad--;
            eliminados++;
            i--;  // Retroceder el índice para verificar el nuevo item en la posición actual
        }
    }
    cout << "Se han eliminado " << eliminados << " items con el nombre '" << nombre << "'.\n";
}

// Función para mostrar todos los items
void verItems() {
    if (cantidad == 0) {
        cout << "No hay items en el inventario.\n";
    } else {
        cout << "Items en el inventario:\n";
        for (int i = 0; i < cantidad; i++) {
            cout << "Nombre: " << items[i].nombre 
                 << ", Rareza: " << obtenerRareza(items[i].rareza) << endl;
        }
    }
}

int main() {
    int opcion;

    do {
        cout << "\nMenu:\n";
        cout << "1. Agregar items\n";
        cout << "2. Eliminar items\n";
        cout << "3. Ver items\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        
        try {
            cin >> opcion;
            if (cin.fail()) throw runtime_error("Entrada no válida. Se esperaba un número.");
        } catch (const exception& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (opcion) {
            case 1: {
                int n, rareza;
                string nombre;

                try {
                    cout << "Ingrese la cantidad de items a agregar: ";
                    cin >> n;
                    if (cin.fail() || n <= 0) throw runtime_error("Cantidad no válida. Se esperaba un número positivo.");
                } catch (const exception& e) {
                    cout << e.what() << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                cout << "Ingrese el nombre del item: ";
                cin.ignore();
                getline(cin, nombre);

                try {
                    cout << "Seleccione la rareza del item:\n";
                    cout << "1. Rareza 1\n";
                    cout << "2. Rareza 2\n";
                    cout << "3. Rareza 3\n";
                    cout << "4. Rareza 4\n";
                    cout << "Opción: ";
                    cin >> rareza;
                    if (cin.fail() || rareza < 1 || rareza > 4) throw runtime_error("Rareza no válida. Seleccione un número entre 1 y 4.");
                    agregarItems(n, nombre, rareza);
                } catch (const exception& e) {
                    cout << e.what() << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }
            case 2: {
                string nombre;
                int n;

                cout << "Ingrese el nombre del item a eliminar: ";
                cin.ignore();
                getline(cin, nombre);

                int disponibles = contarItems(nombre);
                cout << "Hay " << disponibles << " items disponibles con el nombre '" << nombre << "'.\n";

                try {
                    cout << "Ingrese la cantidad de items a eliminar: ";
                    cin >> n;
                    if (cin.fail() || n <= 0) throw runtime_error("Cantidad no válida. Se esperaba un número positivo.");
                    eliminarItems(nombre, n);
                } catch (const exception& e) {
                    cout << e.what() << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }
            case 3:
                verItems();
                break;
            case 4:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}
