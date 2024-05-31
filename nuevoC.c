#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definir el máximo de productos por cliente */
#define MAX_PRODUCTOS_POR_CLIENTE 10000

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
    struct Producto *comprasCliente[MAX_PRODUCTOS_POR_CLIENTE]; // Array de punteros a Productos
    int numCompras; // Número de compras
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

struct NodoClientes* crearClienteConsole(int id, char* rutCliente, int edadCliente, int afiliado, struct Producto **comprasCliente, int numCompras) {
    struct NodoClientes* nuevoNodo = (struct NodoClientes*)malloc(sizeof(struct NodoClientes));
    struct Clientes* nuevoCliente = (struct Clientes*)malloc(sizeof(struct Clientes));

    nuevoCliente->id = id;
    nuevoCliente->rutCliente = strdup(rutCliente);
    nuevoCliente->edadCliente = edadCliente;
    nuevoCliente->afiliado = afiliado;
    nuevoCliente->numCompras = numCompras;

    // Inicializar el array de compras con NULL
    for (int i = 0; i < MAX_PRODUCTOS_POR_CLIENTE; i++) {
        nuevoCliente->comprasCliente[i] = NULL;
    }
    // Copiar los productos existentes
    for (int i = 0; i < numCompras; i++) {
        nuevoCliente->comprasCliente[i] = comprasCliente[i];
    }

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
        if((nodoActual->datosClientes->afiliado)==1)
        {
            printf("Afiliado: Si\n");
        }
        else
        {
            printf("Afiliado: No\n");
        }
        
        // Verificar si hay compras del cliente
        if (nodoActual->datosClientes->numCompras > 0) {
            printf("Compras:\n");
            for (int i = 0; i < nodoActual->datosClientes->numCompras; i++) {
                struct Producto *producto = nodoActual->datosClientes->comprasCliente[i];
                if (producto != NULL) {
                    printf("\t%s - %s\n", producto->codigo, producto->nombreProducto);
                }
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
    for (int i = 0; i < MAX_PRODUCTOS_POR_CLIENTE; i++) {
        nuevoNodo->datosClientes->comprasCliente[i] = NULL;
    }
    nuevoNodo->datosClientes->numCompras = 0;

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

    // Liberar la memoria asociada al cliente
    free(temp->datosClientes->rutCliente);
    for (int i = 0; i < temp->datosClientes->numCompras; i++) {
        free(temp->datosClientes->comprasCliente[i]->nombreProducto);
        free(temp->datosClientes->comprasCliente[i]->descripcion);
        free(temp->datosClientes->comprasCliente[i]->categoria);
        free(temp->datosClientes->comprasCliente[i]->nombreProveedor);
        free(temp->datosClientes->comprasCliente[i]->lote);
        free(temp->datosClientes->comprasCliente[i]->fechaCaducidad);
        free(temp->datosClientes->comprasCliente[i]);
    }
    free(temp->datosClientes);
    free(temp);

    cls();
    printf("Cliente eliminado con éxito.\n");
    pause();
}

void agregarProductoACliente(struct FarmaSalud *farmacia) {
    cls();
    int idCliente;
    printf("Ingrese el ID del cliente al que desea agregar un producto: ");
    scanf("%d", &idCliente);

    struct NodoClientes *clienteActual = farmacia->clientes;
    while (clienteActual != NULL && clienteActual->datosClientes->id != idCliente) {
        clienteActual = clienteActual->sig;
    }

    if (clienteActual == NULL) {
        printf("Cliente no encontrado.\n");
        pause();
        return;
    }

    if (clienteActual->datosClientes->numCompras >= MAX_PRODUCTOS_POR_CLIENTE) {
        printf("El cliente ha alcanzado el máximo número de productos permitidos.\n");
        pause();
        return;
    }

    struct Producto *nuevoProducto = (struct Producto *)malloc(sizeof(struct Producto));
    printf("Ingrese código del producto: ");
    scanf("%s", nuevoProducto->codigo);
    nuevoProducto->nombreProducto = (char *)malloc(50 * sizeof(char));
    printf("Ingrese nombre del producto: ");
    scanf("%s", nuevoProducto->nombreProducto);
    nuevoProducto->descripcion = (char *)malloc(100 * sizeof(char));
    printf("Ingrese descripción del producto: ");
    scanf("%s", nuevoProducto->descripcion);
    nuevoProducto->categoria = (char *)malloc(50 * sizeof(char));
    printf("Ingrese categoría del producto: ");
    scanf("%s", nuevoProducto->categoria);
    printf("Ingrese precio del producto: ");
    scanf("%d", &nuevoProducto->precio);
    nuevoProducto->nombreProveedor = (char *)malloc(50 * sizeof(char));
    printf("Ingrese nombre del proveedor: ");
    scanf("%s", nuevoProducto->nombreProveedor);
    nuevoProducto->lote = (char *)malloc(20 * sizeof(char));
    printf("Ingrese lote del producto: ");
    scanf("%s", nuevoProducto->lote);
    nuevoProducto->fechaCaducidad = (char *)malloc(15 * sizeof(char));
    printf("Ingrese fecha de caducidad del producto (YYYY-MM-DD): ");
    scanf("%s", nuevoProducto->fechaCaducidad);
    printf("Ingrese cantidad del producto: ");
    scanf("%d", &nuevoProducto->cantidad);
    printf("¿Requiere receta? (1-Sí, 0-No): ");
    scanf("%d", &nuevoProducto->requiereReceta);

    // Agregar el nuevo producto al array de compras del cliente
    clienteActual->datosClientes->comprasCliente[clienteActual->datosClientes->numCompras] = nuevoProducto;
    clienteActual->datosClientes->numCompras++;

    cls();
    printf("Producto agregado con éxito al cliente.\n");
    pause();
}

void leerSucursales(struct FarmaSalud *farmacia) {
    cls();
    struct NodoSucursales *nodoActual = farmacia->sucursales;
    if (nodoActual == NULL) {
        printf("No hay sucursales registradas.\n");
        pause();
        return;
    }
    do {
        printf("ID: %d\n", nodoActual->datosSucursal->id);
        printf("Nombre: %s\n", nodoActual->datosSucursal->nombre);
        printf("Dirección: %s\n", nodoActual->datosSucursal->direccion);
        printf("Capacidad de Almacenamiento: %d\n", nodoActual->datosSucursal->capacidadAlmacenamiento);
        
        // Verificar si la sucursal tiene productos asociados
        if (nodoActual->datosSucursal->productos != NULL) {
            printf("Productos:\n");
            struct NodoProducto *productoNodo = nodoActual->datosSucursal->productos;
            while (productoNodo != NULL) {
                printf("\t%s - %s\n", productoNodo->datosProducto->codigo, productoNodo->datosProducto->nombreProducto);
                productoNodo = productoNodo->sig;
            }
            printf("\n");
        } else {
            printf("Sucursal sin productos\n\n");
        }

        nodoActual = nodoActual->sig;
    } while (nodoActual != farmacia->sucursales);
    pause();
}

void crearSucursal(struct FarmaSalud *farmacia) {
    cls();
    struct NodoSucursales *nuevoNodo = (struct NodoSucursales*)malloc(sizeof(struct NodoSucursales));
    struct Sucursal *nuevaSucursal = (struct Sucursal*)malloc(sizeof(struct Sucursal));
    
    nuevoNodo->datosSucursal = nuevaSucursal;
    nuevoNodo->ant = nuevoNodo->sig = NULL;

    printf("Ingrese ID de la sucursal: ");
    scanf("%d", &nuevaSucursal->id);
    printf("Ingrese nombre de la sucursal: ");
    nuevaSucursal->nombre = (char *)malloc(50 * sizeof(char));
    scanf("%s", nuevaSucursal->nombre);
    printf("Ingrese dirección de la sucursal: ");
    nuevaSucursal->direccion = (char *)malloc(100 * sizeof(char));
    scanf("%s", nuevaSucursal->direccion);
    printf("Ingrese capacidad de almacenamiento de la sucursal: ");
    scanf("%d", &nuevaSucursal->capacidadAlmacenamiento);

    nuevaSucursal->productos = NULL;

    agregarSucursalConsole(farmacia, nuevoNodo);

    cls();
    printf("Sucursal agregada con éxito.\n");
    pause();
}

void eliminarSucursal(struct FarmaSalud *farmacia) {
    cls();
    int idEliminar;
    struct NodoSucursales *temp, *prev;

    // Pedir al usuario que ingrese el ID de la sucursal a eliminar
    printf("Ingrese el ID de la sucursal que desea eliminar: ");
    scanf("%d", &idEliminar);

    temp = farmacia->sucursales;
    if (temp == NULL) {
        printf("No hay sucursales registradas.\n");
        pause();
        return;
    }

    // Buscar la sucursal con el ID proporcionado
    do {
        if (temp->datosSucursal->id == idEliminar) {
            break;
        }
        temp = temp->sig;
    } while (temp != farmacia->sucursales);

    // Si no se encontró la sucursal con el ID proporcionado
    if (temp->datosSucursal->id != idEliminar) {
        cls();
        printf("Sucursal no encontrada.\n");
        pause();
        return;
    }

    // Manejar los casos especiales para el primer y último nodo
    if (temp->ant == temp && temp->sig == temp) {
        farmacia->sucursales = NULL;
    } else {
        prev = temp->ant;
        prev->sig = temp->sig;
        temp->sig->ant = prev;
        if (temp == farmacia->sucursales) {
            farmacia->sucursales = temp->sig;
        }
    }

    // Liberar la memoria asociada a la sucursal
    free(temp->datosSucursal->nombre);
    free(temp->datosSucursal->direccion);
    // Aquí podrías añadir código para liberar productos asociados si es necesario
    free(temp->datosSucursal);
    free(temp);

    cls();
    printf("Sucursal eliminada con éxito.\n");
    pause();
}


void menuPrincipal(struct FarmaSalud *farmacia) {
    int opcion;
    do {
        printf("\n--- FarmaSalud ---\n");
        printf("1. leerClientes\n");
        printf("2. crearCliente\n");
        printf("3. eliminarCliente\n");
        printf("4. agregarProductoACliente\n");
        printf("5. leerSucursales\n");
        printf("6. crearSucursal\n");
        printf("7. eliminarSucursal\n");
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
            case 4:
                agregarProductoACliente(farmacia);
                cls();
                break;
            case 5:
                leerSucursales(farmacia);
                cls();
                break;
            case 6:
                crearSucursal(farmacia);
                cls();
                break;
            case 7:
                eliminarSucursal(farmacia);
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

struct NodoProveedor* crearProveedorConsole(int id, const char* nombre, const char* direccion, const char* telefono) {
    struct NodoProveedor* nuevoProveedor = (struct NodoProveedor*)malloc(sizeof(struct NodoProveedor));
    if (nuevoProveedor == NULL) {
        fprintf(stderr, "Error al asignar memoria para el nuevo proveedor.\n");
        exit(1);
    }

    nuevoProveedor->datosProveedor = (struct Proveedor*)malloc(sizeof(struct Proveedor));
    if (nuevoProveedor->datosProveedor == NULL) {
        fprintf(stderr, "Error al asignar memoria para los datos del proveedor.\n");
        free(nuevoProveedor);
        exit(1);
    }

    nuevoProveedor->datosProveedor->id = id;
    nuevoProveedor->datosProveedor->nombre = strdup(nombre);
    nuevoProveedor->datosProveedor->direccion = strdup(direccion);
    nuevoProveedor->datosProveedor->telefono = strdup(telefono);
    nuevoProveedor->datosProveedor->productos = NULL;
    nuevoProveedor->ant = nuevoProveedor->sig = NULL;

    return nuevoProveedor;
}


void agregarProveedorConsole(struct FarmaSalud* farmacia, struct NodoProveedor* nuevoProveedor) {
    if (farmacia->proveedores == NULL) {
        // Crear el nodo fantasma
        farmacia->proveedores = (struct NodoProveedor*)malloc(sizeof(struct NodoProveedor));
        if (farmacia->proveedores == NULL) {
            fprintf(stderr, "Error al asignar memoria para el nodo fantasma de proveedores.\n");
            exit(1);
        }
        farmacia->proveedores->datosProveedor = NULL;
        farmacia->proveedores->ant = farmacia->proveedores->sig = farmacia->proveedores;
    }

    struct NodoProveedor* ultimo = farmacia->proveedores->ant;
    nuevoProveedor->sig = farmacia->proveedores;
    nuevoProveedor->ant = ultimo;
    ultimo->sig = nuevoProveedor;
    farmacia->proveedores->ant = nuevoProveedor;
}

int main() 
{
    struct FarmaSalud *farmacia;
    farmacia = (struct FarmaSalud *)malloc(sizeof(struct FarmaSalud));

    farmacia->clientes = NULL;
    farmacia->sucursales = NULL;
    farmacia->proveedores = NULL;

    struct Producto prod1 = {"001", "Producto A", "Descripcion A", "Categoria A", 100, "Proveedor A", "Lote A", "2023-12-31", 10, 0};
    struct Producto prod2 = {"002", "Producto B", "Descripcion B", "Categoria B", 200, "Proveedor B", "Lote B", "2024-12-31", 20, 1};
    struct Producto* compras1[] = {&prod1, &prod2};

    struct NodoClientes* cliente1 = crearClienteConsole(1, "11111111-1", 30, 1, compras1, 2);
    agregarClienteConsole(farmacia, cliente1);

    struct Producto prod3 = {"003", "Producto C", "Descripcion C", "Categoria C", 300, "Proveedor C", "Lote C", "2025-12-31", 30, 0};
    struct Producto prod4 = {"004", "Producto D", "Descripcion D", "Categoria D", 400, "Proveedor D", "Lote D", "2026-12-31", 40, 1};
    struct Producto* compras2[] = {&prod3, &prod4};

    struct NodoClientes* cliente2 = crearClienteConsole(2, "22222222-2", 25, 0, compras2, 2);
    agregarClienteConsole(farmacia, cliente2);

    struct NodoSucursales* sucursal1 = crearSucursalConsole(1, "Sucursal A", "Direccion A", 100);
    agregarSucursalConsole(farmacia, sucursal1);
    
    struct NodoSucursales* sucursal2 = crearSucursalConsole(2, "Sucursal B", "Direccion B", 200);
    agregarSucursalConsole(farmacia, sucursal2);

    struct NodoProveedor* proveedor1 = crearProveedorConsole(1, "Proveedor A", "Direccion A", "123456789");
    agregarProveedorConsole(farmacia, proveedor1);

    struct NodoProveedor* proveedor2 = crearProveedorConsole(2, "Proveedor B", "Direccion B", "987654321");
    agregarProveedorConsole(farmacia, proveedor2);

    while (1) {
        cls();
        menuPrincipal(farmacia);
    }

    return 0;
}
