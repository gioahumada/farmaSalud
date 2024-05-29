#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Producto {
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

struct NodoProducto {
    struct Producto *datosProducto;
    struct NodoProducto *ant, *sig;
};

struct Sucursal {
    int id;
    char *nombre;
    char *direccion;
    int capacidadAlmacenamiento;
    struct NodoProducto *productos;
};

struct NodoSucursales {
    struct Sucursal *datosSucursal;
    struct NodoSucursales *ant, *sig;
};

struct Clientes {
    int id;
    char *rutCliente;
    int edadCliente; 
    int afiliado;
    char **comprasCliente; 
};

struct NodoClientes {
    struct Clientes *datosClientes;
    struct NodoClientes *ant, *sig;
};

struct Proveedor {
    int id;
    char *nombre;
    char *direccion;
    char *telefono;
    struct NodoArbolProducto *productos;
};

struct NodoProveedor {
    struct Proveedor *datosProveedor;
    struct NodoProveedor *ant, *sig;
};

struct NodoArbolProducto {
    struct Producto *datosProducto;
    struct NodoArbolProducto *izq, *der;
};

struct FarmaSalud {
    struct NodoClientes *clientes;
    struct NodoSucursales *sucursales;
    struct NodoProveedor *proveedores;
};

// Prototipos de funciones
void imprimirSaltosDeLinea();

// Menus
void menuPrincipal(struct FarmaSalud *farmacia);
void menuClientes(struct FarmaSalud *farmacia);
void menuSucursales(struct FarmaSalud *farmacia);
void menuProveedores(struct FarmaSalud *farmacia);

// Agregar 
void agregarCliente(struct FarmaSalud *farmacia, int id, char *rut, int edad, int afiliado, char **compras);
void agregarProveedor(struct FarmaSalud *farmacia, int id, char *nombre, char *direccion, char *telefono);
void agregarSucursal(struct FarmaSalud *farmacia, int id, char *nombre, char *direccion, int capacidad);

void identificarCliente(struct FarmaSalud *farmacia);
void verComprasCliente(struct FarmaSalud *farmacia);
void eliminarHistorialCliente(struct FarmaSalud *farmacia);

/* 

███╗   ███╗ █████╗ ██╗███╗   ██╗
████╗ ████║██╔══██╗██║████╗  ██║
██╔████╔██║███████║██║██╔██╗ ██║
██║╚██╔╝██║██╔══██║██║██║╚██╗██║
██║ ╚═╝ ██║██║  ██║██║██║ ╚████║
╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝

*/

int main() {
    struct FarmaSalud farmacia;

    char *comprasCliente1[] = {"Producto1", "Producto2", NULL};
    agregarCliente(&farmacia, 1, "12345678-9", 30, 1, comprasCliente1);

    char *comprasCliente2[] = {"Producto3", "Producto4", NULL};
    agregarCliente(&farmacia, 2, "98765432-1", 25, 0, comprasCliente2);

    // Agregar proveedores
    agregarProveedor(&farmacia, 1, "Proveedor1", "Direccion1", "Telefono1");
    agregarProveedor(&farmacia, 2, "Proveedor2", "Direccion2", "Telefono2");

    // Agregar sucursales
    agregarSucursal(&farmacia, 1, "Sucursal1", "Direccion Sucursal1", 100);
    agregarSucursal(&farmacia, 2, "Sucursal2", "Direccion Sucursal2", 200);

    // Desplegar Menu
    menuPrincipal(&farmacia);

    return 0;
}

/* 

███████╗██╗   ██╗███╗   ██╗ ██████╗
██╔════╝██║   ██║████╗  ██║██╔════╝
█████╗  ██║   ██║██╔██╗ ██║██║     
██╔══╝  ██║   ██║██║╚██╗██║██║     
██║     ╚██████╔╝██║ ╚████║╚██████╗
╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝
                                   
*/

void imprimirSaltosDeLinea() {
    int i;
    for(i = 0;i<20;i++) printf("\n");
}

/*

            Menu 

*/

void menuPrincipal(struct FarmaSalud *farmacia) {
    int opcion;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Clientes\n");
        printf("2. Sucursales\n");
        printf("3. Proveedores\n");
        printf("4. Analisis de datos\n");
        printf("9. Salir\n");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                imprimirSaltosDeLinea();
                menuClientes(farmacia);
                break;
            case 2:
                imprimirSaltosDeLinea();
                menuSucursales(farmacia);
                break;
            case 3:
                imprimirSaltosDeLinea();
                menuProveedores(farmacia);
                break;
            case 4:
                imprimirSaltosDeLinea();
                // Analisis de datos no implementado
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

void menuClientes(struct FarmaSalud *farmacia) {
    int opcion;
    do {
        printf("\n--- Clientes ---\n\n");
        printf("1. Identificar Cliente\n");
        printf("2. Ver Compras Cliente\n");
        printf("3. Eliminar Historial Cliente\n");
        printf("9. Volver\n");
        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                imprimirSaltosDeLinea();
                identificarCliente(farmacia);
                break;
            case 2:
                imprimirSaltosDeLinea();
                // Ver Compras Cliente
                break;
            case 3:
                imprimirSaltosDeLinea();
                // Eliminar Historial Cliente
                break;
            case 9:
                imprimirSaltosDeLinea();
                printf("Volviendo al menu principal...\n");
                break;
            default:
                imprimirSaltosDeLinea();
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 9);
}

void menuSucursales(struct FarmaSalud *farmacia) {
    int opcion;
    do {
        printf("\n--- Sucursales ---\n");
        printf("1. Buscar Sucursal por nombre\n");
        printf("2. Ventas Sucursal\n");
        printf("3. Ver inventario de una Sucursal\n");
        printf("4. Actualizar Catalogo Sucursales\n");
        printf("5. Eliminar Productos Vencidos\n");
        printf("9. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Buscar Sucursal por nombre
                break;
            case 2:
                // Ventas Sucursal
                break;
            case 3:
                // Ver inventario de una Sucursal
                break;
            case 4:
                // Actualizar Catalogo Sucursales
                break;
            case 5:
                // Eliminar Productos Vencidos
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

void menuProveedores(struct FarmaSalud *farmacia) {
    int opcion;
    do {
        printf("\n--- Proveedores ---\n");
        printf("1. Buscar Proveedores\n");
        printf("2. Ver Productos de Proveedores\n");
        printf("9. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Buscar Proveedores
                break;
            case 2:
                // Ver Productos de Proveedores
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

        Funcionamiento

*/

void identificarCliente(struct FarmaSalud *farmacia) {
    char rut[20];
    printf("Ingrese el RUT del cliente: ");
    scanf("%s", rut);

    struct NodoClientes *actual = farmacia->clientes;
    while (actual != NULL) {
        if (strcmp(actual->datosClientes->rutCliente, rut) == 0) {
            printf("Cliente encontrado:\n");
            printf("ID: %d\n", actual->datosClientes->id);
            printf("RUT: %s\n", actual->datosClientes->rutCliente);
            printf("Edad: %d\n", actual->datosClientes->edadCliente);
            printf("Afiliado: %d\n", actual->datosClientes->afiliado);
            return;
        }
        actual = actual->sig;
    }
    printf("Cliente no encontrado.\n");
}

void agregarCliente(struct FarmaSalud *farmacia, int id, char *rut, int edad, int afiliado, char **compras) {
    struct NodoClientes *nuevoNodo = (struct NodoClientes*)malloc(sizeof(struct NodoClientes));
    nuevoNodo->datosClientes = (struct Clientes*)malloc(sizeof(struct Clientes));
    nuevoNodo->datosClientes->id = id;
    nuevoNodo->datosClientes->rutCliente = strdup(rut);
    nuevoNodo->datosClientes->edadCliente = edad;
    nuevoNodo->datosClientes->afiliado = afiliado;
    nuevoNodo->datosClientes->comprasCliente = compras;
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = farmacia->clientes;
    if (farmacia->clientes != NULL) {
        farmacia->clientes->ant = nuevoNodo;
    }
    farmacia->clientes = nuevoNodo;
}

void agregarProveedor(struct FarmaSalud *farmacia, int id, char *nombre, char *direccion, char *telefono) {
    struct NodoProveedor *nuevoNodo = (struct NodoProveedor*)malloc(sizeof(struct NodoProveedor));
    nuevoNodo->datosProveedor = (struct Proveedor*)malloc(sizeof(struct Proveedor));
    nuevoNodo->datosProveedor->id = id;
    nuevoNodo->datosProveedor->nombre = strdup(nombre);
    nuevoNodo->datosProveedor->direccion = strdup(direccion);
    nuevoNodo->datosProveedor->telefono = strdup(telefono);
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = farmacia->proveedores;
    if (farmacia->proveedores != NULL) {
        farmacia->proveedores->ant = nuevoNodo;
    }
    farmacia->proveedores = nuevoNodo;
}

void agregarSucursal(struct FarmaSalud *farmacia, int id, char *nombre, char *direccion, int capacidad) {
    struct NodoSucursales *nuevoNodo = (struct NodoSucursales*)malloc(sizeof(struct NodoSucursales));
    nuevoNodo->datosSucursal = (struct Sucursal*)malloc(sizeof(struct Sucursal));
    nuevoNodo->datosSucursal->id = id;
    nuevoNodo->datosSucursal->nombre = strdup(nombre);
    nuevoNodo->datosSucursal->direccion = strdup(direccion);
    nuevoNodo->datosSucursal->capacidadAlmacenamiento = capacidad;
    nuevoNodo->datosSucursal->productos = NULL; // Inicialmente no hay productos
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = farmacia->sucursales;
    if (farmacia->sucursales != NULL) {
        farmacia->sucursales->ant = nuevoNodo;
    }
    farmacia->sucursales = nuevoNodo;
}
