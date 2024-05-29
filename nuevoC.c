#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ----------
    Estructura Principal
*/

struct FarmaSalud 
{
    struct NodoClientes *clientes;
    struct NodoSucursales *sucursales;
    struct NodoProveedor *proveedores;
};

/* ----------
    Izquierda
*/

// Lista doblemente Enlazada Nodo Fantasma
struct NodoClientes 
{
    struct Clientes *datosClientes;
    struct NodoClientes *ant, *sig;
};

struct Clientes 
{
    int id;
    char *rutCliente;
    int edadCliente; 
    int afiliado;
    char **comprasCliente; // Array
};

/* ----------
    Centro
*/

// Lista Circular Doblemente Enlazada 
struct NodoSucursales
{
    struct Sucursal *datosSucursal;
    struct NodoSucursales *ant, *sig;
};

struct Sucursal 
{
    int id;
    char *nombre;
    char *direccion;
    int capacidadAlmacenamiento;
    struct NodoProducto *productos;
};

// Lista doblemente enlazada con nodo fantasma
struct NodoProducto 
{
    struct Producto *datosProducto;
    struct NodoProducto *ant, *sig;
};

struct Producto 
{
    char codigo[10];
    char *nombreProducto;
    char *descripcion;
    char *categoria;
    int precio;
    char *nombreProveedor;
    char *lote;
    char *fechaCaducidad;
    int cantidad;
    int requiereReceta;
};

/* ----------
    Izquierda
*/

// Lista doblemente enlazada nodo fantasma 
struct NodoProveedor 
{
    struct Proveedor *datosProveedor;
    struct NodoProveedor *ant, *sig;
};

struct Proveedor 
{
    int id;
    char *nombre;
    char *direccion;
    char *telefono;
    struct NodoArbolProducto *productos;
};

// Arbol de busqueda binaria
struct NodoArbolProducto 
{
    struct Producto *datosProducto;
    struct NodoArbolProducto *izq, *der;
};

/* - - - - - - - - - */

void pause() {
    printf("\nPresione Enter para continuar...\n");
    while (getchar() != '\n'); // Limpiar el búfer de entrada
    getchar(); // Esperar a que se presione Enter
}

void cls() {
    int i;
    for(i=0;i<20;i++) printf("\n");
}

struct NodoClientes* crearClienteConsole(int id, char* rutCliente, int edadCliente, int afiliado, char** comprasCliente) {
    struct NodoClientes* nuevoNodo = (struct NodoClientes*)malloc(sizeof(struct NodoClientes));
    struct Clientes* nuevoCliente = (struct Clientes*)malloc(sizeof(struct Clientes));

    nuevoCliente->id = id;
    nuevoCliente->rutCliente = strdup(rutCliente);
    nuevoCliente->edadCliente = edadCliente;
    nuevoCliente->afiliado = afiliado;

    // Asignar memoria y copiar cada elemento de la lista de compras
    int i, count = 0;
    while (comprasCliente[count] != NULL) count++;
    nuevoCliente->comprasCliente = (char**)malloc((count + 1) * sizeof(char*));
    for (i = 0; i < count; i++) {
        nuevoCliente->comprasCliente[i] = strdup(comprasCliente[i]);
    }
    nuevoCliente->comprasCliente[count] = NULL;

    nuevoNodo->datosClientes = nuevoCliente;
    nuevoNodo->ant = nuevoNodo->sig = NULL;

    return nuevoNodo;
}

void agregarClienteConsole(struct FarmaSalud *farmacia, struct NodoClientes *nuevoCliente) {
    if (farmacia->clientes == NULL) {
        farmacia->clientes = nuevoCliente;
    } else {
        struct NodoClientes *temp = farmacia->clientes;
        while (temp->sig != NULL) {
            temp = temp->sig;
        }
        temp->sig = nuevoCliente;
        nuevoCliente->ant = temp;
    }
}

struct NodoSucursales* crearSucursalConsole(int id, char* nombre, char* direccion, int capacidadAlmacenamiento) {
    struct NodoSucursales* nuevoNodo = (struct NodoSucursales*)malloc(sizeof(struct NodoSucursales));
    struct Sucursal* nuevaSucursal = (struct Sucursal*)malloc(sizeof(struct Sucursal));
    
    nuevaSucursal->id = id;
    nuevaSucursal->nombre = strdup(nombre);
    nuevaSucursal->direccion = strdup(direccion);
    nuevaSucursal->capacidadAlmacenamiento = capacidadAlmacenamiento;
    nuevaSucursal->productos = NULL;
    
    nuevoNodo->datosSucursal = nuevaSucursal;
    nuevoNodo->ant = nuevoNodo->sig = nuevoNodo;
    
    return nuevoNodo;
}

void agregarSucursalConsole(struct FarmaSalud *farmacia, struct NodoSucursales *nuevaSucursal) {
    if (farmacia->sucursales == NULL) {
        farmacia->sucursales = nuevaSucursal;
    } else {
        struct NodoSucursales *temp = farmacia->sucursales;
        while (temp->sig != farmacia->sucursales) {
            temp = temp->sig;
        }
        temp->sig = nuevaSucursal;
        nuevaSucursal->ant = temp;
        nuevaSucursal->sig = farmacia->sucursales;
        farmacia->sucursales->ant = nuevaSucursal;
    }
}

void leerClientes(struct FarmaSalud *farmacia) {
    cls();
    struct NodoClientes *nodoActual = farmacia->clientes;
    while(nodoActual != NULL) {
        printf("ID: %d\n", nodoActual->datosClientes->id);
        printf("RUT: %s\n", nodoActual->datosClientes->rutCliente);
        printf("Edad: %d\n", nodoActual->datosClientes->edadCliente);
        printf("Afiliado: %d\n", nodoActual->datosClientes->afiliado);
        
        // Verificar si hay compras del cliente
        if (nodoActual->datosClientes->comprasCliente != NULL) {
            printf("Compras:\n");
            char **compras = nodoActual->datosClientes->comprasCliente;
            while(*compras != NULL) {
                printf("\t%s\n", *compras);
                compras++;
            }
            printf("\n");
        } else {
            printf("Cliente sin compras\n\n");
        }
        
        nodoActual = nodoActual->sig;
    }
    pause();
}


void agregarCliente(struct FarmaSalud *farmacia) 
{
    struct NodoClientes *nuevoNodo = (struct NodoClientes *)malloc(sizeof(struct NodoClientes));
    nuevoNodo->datosClientes = (struct Clientes *)malloc(sizeof(struct Clientes));
    
    cls();
    printf("Ingrese ID del cliente: ");
    scanf("%d", &nuevoNodo->datosClientes->id);
    printf("Ingrese RUT del cliente: ");
    nuevoNodo->datosClientes->rutCliente = (char *)malloc(20 * sizeof(char));
    scanf("%s", nuevoNodo->datosClientes->rutCliente);
    printf("Ingrese edad del cliente: ");
    scanf("%d", &nuevoNodo->datosClientes->edadCliente);
    printf("¿Es afiliado? (1-Si, 0-No): ");
    scanf("%d", &nuevoNodo->datosClientes->afiliado);
    
    // Inicializar comprasCliente como una lista vacía
    nuevoNodo->datosClientes->comprasCliente = NULL;

    // Agregar cliente al final de la lista
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = NULL;
    if (farmacia->clientes == NULL) {
        farmacia->clientes = nuevoNodo;
    } else {
        struct NodoClientes *temp = farmacia->clientes;
        while (temp->sig != NULL) {
            temp = temp->sig;
        }
        temp->sig = nuevoNodo;
        nuevoNodo->ant = temp;
    }
    
    cls();
    printf("Cliente agregado con éxito.\n");
    pause();
}

void eliminarCliente(struct FarmaSalud *farmacia) {
    cls();
    int idEliminar;
    struct NodoClientes *temp, *prev;

    // Pedir al usuario que ingrese el ID del cliente a eliminar
    printf("Ingrese el ID del cliente que desea eliminar: ");
    scanf("%d", &idEliminar);

    temp = farmacia->clientes;
    prev = NULL;

    // Buscar el cliente con el ID proporcionado
    while (temp != NULL && temp->datosClientes->id != idEliminar) {
        prev = temp;
        temp = temp->sig;
    }

    // Si no se encontró el cliente con el ID proporcionado
    if (temp == NULL) {
        cls();
        printf("Cliente no encontrado.\n");
        pause();
        return;
    }

    // Manejar los casos especiales para el primer y último nodo
    if (prev == NULL) {
        farmacia->clientes = temp->sig;
    } else {
        prev->sig = temp->sig;
    }

    if (temp->sig != NULL) {
        temp->sig->ant = prev;
    }

    // Liberar la memoria asignada al cliente eliminado
    free(temp->datosClientes->rutCliente);
    free(temp->datosClientes->comprasCliente);
    free(temp->datosClientes);
    free(temp);

    cls();
    printf("Cliente eliminado con éxito.\n");
    pause();
}


void menuPrincipal(struct FarmaSalud *farmacia) {
    int opcion;
    do {
        printf("\n--- FarmaSalud ---\n");
        printf("1. leerClientes\n");
        printf("2. crearCliente\n");
        printf("3. eliminarCliente\n");
        printf("\n9. Salir\n");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                leerClientes(farmacia);
                cls();
                break;
            case 2:
                agregarCliente(farmacia);
                cls();
                break;
            case 3:
                eliminarCliente(farmacia);
                cls();
                break;
            case 9:
                printf("Saliendo...\n");
                exit(0);
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 9);
}

int main() {
    struct FarmaSalud *farmacia;
    farmacia = (struct FarmaSalud *) malloc(sizeof(struct FarmaSalud));

    farmacia->clientes = NULL;
    farmacia->sucursales = NULL;
    farmacia->proveedores = NULL;

    char* compras1[] = {"Producto A", "Producto B", NULL};
    struct NodoClientes* cliente1 = crearClienteConsole(1, "11111111-1", 30, 1, compras1);
    agregarClienteConsole(farmacia, cliente1);

    char* compras2[] = {"Producto C", "Producto D", NULL};
    struct NodoClientes* cliente2 = crearClienteConsole(2, "22222222-2", 25, 0, compras2);
    agregarClienteConsole(farmacia, cliente2);

    struct NodoSucursales* sucursal1 = crearSucursalConsole(1, "Sucursal A", "Direccion A", 100);
    agregarSucursalConsole(farmacia, sucursal1);
    
    struct NodoSucursales* sucursal2 = crearSucursalConsole(2, "Sucursal B", "Direccion B", 200);
    agregarSucursalConsole(farmacia, sucursal2);

    while (1) {
        cls();
        menuPrincipal(farmacia);
    }

    return 0;
}
