// 4. Funciones de sucursales
int espacioRestante(struct Sucursal *sucursal) {
    if (sucursal == NULL) {
        return -1;
    }

    int totalProductos = 0;
    struct NodoProducto *nodoActual = sucursal->productos;

    while (nodoActual != NULL) {
        totalProductos += nodoActual->datosProducto->cantidad;
        nodoActual = nodoActual->sig;
    }
    int espacioRestante = 100000 - totalProductos;
    return espacioRestante;
}

void leerSucursales(struct FarmaSalud *farmacia) {
    cls();
    struct NodoSucursales *nodoActual = farmacia->sucursales;
    if (nodoActual == NULL) {
        printf("No hay sucursales registradas.\n");
        pause();
        return;
    }
    do {
        printf("ID: %d\n", nodoActual->datosSucursal->id);
        printf("Nombre: %s\n", nodoActual->datosSucursal->nombre);
        printf("Dirección: %s\n", nodoActual->datosSucursal->direccion);


        if (nodoActual->datosSucursal->productos != NULL) {
            printf("Productos:\n");
            struct NodoProducto *productoNodo = nodoActual->datosSucursal->productos;
            while (productoNodo != NULL) {
                printf("\t%s - %s\n", productoNodo->datosProducto->codigo, productoNodo->datosProducto->nombreProducto);
                productoNodo = productoNodo->sig;
            }
            printf("\n");
        } else {
            printf("Sucursal sin productos\n");
        }


        int espacio = espacioRestante(nodoActual->datosSucursal);
        printf("Espacio restante en la sucursal: %d\n\n", espacio);

        nodoActual = nodoActual->sig;
    } while (nodoActual != farmacia->sucursales);
    pause();
}

struct NodoSucursales* crearSucursalConsole(int id, char* nombre, char* direccion, int capacidadAlmacenamiento) {
    struct NodoSucursales* nuevoNodo = (struct NodoSucursales*)malloc(sizeof(struct NodoSucursales));
    struct Sucursal* nuevaSucursal = (struct Sucursal*)malloc(sizeof(struct Sucursal));
    
    nuevaSucursal->id = id;
    nuevaSucursal->nombre = strdup(nombre);
    nuevaSucursal->direccion = strdup(direccion);
    nuevaSucursal->capacidadAlmacenamiento = capacidadAlmacenamiento;
    nuevaSucursal->productos = NULL;
    
    nuevoNodo->datosSucursal = nuevaSucursal;
    nuevoNodo->ant = nuevoNodo->sig = nuevoNodo;
    
    return nuevoNodo;
}

void agregarSucursalConsole(struct FarmaSalud *farmacia, struct NodoSucursales *nuevaSucursal) {
    if (farmacia->sucursales == NULL) {
        farmacia->sucursales = nuevaSucursal;
    } else {
        struct NodoSucursales *temp = farmacia->sucursales;
        while (temp->sig != farmacia->sucursales) {
            temp = temp->sig;
        }
        temp->sig = nuevaSucursal;
        nuevaSucursal->ant = temp;
        nuevaSucursal->sig = farmacia->sucursales;
        farmacia->sucursales->ant = nuevaSucursal;
    }
}

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

    nuevaSucursal->productos = NULL;

    agregarSucursalConsole(farmacia, nuevoNodo);

    cls();
    printf("Sucursal agregada con éxito.\n");
    pause();
}

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
    // Aquí podrías añadir código para liberar productos asociados si es necesario
    free(temp->datosSucursal);
    free(temp);

    cls();
    printf("Sucursal eliminada con éxito.\n");
    pause();
}

struct NodoSucursales* buscarSucursalPorID(struct FarmaSalud *farmacia, int idSucursal) {
    struct NodoSucursales *sucursalActual = farmacia->sucursales;
    if (sucursalActual == NULL) {
        return NULL;
    }

    struct NodoSucursales *inicio = sucursalActual;
    do {
        if (sucursalActual->datosSucursal->id == idSucursal) {
            return sucursalActual;
        }
        sucursalActual = sucursalActual->sig;
    } while (sucursalActual != inicio);

    return NULL;
}