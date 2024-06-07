void eliminarProveedor(struct FarmaSalud *farmacia) {
    cls();
    int idEliminar;
    struct NodoProveedor *temp, *prev;

    // Pedir al usuario que ingrese el ID del proveedor a eliminar
    printf("Ingrese el ID del proveedor que desea eliminar: ");
    scanf("%d", &idEliminar);

    temp = farmacia->proveedores;
    prev = NULL;

    // Buscar el proveedor con el ID proporcionado
    while (temp != NULL && temp->datosProveedor->id != idEliminar) {
        prev = temp;
        temp = temp->sig;
    }

    // Si no se encontró el proveedor con el ID proporcionado
    if (temp == NULL) {
        cls();
        printf("Proveedor no encontrado.\n");
        pause();
        return;
    }

    // Manejar los casos especiales para el primer y último nodo
    if (prev == NULL) {
        farmacia->proveedores = temp->sig;
    } else {
        prev->sig = temp->sig;
    }
    if (temp->sig != NULL) {
        temp->sig->ant = prev;
    }

    // Liberar la memoria asociada al proveedor
    free(temp->datosProveedor->nombre);
    free(temp->datosProveedor->direccion);
    free(temp->datosProveedor->telefono);
    free(temp->datosProveedor);
    free(temp);

    cls();
    printf("Proveedor eliminado con éxito.\n");
    pause();
}