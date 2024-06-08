int compararFechasVencidas(char *fecha1, char *fecha2) {
    int mes1, anio1, mes2, anio2;

    sscanf(fecha1, "%d/%d", &mes1, &anio1);
    sscanf(fecha2, "%d/%d", &mes2, &anio2);

    if (anio1 < anio2) return -1;
    if (anio1 > anio2) return 1;
    if (mes1 < mes2) return -1;
    if (mes1 > mes2) return 1;
    return 0;
}

int validarFecha(const char *fecha) {
    int mes, anio;
    if (sscanf(fecha, "%d/%d", &mes, &anio) != 2) {
        return 0;
    }
    if (mes < 1 || mes > 12) {
        return 0;
    }
    return 1;
}

void eliminarProductosVencidos(struct Sucursal *sucursal, char *fechaLimite) {
    if (sucursal == NULL || sucursal->productos == NULL) {
        printf("Sucursal o productos no válidos.\n");
        return;
    }
    if (!validarFecha(fechaLimite)) {
        printf("Fecha de caducidad inválida.\n");
        return;
    }

    struct NodoProducto *productoActual = sucursal->productos;
    while (productoActual != NULL) {
        struct NodoProducto *siguienteProducto = productoActual->sig;
        if (compararFechasVencidas(productoActual->datosProducto->fechaCaducidad, fechaLimite) < 0) {
            if (productoActual->ant != NULL) {
                productoActual->ant->sig = productoActual->sig;
            } else {
                sucursal->productos = productoActual->sig;
            }

            if (productoActual->sig != NULL) {
                productoActual->sig->ant = productoActual->ant;
            }

            // Verifica si los punteros no son NULL antes de liberar e imprime las direcciones de memoria
            if (productoActual->datosProducto->nombreProducto != NULL) {
                printf("Liberando nombreProducto: %s (dirección: %p)\n", productoActual->datosProducto->nombreProducto, (void*)productoActual->datosProducto->nombreProducto);
                free(productoActual->datosProducto->nombreProducto);
            }
            if (productoActual->datosProducto->descripcion != NULL) {
                printf("Liberando descripcion (dirección: %p)\n", (void*)productoActual->datosProducto->descripcion);
                free(productoActual->datosProducto->descripcion);
            }
            if (productoActual->datosProducto->categoria != NULL) {
                printf("Liberando categoria (dirección: %p)\n", (void*)productoActual->datosProducto->categoria);
                free(productoActual->datosProducto->categoria);
            }
            if (productoActual->datosProducto->idProveedor != NULL) {
                printf("Liberando idProveedor (dirección: %p)\n", (void*)productoActual->datosProducto->idProveedor);
                free(productoActual->datosProducto->idProveedor);
            }
            if (productoActual->datosProducto->lote != NULL) {
                printf("Liberando lote (dirección: %p)\n", (void*)productoActual->datosProducto->lote);
                free(productoActual->datosProducto->lote);
            }
            if (productoActual->datosProducto->fechaCaducidad != NULL) {
                printf("Liberando fechaCaducidad (dirección: %p)\n", (void*)productoActual->datosProducto->fechaCaducidad);
                free(productoActual->datosProducto->fechaCaducidad);
            }

            printf("Liberando datosProducto (dirección: %p)\n", (void*)productoActual->datosProducto);
            free(productoActual->datosProducto);
            printf("Liberando productoActual (dirección: %p)\n", (void*)productoActual);
            free(productoActual);
        }
        productoActual = siguienteProducto;
    }
}

void eliminarProductosVencidosDeTodasLasSucursales(struct FarmaSalud *farmacia, char *fechaLimite) {
    if (farmacia == NULL || farmacia->sucursales == NULL) {
        printf("No hay sucursales registradas.\n");
        return;
    }

    if (!validarFecha(fechaLimite)) {
        printf("Fecha de caducidad inválida.\n");
        return;
    }

    struct NodoSucursales *sucursalActual = farmacia->sucursales;
    do {
        eliminarProductosVencidos(sucursalActual->datosSucursal, fechaLimite);
        sucursalActual = sucursalActual->sig;
    } while (sucursalActual != farmacia->sucursales);

    printf("Productos vencidos eliminados de todas las sucursales correctamente.\n");
}



void menuEliminarProductosVencidos(struct FarmaSalud *farmacia) {
    cls();
    int idSucursal;
    char fechaLimite[8];

    mostrarSucursales(farmacia);
    printf("Ingrese el ID de la sucursal (o -1 para todas las sucursales): ");
    scanf("%d", &idSucursal);

    do {
        printf("Ingrese la fecha de vencimiento (MM/AAAA): ");
        scanf("%s", fechaLimite);

        if (!validarFecha(fechaLimite)) {
            printf("Fecha de caducidad invalida. Por favor, ingrese una fecha válida.\n");
        }
    } while (!validarFecha(fechaLimite));

    if (idSucursal == -1) {
        eliminarProductosVencidosDeTodasLasSucursales(farmacia, fechaLimite);
    } else {
        struct NodoSucursales *sucursalNodo = buscarSucursalPorID(farmacia, idSucursal);
        if (sucursalNodo == NULL) {
            printf("Sucursal no encontrada.\n");
            return;
        }
        eliminarProductosVencidos(sucursalNodo->datosSucursal, fechaLimite);
        cls();
        printf("Productos vencidos eliminados correctamente.\n");
    }
}