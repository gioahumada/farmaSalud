void sucursalConMasVentas(struct FarmaSalud *farmacia) {
    if (farmacia->sucursales == NULL) {
        cls();
        printf("No hay sucursales registradas.\n");
        pause();
        return;
    }

    struct NodoSucursales *actual = farmacia->sucursales;
    struct Sucursal *mayorSucursal = actual->datosSucursal;

    int totalSucursales = 0;
    int todasCero = 1; // Bandera para verificar si todas las ventas son cero

    do {
        if (actual->datosSucursal->cantidadDeVentas > 0) {
            todasCero = 0;
        }
        if (actual->datosSucursal->cantidadDeVentas > mayorSucursal->cantidadDeVentas) {
            mayorSucursal = actual->datosSucursal;
        }
        actual = actual->sig;
        totalSucursales++;
    } while (actual != farmacia->sucursales);

    if (todasCero) {
        cls();
        printf("No hay ventas en las sucursales.\n");
        pause();
    } else {
        cls();
        printf("La sucursal con más ventas es: %s con %d ventas.\n",
               mayorSucursal->nombre, mayorSucursal->cantidadDeVentas);
        pause();
    }
}