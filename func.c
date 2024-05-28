struct NodoProducto* crearNodoProducto(struct Producto *producto)
{
    struct NodoProducto *nuevo = (struct NodoProducto*)malloc(sizeof(struct NodoProducto));
    nuevo->datosProducto = producto;
    nuevo->ant = nuevo->sig = NULL;
    return nuevo;
}

void agregarProducto(struct NodoProducto **lista, struct Producto *producto) 
{
    struct NodoProducto *nuevo = crearNodoProducto(producto);
    if (*lista == NULL)
     {
        *lista = nuevo;
        nuevo->ant = nuevo->sig = nuevo;
    } 
    else 
    {
        struct NodoProducto *ultimo = (*lista)->ant;
        ultimo->sig = nuevo;
        nuevo->ant = ultimo;
        nuevo->sig = *lista;
        (*lista)->ant = nuevo;
    }
}

struct Producto* crearProducto(char *codigo, char *nombre, char *descripcion, char *categoria, float precio, char *proveedor, char *lote, char *fecha_caducidad, int cantidad, int requiere_receta) 
{
    struct Producto *nuevo = (struct Producto*)malloc(sizeof(struct Producto));
    strcpy(nuevo->codigo, codigo);
    nuevo->nombre = nombre;
    nuevo->descripcion = descripcion;
    nuevo->categoria = categoria;
    nuevo->precio = precio;
    nuevo->proveedor = proveedor;
    nuevo->lote = lote;
    nuevo->fecha_caducidad = fecha_caducidad;
    nuevo->cantidad = cantidad;
    nuevo->requiere_receta = requiere_receta;
    return nuevo;
}


void mostrarProductos(struct NodoProducto *lista) 
{
    struct NodoProducto *temp;
    if (lista == NULL) {
        printf("No hay productos.\n");
        return;
    }

    temp = lista;
    do
     {
        printf("Codigo: %s, Nombre: %s, Cantidad: %d, Fecha Caducidad: %s\n", temp->datosProducto->codigo, temp->datosProducto->nombre, temp->datosProducto->cantidad, temp->datosProducto->fecha_caducidad);
        temp = temp->sig;
    } while (temp != lista);
}

// Funciones para gestionar sucursales

struct NodoSucursales* crearNodoSucursal(struct Sucursal *sucursal)
{
    struct NodoSucursales *nuevo = (struct NodoSucursales*)malloc(sizeof(struct NodoSucursales));
    nuevo->datosSucursal = sucursal;
    nuevo->ant = nuevo->sig = NULL;
    nuevo->productos = NULL;
    return nuevo;
}

void agregarSucursal(struct NodoSucursales **lista, struct Sucursal *sucursal) 
{
    struct NodoSucursales *nuevo = crearNodoSucursal(sucursal);
    if (*lista == NULL) 
    {
        *lista = nuevo;
        nuevo->ant = nuevo->sig = nuevo;
    }
     else 
     {
        struct NodoSucursales *ultimo = (*lista)->ant;
        ultimo->sig = nuevo;
        nuevo->ant = ultimo;
        nuevo->sig = *lista;
        (*lista)->ant = nuevo;
    }
}

struct Sucursal* crearSucursal(int id, char *nombre, char *direccion, int capacidad_almacenamiento)
{
    struct Sucursal *nuevo = (struct Sucursal*)malloc(sizeof(struct Sucursal));
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->direccion = direccion;
    nuevo->capacidad_almacenamiento = capacidad_almacenamiento;
    return nuevo;
}

void mostrarSucursales(struct NodoSucursales *lista)
{
    struct NodoSucursales *temp;
    if (lista == NULL)
    {
        printf("No hay sucursales.\n");
        return;
    }
    temp = lista;
    do 
    {
        printf("ID: %d, Nombre: %s, Direccion: %s, Capacidad: %d\n", temp->datosSucursal->id, temp->datosSucursal->nombre, temp->datosSucursal->direccion, temp->datosSucursal->capacidad_almacenamiento);
        mostrarProductos(temp->productos);
        temp = temp->sig;
    } while (temp != lista);
}

// Gestionar Proveedores

struct NodoProveedores* crearNodoProveedor(struct Proveedor *proveedor)
{
    struct NodoProveedores *nuevo = (struct NodoProveedores*)malloc(sizeof(struct NodoProveedores));
    nuevo->datosProveedor = proveedor;
    nuevo->ant = nuevo->sig = NULL;
    nuevo->productos = NULL;
    return nuevo;
}

void agregarProveedor(struct NodoProveedores **lista, struct Proveedor *proveedor) 
{
    struct NodoProveedores *nuevo = crearNodoProveedor(proveedor);
    if (*lista == NULL)
    {
        *lista = nuevo;
        nuevo->ant = nuevo->sig = nuevo;
    } 
    else
    {
        struct NodoProveedores *ultimo = (*lista)->ant;
        ultimo->sig = nuevo;
        nuevo->ant = ultimo;
        nuevo->sig = *lista;
        (*lista)->ant = nuevo;
    }
}

struct Proveedor* crearProveedor(int id, char *nombre, char *direccion, char *telefono)
 {
    struct Proveedor *nuevo = (struct Proveedor*)malloc(sizeof(struct Proveedor));
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->direccion = direccion;
    nuevo->telefono = telefono;
    return nuevo;
}

void mostrarProveedores(struct NodoProveedores *lista)
 {
    struct NodoProveedores *temp;
    if (lista == NULL) 
    {
        printf("No hay proveedores.\n");
        return;
    }
    temp = lista;
    do 
    {
        printf("ID: %d, Nombre: %s, Direccion: %s, Telefono: %s\n", temp->datosProveedor->id, temp->datosProveedor->nombre, temp->datosProveedor->direccion, temp->datosProveedor->telefono);
        temp = temp->sig;
    } while (temp != lista);
}