/* 
To-do list:

* Funcion 12 preguntar el stock de cada producto a agregar para ser registrado en sucursal
* Crear Funcion para agregar un producto en especifico a una sucursal 
* Crear Funcion que actualice el espacio disponible de una sucursal (debe verificar stock y no cantidad de productos)
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

struct FarmaSalud {
    struct NodoClientes *clientes;
    struct NodoSucursales *sucursales;
    struct NodoProveedor *proveedores;
};

struct NodoClientes {
    struct Clientes *datosClientes;
    struct NodoClientes *ant, *sig;
};

struct Clientes {
    int id;
    char *rutCliente;
    int edadCliente;
    int afiliado;
    struct Producto *comprasCliente[MAX_PRODUCTOS_POR_CLIENTE];
    int numCompras;
};

struct NodoSucursales {
    struct Sucursal *datosSucursal;
    struct NodoSucursales *ant, *sig;
};

struct Sucursal {
    int id;
    char *nombre;
    char *direccion;
    int capacidadAlmacenamiento;
    struct NodoProducto *productos;
};

struct NodoProducto {
    struct Producto *datosProducto;
    struct NodoProducto *ant, *sig;
};

struct Producto {
    char codigo[10];
    char *nombreProducto;
    char *descripcion;
    char *categoria;
    int precio;
    char *idProveedor;
    char *lote;
    char *fechaCaducidad;
    int cantidad;
    int requiereReceta;
};

struct NodoProveedor {
    struct Proveedor *datosProveedor;
    struct NodoProveedor *ant, *sig;
};

struct Proveedor {
    int id;
    char *nombre;
    char *direccion;
    char *telefono;
    struct NodoArbolProducto *productos;
};

struct NodoArbolProducto {
    struct Producto *datosProducto;
    struct NodoArbolProducto *izq, *der;
};

#include "Utilidades.h"
#include "FuncionesDeClientes.h"
#include "FuncionesDeSucursales.h"
#include "FuncionesDeProveedores.h"
#include "FuncionesDeTransferencia.h"
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

    struct Producto* producto1 = crearProductoFalso("1", "Producto1", "Descripción del Producto 1", "Categoría1", 1000, "Lab. de Chile", "Lote1", "01/01/2025", 50, 0);
    struct Producto* producto2 = crearProductoFalso("2", "Producto2", "Descripción del Producto 2", "Categoría2", 2000, "Lab. de Chile", "Lote2", "01/01/2026", 30, 1);
    struct Producto* producto3 = crearProductoFalso("3", "Producto3", "Descripción del Producto 3", "Categoría3", 1500, "Lab. Maver", "Lote3", "01/01/2027", 20, 0);
    struct Producto* producto4 = crearProductoFalso("4", "Producto4", "Descripción del Producto 4", "Categoría4", 2500, "Lab. Maver", "Lote4", "01/01/2028", 10, 1);

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
