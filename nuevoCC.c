/* 
To-do list:

* Funcion 12 preguntar el stock de cada producto a agregar para ser registrado en sucursal
* Crear Funcion para agregar un producto en especifico a una sucursal
* Crear Funcion que actualice el espacio de una sucursal
* Crear Funcion Estadisticas (sucursal con mas items, proveedor con mas items, etc etc)
* Crear Funcion para concretar ventas y que se le agregue a cliente, que de una boleta 
* Crear Funcion para quitar productos con vencimiento

*/



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
    char *idProveedor;
    char *lote;
    char *fechaCaducidad; // DD/MM/YYYY
    int cantidad;
    int requiereReceta;
};

/* ----------
    Derecha
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
    
    // Obtener y asignar automáticamente el ID basado en el último ID disponible
    int maxId = 0;
    struct NodoClientes *temp = farmacia->clientes;
    while (temp != NULL) {
        if (temp->datosClientes->id > maxId) {
            maxId = temp->datosClientes->id;
        }
        temp = temp->sig;
    }
    nuevoNodo->datosClientes->id = maxId + 1;
    
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
        temp = farmacia->clientes;
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
        free(temp->datosClientes->comprasCliente[i]->idProveedor);
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
    nuevoProducto->idProveedor = (char *)malloc(50 * sizeof(char));
    printf("Ingrese nombre del proveedor: ");
    scanf("%s", nuevoProducto->idProveedor);
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

int espacioRestante(struct Sucursal *sucursal) {
    if (sucursal == NULL) {
        return -1;
    }

    int totalProductos = 0;
    struct NodoProducto *nodoActual = sucursal->productos;

    while (nodoActual != NULL) {
        totalProductos += nodoActual->datosProducto->cantidad;
        nodoActual = nodoActual->sig;
    }
    int espacioRestante = 100000 - totalProductos;
    return espacioRestante;
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


        if (nodoActual->datosSucursal->productos != NULL) {
            printf("Productos:\n");
            struct NodoProducto *productoNodo = nodoActual->datosSucursal->productos;
            while (productoNodo != NULL) {
                printf("\t%s - %s\n", productoNodo->datosProducto->codigo, productoNodo->datosProducto->nombreProducto);
                productoNodo = productoNodo->sig;
            }
            printf("\n");
        } else {
            printf("Sucursal sin productos\n");
        }


        int espacio = espacioRestante(nodoActual->datosSucursal);
        printf("Espacio restante en la sucursal: %d\n\n", espacio);

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

struct NodoProveedor* crearProveedorConsole(int id, char* nombre, char* direccion, char* telefono) {
    struct NodoProveedor* nuevoNodo = (struct NodoProveedor*)malloc(sizeof(struct NodoProveedor));
    struct Proveedor* nuevoProveedor = (struct Proveedor*)malloc(sizeof(struct Proveedor));

    nuevoProveedor->id = id;
    nuevoProveedor->nombre = strdup(nombre);
    nuevoProveedor->direccion = strdup(direccion);
    nuevoProveedor->telefono = strdup(telefono);
    nuevoProveedor->productos = NULL;

    nuevoNodo->datosProveedor = nuevoProveedor;
    nuevoNodo->ant = nuevoNodo->sig = NULL;

    return nuevoNodo;
}

void agregarProveedorConsole(struct FarmaSalud *farmacia, struct NodoProveedor *nuevoProveedor) {
    if (farmacia->proveedores == NULL) {
        farmacia->proveedores = nuevoProveedor;
    } else {
        struct NodoProveedor *temp = farmacia->proveedores;
        while (temp->sig != NULL) {
            temp = temp->sig;
        }
        temp->sig = nuevoProveedor;
        nuevoProveedor->ant = temp;
    }
}

void mostrarProductosProveedor(struct NodoArbolProducto *nodoProducto) {
    char *requiereReceta;

    if (nodoProducto == NULL) {
        return;
    }

    mostrarProductosProveedor(nodoProducto->izq);

    struct Producto *producto = nodoProducto->datosProducto;
    if (producto->requiereReceta) {
        requiereReceta = "Sí";
    } else {
        requiereReceta = "No";
    }
    printf("  - Código: %s\t", producto->codigo);
    printf("Nombre: %s\t", producto->nombreProducto);
    printf("Descripción: %s\t", producto->descripcion);
    printf("Precio: %d\t", producto->precio);
    printf("Requiere Receta: %s\n", requiereReceta);

    mostrarProductosProveedor(nodoProducto->der);
}

void leerProveedores(struct FarmaSalud *farmacia) {
    cls();
    struct NodoProveedor *nodoActual = farmacia->proveedores;
    if (nodoActual == NULL) {
        printf("No hay proveedores registrados.\n");
        pause();
        return;
    }

    while (nodoActual != NULL) {
        printf("ID: %d\n", nodoActual->datosProveedor->id);
        printf("Nombre: %s\n", nodoActual->datosProveedor->nombre);
        printf("Dirección: %s\n", nodoActual->datosProveedor->direccion);
        printf("Teléfono: %s\n", nodoActual->datosProveedor->telefono);

        // Mostrar productos del proveedor
        if (nodoActual->datosProveedor->productos == NULL) {
            printf("No hay productos asociados a este proveedor.\n\n");
        } else {
            printf("Productos:\n\n");
            mostrarProductosProveedor(nodoActual->datosProveedor->productos);
        }

        nodoActual = nodoActual->sig;
    }
    pause();
}

void crearProveedor(struct FarmaSalud *farmacia) {
    cls();
    struct NodoProveedor *nuevoNodo = (struct NodoProveedor*)malloc(sizeof(struct NodoProveedor));
    struct Proveedor *nuevoProveedor = (struct Proveedor*)malloc(sizeof(struct Proveedor));

    nuevoNodo->datosProveedor = nuevoProveedor;
    nuevoNodo->ant = nuevoNodo->sig = NULL;

    printf("Ingrese ID del proveedor: ");
    scanf("%d", &nuevoProveedor->id);
    getchar();  // Consumir el salto de línea que queda en el buffer

    printf("Ingrese nombre del proveedor: ");
    nuevoProveedor->nombre = (char *)malloc(50 * sizeof(char));
    fgets(nuevoProveedor->nombre, 50, stdin);
    nuevoProveedor->nombre[strcspn(nuevoProveedor->nombre, "\n")] = 0;  // Eliminar el salto de línea

    printf("Ingrese dirección del proveedor: ");
    nuevoProveedor->direccion = (char *)malloc(100 * sizeof(char));
    fgets(nuevoProveedor->direccion, 100, stdin);
    nuevoProveedor->direccion[strcspn(nuevoProveedor->direccion, "\n")] = 0;  // Eliminar el salto de línea

    printf("Ingrese teléfono del proveedor: ");
    nuevoProveedor->telefono = (char *)malloc(15 * sizeof(char));
    fgets(nuevoProveedor->telefono, 15, stdin);
    nuevoProveedor->telefono[strcspn(nuevoProveedor->telefono, "\n")] = 0;  // Eliminar el salto de línea

    nuevoProveedor->productos = NULL;

    agregarProveedorConsole(farmacia, nuevoNodo);

    cls();
    printf("Proveedor agregado con éxito.\n");
    pause();
}

void eliminarProveedor(struct FarmaSalud *farmacia) {
    cls();
    int idEliminar;
    struct NodoProveedor *temp, *prev;

    // Pedir al usuario que ingrese el ID del proveedor a eliminar
    printf("Ingrese el ID del proveedor que desea eliminar: ");
    scanf("%d", &idEliminar);

    temp = farmacia->proveedores;
    prev = NULL;

    // Buscar el proveedor con el ID proporcionado
    while (temp != NULL && temp->datosProveedor->id != idEliminar) {
        prev = temp;
        temp = temp->sig;
    }

    // Si no se encontró el proveedor con el ID proporcionado
    if (temp == NULL) {
        cls();
        printf("Proveedor no encontrado.\n");
        pause();
        return;
    }

    // Manejar los casos especiales para el primer y último nodo
    if (prev == NULL) {
        farmacia->proveedores = temp->sig;
    } else {
        prev->sig = temp->sig;
    }
    if (temp->sig != NULL) {
        temp->sig->ant = prev;
    }

    // Liberar la memoria asociada al proveedor
    free(temp->datosProveedor->nombre);
    free(temp->datosProveedor->direccion);
    free(temp->datosProveedor->telefono);
    free(temp->datosProveedor);
    free(temp);

    cls();
    printf("Proveedor eliminado con éxito.\n");
    pause();
}

void agregarProductoProveedor(struct FarmaSalud *farmacia) {
    cls();

    // Crear y llenar los datos del nuevo producto
    struct Producto *nuevoProducto = (struct Producto *)malloc(sizeof(struct Producto));
    printf("Ingrese código del producto: ");
    scanf("%s", nuevoProducto->codigo);
    getchar(); // Para consumir el '\n' que queda en el buffer después de scanf
    nuevoProducto->nombreProducto = (char *)malloc(50 * sizeof(char));
    cls();
    printf("Ingrese nombre del producto: ");
    fgets(nuevoProducto->nombreProducto, 50, stdin);
    nuevoProducto->descripcion = (char *)malloc(100 * sizeof(char));
    cls();
    printf("Ingrese descripción del producto: ");
    fgets(nuevoProducto->descripcion, 100, stdin);
    nuevoProducto->categoria = (char *)malloc(50 * sizeof(char));
    cls();
    printf("Ingrese categoría del producto: ");
    fgets(nuevoProducto->categoria, 50, stdin);
    cls();
    printf("Ingrese precio del producto: ");
    scanf("%d", &nuevoProducto->precio);
    getchar(); // Para consumir el '\n' que queda en el buffer después de scanf

    // Mostrar todos los proveedores disponibles
    struct NodoProveedor *proveedorActual = farmacia->proveedores;
    cls();
    printf("Proveedores disponibles:\n");
    while (proveedorActual != NULL) {
        printf("ID: %d, Nombre: %s\n", proveedorActual->datosProveedor->id, proveedorActual->datosProveedor->nombre);
        proveedorActual = proveedorActual->sig;
    }

    // Solicitar el ID del proveedor durante la creación del producto
    nuevoProducto->idProveedor = (char *)malloc(20 * sizeof(char));
    printf("\nIngrese ID del proveedor: ");
    scanf("%s", nuevoProducto->idProveedor);

    cls();
    // Asignar "N/A" a lote y fechaCaducidad, no preguntar al usuario
    nuevoProducto->lote = strdup("N/A");
    nuevoProducto->fechaCaducidad = strdup("N/A");

    // No preguntar por cantidad, asignar -1 para indicar que es un producto del proveedor
    nuevoProducto->cantidad = -1;

    cls();
    printf("¿Requiere receta? (1-Sí, 0-No): ");
    scanf("%d", &nuevoProducto->requiereReceta);

    // Convertir idProveedor de char* a int
    int idProveedorInt = atoi(nuevoProducto->idProveedor);

    // Buscar el proveedor por ID
    proveedorActual = farmacia->proveedores;
    while (proveedorActual != NULL && proveedorActual->datosProveedor->id != idProveedorInt) {
        proveedorActual = proveedorActual->sig;
    }

    if (proveedorActual == NULL) {
        printf("Proveedor no encontrado.\n");
        // Liberar memoria asignada al nuevo producto si el proveedor no se encuentra
        free(nuevoProducto->nombreProducto);
        free(nuevoProducto->descripcion);
        free(nuevoProducto->categoria);
        free(nuevoProducto->idProveedor);
        free(nuevoProducto->lote);
        free(nuevoProducto->fechaCaducidad);
        free(nuevoProducto);
        pause();
        return;
    }

    // Crear un nuevo nodo para el producto
    struct NodoArbolProducto *nuevoNodoProducto = (struct NodoArbolProducto *)malloc(sizeof(struct NodoArbolProducto));
    nuevoNodoProducto->datosProducto = nuevoProducto;
    nuevoNodoProducto->izq = nuevoNodoProducto->der = NULL;

    // Insertar el nuevo nodo en el árbol de productos del proveedor
    if (proveedorActual->datosProveedor->productos == NULL) {
        proveedorActual->datosProveedor->productos = nuevoNodoProducto;
    } else {
        struct NodoArbolProducto *actualProducto = proveedorActual->datosProveedor->productos;
        struct NodoArbolProducto *padreProducto = NULL;

        while (actualProducto != NULL) {
            padreProducto = actualProducto;
            if (strcmp(nuevoProducto->codigo, actualProducto->datosProducto->codigo) < 0) {
                actualProducto = actualProducto->izq;
            } else {
                actualProducto = actualProducto->der;
            }
        }

        if (strcmp(nuevoProducto->codigo, padreProducto->datosProducto->codigo) < 0) {
            padreProducto->izq = nuevoNodoProducto;
        } else {
            padreProducto->der = nuevoNodoProducto;
        }
    }

    cls();
    printf("Producto agregado con éxito al proveedor.\n");
    pause();
}

struct Producto* crearProductoFalso(char* codigo, char* nombre, char* descripcion, char* categoria, int precio, char* idProveedor, char* lote, char* fechaCaducidad, int cantidad, int requiereReceta) {
    struct Producto* nuevoProducto = (struct Producto*)malloc(sizeof(struct Producto));

    strcpy(nuevoProducto->codigo, codigo);
    nuevoProducto->nombreProducto = strdup(nombre);
    nuevoProducto->descripcion = strdup(descripcion);
    nuevoProducto->categoria = strdup(categoria);
    nuevoProducto->precio = precio;
    nuevoProducto->idProveedor = strdup(idProveedor);
    nuevoProducto->lote = strdup(lote);
    nuevoProducto->fechaCaducidad = strdup(fechaCaducidad);
    nuevoProducto->cantidad = cantidad;
    nuevoProducto->requiereReceta = requiereReceta;

    return nuevoProducto;
}

// Nueva función para agregar producto a un proveedor específico
void agregarProductoAProveedor(struct Proveedor* proveedor, struct Producto* producto) {
    struct NodoArbolProducto* nuevoNodo = (struct NodoArbolProducto*)malloc(sizeof(struct NodoArbolProducto));
    nuevoNodo->datosProducto = producto;
    nuevoNodo->izq = nuevoNodo->der = NULL;

    if (proveedor->productos == NULL) {
        proveedor->productos = nuevoNodo;
    } else {
        struct NodoArbolProducto* actual = proveedor->productos;
        struct NodoArbolProducto* padre = NULL;

        while (actual != NULL) {
            padre = actual;
            if (strcmp(producto->codigo, actual->datosProducto->codigo) < 0) {
                actual = actual->izq;
            } else {
                actual = actual->der;
            }
        }

        if (strcmp(producto->codigo, padre->datosProducto->codigo) < 0) {
            padre->izq = nuevoNodo;
        } else {
            padre->der = nuevoNodo;
        }
    }
}

struct NodoProveedor* buscarProveedorPorID(struct FarmaSalud *farmacia, int idProveedor) {
    struct NodoProveedor *proveedorActual = farmacia->proveedores;
    while (proveedorActual != NULL && proveedorActual->datosProveedor->id != idProveedor) {
        proveedorActual = proveedorActual->sig;
    }
    return proveedorActual;
}

struct NodoSucursales* buscarSucursalPorID(struct FarmaSalud *farmacia, int idSucursal) {
    struct NodoSucursales *sucursalActual = farmacia->sucursales;
    if (sucursalActual == NULL) {
        return NULL;
    }

    struct NodoSucursales *inicio = sucursalActual;
    do {
        if (sucursalActual->datosSucursal->id == idSucursal) {
            return sucursalActual;
        }
        sucursalActual = sucursalActual->sig;
    } while (sucursalActual != inicio);

    return NULL;
}

void transferirProductos(struct NodoArbolProducto *nodoProducto, struct NodoSucursales *sucursalActual) {
    if (nodoProducto == NULL) {
        return;
    }

    // Recursivamente transferir los productos de los subárboles izquierdo y derecho
    transferirProductos(nodoProducto->izq, sucursalActual);
    transferirProductos(nodoProducto->der, sucursalActual);

    // Crear un nodo de producto para la sucursal
    struct NodoProducto *nuevoNodoProducto = (struct NodoProducto *)malloc(sizeof(struct NodoProducto));
    nuevoNodoProducto->datosProducto = nodoProducto->datosProducto;
    nuevoNodoProducto->ant = nuevoNodoProducto->sig = NULL;

    // Agregar el producto a la lista de productos de la sucursal
    if (sucursalActual->datosSucursal->productos == NULL) {
        sucursalActual->datosSucursal->productos = nuevoNodoProducto;
    } else {
        struct NodoProducto *temp = sucursalActual->datosSucursal->productos;
        while (temp->sig != NULL) {
            temp = temp->sig;
        }
        temp->sig = nuevoNodoProducto;
        nuevoNodoProducto->ant = temp;
    }
}

void actualizarInventario(struct NodoSucursales *sucursal) {
    struct NodoProducto *productoActual = sucursal->datosSucursal->productos;

    // Recorrer la lista de productos
    while (productoActual != NULL) {
        // Actualizar la cantidad del producto
        productoActual->datosProducto->cantidad += 1;

        // Ir al siguiente producto
        productoActual = productoActual->sig;
    }

    printf("Inventario de la sucursal con ID %d actualizado.\n", sucursal->datosSucursal->id);
}

void transferirProductosProveedorASucursal(struct FarmaSalud *farmacia) {
    int idProveedor, idSucursal;

    printf("Ingrese el ID del proveedor: ");
    scanf("%d", &idProveedor);

    // Buscar el proveedor por ID
    struct NodoProveedor *proveedorActual = buscarProveedorPorID(farmacia, idProveedor);
    if (proveedorActual == NULL) {
        printf("Proveedor con ID %d no encontrado.\n", idProveedor);
        return;
    }

    printf("Ingrese el ID de la sucursal: ");
    scanf("%d", &idSucursal);

    // Buscar la sucursal por ID
    struct NodoSucursales *sucursalActual = buscarSucursalPorID(farmacia, idSucursal);
    if (sucursalActual == NULL) {
        printf("Sucursal con ID %d no encontrada.\n", idSucursal);
        return;
    }

    // Transferir productos del proveedor a la sucursal
    transferirProductos(proveedorActual->datosProveedor->productos, sucursalActual);

    // Actualizar el inventario de la sucursal
    actualizarInventario(sucursalActual);

    printf("Productos transferidos del proveedor con ID %d a la sucursal con ID %d.\n", idProveedor, idSucursal);

    pause();
    cls();
}

struct Producto *buscarProductoPorCodigo(struct NodoProveedor *proveedor, char *codigoProducto) {
    struct NodoProducto *productoActual = proveedor->datosProveedor->productos;

    // Recorrer la lista de productos
    while (productoActual != NULL) {
        if (strcmp(productoActual->datosProducto->codigo, codigoProducto) == 0) {
            // Si el producto con el código dado se encuentra, devolver el producto
            return productoActual->datosProducto;
        }
        productoActual = productoActual->sig;
    }

    // Si el producto con el código dado no se encuentra, devolver NULL
    return NULL;
}

void agregarProducto(struct Producto *producto, struct NodoSucursales *sucursal) {
    // Buscar el producto en la lista de productos de la sucursal
    struct NodoProducto *productoActual = sucursal->datosSucursal->productos;
    while (productoActual != NULL) {
        if (strcmp(productoActual->datosProducto->codigo, producto->codigo) == 0) {
            // Si el producto ya existe en la lista, incrementar su cantidad
            productoActual->datosProducto->cantidad += 1;
            printf("Cantidad del producto con codigo %s incrementada en la sucursal con ID %d.\n", producto->codigo, sucursal->datosSucursal->id);
            return;
        }
        productoActual = productoActual->sig;
    }

    // Si el producto no existe en la lista, agregarlo a la lista
    struct NodoProducto *nuevoProducto = (struct NodoProducto *)malloc(sizeof(struct NodoProducto));
    nuevoProducto->datosProducto = producto;
    nuevoProducto->sig = NULL;

    if (sucursal->datosSucursal->productos == NULL) {
        // Si la lista de productos está vacía, hacer que el nuevo producto sea el primer nodo
        sucursal->datosSucursal->productos = nuevoProducto;
    } else {
        // Si la lista de productos no está vacía, agregar el nuevo producto al final de la lista
        productoActual = sucursal->datosSucursal->productos;
        while (productoActual->sig != NULL) {
            productoActual = productoActual->sig;
        }
        productoActual->sig = nuevoProducto;
    }

    printf("Producto con codigo %s agregado a la sucursal con ID %d.\n", producto->codigo, sucursal->datosSucursal->id);
}


void agregarProductoEspecificoASucursalDesdeProveedor(struct FarmaSalud *farmacia) {
    int idProveedor, idSucursal;
    char codigoProducto[10];
    struct NodoProveedor *proveedorActual;
    struct Producto *productoActual;
    struct NodoSucursales *sucursalActual;

    do {
        printf("Ingrese el ID del proveedor: ");
        scanf("%d", &idProveedor);

        // Buscar el proveedor por ID
        proveedorActual = buscarProveedorPorID(farmacia, idProveedor);
        if (proveedorActual == NULL) {
            printf("Proveedor con ID %d no encontrado. Por favor, ingrese un ID valido.\n", idProveedor);
        }
    } while (proveedorActual == NULL);

    do {
        printf("Ingrese el codigo del producto: ");
        scanf("%s", codigoProducto);

        // Buscar el producto por codigo
        productoActual = buscarProductoPorCodigo(proveedorActual, codigoProducto);
        if (productoActual == NULL) {
            printf("Producto con codigo %s no encontrado en el proveedor con ID %d. Por favor, ingrese un codigo valido.\n", codigoProducto, idProveedor);
        }
    } while (productoActual == NULL);

    do {
        printf("Ingrese el ID de la sucursal: ");
        scanf("%d", &idSucursal);

        // Buscar la sucursal por ID
        sucursalActual = buscarSucursalPorID(farmacia, idSucursal);
        if (sucursalActual == NULL) {
            printf("Sucursal con ID %d no encontrada. Por favor, ingrese un ID valido.\n", idSucursal);
        }
    } while (sucursalActual == NULL);

    // Agregar producto a la sucursal
    agregarProducto(productoActual, sucursalActual);


    printf("Producto con codigo %s transferido del proveedor con ID %d a la sucursal con ID %d.\n", codigoProducto, idProveedor, idSucursal);

    pause();
    cls();
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
        printf("8. crearProveedor\n");
        printf("9. leerProveedor\n");
        printf("10. eliminarProveedor\n");
        printf("11. agregarProductoProveedor\n");
        printf("12. transferirProductosProveedorASucursal\n");
        printf("13. agregarProductoASucursal");

        printf("\n14. Salir\n");
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
            case 8:
                crearProveedor(farmacia);
                cls();
                break;
            case 9:
                leerProveedores(farmacia);
                cls();
                break;
            case 10:
                eliminarProveedor(farmacia);
                cls();
                break;
            case 11:
                agregarProductoProveedor(farmacia);
                cls();
                break;
            case 12:
                transferirProductosProveedorASucursal(farmacia);
                cls();
                break;
            case 13:
                agregarProductoEspecificoASucursalDesdeProveedor(farmacia);
                cls();
                break;  
            case 14:
                printf("Saliendo...\n");
                exit(0);
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 13);
}



int main() 
{
    struct FarmaSalud *farmacia;
    farmacia = (struct FarmaSalud *)malloc(sizeof(struct FarmaSalud));

    farmacia->clientes = NULL;
    farmacia->sucursales = NULL;
    farmacia->proveedores = NULL;

    struct Producto prod1 = {"001", "Ibuprofeno", "Recomendado para el dolor de garganta", "Anti-inflamatorio", 100, "Bioequivalente", "Lote A", "2023-12-31", 10, 0};
    struct Producto prod2 = {"002", "Condones", "Ultra resistente y ultra delgado", "Anticonceptivo", 200, "Condoneria Nacional", "Lote B", "2024-12-31", 20, 1};
    struct Producto* compras1[] = {&prod1, &prod2};

    struct NodoClientes* cliente1 = crearClienteConsole(1, "8032837-5", 25, 1, compras1, 2);
    agregarClienteConsole(farmacia, cliente1);

    struct Producto prod3 = {"003", "Paracetamol", "Recomendado para el dolor de cabeza", "Analgesico", 300, "Lab. de Chile", "Lote C", "2025-12-31", 30, 0};
    struct Producto prod4 = {"004", "Tapsin", "Perfecto Para los resfriados", "Analgésico", 400, "Tapsin Chile", "Lote D", "2026-12-31", 40, 1};
    struct Producto* compras2[] = {&prod3, &prod4};

    struct NodoClientes* cliente2 = crearClienteConsole(2, "22222222-2", 25, 0, compras2, 2);
    agregarClienteConsole(farmacia, cliente2);

    struct NodoSucursales* sucursal1 = crearSucursalConsole(1, "Kennedy", "Apoquindo 234, Santiago", 100);
    agregarSucursalConsole(farmacia, sucursal1);
    
    struct NodoSucursales* sucursal2 = crearSucursalConsole(2, "Los Heroes", "Metro Pedro de Valdivia, Santiago", 200);
    agregarSucursalConsole(farmacia, sucursal2);

    struct NodoProveedor* proveedor1 = crearProveedorConsole(1, "Lab. de Chile", "Av. Marathon 1315", "90322000-7");
    agregarProveedorConsole(farmacia, proveedor1);

    struct NodoProveedor* proveedor2 = crearProveedorConsole(2, "Lab. Maver", "Las Encinas 1777", "98765432-1");
    agregarProveedorConsole(farmacia, proveedor2);

    struct Producto* producto1 = crearProductoFalso("001", "Producto1", "Descripcion del Producto 1", "Categoría1", 1000, "Lab. de Chile", "Lote1", "01/01/2025", 50, 0);
    struct Producto* producto2 = crearProductoFalso("002", "Producto2", "Descripcion del Producto 2", "Categoría2", 2000, "Lab. de Chile", "Lote2", "01/01/2026", 30, 1);
    struct Producto* producto3 = crearProductoFalso("003", "Producto3", "Descripcion del Producto 3", "Categoría3", 1500, "Lab. Maver", "Lote3", "01/01/2027", 20, 0);
    struct Producto* producto4 = crearProductoFalso("004", "Producto4", "Descripcion del Producto 4", "Categoría4", 2500, "Lab. Maver", "Lote4", "01/01/2028", 10, 1);

    agregarProductoAProveedor(proveedor1->datosProveedor, producto1);
    agregarProductoAProveedor(proveedor1->datosProveedor, producto2);
    agregarProductoAProveedor(proveedor2->datosProveedor, producto3);
    agregarProductoAProveedor(proveedor2->datosProveedor, producto4);
    
    while (1) {
        cls();
        menuPrincipal(farmacia);
    }

    return 0;
}
