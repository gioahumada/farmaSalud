void agregarCliente(struct FarmaSalud *farmacia)
{
    struct NodoClientes *nuevoNodo = (struct NodoClientes *)malloc(sizeof(struct NodoClientes));
    nuevoNodo->datosClientes = (struct Clientes *)malloc(sizeof(struct Clientes));

    clrscr();

    int maxId = 0;
    struct NodoClientes *temp = farmacia->clientes;
    while (temp != NULL) {
        if (temp->datosClientes->id > maxId) {
            maxId = temp->datosClientes->id;
        }
        temp = temp->sig;
    }
    nuevoNodo->datosClientes->id = maxId + 1;

    printf("Ingrese RUT del cliente: ");
    nuevoNodo->datosClientes->rutCliente = (char *)malloc(20 * sizeof(char));
    scanf("%s", nuevoNodo->datosClientes->rutCliente);
    printf("Ingrese edad del cliente: ");
    scanf("%d", &nuevoNodo->datosClientes->edadCliente);
    printf("¿Es afiliado? (1-Si, 0-No): ");
    scanf("%d", &nuevoNodo->datosClientes->afiliado);

    for (int i = 0; i < MAX_PRODUCTOS_POR_CLIENTE; i++) {
        nuevoNodo->datosClientes->comprasCliente[i] = NULL;
    }
    nuevoNodo->datosClientes->numCompras = 0;

    nuevoNodo->ant = NULL;
    nuevoNodo->sig = NULL;
    if (farmacia->clientes == NULL) {
        farmacia->clientes = nuevoNodo;
    } else {
        temp = farmacia->clientes;
        while (temp->sig != NULL) {
            temp = temp->sig;
        }
        temp->sig = nuevoNodo;
        nuevoNodo->ant = temp;
    }

    clrscr();
    printf("Cliente agregado con éxito.\n");
    getch();
}
