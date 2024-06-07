void quitarNuevaLinea(char *cadena) {
    int longitud = strlen(cadena);
    if (cadena[longitud - 1] == '\n') {
        cadena[longitud - 1] = '\0';
    }
}

void agregarProductoProveedor(struct FarmaSalud *farmacia) {
    cls();

    // Crear y llenar los datos del nuevo producto
    struct Producto *nuevoProducto = (struct Producto *)malloc(sizeof(struct Producto));
    printf("Ingrese código del producto: ");
    scanf("%s", nuevoProducto->codigo);
    getchar(); // Para consumir el '\n' que queda en el buffer después de scanf
    nuevoProducto->nombreProducto = (char *)malloc(50 * sizeof(char));
    cls();
    printf("Ingrese nombre del producto: ");
    fgets(nuevoProducto->nombreProducto, 50, stdin);
    quitarNuevaLinea(nuevoProducto->nombreProducto);
    nuevoProducto->descripcion = (char *)malloc(100 * sizeof(char));
    cls();
    printf("Ingrese descripción del producto: ");
    fgets(nuevoProducto->descripcion, 100, stdin);
    quitarNuevaLinea(nuevoProducto->descripcion);
    nuevoProducto->categoria = (char *)malloc(50 * sizeof(char));
    cls();
    printf("Ingrese categoría del producto: ");
    fgets(nuevoProducto->categoria, 50, stdin);
    quitarNuevaLinea(nuevoProducto->categoria);
    cls();
    printf("Ingrese precio del producto: ");
    scanf("%d", &nuevoProducto->precio);
    getchar(); // Para consumir el '\n' que queda en el buffer después de scanf

    // Mostrar todos los proveedores disponibles
    struct NodoProveedor *proveedorActual = farmacia->proveedores;
    cls();
    printf("Proveedores disponibles:\n");
    while (proveedorActual != NULL) {
        printf("ID: %d, Nombre: %s\n", proveedorActual->datosProveedor->id, proveedorActual->datosProveedor->nombre);
        proveedorActual = proveedorActual->sig;
    }

    // Solicitar el ID del proveedor durante la creación del producto
    nuevoProducto->idProveedor = (char *)malloc(20 * sizeof(char));
    printf("\nIngrese ID del proveedor: ");
    scanf("%s", nuevoProducto->idProveedor);

    cls();
    // Asignar "N/A" a lote y fechaCaducidad, no preguntar al usuario
    nuevoProducto->lote = strdup("N/A");
    nuevoProducto->fechaCaducidad = strdup("N/A");

    // No preguntar por cantidad, asignar -1 para indicar que es un producto del proveedor
    nuevoProducto->cantidad = -1;

    cls();
    printf("¿Requiere receta? (1-Sí, 0-No): ");
    scanf("%d", &nuevoProducto->requiereReceta);

    // Convertir idProveedor de char* a int
    int idProveedorInt = atoi(nuevoProducto->idProveedor);

    // Buscar el proveedor por ID
    proveedorActual = farmacia->proveedores;
    while (proveedorActual != NULL && proveedorActual->datosProveedor->id != idProveedorInt) {
        proveedorActual = proveedorActual->sig;
    }

    if (proveedorActual == NULL) {
        printf("Proveedor no encontrado.\n");
        // Liberar memoria asignada al nuevo producto si el proveedor no se encuentra
        free(nuevoProducto->nombreProducto);
        free(nuevoProducto->descripcion);
        free(nuevoProducto->categoria);
        free(nuevoProducto->idProveedor);
        free(nuevoProducto->lote);
        free(nuevoProducto->fechaCaducidad);
        free(nuevoProducto);
        pause();
        return;
    }

    // Crear un nuevo nodo para el producto
    struct NodoArbolProducto *nuevoNodoProducto = (struct NodoArbolProducto *)malloc(sizeof(struct NodoArbolProducto));
    nuevoNodoProducto->datosProducto = nuevoProducto;
    nuevoNodoProducto->izq = nuevoNodoProducto->der = NULL;

    // Insertar el nuevo nodo en el árbol de productos del proveedor
    if (proveedorActual->datosProveedor->productos == NULL) {
        proveedorActual->datosProveedor->productos = nuevoNodoProducto;
    } else {
        struct NodoArbolProducto *actualProducto = proveedorActual->datosProveedor->productos;
        struct NodoArbolProducto *padreProducto = NULL;

        while (actualProducto != NULL) {
            padreProducto = actualProducto;
            if (strcmp(nuevoProducto->codigo, actualProducto->datosProducto->codigo) < 0) {
                actualProducto = actualProducto->izq;
            } else {
                actualProducto = actualProducto->der;
            }
        }

        if (strcmp(nuevoProducto->codigo, padreProducto->datosProducto->codigo) < 0) {
            padreProducto->izq = nuevoNodoProducto;
        } else {
            padreProducto->der = nuevoNodoProducto;
        }
    }

    cls();
    printf("Producto agregado con éxito al proveedor.\n");
    pause();
}