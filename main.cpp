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
    for (int i = 0; i < n; i++) {
        items[cantidad].nombre = nombre;
        items[cantidad].rareza = rareza;
        cantidad++;
    }
    int espaciosRestantes = MAX_ITEMS - cantidad;
    cout << "Se han agregado " << n << " items con nombre '" << nombre 
         << "' y rareza " << obtenerRareza(rareza) 
         << ". Espacios disponibles después de agregar: " << espaciosRestantes << "\n";
}

// Función para contar items con el mismo nombre y rareza
int contarItems(const string& nombre, int rareza = -1) {
    int contador = 0;
    for (int i = 0; i < cantidad; i++) {
        if (items[i].nombre == nombre && (rareza == -1 || items[i].rareza == rareza)) {
            contador++;
        }
    }
    return contador;
}

// Función para verificar si existen rarezas distintas para un mismo nombre
bool hayRarezasDiferentes(const string& nombre) {
    int rarezaEncontrada = -1;
    for (int i = 0; i < cantidad; i++) {
        if (items[i].nombre == nombre) {
            if (rarezaEncontrada == -1) {
                rarezaEncontrada = items[i].rareza;
            } else if (items[i].rareza != rarezaEncontrada) {
                return true;
            }
        }
    }
    return false;
}

// Función para verificar si una rareza específica existe para un nombre dado
bool existeRarezaParaNombre(const string& nombre, int rareza) {
    for (int i = 0; i < cantidad; i++) {
        if (items[i].nombre == nombre && items[i].rareza == rareza) {
            return true;
        }
    }
    return false;
}

// Función para eliminar n items por nombre y rareza
void eliminarItems(const string& nombre, int n, int rareza) {
    int disponibles = contarItems(nombre, rareza);

    if (disponibles == 0) {
        cout << "No se encontraron items con el nombre '" << nombre << "' y rareza " << obtenerRareza(rareza) << ".\n";
        return;
    }

    if (n > disponibles) {
        cout << "Solo hay " << disponibles << " items disponibles con el nombre '" << nombre << "' y rareza " << obtenerRareza(rareza) << ". Eliminando todos ellos.\n";
        n = disponibles;
    } else {
        cout << "Eliminando " << n << " items con el nombre '" << nombre << "' y rareza " << obtenerRareza(rareza) << ".\n";
    }

    int eliminados = 0;
    for (int i = 0; i < cantidad && eliminados < n; i++) {
        if (items[i].nombre == nombre && items[i].rareza == rareza) {
            // Mover los items hacia atrás para llenar el espacio eliminado
            for (int j = i; j < cantidad - 1; j++) {
                items[j] = items[j + 1];
            }
            cantidad--;
            eliminados++;
            i--; // Decrementar i para revisar el nuevo item en la posición actual
        }
    }
    cout << "Se han eliminado " << eliminados << " items con el nombre '" << nombre << "' y rareza " << obtenerRareza(rareza) << ".\n";
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
                 if (cantidad >= MAX_ITEMS) {
                    cout << "El inventario está lleno. No se pueden agregar más items.\n";
                    break;
                }
                int n, rareza;
                string nombre;

                // Mostrar espacios disponibles antes de pedir la cantidad a agregar
                int espaciosDisponibles = MAX_ITEMS - cantidad;
                cout << "Ingrese la cantidad de items a agregar (cantidad disponible: " << espaciosDisponibles << "): ";
                
                // Validación de la cantidad
                while (true) {
                    cin >> n;
                    if (cin.fail() || n <= 0 || n > espaciosDisponibles) {
                        cout << "Cantidad no válida. Asegúrese de que está ingresando un número positivo y no mayor que " << espaciosDisponibles << ".\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Ingrese nuevamente la cantidad de items a agregar (cantidad disponible: " << espaciosDisponibles << "): ";
                    } else {
                        break;
                    }
                }

                cout << "Ingrese el nombre del item: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, nombre);

                // Validación de rareza
                while (true) {
                    cout << "Seleccione la rareza del item:\n";
                    cout << "1. Rareza 1\n";
                    cout << "2. Rareza 2\n";
                    cout << "3. Rareza 3\n";
                    cout << "4. Rareza 4\n";
                    cout << "Opción: ";
                    cin >> rareza;
                    if (cin.fail() || rareza < 1 || rareza > 4) {
                        cout << "Rareza no válida. Seleccione un número entre 1 y 4.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else {
                        break;
                    }
                }
                
                agregarItems(n, nombre, rareza);
                break;
            }
            case 2: {
                if (cantidad == 0) {
                cout << "No hay items en el inventario para eliminar.\n";
                break;
                }
                string nombre;
                int n, rareza = -1;

                // Validación inmediata del nombre del item a eliminar
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpiar el buffer solo una vez al inicio
                while (true) {
                    cout << "Ingrese el nombre del item a eliminar: ";
                    getline(cin, nombre);
                    int disponibles = contarItems(nombre);
                    if (disponibles == 0) {
                        cout << "No se encontraron items con el nombre '" << nombre << "'. Intente de nuevo.\n";
                    } else {
                        cout << "Hay " << disponibles << " items disponibles con el nombre '" << nombre << "'.\n";
                        break;
                    }
                }

                // Verificar si hay rarezas diferentes para el mismo nombre
                if (hayRarezasDiferentes(nombre)) {
                    cout << "Se encontraron items con rarezas diferentes. Seleccione la rareza que desea eliminar:\n";
                    while (true) {
                        cout << "1. Rareza 1\n";
                        cout << "2. Rareza 2\n";
                        cout << "3. Rareza 3\n";
                        cout << "4. Rareza 4\n";
                        cout << "Opción: ";
                        cin >> rareza;
                        if (cin.fail() || rareza < 1 || rareza > 4 || !existeRarezaParaNombre(nombre, rareza)) {
                            cout << "Rareza no válida o inexistente para este item. Seleccione una rareza válida entre las opciones disponibles.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }
                } else {
                    // Si no hay rarezas diferentes, tomar la primera rareza encontrada
                    for (int i = 0; i < cantidad; i++) {
                        if (items[i].nombre == nombre) {
                            rareza = items[i].rareza;
                            break;
                        }
                    }
                }

                // Validación inmediata de la cantidad de items a eliminar
                while (true) {
                    cout << "Ingrese la cantidad de items a eliminar: ";
                    cin >> n;
                    int disponibles = contarItems(nombre, rareza);
                    if (cin.fail() || n <= 0) {
                        cout << "Cantidad no válida. Se esperaba un número positivo.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else if (n > disponibles) {
                        cout << "No hay suficientes items. Solo hay " << disponibles << " disponibles. Intente con una cantidad menor.\n";
                    } else {
                        eliminarItems(nombre, n, rareza);
                        break;
                    }
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
