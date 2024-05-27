#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estructuras - Poco modificables */

struct FarmaSalud {
    struct NodoClientes *DatosClientes;
    struct NodoSucursales *sucursales;
    struct NodoProveedores *proveedores;
};

// Lista doblemente enlazada para Clientes
struct NodoClientes {
    struct Clientes *datosCliente;
    struct NodoClientes *ant, *sig;
};

struct Clientes {
    int id;
    char *rut;
    char *nombre;
    char *apellido;
    int edad;
    char **compras;
    int afiliado;
};

// Lista doblemente enlazada para Productos
struct NodoProducto {
    struct Producto *datosProducto;
    struct NodoProducto *ant, *sig;
};

struct Producto {
    char codigo[11]; // Código único de 10 dígitos
    char *nombre;
    char *descripcion;
    char *categoria;
    float precio;
    char *proveedor;
    char *lote;
    char *fecha_caducidad; // Fecha de caducidad
    int cantidad;
    int requiere_receta; // 1 si requiere receta médica, 0 si no
};

// Lista doblemente enlazada para Sucursales
struct NodoSucursales {
    struct Sucursal *datosSucursal;
    struct NodoSucursales *ant, *sig;
    struct NodoProducto *productos; // Lista doblemente enlazada de productos
};

struct Sucursal {
    int id;
    char *nombre;
    char *direccion;
    int capacidad_almacenamiento; // Capacidad de almacenamiento
};

// Árbol binario para Productos en Proveedores
struct NodoArbolProducto {
    struct Producto *datosProducto;
    struct NodoArbolProducto *izq, *der;
};

// Lista doblemente enlazada con Nodo Fantasma para Proveedores
struct NodoProveedores {
    struct Proveedor *datosProveedor;
    struct NodoProveedores *ant, *sig;
    struct NodoArbolProducto *productos; // Árbol binario de productos
};

struct Proveedor {
    int id;
    char *nombre;
    char *direccion;
    char *telefono;
};

/* 

Funciones

*/

// - Gestionar Productos

struct NodoProducto* crearNodoProducto(struct Producto *producto) {
    struct NodoProducto *nuevo = (struct NodoProducto*)malloc(sizeof(struct NodoProducto));
    nuevo->datosProducto = producto;
    nuevo->ant = nuevo->sig = NULL;
    return nuevo;
}

void agregarProducto(struct NodoProducto **lista, struct Producto *producto) {
    struct NodoProducto *nuevo = crearNodoProducto(producto);
    if (*lista == NULL) {
        *lista = nuevo;
        nuevo->ant = nuevo->sig = nuevo;
    } else {
        struct NodoProducto *ultimo = (*lista)->ant;
        ultimo->sig = nuevo;
        nuevo->ant = ultimo;
        nuevo->sig = *lista;
        (*lista)->ant = nuevo;
    }
}

struct Producto* crearProducto(char *codigo, char *nombre, char *descripcion, char *categoria, float precio, char *proveedor, char *lote, char *fecha_caducidad, int cantidad, int requiere_receta) {
    struct Producto *nuevo = (struct Producto*)malloc(sizeof(struct Producto));
    strcpy(nuevo->codigo, codigo);
    nuevo->nombre = nombre;
    nuevo->descripcion = descripcion;
    nuevo->categoria = categoria;
    nuevo->precio = precio;
    nuevo->proveedor = proveedor;
    nuevo->lote = lote;
    nuevo->fecha_caducidad = fecha_caducidad;
    nuevo->cantidad = cantidad;
    nuevo->requiere_receta = requiere_receta;
    return nuevo;
}


void mostrarProductos(struct NodoProducto *lista) {
    if (lista == NULL) {
        printf("No hay productos.\n");
        return;
    }
    struct NodoProducto *temp = lista;
    do {
        printf("Codigo: %s, Nombre: %s, Cantidad: %d, Fecha Caducidad: %s\n", temp->datosProducto->codigo, temp->datosProducto->nombre, temp->datosProducto->cantidad, temp->datosProducto->fecha_caducidad);
        temp = temp->sig;
    } while (temp != lista);
}

// Funciones para gestionar sucursales

struct NodoSucursales* crearNodoSucursal(struct Sucursal *sucursal) {
    struct NodoSucursales *nuevo = (struct NodoSucursales*)malloc(sizeof(struct NodoSucursales));
    nuevo->datosSucursal = sucursal;
    nuevo->ant = nuevo->sig = NULL;
    nuevo->productos = NULL;
    return nuevo;
}

void agregarSucursal(struct NodoSucursales **lista, struct Sucursal *sucursal) {
    struct NodoSucursales *nuevo = crearNodoSucursal(sucursal);
    if (*lista == NULL) {
        *lista = nuevo;
        nuevo->ant = nuevo->sig = nuevo;
    } else {
        struct NodoSucursales *ultimo = (*lista)->ant;
        ultimo->sig = nuevo;
        nuevo->ant = ultimo;
        nuevo->sig = *lista;
        (*lista)->ant = nuevo;
    }
}

struct Sucursal* crearSucursal(int id, char *nombre, char *direccion, int capacidad_almacenamiento) {
    struct Sucursal *nuevo = (struct Sucursal*)malloc(sizeof(struct Sucursal));
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->direccion = direccion;
    nuevo->capacidad_almacenamiento = capacidad_almacenamiento;
    return nuevo;
}

void mostrarSucursales(struct NodoSucursales *lista) {
    if (lista == NULL) {
        printf("No hay sucursales.\n");
        return;
    }
    struct NodoSucursales *temp = lista;
    do {
        printf("ID: %d, Nombre: %s, Direccion: %s, Capacidad: %d\n", temp->datosSucursal->id, temp->datosSucursal->nombre, temp->datosSucursal->direccion, temp->datosSucursal->capacidad_almacenamiento);
        mostrarProductos(temp->productos);
        temp = temp->sig;
    } while (temp != lista);
}

// Gestionar Proveedores

struct NodoProveedores* crearNodoProveedor(struct Proveedor *proveedor) {
    struct NodoProveedores *nuevo = (struct NodoProveedores*)malloc(sizeof(struct NodoProveedores));
    nuevo->datosProveedor = proveedor;
    nuevo->ant = nuevo->sig = NULL;
    nuevo->productos = NULL;
    return nuevo;
}

void agregarProveedor(struct NodoProveedores **lista, struct Proveedor *proveedor) {
    struct NodoProveedores *nuevo = crearNodoProveedor(proveedor);
    if (*lista == NULL) {
        *lista = nuevo;
        nuevo->ant = nuevo->sig = nuevo;
    } else {
        struct NodoProveedores *ultimo = (*lista)->ant;
        ultimo->sig = nuevo;
        nuevo->ant = ultimo;
        nuevo->sig = *lista;
        (*lista)->ant = nuevo;
    }
}

struct Proveedor* crearProveedor(int id, char *nombre, char *direccion, char *telefono) {
    struct Proveedor *nuevo = (struct Proveedor*)malloc(sizeof(struct Proveedor));
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->direccion = direccion;
    nuevo->telefono = telefono;
    return nuevo;
}

void mostrarProveedores(struct NodoProveedores *lista) {
    if (lista == NULL) {
        printf("No hay proveedores.\n");
        return;
    }
    struct NodoProveedores *temp = lista;
    do {
        printf("ID: %d, Nombre: %s, Direccion: %s, Telefono: %s\n", temp->datosProveedor->id, temp->datosProveedor->nombre, temp->datosProveedor->direccion, temp->datosProveedor->telefono);
        temp = temp->sig;
    } while (temp != lista);
}


int main() {
    struct NodoSucursales *sucursales = NULL;
    struct NodoProveedores *proveedores = NULL;
    struct NodoProducto *productos = NULL;

    // Crear y agregar sucursales
    struct Sucursal *sucursal1 = crearSucursal(1, "Sucursal A", "Direccion A", 10000);
    struct Sucursal *sucursal2 = crearSucursal(2, "Sucursal B", "Direccion B", 8000);
    agregarSucursal(&sucursales, sucursal1);
    agregarSucursal(&sucursales, sucursal2);

    // Crear y agregar productos
    struct Producto *producto1 = crearProducto("1234567890", "Producto A", "Descripcion A", "Categoria A", 10.0, "Proveedor A", "Lote A", "2024-12-31", 500, 0);
    struct Producto *producto2 = crearProducto("0987654321", "Producto B", "Descripcion B", "Categoria B", 15.0, "Proveedor B", "Lote B", "2023-11-30", 300, 1);
    agregarProducto(&(sucursales->productos), producto1);
    agregarProducto(&(sucursales->productos), producto2);

    // Crear y agregar proveedores
    struct Proveedor *proveedor1 = crearProveedor(1, "Proveedor A", "Direccion A", "Telefono A");
    struct Proveedor *proveedor2 = crearProveedor(2, "Proveedor B", "Direccion B", "Telefono B");
    agregarProveedor(&proveedores, proveedor1);
    agregarProveedor(&proveedores, proveedor2);

    // Mostrar datos
    printf("Sucursales:\n");
    mostrarSucursales(sucursales);

    printf("\nProveedores:\n");
    mostrarProveedores(proveedores);

    return 0;
}

/*
Error que lanza

main.c:
Error main.c 134: Declaration
is not allowed here in function mostrarProductos
Error main.c 177: Declaration
is not allowed here
in function mostrarSucursales
Error main.c ZZ1: Declaration
is not allowed here in function mostrarProveedores
Error main.c 238: Declaration
is not allowed here in function main
Error main.c 239: Declaration
is not allowed here
in function main
Error main.c Z43: Declaration
is not allowed here
in function main
Error main.c Z44: Declaration
is not allowed here in function main
Warning main.c 255: 'productos'
is assigned a value that is never used in functi
on main
？ errors in Compile **
Available memory 4117560
Illegal command:

*/

