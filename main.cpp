#include <iostream>
#include <string>
#include <limits>  // Para manejar errores de entrada
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

using namespace std;

const int MAX_ITEMS = 50;

struct Item
{
    string nombre;
    int estrellas;
};

Item items[MAX_ITEMS];
int cantidad = 0;

double calcularProbabilidad(int num_intentos, int cantidad_items, int total_items)
{
    double proba_no_obtener = 1.0;                               // Probabilidad de no obtener el item en ningún intento
    double proba_obtener = cantidad_items / double(total_items); // Probabilidad de obtener el item en un intento

    for (int i = 1; i <= num_intentos; ++i)
    {
        // Calculamos la probabilidad de no obtener el item en el intento actual
        proba_no_obtener *= (1.0 - proba_obtener);
    }
    // Probabilidad de obtener el item al menos una vez en los intentos dados
    return 1.0 - proba_no_obtener;
}

// Función para agregar múltiples items con los mismos datos
void agregarItems(int n, const string &nombre)
{
    for (int i = 0; i < n; i++)
    {
        items[cantidad].nombre = nombre;
        cantidad++;
    }
    int espaciosRestantes = MAX_ITEMS - cantidad;
    cout << "Se han agregado " << n << " items con nombre '" << nombre
         << "'. Espacios disponibles después de agregar: " << espaciosRestantes << "\n";
}

// Función para contar items con el mismo nombre
int contarItems(const string &nombre)
{
    int contador = 0;
    for (int i = 0; i < cantidad; i++)
    {
        if (items[i].nombre == nombre)
        {
            contador++;
        }
    }
    return contador;
}

// Función para eliminar n items por nombre y cantidad de estrellas
void eliminarItems(const string &nombre, int n)
{
    int disponibles = contarItems(nombre);

    if (disponibles == 0)
    {
        cout << "No se encontraron items con el nombre '" << nombre << "'.\n";
        return;
    }

    if (n > disponibles)
    {
        cout << "Solo hay " << disponibles << " items disponibles con el nombre '" << nombre << "'. Eliminando todos ellos.\n";
        n = disponibles;
    }
    else
    {
        cout << "Eliminando " << n << " items con el nombre '" << nombre << "'.\n";
    }

    int eliminados = 0;
    for (int i = 0; i < cantidad && eliminados < n; i++)
    {
        if (items[i].nombre == nombre)
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
    cout << "Se han eliminado " << eliminados << " items con el nombre '" << nombre << "'.\n";
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

        // Arreglos para guardar los items ya contados
        Item itemsContados[MAX_ITEMS];
        int cantidadContados = 0;

        for (int i = 0; i < cantidad; i++)
        {
            bool yaContado = false;

            // Revisamos si el item ya ha sido contado
            for (int j = 0; j < cantidadContados; j++)
            {
                if (items[i].nombre == itemsContados[j].nombre)
                {
                    yaContado = true;
                    break;
                }
            }

            // Si no ha sido contado, lo contamos y lo mostramos
            if (!yaContado)
            {
                int conteo = 0;
                for (int k = 0; k < cantidad; k++)
                {
                    if (items[i].nombre == items[k].nombre)
                    {
                        conteo++;
                    }
                }

                // Agregamos el item a los items contados
                itemsContados[cantidadContados] = items[i];
                cantidadContados++;

                // Mostramos el item y su conteo
                cout << "------------------------------------------------------------------------\n";
                cout << "Nombre: " << items[i].nombre
                     << ", Cantidad: " << conteo << "\n";
                cout << "------------------------------------------------------------------------\n";
            }
        }
    }
}

// Función para tirar un objeto al azar
void tirarObjeto()
{
    if (cantidad == 0)
    {
        cout << "No hay objetos disponibles para obtener.\n";
        return;
    } else
    {
    int opcion;
    cout << "Seleccione una opción:\n";
    cout << "1. Hacer un tiro individual\n";
    cout << "2. Hacer 10 tiros de una sola vez\n";
    cout << "Ingrese su opción: ";
    cin >> opcion;
    if (opcion == 1)
    {
        // Hacer un tiro individual
        int randomIndex = rand() % cantidad; // Selecciona un índice aleatorio
        cout << "Has obtenido: " << items[randomIndex].nombre << "\n";
        // Elimina el objeto de la lista
        for (int j = randomIndex; j < cantidad - 1; j++)
        {
            items[j] = items[j + 1]; // Desplaza los elementos hacia la izquierda
        }
        cantidad--; // Reduce la cantidad de objetos
    }
    else if (opcion == 2)
    {
        if (cantidad >= 10)
        {
                // Hacer 10 tiros de una sola vez
            cout << "Objetos obtenidos:\n";
            for (int i = 0; i < 10 && cantidad > 0; i++)
            {
                int randomIndex = rand() % cantidad; // Selecciona un índice aleatorio
                cout << items[randomIndex].nombre << "\n";
                // Elimina el objeto de la lista
                for (int j = randomIndex; j < cantidad - 1; j++)
                {
                    items[j] = items[j + 1]; // Desplaza los elementos hacia la izquierda
                }
                cantidad--; // Reduce la cantidad de objetos
            }
        } else
        {
            cout << "No hay suficientes objetos para realizar 10 tiros.\n";
        }
    }
    else
    {
        cout << "Opción no válida. Por favor, seleccione 1 o 2.\n";
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
        cout << "5. Tiro aleatorio\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";

        try
        {
            cin >> opcion;
            if (cin.fail())
                throw runtime_error("Entrada no valida. Se esperaba un numero.");
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
                cout << "El inventario esta lleno. No se pueden agregar mas items.\n";
                break;
            }
            int n;
            string nombre;

            int espaciosDisponibles = MAX_ITEMS - cantidad;
            cout << "Ingrese la cantidad de items a agregar (cantidad disponible: " << espaciosDisponibles << "): ";

            while (true)
            {
                cin >> n;
                if (cin.fail() || n <= 0 || n > espaciosDisponibles)
                {
                    cout << "Cantidad no valida. Asegurese de que está ingresando un número positivo y no mayor que " << espaciosDisponibles << ".\n";
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

            agregarItems(n, nombre);
            break;
        }
        case 2:
        {
            if (cantidad == 0)
            {
                cout << "El inventario está vacio. No hay items para eliminar.\n";
                break;
            }
            string nombre;
            int n;

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
            while (true)
            {
                cout << "Ingrese la cantidad de items a eliminar: ";
                cin >> n;
                int disponibles = contarItems(nombre);
                if (cin.fail() || n <= 0)
                {
                    cout << "Cantidad no valida. Se esperaba un numero positivo.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else if (n > disponibles)
                {
                    cout << "No hay suficientes items. Solo hay " << disponibles << " disponibles. Intente con una cantidad menor.\n";
                }
                else
                {
                    eliminarItems(nombre, n);
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
            int n, disponibles;

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

            while (true)
            {
                cout << "Ingrese la cantidad de tiros en los que quiere calcular: ";
                cin >> n;
                if (cin.fail() || n <= 0)
                {
                    cout << "Cantidad no valida. Se esperaba un numero positivo.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    double result = calcularProbabilidad(n, disponibles, cantidad);
                    cout << "La probabilidad de obtener " << nombre << " en " << n
                         << " intentos es: " << result * 100 << "%" << endl;
                    break;
                }
            }
            break;
        }
        case 5:
            tirarObjeto();
            break;
        case 6:
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opción no valida. Seleccione una opcion entre 1 y 6.\n";
        }
    } while (opcion != 6);

    return 0;
}
