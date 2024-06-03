// 6. Funciones de transferencia
void transferirProductosProveedorASucursal(struct FarmaSalud *farmacia) {
    int idProveedor, idSucursal;

    printf("Ingrese el ID del proveedor: ");
    scanf("%d", &idProveedor);

    // Buscar el proveedor por ID
    struct NodoProveedor *proveedorActual = buscarProveedorPorID(farmacia, idProveedor);
    if (proveedorActual == NULL) {
        printf("Proveedor con ID %d no encontrado.\n", idProveedor);
        return;
    }

    printf("Ingrese el ID de la sucursal: ");
    scanf("%d", &idSucursal);

    // Buscar la sucursal por ID
    struct NodoSucursales *sucursalActual = buscarSucursalPorID(farmacia, idSucursal);
    if (sucursalActual == NULL) {
        printf("Sucursal con ID %d no encontrada.\n", idSucursal);
        return;
    }

    // Transferir productos del proveedor a la sucursal
    transferirProductos(proveedorActual->datosProveedor->productos, sucursalActual);

    // Vaciar la lista de productos del proveedor
    proveedorActual->datosProveedor->productos = NULL;

    printf("Productos transferidos del proveedor con ID %d a la sucursal con ID %d.\n", idProveedor, idSucursal);

    pause();
    cls();
}