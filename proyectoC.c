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

/* ----------
    Funciones
*/



int main() {

    return 0;
}

/*
--- Menu ---

1. Clientes
2. Sucursales -> cuando se entre se activa una funcion que revisa cada sucursal viendo caducidades y debastecimiento
3. Proveedores
4. Analisis de datos

*/

/*
--- Clientes ---
1. Identificar Cliente
2. Ver Compras Cliente
3. Eliminar Historial Cliente 

9. Volver 
*/

/*
--- Sucursales ---
1. Buscar Sucursal por nombre
2. Ventas Sucursal
3. Ver inventario de una Sucursal 
4. Actualizar Catalogo Sucursales
5. Eliminar Productos Vencidos

9. Volver
*/

/*
--- Proveedores ---
1. Buscar Proveedores 
2. Ver Productos de Proveedores 

9. Volver
*/



