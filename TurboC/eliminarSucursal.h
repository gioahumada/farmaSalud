void eliminarSucursal(struct FarmaSalud *farmacia) {
    cls();
    int idEliminar;
    struct NodoSucursales *temp, *prev;

    // Pedir al usuario que ingrese el ID de la sucursal a eliminar
    printf("Ingrese el ID de la sucursal que desea eliminar: ");
    scanf("%d", &idEliminar);

    temp = farmacia->sucursales;
    if (temp == NULL) {
        printf("No hay sucursales registradas.\n");
        pause();
        return;
    }

    // Buscar la sucursal con el ID proporcionado
    do {
        if (temp->datosSucursal->id == idEliminar) {
            break;
        }
        temp = temp->sig;
    } while (temp != farmacia->sucursales);

    // Si no se encontró la sucursal con el ID proporcionado
    if (temp->datosSucursal->id != idEliminar) {
        cls();
        printf("Sucursal no encontrada.\n");
        pause();
        return;
    }

    // Manejar los casos especiales para el primer y último nodo
    if (temp->ant == temp && temp->sig == temp) {
        farmacia->sucursales = NULL;
    } else {
        prev = temp->ant;
        prev->sig = temp->sig;
        temp->sig->ant = prev;
        if (temp == farmacia->sucursales) {
            farmacia->sucursales = temp->sig;
        }
    }

    // Liberar la memoria asociada a la sucursal
    free(temp->datosSucursal->nombre);
    free(temp->datosSucursal->direccion);
    for (int i = 0; i < temp->datosSucursal->numRegistros; i++) {
        free(temp->datosSucursal->registrosEnvios[i]);
    }
    free(temp->datosSucursal);
    free(temp);

    cls();
    printf("Sucursal eliminada con éxito.\n");
    pause();
}