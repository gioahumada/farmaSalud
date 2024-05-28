#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estructuras - Poco modificables */

struct FarmaSalud /* struct que referencia a todo el resto*/
 {
    struct NodoClientes *DatosClientes;
    struct NodoSucursales *sucursales;
    struct NodoProveedores *proveedores;
};

struct Clientes 
{
    int id; /* ID Unico*/
    char *rutCliente; /* 1234564-1 */
    char *nombreCliente; /* Juan Perez */
    int edadCliente; /*36*/
    char **comprasCliente; /* Array - [SUCURSAL - AASDSADA]*/ // modificar
    int afiliado; /* booleano de tipo int si esta registrado en el sistema o no*/
};

// Lista doblemente enlazada para Clientes
struct NodoClientes
 {
    struct Clientes *datosCliente;
    struct NodoClientes *ant, *sig;
};

// Lista doblemente enlazada para Productos
struct NodoProducto
 {
    struct Producto *datosProducto;
    struct NodoProducto *ant, *sig;
};

struct Producto 
{
    char codigo[10]; // Codigo unico de 10 digitos + \n
    char *nombreProducto;
    char *descripcion;
    char *categoria;
    int precio;
    char *nombreProveedor;
    char *lote; /* numero de lote 3523*/ //VERIFICAR SI SE PUEDE MODIFICAR 
    char *fechaCaducidad; // Fecha de caducidad
    int cantidad; /* cantidad de producto disponible */
    int requiereReceta; // booleano de tipo int 1 si requiere receta medica, 0 si no
};

// Lista doblemente enlazada para Sucursales
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
    int capacidadAlmacenamiento; // Capacidad de almacenamiento
    struct NodoProducto *productos; // Lista doblemente enlazada de productos
};

// Árbol binario para Productos en Proveedores
struct NodoArbolProducto
 {
    struct Producto *datosProducto;
    struct NodoArbolProducto *izq, *der;
};

// Lista doblemente enlazada con Nodo Fantasma para Proveedores
struct NodoProveedores 
{
    struct Proveedor *datosProveedor;
    struct NodoProveedores *ant, *sig;
    struct NodoArbolProducto *productos; // Arbol binario de productos
};

struct Proveedor 
{
    int id;
    char *nombre;
    char *direccion;
    char *telefono;
};

/*Funciones*/



// - Gestionar Productos


int main() 
{
    return 0;
}
