#include <iostream>
#include <string>
#include <limits> // Para manejar errores de entrada

using namespace std;

const int MAX_ITEMS = 50;

struct Item
{
    string nombre;
    int estrellas;
};

Item items[MAX_ITEMS];
int cantidad = 0;

double calcularProbabilidad(int num_intentos, double proba_base, int cantidad_items, int total_items)
{
    double proba_no_obtener = 1.0; // Probabilidad de no obtener el item en ningun intento
    double proba_obtener = (proba_base / 100.0) * (cantidad_items / double(total_items)); // Ajuste inicial por la cantidad de items

    // Si la probabilidad base es 0.6 (correspondiente a los items de 3 estrellas)
    if (proba_base == 0.6)
    {
        for (int i = 1; i <= num_intentos; ++i)
        {
            // A partir del intento 10, vamos incrementando la probabilidad
            if (i >= 10)
            {
                // Aumento progresivo de 0.2% por intento hasta un máximo de 3.2%
                double incremento = (i - 9) * 0.2 / 100.0; // Incrementa 0.2% por intento
                if (proba_obtener + incremento > 0.032) // Limitar el incremento máximo al 3.2% total
                {
                    incremento = 0.032 - proba_obtener; // No permitir que se pase del 3.2%
                }
                proba_obtener += incremento;
            }

            // Calculamos la probabilidad de no obtener el item
            proba_no_obtener *= (1.0 - proba_obtener);
        }
    }
    else
    {
        // Si la probabilidad base no es 0.6, no hacemos el incremento
        for (int i = 1; i <= num_intentos; ++i)
        {
            // Calculamos la probabilidad de no obtener el item
            proba_no_obtener *= (1.0 - proba_obtener);
        }
    }

    // Probabilidad de obtener el item al menos una vez
    return 1.0 - proba_no_obtener;
}

// Función para mostrar el nombre de la cantidad de estrellas basado en el número
string obtenerEstrellas(int estrellas)
{
    switch (estrellas)
    {
    case 1:
        return "1 estrella";
    case 2:
        return "2 estrellas";
    case 3:
        return "3 estrellas";
    default:
        return "Desconocida";
    }
}

// Función para agregar múltiples items con los mismos datos
void agregarItems(int n, const string &nombre, int estrellas)
{
    for (int i = 0; i < n; i++)
    {
        items[cantidad].nombre = nombre;
        items[cantidad].estrellas = estrellas;
        cantidad++;
    }
    int espaciosRestantes = MAX_ITEMS - cantidad;
    cout << "Se han agregado " << n << " items con nombre '" << nombre
         << "' y de " << obtenerEstrellas(estrellas)
         << ". Espacios disponibles después de agregar: " << espaciosRestantes << "\n";
}

// Función para contar items con el mismo nombre y cantidad de estrellas
int contarItems(const string &nombre, int estrellas = -1)
{
    int contador = 0;
    for (int i = 0; i < cantidad; i++)
    {
        if (items[i].nombre == nombre && (estrellas == -1 || items[i].estrellas == estrellas))
        {
            contador++;
        }
    }
    return contador;
}

// Función para verificar si existen diferentes niveles de estrellas para un mismo nombre
bool hayEstrellasDiferentes(const string &nombre)
{
    int estrellasEncontradas = -1;
    for (int i = 0; i < cantidad; i++)
    {
        if (items[i].nombre == nombre)
        {
            if (estrellasEncontradas == -1)
            {
                estrellasEncontradas = items[i].estrellas;
            }
            else if (items[i].estrellas != estrellasEncontradas)
            {
                return true;
            }
        }
    }
    return false;
}

// Función para verificar si una cantidad específica de estrellas existe para un nombre dado
bool existeEstrellasParaNombre(const string &nombre, int estrellas)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (items[i].nombre == nombre && items[i].estrellas == estrellas)
        {
            return true;
        }
    }
    return false;
}

// Función para eliminar n items por nombre y cantidad de estrellas
void eliminarItems(const string &nombre, int n, int estrellas)
{
    int disponibles = contarItems(nombre, estrellas);

    if (disponibles == 0)
    {
        cout << "No se encontraron items con el nombre '" << nombre << "' y " << obtenerEstrellas(estrellas) << ".\n";
        return;
    }

    if (n > disponibles)
    {
        cout << "Solo hay " << disponibles << " items disponibles con el nombre '" << nombre << "' y " << obtenerEstrellas(estrellas) << ". Eliminando todos ellos.\n";
        n = disponibles;
    }
    else
    {
        cout << "Eliminando " << n << " items con el nombre '" << nombre << "' y " << obtenerEstrellas(estrellas) << ".\n";
    }

    int eliminados = 0;
    for (int i = 0; i < cantidad && eliminados < n; i++)
    {
        if (items[i].nombre == nombre && items[i].estrellas == estrellas)
        {
            for (int j = i; j < cantidad - 1; j++)
            {
                items[j] = items[j + 1];
            }
            cantidad--;
            eliminados++;
            i--;
        }
    }
    cout << "Se han eliminado " << eliminados << " items con el nombre '" << nombre << "' y " << obtenerEstrellas(estrellas) << ".\n";
}

// Función para mostrar todos los items
void verItems()
{
    if (cantidad == 0)
    {
        cout << "No hay items en el inventario.\n";
    }
    else
    {
        cout << "Items en el inventario:\n";
        for (int i = 0; i < cantidad; i++)
        {
            cout << "Nombre: " << items[i].nombre
                 << ", Estrellas: " << obtenerEstrellas(items[i].estrellas) << endl;
        }
    }
}

int main()
{
    int opcion;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Agregar items\n";
        cout << "2. Eliminar items\n";
        cout << "3. Ver items\n";
        cout << "4. Calcular probabilidad de obtener un item en base a una cantidad de tiros\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";

        try
        {
            cin >> opcion;
            if (cin.fail())
                throw runtime_error("Entrada no válida. Se esperaba un número.");
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (opcion)
        {
        case 1:
        {
            if (cantidad >= MAX_ITEMS)
            {
                cout << "El inventario está lleno. No se pueden agregar más items.\n";
                break;
            }
            int n, estrellas;
            string nombre;

            int espaciosDisponibles = MAX_ITEMS - cantidad;
            cout << "Ingrese la cantidad de items a agregar (cantidad disponible: " << espaciosDisponibles << "): ";

            while (true)
            {
                cin >> n;
                if (cin.fail() || n <= 0 || n > espaciosDisponibles)
                {
                    cout << "Cantidad no válida. Asegúrese de que está ingresando un número positivo y no mayor que " << espaciosDisponibles << ".\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ingrese nuevamente la cantidad de items a agregar (cantidad disponible: " << espaciosDisponibles << "): ";
                }
                else
                {
                    break;
                }
            }

            cout << "Ingrese el nombre del item: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nombre);

            while (true)
            {
                cout << "Seleccione la cantidad de estrellas del item:\n";
                cout << "1. 1 estrella\n";
                cout << "2. 2 estrellas\n";
                cout << "3. 3 estrellas\n";
                cout << "Opción: ";
                cin >> estrellas;
                if (cin.fail() || estrellas < 1 || estrellas > 3)
                {
                    cout << "Opción no válida. Seleccione un número entre 1 y 3.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    break;
                }
            }

            agregarItems(n, nombre, estrellas);
            break;
        }
        case 2:
        {
            if (cantidad == 0)
            {
                cout << "El inventario está vacío. No hay items para eliminar.\n";
                break;
            }
            string nombre;
            int n, estrellas = -1;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (true)
            {
                cout << "Ingrese el nombre del item a eliminar: ";
                getline(cin, nombre);
                int disponibles = contarItems(nombre);
                if (disponibles == 0)
                {
                    cout << "No se encontraron items con el nombre '" << nombre << "'. Intente de nuevo.\n";
                }
                else
                {
                    cout << "Hay " << disponibles << " items disponibles con el nombre '" << nombre << "'.\n";
                    break;
                }
            }

            if (hayEstrellasDiferentes(nombre))
            {
                cout << "Se encontraron items con diferentes cantidades de estrellas. Seleccione las estrellas del item que desea eliminar:\n";
                while (true)
                {
                    cout << "1. 1 estrella\n";
                    cout << "2. 2 estrellas\n";
                    cout << "3. 3 estrellas\n";
                    cout << "Opción: ";
                    cin >> estrellas;
                    if (cin.fail() || estrellas < 1 || estrellas > 3 || !existeEstrellasParaNombre(nombre, estrellas))
                    {
                        cout << "Opción no válida o inexistente para este item. Seleccione una cantidad válida de estrellas.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < cantidad; i++)
                {
                    if (items[i].nombre == nombre)
                    {
                        estrellas = items[i].estrellas;
                        break;
                    }
                }
            }

            while (true)
            {
                cout << "Ingrese la cantidad de items a eliminar: ";
                cin >> n;
                int disponibles = contarItems(nombre, estrellas);
                if (cin.fail() || n <= 0)
                {
                    cout << "Cantidad no válida. Se esperaba un número positivo.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else if (n > disponibles)
                {
                    cout << "No hay suficientes items. Solo hay " << disponibles << " disponibles. Intente con una cantidad menor.\n";
                }
                else
                {
                    eliminarItems(nombre, n, estrellas);
                    break;
                }
            }
            break;
        }
        case 3:
        {
            verItems();
            break;
        }
        case 4:
        {
            string nombre;
            int n, estrellas = -1;
            int disponibles = 0;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (true)
            {
                cout << "Ingrese el nombre del item del que desea calcular la probabilidad: ";
                getline(cin, nombre);
                disponibles = contarItems(nombre);
                if (disponibles == 0)
                {
                    cout << "No se encontraron items con el nombre '" << nombre << "'. Intente de nuevo.\n";
                }
                else
                {
                    cout << "Hay " << disponibles << " items disponibles con el nombre '" << nombre << "'.\n";
                    break;
                }
            }

            if (hayEstrellasDiferentes(nombre))
            {
                cout << "Se encontraron items con diferentes cantidades de estrellas. Seleccione las estrellas del item del que desea calcular la probabilidad:\n";
                while (true)
                {
                    cout << "1. 1 estrella\n";
                    cout << "2. 2 estrellas\n";
                    cout << "3. 3 estrellas\n";
                    cout << "Opción: ";
                    cin >> estrellas;
                    if (cin.fail() || estrellas < 1 || estrellas > 3 || !existeEstrellasParaNombre(nombre, estrellas))
                    {
                        cout << "Opción no válida o inexistente para este item. Seleccione una cantidad válida de estrellas.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < cantidad; i++)
                {
                    if (items[i].nombre == nombre)
                    {
                        estrellas = items[i].estrellas;
                        break;
                    }
                }
            }

            while (true)
            {
                cout << "Ingrese la cantidad de tiros en los que quiere calcular: ";
                cin >> n;
                if (cin.fail() || n <= 0)
                {
                    cout << "Cantidad no válida. Se esperaba un número positivo.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    double proba_base;
                    // Ajuste de probabilidades según la rareza
                    if (estrellas == 1)
                    {
                        proba_base = 94.4;
                    }
                    else if (estrellas == 2)
                    {
                        proba_base = 5.1;
                    }
                    else if (estrellas == 3)
                    {
                        proba_base = 0.6;
                    }

                    double result = calcularProbabilidad(n, proba_base, disponibles, cantidad);
                    cout << "La probabilidad de obtener " << nombre << " en " << n
                         << " intentos es: " << result * 100 << "%" << endl;
                    break; // Sale del while cuando se calcula la probabilidad
                }
            }
            break; // Sale del case 4 cuando termina el proceso
        }
        break;
        case 5:
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opción no válida. Seleccione una opción entre 1 y 4.\n";
        }
    } while (opcion != 5);

    return 0;
}
