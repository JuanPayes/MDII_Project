#include <iostream>
#include <string>
#include <limits> // Para manejar errores de entrada
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

/*double calcularProbabilidad(int num_intentos, double proba_base, int cantidad_items, int total_items)
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
}*/

// Función para mostrar el nombre de la cantidad de estrellas basado en el número
/*string obtenerEstrellas(int estrellas)
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
}*/

// Función para agregar múltiples items con los mismos datos
void agregarItems(int n, const string &nombre) {
    for (int i = 0; i < n; i++) {
        items[cantidad].nombre = nombre;
        cantidad++;
    }
    int espaciosRestantes = MAX_ITEMS - cantidad;
    cout << "Se han agregado " << n << " items con nombre '" << nombre
         << "'. Espacios disponibles después de agregar: " << espaciosRestantes << "\n";
}

// Función para contar items con el mismo nombre
int contarItems(const string &nombre) {
    int contador = 0;
    for (int i = 0; i < cantidad; i++) {
        if (items[i].nombre == nombre) {
            contador++;
        }
    }
    return contador;
}

// Función para verificar si existen diferentes niveles de estrellas para un mismo nombre
/*bool hayEstrellasDiferentes(const string &nombre)
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
*/
// Función para verificar si una cantidad específica de estrellas existe para un nombre dado
/*bool existeEstrellasParaNombre(const string &nombre, int estrellas)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (items[i].nombre == nombre && items[i].estrellas == estrellas)
        {
            return true;
        }
    }
    return false;
}*/

// Función para eliminar n items por nombre y cantidad de estrellas
void eliminarItems(const string &nombre, int n) {
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
            for (int j = i; j < cantidad - 1; j++) {
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
void verItems() {
    if (cantidad == 0) {
        cout << "No hay items en el inventario.\n";
    } else {
        cout << "Items en el inventario:\n";

        // Arreglos para guardar los items ya contados
        Item itemsContados[MAX_ITEMS];
        int cantidadContados = 0;

        for (int i = 0; i < cantidad; i++) {
            bool yaContado = false;

            // Revisamos si el item ya ha sido contado
            for (int j = 0; j < cantidadContados; j++) {
                if (items[i].nombre == itemsContados[j].nombre) {
                    yaContado = true;
                    break;
                }
            }

            // Si no ha sido contado, lo contamos y lo mostramos
            if (!yaContado) {
                int conteo = 0;
                for (int k = 0; k < cantidad; k++) {
                    if (items[i].nombre == items[k].nombre) {
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
/*void tirarObjeto()
{
    if (cantidad == 0)
    {
        cout << "No hay objetos disponibles para obtener.\n";
        return;
    }

    // Calcular el total de probabilidades
    double totalProbabilidad = 0.0;
    for (int i = 0; i < cantidad; i++)
    {
        if (items[i].estrellas == 1)
            totalProbabilidad += 94.4; // Probabilidad base para 1 estrella
        else if (items[i].estrellas == 2)
            totalProbabilidad += 5.1; // Probabilidad base para 2 estrellas
        else if (items[i].estrellas == 3)
            totalProbabilidad += 0.6; // Probabilidad base para 3 estrellas
    }

    // Generar un número aleatorio entre 0 y totalProbabilidad
    double randomValue = (rand() % 10000) / 100.0; // Escala de 0 a 100.0
    double acumulador = 0.0;

    // Determinar qué objeto se obtiene basado en la probabilidad
    for (int i = 0; i < cantidad; i++)
    {
        double probabilidadItem = 0.0;
        if (items[i].estrellas == 1)
            probabilidadItem = 94.4; // Probabilidad base para 1 estrella
        else if (items[i].estrellas == 2)
            probabilidadItem = 5.1; // Probabilidad base para 2 estrellas
        else if (items[i].estrellas == 3)
            probabilidadItem = 0.6; // Probabilidad base para 3 estrellas

        acumulador += probabilidadItem;

        if (randomValue <= acumulador)
        {
            // Muestra el objeto tirado
            cout << "Has obtenido: " << items[i].nombre << " (" << obtenerEstrellas(items[i].estrellas) << ")\n";

            // Elimina el objeto de la lista
            for (int j = i; j < cantidad - 1; j++)
            {
                items[j] = items[j + 1]; // Desplaza los elementos hacia la izquierda
            }
            cantidad--; // Reduce la cantidad de objetos
            return; // Salir de la función después de obtener el objeto
        }
    }
}
*/
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
            int n;
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

            agregarItems(n, nombre);
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
            /*
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
            */
            break; // Sale del case 4 cuando termina el proceso
        }
        case 5:
            /*
            tirarObjeto();
            */
            break;
        case 6:
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opción no válida. Seleccione una opción entre 1 y 6.\n";
        }
    } while (opcion != 6);

    return 0;
}

