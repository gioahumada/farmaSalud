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

struct Sucursal *sucursalConMasVentas(struct FarmaSalud *farmaSalud) {
    if (farmaSalud == NULL || farmaSalud->sucursales == NULL) {
        return NULL;
    }

    struct NodoSucursales *actual = farmaSalud->sucursales;
    struct Sucursal *sucursalMasVentas = actual->datosSucursal;
    int maxVentas = sucursalMasVentas->cantidadDeVentas;

    actual = actual->sig;
    while (actual != farmaSalud->sucursales) {
        if (actual->datosSucursal->cantidadDeVentas > maxVentas) {
            sucursalMasVentas = actual->datosSucursal;
            maxVentas = sucursalMasVentas->cantidadDeVentas;
        }
        actual = actual->sig;
    }

    return sucursalMasVentas;
}

char* nombreProductoMasVendidoPorSucursal(struct Sucursal *sucursal) 
{
    if (sucursal == NULL || sucursal->productosVendidos == NULL) {
        return NULL;
    }

    struct NodoProducto *actual = sucursal->productosVendidos->sig;
    char *nombreProductoMasVendido = NULL;
    int maxVentas = 0;

    while (actual != sucursal->productosVendidos) {
        if (actual->datosProducto->cantidad > maxVentas) {
            maxVentas = actual->datosProducto->cantidad;
            nombreProductoMasVendido = actual->datosProducto->nombreProducto;
        }
        actual = actual->sig;
    }

    return nombreProductoMasVendido;
}

void M
