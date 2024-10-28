#include "config.h"

int cargarConfig(const char *archivo_config, tConfig *configs, unsigned cant_configs)
{
    FILE *pf_config;
    tConfig buffer;
    int i;
    /// TODO: convertir en un seleccionador de linea el archivo de configuracion,
    /**
       Primero tiene que mostrar las configuraciones y luego el usuario debe elegir
    */

    i = 0;
    pf_config = fopen(archivo_config, "rt");
    if (!pf_config)
        return ERROR_ARCH;

    while (fscanf(pf_config, " %c | %u | %u | %u",
                  &buffer.nivel,
                  &buffer.tiempo_muestra,
                  &buffer.tiempo_turno,
                  &buffer.cant_vidas) == 4 &&
            i < cant_configs)
    {
        if (validarConfig(&buffer) == TODO_OK)
        {
            mostrarConfig(&buffer);
            memcpy(configs, &buffer, sizeof(tConfig));
            configs++;
        }
        i++;
    }

    fclose(pf_config);
    return TODO_OK;
}

int validarConfig(tConfig *config)
{
    if (!isalpha(config->nivel) || config->cant_vidas > 5 || config->cant_vidas < 0 || config->tiempo_muestra > 20 || config->tiempo_muestra <= 0 || config->tiempo_turno > 20 || config->tiempo_turno <= 0)
    {
        return NON_VALID; // cambiar a una contantes de macros.h
    }

    return TODO_OK;
}
void mostrarConfig(tConfig *config)
{
<<<<<<< Updated upstream
    printf("Nivel de dificultad: %c\nTiempo de Muestra: %u\nTiempo por turno: %u\nCantidad de Vidas: %u\n",
           config->nivel,
           config->tiempo_muestra,
           config->tiempo_turno,
           config->cant_vidas);
}
=======
    int i;
    int pos = 1;

    for (i = 0; i < CANT_MAX_CONFIG; i++)
    {
        printf("| Indice | Nivel | T. Muestra | T. Respuesta | Cant. Vidas  |\n");
        printf("+--------+-------+------------+--------------+--------------+\n");
        printf("| %-6d | %-5c | %-10d | %-12d | %-12d |\n",
               pos,
               config->nivel,
               config->tiempo_muestra,
               config->tiempo_turno,
               config->cant_vidas);
        printf("+--------+-------+------------+--------------+--------------+\n");
        config++;
        pos++;
    }


}

int seleccionaConfigIndice(tConfig *vec)
{
    int indice = -1;

    limpiarPantalla();
    mostrarConfig(vec);

    do
    {
        limpiarBufferTeclado();
        printf("\nIngrese un Indice para seleccionar configuracion del juego: ");
        scanf("%d", &indice);
        if (indice <= 0 || indice > CANT_MAX_CONFIG)
            printf("\nFuera de rango.\nPor favor elija un indice entre 1 y %d: ", CANT_MAX_CONFIG);
    }
    while (indice <= 0 || indice > CANT_MAX_CONFIG);

    return --indice;
}
>>>>>>> Stashed changes
