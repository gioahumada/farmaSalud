void actualizarInventariosSucursales(struct FarmaSalud *farmacia) {
    if (farmacia == NULL || farmacia->sucursales == NULL) {
        printf("No hay sucursales registradas.\n");
        return;
    }

    struct NodoSucursales *sucursalActual = farmacia->sucursales;

    // Iterar sobre cada sucursal
    do {
        if (sucursalActual->datosSucursal == NULL || sucursalActual->datosSucursal->productos == NULL) {
            sucursalActual = sucursalActual->sig;
            continue;
        }

        struct NodoProducto *productoActual = sucursalActual->datosSucursal->productos; // Iniciar en el primer nodo (sin nodo fantasma)
        while (productoActual != NULL) {
            struct NodoProducto *siguienteProducto = productoActual->sig;
            if (productoActual->datosProducto != NULL && productoActual->datosProducto->cantidad == 0) {
                // Eliminar producto con cantidad 0
                if (productoActual->ant != NULL) {
                    productoActual->ant->sig = productoActual->sig;
                } else {
                    // Si es el primer producto, actualizamos el puntero inicial de productos
                    sucursalActual->datosSucursal->productos = productoActual->sig;
                }

                if (productoActual->sig != NULL) {
                    productoActual->sig->ant = productoActual->ant;
                }

                // Liberar memoria del producto
                free(productoActual->datosProducto->nombreProducto);
                free(productoActual->datosProducto->descripcion);
                free(productoActual->datosProducto->categoria);
                free(productoActual->datosProducto->idProveedor);
                free(productoActual->datosProducto->lote);
                free(productoActual->datosProducto->fechaCaducidad);
                free(productoActual->datosProducto);
                free(productoActual);
            }
            productoActual = siguienteProducto;
        }
        sucursalActual = sucursalActual->sig;
    } while (sucursalActual != farmacia->sucursales);

    printf("Inventarios actualizados. Productos con stock 0 eliminados.\n");
}