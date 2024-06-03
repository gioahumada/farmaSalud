void pause() {
    char c;
    printf("\nPresione Enter para continuar...\n");
    do {
        c = getchar();
    } while (c != '\n');
}

void cls() {
    int i;
    for(i=0;i<20;i++) printf("\n");
}

void quitarNuevaLinea(char *cadena) {
    int longitud = strlen(cadena);
    if (cadena[longitud - 1] == '\n') {
        cadena[longitud - 1] = '\0';
    }
}