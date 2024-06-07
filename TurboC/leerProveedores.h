void mostrarProductosProveedor(struct NodoArbolProducto *nodoProducto) {
    char *requiereReceta;

    if (nodoProducto == NULL) {
        return;
    }

    mostrarProductosProveedor(nodoProducto->izq);

    struct Producto *producto = nodoProducto->datosProducto;
    if (producto->requiereReceta) {
        requiereReceta = "Sí";
    } else {
        requiereReceta = "No";
    }

    printf("%-10s", producto->codigo);
    printf("%-40s", producto->nombreProducto);
    printf("$%-20d", producto->precio);
    printf("%-18s\n", requiereReceta);

    mostrarProductosProveedor(nodoProducto->der);
}

void leerProveedores(struct FarmaSalud *farmacia) {
    cls();
    struct NodoProveedor *nodoActual = farmacia->proveedores;
    if (nodoActual == NULL) {
        printf("No hay proveedores registrados.\n");
        pause();
        return;
    }


    while (nodoActual != NULL) {
        printf("ID: %d\n", nodoActual->datosProveedor->id);
        printf("Nombre: %s\n", nodoActual->datosProveedor->nombre);
        printf("Dirección: %s\n", nodoActual->datosProveedor->direccion);
        printf("Teléfono: %s\n", nodoActual->datosProveedor->telefono);

        // Mostrar productos del proveedor
        if (nodoActual->datosProveedor->productos == NULL) {
            printf("No hay productos asociados a este proveedor.\n\n");
        } else {
            printf("Productos:\n\n");
            printf("ID          Nombre                                    Precio                Requiere receta\n\n");
            mostrarProductosProveedor(nodoActual->datosProveedor->productos);
            printf("\n");
        }

        nodoActual = nodoActual->sig;
    }
    pause();
}