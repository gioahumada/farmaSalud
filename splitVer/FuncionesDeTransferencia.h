void transferirProductosProveedorASucursal(struct FarmaSalud *farmacia) {
    int idProveedor, idSucursal;
    char fechaCaducidad[11];
    char lote[50];
    int cantidad;

    cls();

    mostrarProveedores(farmacia);
    printf("Ingrese el ID del proveedor: ");
    scanf("%d", &idProveedor);

    // Buscar el proveedor por ID
    struct NodoProveedor *proveedorActual = buscarProveedorPorID(farmacia, idProveedor);
    if (proveedorActual == NULL) {
        printf("Proveedor con ID %d no encontrado.\n", idProveedor);
        return;
    }

    cls();
    mostrarSucursales(farmacia);
    printf("Ingrese el ID de la sucursal: ");
    scanf("%d", &idSucursal);

    // Buscar la sucursal por ID
    struct NodoSucursales *sucursalActual = buscarSucursalPorID(farmacia, idSucursal);
    if (sucursalActual == NULL) {
        cls();
        printf("Sucursal con ID %d no encontrada.\n", idSucursal);
        pause();
        return;
    }

    // Transferir productos del proveedor a la sucursal
    struct NodoArbolProducto *nodoProducto = proveedorActual->datosProveedor->productos;
    while (nodoProducto != NULL) {
        cls();
        printf("Ingrese la fecha de vencimiento para el producto [%s]: ", nodoProducto->datosProducto->nombreProducto);
        scanf("%s", fechaCaducidad);
        cls();
        printf("Ingrese el lote para el producto [%s]: ", nodoProducto->datosProducto->nombreProducto);
        scanf("%s", lote);
        cls();
        printf("Ingrese la cantidad para el producto [%s]: ", nodoProducto->datosProducto->nombreProducto);
        scanf("%d", &cantidad);

        struct NodoProducto *nuevoNodoProducto = (struct NodoProducto *)malloc(sizeof(struct NodoProducto));
        nuevoNodoProducto->datosProducto = nodoProducto->datosProducto;
        strcpy(nuevoNodoProducto->datosProducto->fechaCaducidad, fechaCaducidad);
        strcpy(nuevoNodoProducto->datosProducto->lote, lote);
        nuevoNodoProducto->datosProducto->cantidad = cantidad;
        nuevoNodoProducto->ant = nuevoNodoProducto->sig = NULL;

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

        nodoProducto = nodoProducto->der;
    }

    cls();
    printf("Productos transferidos del proveedor con ID %d a la sucursal con ID %d.\n", idProveedor, idSucursal);

    pause();
    cls();
}

struct Producto *buscarProductoPorCodigo(struct NodoProveedor *proveedor, char *codigoProducto) {
    struct NodoProducto *productoActual = proveedor->datosProveedor->productos;

    // Recorrer la lista de productos
    while (productoActual != NULL) {
        if (strcmp(productoActual->datosProducto->codigo, codigoProducto) == 0) {
            // Si el producto con el código dado se encuentra, devolver el producto
            return productoActual->datosProducto;
        }
        productoActual = productoActual->sig;
    }

    // Si el producto con el código dado no se encuentra, devolver NULL
    return NULL;
}

void agregarProducto(struct Producto *producto, struct NodoSucursales *sucursal) {
    // Buscar el producto en la lista de productos de la sucursal
    struct NodoProducto *productoActual = sucursal->datosSucursal->productos;
    while (productoActual != NULL) {
        if (strcmp(productoActual->datosProducto->codigo, producto->codigo) == 0) {
            // Si el producto ya existe en la lista, incrementar su cantidad
            productoActual->datosProducto->cantidad += 1;
            printf("Cantidad del producto con codigo %s incrementada en la sucursal con ID %d.\n", producto->codigo, sucursal->datosSucursal->id);
            return;
        }
        productoActual = productoActual->sig;
    }

    // Si el producto no existe en la lista, agregarlo a la lista
    struct NodoProducto *nuevoProducto = (struct NodoProducto *)malloc(sizeof(struct NodoProducto));
    nuevoProducto->datosProducto = producto;
    nuevoProducto->sig = NULL;

    if (sucursal->datosSucursal->productos == NULL) {
        // Si la lista de productos está vacía, hacer que el nuevo producto sea el primer nodo
        sucursal->datosSucursal->productos = nuevoProducto;
    } else {
        // Si la lista de productos no está vacía, agregar el nuevo producto al final de la lista
        productoActual = sucursal->datosSucursal->productos;
        while (productoActual->sig != NULL) {
            productoActual = productoActual->sig;
        }
        productoActual->sig = nuevoProducto;
    }

    printf("Producto con codigo %s agregado a la sucursal con ID %d.\n", producto->codigo, sucursal->datosSucursal->id);
}


void agregarProductoEspecificoASucursalDesdeProveedor(struct FarmaSalud *farmacia) {
    int idProveedor, idSucursal;
    char codigoProducto[10];
    struct NodoProveedor *proveedorActual;
    struct Producto *productoActual;
    struct NodoSucursales *sucursalActual;

    do {
        printf("Ingrese el ID del proveedor: ");
        scanf("%d", &idProveedor);

        // Buscar el proveedor por ID
        proveedorActual = buscarProveedorPorID(farmacia, idProveedor);
        if (proveedorActual == NULL) {
            printf("Proveedor con ID %d no encontrado. Por favor, ingrese un ID valido.\n", idProveedor);
        }
    } while (proveedorActual == NULL);

    do {
        printf("Ingrese el codigo del producto: ");
        scanf("%s", codigoProducto);

        // Buscar el producto por codigo
        productoActual = buscarProductoPorCodigo(proveedorActual, codigoProducto);
        if (productoActual == NULL) {
            printf("Producto con codigo %s no encontrado en el proveedor con ID %d. Por favor, ingrese un codigo valido.\n", codigoProducto, idProveedor);
        }
    } while (productoActual == NULL);

    do {
        printf("Ingrese el ID de la sucursal: ");
        scanf("%d", &idSucursal);

        // Buscar la sucursal por ID
        sucursalActual = buscarSucursalPorID(farmacia, idSucursal);
        if (sucursalActual == NULL) {
            printf("Sucursal con ID %d no encontrada. Por favor, ingrese un ID valido.\n", idSucursal);
        }
    } while (sucursalActual == NULL);

    // Agregar producto a la sucursal
    agregarProducto(productoActual, sucursalActual);


    printf("Producto con codigo %s transferido del proveedor con ID %d a la sucursal con ID %d.\n", codigoProducto, idProveedor, idSucursal);

    pause();
    cls();
}
