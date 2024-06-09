void obtenerDetallesProducto(char* fechaCaducidad, char* lote, int* cantidad, char* nombreProducto) {
    printf("Ingrese la fecha de vencimiento para el producto (formato MM/AAAA) [%s]: ", nombreProducto);
    scanf("%s", fechaCaducidad);
    printf("Ingrese el lote para el producto [%s]: ", nombreProducto);
    scanf("%s", lote);
    printf("Ingrese la cantidad para el producto [%s]: ", nombreProducto);
    scanf("%d", cantidad);
}

void transferirProductoProveedorASucursal(struct FarmaSalud *farmacia) {
    cls();
    int idProveedor = solicitarIdProveedor(farmacia);
    if (idProveedor == -1) return;

    cls();
    int idSucursal = solicitarIdSucursal(farmacia);
    if (idSucursal == -1) return;

    cls();
    char codigoProducto[10];
    if (!solicitarCodigoProducto(farmacia, idProveedor, codigoProducto)) return;

    char fechaCaducidad[11];
    char lote[50];
    int cantidad;
    struct Producto *productoSeleccionado = buscarProductoPorCodigo(farmacia, idProveedor, codigoProducto);
    if (productoSeleccionado == NULL) {
        printf("Producto con codigo %s no encontrado.\n", codigoProducto);
        pause();
        return;
    }

    obtenerDetallesProducto(fechaCaducidad, lote, &cantidad, productoSeleccionado->nombreProducto);
    transferirProducto(farmacia, idProveedor, idSucursal, productoSeleccionado, fechaCaducidad, lote, cantidad, codigoProducto);
}

int solicitarIdProveedor(struct FarmaSalud *farmacia) {
    mostrarProveedores(farmacia->proveedores);
    printf("Ingrese el ID del proveedor: ");
    int idProveedor;
    scanf("%d", &idProveedor);

    struct NodoProveedor *proveedorActual = buscarProveedorPorID(farmacia, idProveedor);
    if (proveedorActual == NULL) {
        printf("Proveedor con ID %d no encontrado.\n", idProveedor);
        pause();
        return -1;
    }
    return idProveedor;
}

int solicitarIdSucursal(struct FarmaSalud *farmacia) {
    mostrarSucursales(farmacia->sucursales);
    printf("Ingrese el ID de la sucursal: ");
    int idSucursal;
    scanf("%d", &idSucursal);

    struct NodoSucursales *sucursalActual = buscarSucursalPorID(farmacia, idSucursal);
    if (sucursalActual == NULL) {
        printf("Sucursal con ID %d no encontrada.\n", idSucursal);
        pause();
        return -1;
    }
    return idSucursal;
}

int solicitarCodigoProducto(struct FarmaSalud *farmacia, int idProveedor, char *codigoProducto) {
    struct NodoProveedor *proveedorActual = buscarProveedorPorID(farmacia, idProveedor);
    if (proveedorActual == NULL) return 0;

    printf("Productos del proveedor:\n");
    struct NodoArbolProducto *nodoProducto = proveedorActual->datosProveedor->productos;
    while (nodoProducto != NULL) {
        printf("Codigo: %s, Nombre: %s\n", nodoProducto->datosProducto->codigo, nodoProducto->datosProducto->nombreProducto);
        nodoProducto = nodoProducto->der;
    }
    printf("Ingrese el codigo del producto a transferir: ");
    scanf("%s", codigoProducto);
    return 1;
}

struct Producto* buscarProductoPorCodigo(struct FarmaSalud *farmacia, int idProveedor, char *codigoProducto) {
    struct NodoProveedor *proveedorActual = buscarProveedorPorID(farmacia, idProveedor);
    struct NodoArbolProducto *nodoProducto = proveedorActual->datosProveedor->productos;
    struct Producto *productoSeleccionado = NULL;

    while (nodoProducto != NULL) {
        if (strcmp(nodoProducto->datosProducto->codigo, codigoProducto) == 0) {
            productoSeleccionado = nodoProducto->datosProducto;
            break;
        }
        nodoProducto = nodoProducto->der;
    }
    return productoSeleccionado;
}

void transferirProducto(struct FarmaSalud *farmacia, int idProveedor, int idSucursal, struct Producto *productoSeleccionado, char *fechaCaducidad, char *lote, int cantidad, char *codigoProducto) {
    struct Producto *nuevoProducto = (struct Producto *)malloc(sizeof(struct Producto));
    if (nuevoProducto == NULL) {
        printf("Error al asignar memoria para el nuevo producto.\n");
        pause();
        return;
    }
    // Copiar datos del producto original al nuevo producto
    strcpy(nuevoProducto->codigo, productoSeleccionado->codigo);
    nuevoProducto->nombreProducto = strdup(productoSeleccionado->nombreProducto);
    nuevoProducto->descripcion = strdup(productoSeleccionado->descripcion);
    nuevoProducto->categoria = strdup(productoSeleccionado->categoria);
    nuevoProducto->precio = productoSeleccionado->precio;
    nuevoProducto->idProveedor = strdup(productoSeleccionado->idProveedor);
    nuevoProducto->lote = strdup(lote);
    nuevoProducto->fechaCaducidad = strdup(fechaCaducidad);
    nuevoProducto->cantidad = cantidad;
    nuevoProducto->requiereReceta = productoSeleccionado->requiereReceta;

    struct NodoProducto *nuevoNodoProducto = (struct NodoProducto *)malloc(sizeof(struct NodoProducto));
    if (nuevoNodoProducto == NULL) {
        printf("Error al asignar memoria para el nuevo nodo de producto.\n");
        free(nuevoProducto);
        pause();
        return;
    }
    nuevoNodoProducto->datosProducto = nuevoProducto;
    nuevoNodoProducto->ant = nuevoNodoProducto->sig = NULL;

    struct NodoSucursales *sucursalActual = buscarSucursalPorID(farmacia, idSucursal);
    if (sucursalActual->datosSucursal->productos == NULL) {
        sucursalActual->datosSucursal->productos = nuevoNodoProducto;
    } else {
        struct NodoProducto *temp = sucursalActual->datosSucursal->productos;
        while (temp->sig != NULL) {
            temp = temp->sig;
        }
        temp->sig = nuevoNodoProducto;
        nuevoNodoProducto->ant = temp;
    }

    cls();
    printf("Producto %s transferido del proveedor con ID %d a la sucursal con ID %d.\n", codigoProducto, idProveedor, idSucursal);
    pause();
    cls();
}
