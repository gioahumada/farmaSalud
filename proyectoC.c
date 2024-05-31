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

Paracetal - 20
Pañales -20

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

/* 

Prototipo Funciones 

*/

void imprimirSaltosDeLinea();

// Menus
void menuPrincipal(struct FarmaSalud *farmacia);
void menuAdmin(struct FarmaSalud *farmacia);
void menuCajero(struct FarmaSalud *farmacia);
void menuSucursal(struct FarmaSalud *farmacia);

// Console
struct NodoClientes* crearClienteConsole(int id, char* rutCliente, int edadCliente, int afiliado, char** comprasCliente);
void agregarClienteConsole(struct FarmaSalud *farmacia, struct NodoClientes *nuevoCliente);


// SuperSU
void agregarCliente(struct FarmaSalud *farmacia);
void agregarSucursal(struct FarmaSalud *farmacia);
void agregarProveedor(struct FarmaSalud *farmacia);
void eliminarCliente(struct FarmaSalud *farmacia);
void eliminarSucursal(struct FarmaSalud *farmacia); /* */
void eliminarProveedor(struct FarmaSalud *farmacia); /* */
void verTodosLosClientes(struct FarmaSalud *farmacia); 
void verTodasLasSucursales(struct FarmaSalud *farmacia);
void verTodosLosProductos(struct FarmaSalud *farmacia);
void agregarProducto(struct FarmaSalud *farmacia); /* */
void quitarProducto(struct FarmaSalud *farmacia);
void quitarProductosVencidos(struct FarmaSalud *farmacia); /* */

/* 

███╗   ███╗ █████╗ ██╗███╗   ██╗
████╗ ████║██╔══██╗██║████╗  ██║
██╔████╔██║███████║██║██╔██╗ ██║
██║╚██╔╝██║██╔══██║██║██║╚██╗██║
██║ ╚═╝ ██║██║  ██║██║██║ ╚████║
╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝

*/

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

    // Desplegar Menu
    menuPrincipal(farmacia);

    return 0;
}

/*

███╗   ███╗███████╗███╗   ██╗██╗   ██╗
████╗ ████║██╔════╝████╗  ██║██║   ██║
██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║
██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║
██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝
╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝

*/

void imprimirSaltosDeLinea() {
    int i;
    for(i = 0; i < 20; i++) printf("\n");
}

struct NodoClientes* crearClienteConsole(int id, char* rutCliente, int edadCliente, int afiliado, char** comprasCliente) {
    struct NodoClientes* nuevoNodo = (struct NodoClientes*)malloc(sizeof(struct NodoClientes));
    struct Clientes* nuevoCliente = (struct Clientes*)malloc(sizeof(struct Clientes));

    nuevoCliente->id = id;
    nuevoCliente->rutCliente = strdup(rutCliente);
    nuevoCliente->edadCliente = edadCliente;
    nuevoCliente->afiliado = afiliado;
    nuevoCliente->comprasCliente = comprasCliente;

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

/*

Menu

*/

void menuPrincipal(struct FarmaSalud *farmacia) {
    int opcion;
    do {
        printf("\n--- FarmaSalud ---\n");
        printf("1. Acceso Administrador\n");
        printf("2. Acceso Cajero\n");
        printf("3. Acceso Sucursal\n");
        printf("\n9. Salir\n");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Acceso Administrador
                imprimirSaltosDeLinea();
                menuAdmin(farmacia);
                break;
            case 2:
                // Acceso Cajero
                imprimirSaltosDeLinea();
                menuCajero(farmacia);
                break;
            case 3:
                // Acceso Sucursal
                imprimirSaltosDeLinea();
                menuSucursal(farmacia);
                break;
            case 9:
                imprimirSaltosDeLinea();
                printf("Saliendo...\n");
                break;
            default:
                imprimirSaltosDeLinea();
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 9);
}

void menuAdmin(struct FarmaSalud *farmacia) {
    int opcion;
    do {
        printf("\n--- Administrador ---\n\n");
        printf("1. Agregar Cliente\n");
        printf("2. Agregar Sucursal\n");
        printf("3. Agregar Proveedor\n");

        printf("4. Eliminar Cliente\n");
        printf("5. Eliminar Sucursal\n");
        printf("6. Eliminar Proveedor\n");

        printf("7. Ver TODOS los Clientes\n");
        printf("8. Ver TODAS las Sucursales\n");
        printf("9. Ver TODOS los Productos\n");

        printf("10. Agregar Producto\n");
        printf("11. Quitar Producto\n");

        printf("12. Quitar Productos Vencidos\n");
        printf("\n13. Salir\n");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Agregar Cliente
                imprimirSaltosDeLinea();
                agregarCliente(farmacia);
                break;
            case 2:
                // Agregar Sucursal
                imprimirSaltosDeLinea();
                agregarSucursal(farmacia);
                break;
            case 3:
                // Agregar Proveedor
                imprimirSaltosDeLinea();
                agregarProveedor(farmacia);
                break;
            case 4:
                // Eliminar Cliente
                imprimirSaltosDeLinea();
                eliminarCliente(farmacia);
                break;
            case 5:
                // Eliminar Sucursal
                imprimirSaltosDeLinea();
                eliminarSucursal(farmacia);
                break;
            case 6:
                // Eliminar Proveedor
                imprimirSaltosDeLinea();
                eliminarProveedor(farmacia);
                break;
            case 7:
                // Ver TODOS los Clientes
                imprimirSaltosDeLinea();
                verTodosLosClientes(farmacia);
                break;
            case 8:
                // Ver TODAS las Sucursales
                imprimirSaltosDeLinea();
                verTodasLasSucursales(farmacia);
                break;
            case 9:
                // Ver Todos los Productos
                imprimirSaltosDeLinea();
                verTodosLosProductos(farmacia);
                break;
            case 10:
                // Agregar Productos
                imprimirSaltosDeLinea();
                agregarProducto(farmacia);
                break;
            case 11:
                //Quitar Productos
                imprimirSaltosDeLinea();
                quitarProducto(farmacia);
                break;
            case 12:
                // Quitar Productos Vencidos
                imprimirSaltosDeLinea();
                quitarProductosVencidos(farmacia);
                break;
            case 13:
                imprimirSaltosDeLinea();
                printf("Volviendo al menu principal...\n");
                break;
            default:
                imprimirSaltosDeLinea();
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 13);
}

void menuCajero(struct FarmaSalud *farmacia) 
{
    int opcion;
    do 
    {
        printf("\n--- Sucursales ---\n");
        printf("1. Agregar Cliente\n");
        printf("2. Productos en stock\n");
        printf("3. Revisar Receta medica Cliente\n");
        printf("4. Revisar Receta medica Producto\n");
        printf("5. Historial de compras Cliente\n");
        printf("9. Volver\n");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) 
        {
            case 1:
                // Agregar Cliente
                imprimirSaltosDeLinea();
                break;
            case 2:
                // Productos en stock
                imprimirSaltosDeLinea();
                break;
            case 3:
                // Revisar Receta medica Cliente
                imprimirSaltosDeLinea();
                break;
            case 4:
                // Revisar Receta medica Producto
                imprimirSaltosDeLinea();
                break;
            case 5:
                // Historial de compras Cliente
                imprimirSaltosDeLinea();
                break;
            case 9:
                printf("\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 9);
}

void menuSucursal(struct FarmaSalud *farmacia) 
{
    int opcion;
    do 
    {
        printf("\n--- Sucursal ---\n");
        printf("1. Ver productos sucursal\n");
        printf("2. Nombrar productos Vencidos\n");
        printf("3. Quitar Productos Vencidos\n");
        printf("4. Estadisticas Sucursal\n");

        printf("9. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) 
        {
            case 1:
                // Ver productos sucursal
                imprimirSaltosDeLinea();
                break;
            case 2:
                // Nombrar productos Vencidos
                imprimirSaltosDeLinea();
                break;
            case 3:
                // Quitar Productos Vencidos
                imprimirSaltosDeLinea();
                break;
            case 4:
                // Estadisticas Sucursal
                imprimirSaltosDeLinea();
                break;
            case 9:
                printf("Volviendo al menu principal...\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 9);
}

/* 

███████╗██╗   ██╗███╗   ██╗ ██████╗
██╔════╝██║   ██║████╗  ██║██╔════╝
█████╗  ██║   ██║██╔██╗ ██║██║     
██╔══╝  ██║   ██║██║╚██╗██║██║     
██║     ╚██████╔╝██║ ╚████║╚██████╗
╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝

*/

void agregarCliente(struct FarmaSalud *farmacia) 
{
    struct NodoClientes *nuevoNodo = (struct NodoClientes *)malloc(sizeof(struct NodoClientes));
    nuevoNodo->datosClientes = (struct Clientes *)malloc(sizeof(struct Clientes));
    
    printf("Ingrese ID del cliente: ");
    scanf("%d", &nuevoNodo->datosClientes->id);
    printf("Ingrese RUT del cliente: ");
    nuevoNodo->datosClientes->rutCliente = (char *)malloc(20 * sizeof(char));
    scanf("%s", nuevoNodo->datosClientes->rutCliente);
    printf("Ingrese edad del cliente: ");
    scanf("%d", &nuevoNodo->datosClientes->edadCliente);
    printf("¿Es afiliado? (1-Si, 0-No): ");
    scanf("%d", &nuevoNodo->datosClientes->afiliado);
    
    // Inicializar comprasCliente
    nuevoNodo->datosClientes->comprasCliente = NULL;
    
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = farmacia->clientes;
    if (farmacia->clientes != NULL) 
    {
        farmacia->clientes->ant = nuevoNodo;
    }
    farmacia->clientes = nuevoNodo;
    
    printf("Cliente agregado con éxito.\n");
}

void agregarSucursal(struct FarmaSalud *farmacia) 
{
    struct NodoSucursales *nuevoNodo = (struct NodoSucursales *)malloc(sizeof(struct NodoSucursales));
    nuevoNodo->datosSucursal = (struct Sucursal *)malloc(sizeof(struct Sucursal));
    
    printf("Ingrese ID de la sucursal: ");
    scanf("%d", &nuevoNodo->datosSucursal->id);
    printf("Ingrese nombre de la sucursal: ");
    nuevoNodo->datosSucursal->nombre = (char *)malloc(50 * sizeof(char));
    scanf("%s", nuevoNodo->datosSucursal->nombre);
    printf("Ingrese dirección de la sucursal: ");
    nuevoNodo->datosSucursal->direccion = (char *)malloc(100 * sizeof(char));
    scanf("%s", nuevoNodo->datosSucursal->direccion);
    printf("Ingrese capacidad de almacenamiento de la sucursal: ");
    scanf("%d", &nuevoNodo->datosSucursal->capacidadAlmacenamiento);
    
    nuevoNodo->datosSucursal->productos = NULL;
    
    nuevoNodo->ant = farmacia->sucursales;
    nuevoNodo->sig = farmacia->sucursales->sig;
    farmacia->sucursales->sig = nuevoNodo;
    nuevoNodo->sig->ant = nuevoNodo;

    printf("Sucursal agregada con éxito.\n");
}

void agregarProveedor(struct FarmaSalud *farmacia) 
{
    struct NodoProveedor *nuevoNodo = (struct NodoProveedor *)malloc(sizeof(struct NodoProveedor));
    nuevoNodo->datosProveedor = (struct Proveedor *)malloc(sizeof(struct Proveedor));
    
    printf("Ingrese ID del proveedor: ");
    scanf("%d", &nuevoNodo->datosProveedor->id);
    printf("Ingrese nombre del proveedor: ");
    nuevoNodo->datosProveedor->nombre = (char *)malloc(50 * sizeof(char));
    scanf("%s", nuevoNodo->datosProveedor->nombre);
    printf("Ingrese dirección del proveedor: ");
    nuevoNodo->datosProveedor->direccion = (char *)malloc(100 * sizeof(char));
    scanf("%s", nuevoNodo->datosProveedor->direccion);
    printf("Ingrese teléfono del proveedor: ");
    nuevoNodo->datosProveedor->telefono = (char *)malloc(20 * sizeof(char));
    scanf("%s", nuevoNodo->datosProveedor->telefono);
    
    nuevoNodo->datosProveedor->productos = NULL;
    
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = farmacia->proveedores;
    if (farmacia->proveedores != NULL) 
    {
        farmacia->proveedores->ant = nuevoNodo;
    }
    farmacia->proveedores = nuevoNodo;
    
    printf("Proveedor agregado con éxito.\n");
}

void eliminarCliente(struct FarmaSalud *farmacia) 
{
    int id;
    printf("Ingrese ID del cliente a eliminar: ");
    scanf("%d", &id);
    
    struct NodoClientes *actual = farmacia->clientes;
    while (actual != NULL && actual->datosClientes->id != id) 
    {
        actual = actual->sig;
    }
    
    if (actual != NULL) 
    {
        if (actual->ant != NULL) 
        {
            actual->ant->sig = actual->sig;
        } else 
        {
            farmacia->clientes = actual->sig;
        }
        if (actual->sig != NULL)
        {
            actual->sig->ant = actual->ant;
        }
        free(actual->datosClientes->rutCliente);
        free(actual->datosClientes);
        free(actual);
        printf("Cliente eliminado con éxito.\n");
    } 
    else 
    {
        printf("Cliente no encontrado.\n");
    }
}

void verTodosLosClientes(struct FarmaSalud *farmacia)
{
    if (farmacia == NULL || farmacia->clientes == NULL) 
    {
        printf("\n--- La lista de clientes está vacía ---\n");
        return;
    }

    struct NodoClientes *actual = farmacia->clientes;
    printf("\n--- Lista de Clientes ---\n");
    while (actual != NULL) 
    {
        if (actual->datosClientes != NULL) 
        {
            printf("ID: %d\n", actual->datosClientes->id);
            printf("RUT: %s\n", actual->datosClientes->rutCliente);
            printf("Edad: %d\n", actual->datosClientes->edadCliente);
            printf("Afiliado: %d\n\n", actual->datosClientes->afiliado);
        }
        actual = actual->sig;
    }
}


void verTodasLasSucursales(struct FarmaSalud *farmacia) 
{
    struct NodoSucursales *actual = farmacia->sucursales->sig;
    printf("\n--- Lista de Sucursales ---\n");
    do 
    {
        printf("ID: %d\n", actual->datosSucursal->id);
        printf("Nombre: %s\n", actual->datosSucursal->nombre);
        printf("Dirección: %s\n", actual->datosSucursal->direccion);
        printf("Capacidad de Almacenamiento: %d\n\n", actual->datosSucursal->capacidadAlmacenamiento);
        actual = actual->sig;
    } while (actual != farmacia->sucursales);
}

void verTodosLosProductos(struct FarmaSalud *farmacia) 
{
    struct NodoSucursales *sucursal = farmacia->sucursales->sig;
    printf("\n--- Lista de Productos en Todas las Sucursales ---\n");
    do 
    {
        printf("Sucursal: %s\n", sucursal->datosSucursal->nombre);
        struct NodoProducto *producto = sucursal->datosSucursal->productos->sig;
        while (producto != sucursal->datosSucursal->productos) 
        {
            printf("Código: %s\n", producto->datosProducto->codigo);
            printf("Nombre: %s\n", producto->datosProducto->nombreProducto);
            printf("Descripción: %s\n", producto->datosProducto->descripcion);
            printf("Categoría: %s\n", producto->datosProducto->categoria);
            printf("Precio: %d\n", producto->datosProducto->precio);
            printf("Proveedor: %s\n", producto->datosProducto->nombreProveedor);
            printf("Lote: %s\n", producto->datosProducto->lote);
            printf("Fecha de Caducidad: %s\n", producto->datosProducto->fechaCaducidad);
            printf("Cantidad: %d\n", producto->datosProducto->cantidad);
            printf("Requiere Receta: %d\n\n", producto->datosProducto->requiereReceta);
            producto = producto->sig;
        }
        sucursal = sucursal->sig;
    } while (sucursal != farmacia->sucursales);
}

void quitarProductosVencidos(struct FarmaSalud *farmacia) 
{
    struct NodoSucursales *sucursal = farmacia->sucursales->sig;
    char fechaActual[11];
    printf("Ingrese la fecha actual (DD/MM/AAAA): ");
    scanf("%s", fechaActual);
    
    printf("\n--- Eliminando Productos Vencidos ---\n");
    do 
    {
        struct NodoProducto *producto = sucursal->datosSucursal->productos->sig;
        while (producto != sucursal->datosSucursal->productos) 
        {
            if (strcmp(producto->datosProducto->fechaCaducidad, fechaActual) < 0) 
            {
                struct NodoProducto *aEliminar = producto;
                if (producto->ant != NULL) 
                {
                    producto->ant->sig = producto->sig;
                } 
                else 
                {
                    sucursal->datosSucursal->productos = producto->sig;
                }
                if (producto->sig != NULL) 
                {
                    producto->sig->ant = producto->ant;
                }
                producto = producto->sig;
                free(aEliminar->datosProducto->nombreProducto);
                free(aEliminar->datosProducto->descripcion);
                free(aEliminar->datosProducto->categoria);
                free(aEliminar->datosProducto->nombreProveedor);
                free(aEliminar->datosProducto->lote);
                free(aEliminar->datosProducto->fechaCaducidad);
                free(aEliminar->datosProducto);
                free(aEliminar);
                printf("Producto vencido eliminado.\n");
            } 
            else 
            {
                producto = producto->sig;
            }
        }
        sucursal = sucursal->sig;
    } while (sucursal != farmacia->sucursales);
}


