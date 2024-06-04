
void productoMasVendido(struct FarmaSalud *farmacia) {
    struct NodoSucursales *nodoSucursal = farmacia->sucursales;
    do {
        struct NodoProducto *nodoProducto = nodoSucursal->datosSucursal->productos;
        struct Producto *productoMasVendido = NULL;
        int maxVentas = 0;

        while (nodoProducto != NULL) {
            if (nodoProducto->datosProducto->cantidad > maxVentas) {
                maxVentas = nodoProducto->datosProducto->cantidad;
                productoMasVendido = nodoProducto->datosProducto;
            }
            nodoProducto = nodoProducto->sig;
        }

        if (productoMasVendido != NULL) {
            printf("El producto más vendido en la sucursal %s es %s con %d ventas.\n", 
                   nodoSucursal->datosSucursal->nombre, productoMasVendido->nombreProducto, maxVentas);
        } else {
            printf("No hay ventas registradas en la sucursal %s.\n", nodoSucursal->datosSucursal->nombre);
        }

        nodoSucursal = nodoSucursal->sig;
    } while (nodoSucursal != farmacia->sucursales);
}



// Implementación de la función
void obtenerProductosMasVendidosPorSucursal(struct FarmaSalud *farmaSalud) 
{
    struct NodoSucursales *nodoSucursal = farmaSalud->sucursales;

    if (nodoSucursal == NULL) 
    {
        printf("No hay sucursales registradas.\n");
        return;
    }

    do {
        struct Sucursal *sucursal = nodoSucursal->datosSucursal;
        struct NodoProducto *nodoProducto = sucursal->productosVendidos;

        if (nodoProducto == NULL) {
            printf("La sucursal %s no ha vendido ningún producto.\n", sucursal->nombre);
            nodoSucursal = nodoSucursal->sig;
            continue;
        }

        struct Producto *productoMasVendido = NULL;
        int maxVentas = 0;

        do {
            struct Producto *producto = nodoProducto->datosProducto;

            if (producto->cantidad > maxVentas) {
                maxVentas = producto->cantidad;
                productoMasVendido = producto;
            }

            nodoProducto = nodoProducto->sig;
        } while (nodoProducto != sucursal->productosVendidos);

        if (productoMasVendido) {
            printf("El producto más vendido en la sucursal %s es %s con %d ventas.\n", 
                sucursal->nombre, productoMasVendido->nombreProducto, maxVentas);
        }

        nodoSucursal = nodoSucursal->sig;
    } while (nodoSucursal != farmaSalud->sucursales);
}
