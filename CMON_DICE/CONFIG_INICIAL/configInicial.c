#include "configInicial.h"

int cargarConfig(const char *archivo_config, tConfig *configs,unsigned cant_configs)
{
    FILE *pf_config;
    tConfig buffer;
    int i;
    /// TODO: convertir en un seleccionador de linea el archivo de configuracion,
    /**
       Primero tiene que mostrar las configuraciones y luego el usuario debe elegir
    */
    i=0;
    pf_config = fopen(archivo_config,"rt");
    if(!pf_config) return ERROR_ARCH;

    while(fscanf(pf_config, " %c | %u | %u | %u",
                 &buffer.nivel,
                 &buffer.tiempo_muestra,
                 &buffer.tiempo_turno,
                 &buffer.cant_vidas) == 4 && i < cant_configs)
    {
        if(validarConfig(&buffer) == TODO_OK)
        {
            mostrarConfig(&buffer);
            memcpy(configs,&buffer,sizeof(tConfig));
            configs++;
        }
        i++;
    }

    fclose(pf_config);
    return TODO_OK;
}

int validarConfig(tConfig *config)
{
    if (!isalpha(config->nivel)
            || config->cant_vidas > 5
            || config->cant_vidas < 0
            || config->tiempo_muestra > 20
            || config->tiempo_muestra <= 0
            || config->tiempo_turno > 20
            || config->tiempo_turno <= 0)
    {
        return 0; // cambiar a una contantes de macros.h
    }

    return TODO_OK;
}
void mostrarConfig(tConfig *config) {
    printf("Nivel de dificultad: %c\nTiempo de Muestra: %u\nTiempo por turno: %u\nCantidad de Vidas: %u\n",
           config->nivel,
           config->tiempo_muestra,
           config->tiempo_turno,
           config->cant_vidas);
}
