#include "arte.h"

void mostrarArteASCII(const char* rutaArte)
{
    FILE *pf = fopen(rutaArte, "rt");
    if (pf == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    char linea[100];
    while (fgets(linea, sizeof(linea), pf))
        printf("%s", linea);

    fclose(pf);
}
