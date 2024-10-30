#include "config.h"

int cargarConfig(const char *archivo_config, tConfig *configs, unsigned cant_configs)
{
    FILE *pf_config;
    tConfig buffer;
    int i = 0;

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
        return 0;
    }

    return TODO_OK;
}
void mostrarConfig(tConfig *config)
{
    int i;
    int pos = 1;

    mostrarTitulo();
    printf("+--------+-------+------------+--------------+--------------+\n");
    printf("| Indice | Nivel | T. Muestra | T. Respuesta | Cant. Vidas  |\n");
    printf("+--------+-------+------------+--------------+--------------+\n");
    for (i = 0; i < CANT_MAX_CONFIG; i++)
    {
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
            printf("\bFuera de rango.\nPor favor elija un indice entre 1 y %d: ", CANT_MAX_CONFIG);
        fflush(stdout);
    }
    while (indice <= 0 || indice > CANT_MAX_CONFIG);

    return --indice;
}


