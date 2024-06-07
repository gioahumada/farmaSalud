int espacioRestante(struct Sucursal *sucursal) {
    if (sucursal == NULL) {
        return -1;
    }

    int totalProductos = 0;
    struct NodoProducto *nodoActual = sucursal->productos;

    while (nodoActual != NULL) {
        totalProductos += nodoActual->datosProducto->cantidad;
        nodoActual = nodoActual->sig;
    }
    int espacioRestante = 10000 - totalProductos;
    return espacioRestante;
}

void leerSucursales(struct FarmaSalud *farmacia) {
    int espacio;
    struct NodoSucursales *nodoActual = farmacia->sucursales;
    cls();
    if (nodoActual == NULL) {
        printf("No hay sucursales registradas.\n");
        pause();
        return;
    }
    do {
        printf("ID: %d\n", nodoActual->datosSucursal->id);
        printf("Nombre: %s\n", nodoActual->datosSucursal->nombre);
        printf("Dirección: %s\n", nodoActual->datosSucursal->direccion);
        printf("Cantidad de Ventas: %d\n", nodoActual->datosSucursal->cantidadDeVentas);
        printf("Número de Registros de Envíos: %d\n", nodoActual->datosSucursal->numRegistros);
        for (int i = 0; i < nodoActual->datosSucursal->numRegistros; i++) {
            printf("\tRegistro de Envío %d: %s\n", i + 1, nodoActual->datosSucursal->registrosEnvios[i]);
        }

        if (nodoActual->datosSucursal->productos != NULL) {
            printf("Productos:\n");
            struct NodoProducto *productoNodo = nodoActual->datosSucursal->productos;
            while (productoNodo != NULL) {
                printf("\t%s - %s", productoNodo->datosProducto->codigo, productoNodo->datosProducto->nombreProducto);
                printf("\tCantidad en stock: %d", productoNodo->datosProducto->cantidad);
                printf("\tFecha de caducidad: %s", productoNodo->datosProducto->fechaCaducidad);
                printf("\tLote: %s\n", productoNodo->datosProducto->lote);

                // Comprobar si el producto tiene bajo stock
                if (productoNodo->datosProducto->cantidad < 10) {
                    printf("\t*** ALERTA: Bajo stock! ***\n");
                }

                productoNodo = productoNodo->sig;
            }
            printf("\n");
        } else {
            printf("Sucursal sin productos\n");
        }
        
        espacio = espacioRestante(nodoActual->datosSucursal);
        printf("Espacio restante en la sucursal: %d\n\n", espacio);
        nodoActual = nodoActual->sig;
    } while (nodoActual != farmacia->sucursales);
    pause();
}