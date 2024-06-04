/* 
To-do list:

* (LISTA) Funcion 12 preguntar el stock de cada producto a agregar para ser registrado en sucursal 
* (LISTA ARREGLAR) Crear Funcion para agregar un producto en especifico a una sucursal 
* (LISTA, no se verifica si es que necesita espacio) Crear Funcion que actualice el espacio disponible de una sucursal (debe verificar stock y no cantidad de productos)
* Crear Funcion Estadisticas (sucursal con mas items, proveedor con mas items, etc etc)
* Crear Funcion para concretar ventas y que se le agregue a cliente, que de una boleta (cliente registado o no)
* Crear Funcion para quitar productos con vencimiento DE UNA SUCURSAL o DE TODAS

Quizas hay que actualizar el Struct Sucursal para que tenga un contador de ventas efectuadas, ojop con eso, porque puede
que existan productos que se le vendan a un cliente no registrado por ejemplo, pero igual hay que llevar la cuenta de las ventas
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int cantidadDeVentas;
    int capacidadAlmacenamiento;
    struct NodoProducto *productos;
    struct NodoProducto *productosVendidos;
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

#include "Utilidades.h"
#include "FuncionesDeClientes.h"
#include "FuncionesDeSucursales.h"
#include "FuncionesDeProveedores.h"
#include "FuncionesDeTransferencia.h"
#include "AnalisisDeDatos.h"
#include "menuPrincipal.h"


int main() {
    struct FarmaSalud *farmacia;
    farmacia = (struct FarmaSalud *)malloc(sizeof(struct FarmaSalud));

    farmacia->clientes = NULL;
    farmacia->sucursales = NULL;
    farmacia->proveedores = NULL;

    // Inicialización de datos de prueba
    struct Producto prod1 = {"001", "Ibuprofeno", "Recomendado para el dolor de garganta", "Anti-inflamatorio", 100, "Bioequivalente", "Lote A", "2023-12-31", 10, 0};
    struct Producto prod2 = {"002", "Condones", "Ultra resistente y ultra delgado", "Anticonceptivo", 200, "Condoneria Nacional", "Lote B", "2024-12-31", 20, 1};
    struct Producto* compras1[] = {&prod1, &prod2};

    struct NodoClientes* cliente1 = crearClienteConsole(1, "8032837-5", 25, 1, compras1, 2);
    agregarClienteConsole(farmacia, cliente1);

    struct Producto prod3 = {"003", "Paracetamol", "Recomendado para el dolor de cabeza", "Analgesico", 300, "Lab. de Chile", "Lote C", "2022-12-31", 30, 0}; // Producto vencido
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

    struct Producto* producto1 = crearProductoFalso("1", "Sertralina 100mg 30 Comp", "Antidepresivo en forma de Cápsulas", "Antidepresivo", 6327, "Lab. de Chile", "N/A", "2023-05-31", -1, 1); // Producto vencido
    struct Producto* producto2 = crearProductoFalso("2", "Clonazepam 2 Mg 30 Comp", "Actúa sobre el sistema nervioso central, con propiedades ansiolíticas.", "Ansiolítico", 5007, "Lab. de Chile", "N/A", "N/A", -1, 1);
    struct Producto* producto3 = crearProductoFalso("3", "Tapsin Día-Noche Plus 18 Comp", "Comprimidos Recubiertos rápido alivio de los síntomas de la gripe", "Antigripal", 2575, "Lab. Maver", "N/A", "N/A", -1, 0);
    struct Producto* producto4 = crearProductoFalso("4", "Tapsín Día Limón 6 Un.", "Para el alivio sintomático de las molestias del resfrío y la gripe.", "Antigripal", 2500, "Lab. Maver", "N/A", "N/A", -1, 0);

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