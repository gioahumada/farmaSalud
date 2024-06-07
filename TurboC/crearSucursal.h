void crearSucursal(struct FarmaSalud *farmacia) {
    cls();
    struct NodoSucursales *nuevoNodo = (struct NodoSucursales*)malloc(sizeof(struct NodoSucursales));
    struct Sucursal *nuevaSucursal = (struct Sucursal*)malloc(sizeof(struct Sucursal));

    nuevoNodo->datosSucursal = nuevaSucursal;
    nuevoNodo->ant = nuevoNodo->sig = NULL;

    printf("Ingrese ID de la sucursal: ");
    scanf("%d", &nuevaSucursal->id);
    printf("Ingrese nombre de la sucursal: ");
    nuevaSucursal->nombre = (char *)malloc(50 * sizeof(char));
    scanf("%s", nuevaSucursal->nombre);
    printf("Ingrese dirección de la sucursal: ");
    nuevaSucursal->direccion = (char *)malloc(100 * sizeof(char));
    scanf("%s", nuevaSucursal->direccion);

    nuevaSucursal->cantidadDeVentas = 0; // Inicializar a 0
    nuevaSucursal->capacidadAlmacenamiento = 0; // Cambiar si se necesita un valor específico
    nuevaSucursal->productos = NULL;
    nuevaSucursal->productosVendidos = NULL; // Inicializar a NULL
    nuevaSucursal->numRegistros = 0; // Inicializar a 0
    for (int i = 0; i < MAX_ENVIOS; i++) {
        nuevaSucursal->registrosEnvios[i] = NULL; // Inicializar a NULL
    }

    agregarSucursalConsole(farmacia, nuevoNodo);

    cls();
    printf("Sucursal agregada con éxito.\n");
    pause();
}