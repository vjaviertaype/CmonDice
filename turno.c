#include "turno.h"

int turnoJugador(tJugador* jugador_actual, tConfig config_partida)
{
    /**Se genera una secuencia solo para casos de prueba**/
    tLista l_sec_ya_generada;
    crearLista(&l_sec_ya_generada);
    generarSecuenciaParaPruebas(&l_sec_ya_generada);
    /*************** BORRAR LUEGO ************************/

    //Se inicializan los parametros que se usaran para registrar los movimientos del jugador
    tRonda ronda_juego = {config_partida.cant_vidas, 0, 0};

    //Se crea Lista donde se ira guardando la secuencia que se va generando
    tLista l_sec;
    crearLista(&l_sec);

    //Se crea Lista donde se almacenara la respuesta del jugador
    tLista l_resp;
    crearLista(&l_resp);

    //Todos los jugadores arrancan en la ronda 1
    int ronda = 1;

    //Resultado de respuesta del jugador
    int resp;

    //Almacena la cantidad de caracteres de la respuesta del jugador
    int cant_caracteres_resp;

    //Muestra la ronda actual
    mostrarRonda(ronda);

    //Simulacion de solicitid api
    generarSecuencia(&l_sec_ya_generada,&l_sec);

    //Una vez generada la secuencia se muestra en pantalla el tiempo que indique la configuracion de partida
    puts("Se muestra secuencia : ");

    //Funcion de lista que muestra una lista x tiempo. Si se manda 0 como tiempo de muestra, se mostrara la lista en consola sin limite de tiempo.
    mostrarSecuenciaXTiempo(&l_sec, config_partida.tiempo_muestra, mostrarCaracter);

    //Se inicializa una bandera para seguir jugando
    int seguir_jugando = 1;

    puts("Ingrese su respuesta : ");

    while(seguir_jugando)
    {
        /* Funcion clave : El jugador da su respuesta y la misma se almacenara en una lista letra por letra.
            -A medida que el jugador ingrese su respuesta se ira contando la cantidad de caracteres que esta tuvo.
        */
        cant_caracteres_resp = respuestaJugador(&l_resp, config_partida.tiempo_turno);

        //Se valida la respuesta, para ello se compararan ambas listas.
        resp = validacionRespuesta(&l_sec, &l_resp);
        /** Valores que puede tomar resp
        	Tendremos 4 posibilidades de respuesta
        		1)RESPUESTA_CORRECTA : El jugador respondio correctamente
        		2)RESPUESTA_INCORRECTA : El jugador respondio mal
        		3)USO_CARACTER_ESPECIAL : El jugador apreto una tecla especial(a defidir por el grupo) en medio del ingreso de respuesta.
        		4)NO_CONTESTA : El jugador no puso nada.
        */

        ///Si no tiene vidas y no respondio correctamente...
        if(ronda_juego.vidas_total == 0 && ( resp == RESPUESTA_INCORRECTA || resp == NO_CONTESTA || resp == USO_CARACTER_ESPECIAL))
        {
            limpiarPantalla();
            puts("NO TIENE MAS VIDAS");
            puts("\nGAME OVER\n");
            seguir_jugando = 0;
        }
        else
        {
            if(resp == RESPUESTA_CORRECTA)
            {
                puts("RESPUESTA CORRECTA");
                pausa();
                respuestaCorrecta(jugador_actual,&l_resp, &ronda_juego);

                /**COMIENZA NUEVA RONDA**/
                mostrarRonda(++ronda);
                config_partida.tiempo_turno++;
                generarSecuencia(&l_sec_ya_generada,&l_sec);
                puts("Se muestra Secuencia :");
                mostrarSecuenciaXTiempo(&l_sec, config_partida.tiempo_muestra, mostrarCaracter);
                puts("Ingrese su respuesta :");
            }
            else if(resp == RESPUESTA_INCORRECTA)
            {
                puts("RESPUESTA INCORRECTA");
                pausa();
                respuestaIncorrecta(&l_resp, &ronda_juego, cant_caracteres_resp);
            }
            else if(resp == USO_CARACTER_ESPECIAL)
            {
                puts("Uso caracter especial");
                pausa();
                usoCaracterEspecial(&l_resp, &l_sec,&ronda_juego, config_partida.tiempo_muestra,cant_caracteres_resp);
            }
            else if(resp == NO_CONTESTA)
            {
                puts("No contesta");
                pausa();
                noContesta(&ronda_juego, &l_sec, config_partida.tiempo_muestra);
            }
        }
    }

    vaciarLista(&l_resp);
    vaciarLista(&l_sec);

    return TODO_OK;
}

void respuestaCorrecta(tJugador* jugador, tLista* l_resp, tRonda* ronda_juego)
{
    //Si no uso vidas, el jugador gana 3 puntos...de lo contrario solo sumara 1
    if(ronda_juego->vidas_consumidas == 0)
        jugador->puntos+=3;
    else
        jugador->puntos++;

    vaciarLista(l_resp);

    /*Aca se tendria que generar un informe de fin de turno*/

    ronda_juego->vidas_consumidas = 0;
    ronda_juego->puntos_turno = 0;
}

void noContesta(tRonda* ronda_juego, tLista* sec, unsigned tiempo_muestra)
{
    limpiarPantalla();

    //Si el jugador no contesto, se resta una vida si o si
    ronda_juego->vidas_total--;
    //Se toma registro de la vida que esta usando
    ronda_juego->vidas_consumidas++;

    //...y se le vuelve a mostrar la secuencia
    puts("Se consumio una vida, la secuencia se mostrara nuevamente");
    mostrarSecuenciaXTiempo(sec, tiempo_muestra, mostrarCaracter);
    puts("Vuelva a escribir su respuesta : ");
}

void usoCaracterEspecial(tLista* l_resp,tLista* l_sec, tRonda* ronda_juego, unsigned tiempo_muestra,int cant_car_resp)
{
    limpiarPantalla();

    int vidas_a_usar;

    //
    printf("Vidas totales : %d \n",ronda_juego->vidas_total);

    if(ronda_juego->vidas_total > cant_car_resp)
    {
        /**En este caso el jugador podra usar una vida mas ( si es que tiene) que la cantidad de caracteres de respuesta que tuvo.
            Si esto sucede se le procede a mostrar nuevamente la secuencia.
        */
        vidas_a_usar = cuantasVidasUsar(1, cant_car_resp + 1 );
    }
    else
    {
        vidas_a_usar = cuantasVidasUsar(1, ronda_juego->vidas_total);
    }

    ///Funcion de lista que elimina los ultimos n elementos de la lista
    eliminarNUltimos(l_resp, sizeof(char), vidas_a_usar);

    if( vidas_a_usar > cant_car_resp)
    {
        puts("La secuencia se mostrara nuevamente : ");
        mostrarSecuenciaXTiempo(l_sec, tiempo_muestra, mostrarCaracter);
        puts("Vuelva a escribir su respuesta :");
    }
    else
    {
        if(cant_car_resp == vidas_a_usar)
            puts("Vuelva a poner su respuesta : ");
        else
        {
            puts("Complete su respuesta :");
            mostrarSecuenciaXTiempo(l_resp, 0, mostrarCaracter);
        }
    }
    ronda_juego->vidas_total -= vidas_a_usar;
    ronda_juego->vidas_consumidas += vidas_a_usar;

}

void respuestaIncorrecta(tLista* l_resp, tRonda* ronda_juego, int cant_car_resp)
{
    limpiarPantalla();

    int vidas_a_usar;

    printf("Actualmente tiene %d vidas\n",ronda_juego->vidas_total);
    if(ronda_juego->vidas_total > cant_car_resp)
        vidas_a_usar = cuantasVidasUsar(1, cant_car_resp);
    else
        vidas_a_usar = cuantasVidasUsar(1, ronda_juego->vidas_total);

    ///Funcion de lista que elimina los ultimos n elementos de la lista
    eliminarNUltimos(l_resp, sizeof(char), vidas_a_usar);

    if( cant_car_resp == vidas_a_usar )
        puts("Vuelva a poner su respuesta : ");
    else
    {
        puts("Complete la respuesta :");
        mostrarSecuenciaXTiempo(l_resp, 0, mostrarCaracter);
    }

    ronda_juego->vidas_total -= vidas_a_usar;
    ronda_juego->vidas_consumidas += vidas_a_usar;

}

/** Simulacion de solicitud api :
    Simula un pedido a la api de un digito y lo almacena al final de la lista de secuencia
*/
int generarSecuencia(tLista* sec_ya_generada, tLista* sec)
{
    char letra;
    sacarPrimeroLista(sec_ya_generada, &letra, sizeof(char));

    ponerAlFinal(sec, &letra, sizeof(char));

    return 1;
}

///Funcion que limpia el buffer de teclado en su totalidad...
void limpiarBufferTeclado()
{

    fflush(stdin);
    /**fflush solo limpia el buffer de teclado hasta encontrar un salto de linea (\n), Eso significa que
        ... cualquier cosa después del primer "\n" permanecerá en el buffer.
        Ejemplo : si el usuario escribio por teclado : "xrty\n\n\nrb\n"
        fflush(stdin) solo borrara "xrty\n", pero en el buffer de teclado seguira quedando "\n\nrb\n"

    Para solucionar esto :
        La librería windows.h proporciona funciones específicas para la interacción con el sistema operativo Windows.
        En este caso, utilizamos GetStdHandle para obtener el "handle" o manejador del buffer de entrada de la consola (STD_INPUT_HANDLE)
        ... y FlushConsoleInputBuffer para limpiar dicho buffer, eliminando cualquier entrada PENDIENTE que no haya sido procesada.
        Esto asegura que el buffer esté completamente vacío antes de solicitar nueva entrada del usuario, evitando errores o lecturas no deseadas.
    */
    //HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    //FlushConsoleInputBuffer(hStdin);
}

void mostrarRonda(int ronda)
{
    limpiarPantalla();
    printf("*************************\n");
    printf("***** R O N D A - %d *****\n",ronda);
    printf("*************************\n");
    sleep(2);
    limpiarPantalla();
}

/** EXPLICACION DE HILOS Y COMO SE IMPLEMENTA EN LA FUNCION respuestaJugador()

    La función respuestaJugador() se encarga de recibir la entrada de caracteres del jugador. Mientras tanto,
    ... se ejecuta en paralelo un cronómetro en un hilo independiente, creado con pthread_create, que cuenta el tiempo restante.
    Ambas funciones trabajan simultáneamente: mientras el jugador ingresa caracteres, el cronómetro va disminuyendo el tiempo disponible.

    Si el jugador ingresa 'Z' (carácter especial), se detiene el proceso, tanto en respuestaJugador() como en cronometro(),
    ... ya que la variable continuar cambia su valor a 0, interrumpiendo ambos ciclos.

    - Si el cronómetro llega a 0, también se cambia el valor de continuar a 0, lo que termina el ciclo de entrada del jugador.
     Esto asegura que el programa gestione tanto la entrada de caracteres como el tiempo disponible de forma concurrente.
*/
int respuestaJugador(tLista* l, unsigned int tiempo_turno)
{
    int cant_caracteres_resp = 0;
    int continuar = 1;
    time_t tiempo_inicio = time(NULL),tiempo_actual; // tiempo de inicio
    char letra_resp;

    //Datos datos = {&tiempo_turno, &continuar};
    //pthread_t hiloCronometro;

    //Si la lista no esta vacia se debe contar la cantidad de caracteres que tiene
    if(!listaVacia(l))
        mapLista(l,&cant_caracteres_resp, contarCantidad);

    // Crear el hilo para el cronómetro
    //if (pthread_create(&hiloCronometro, NULL, cronometro, &datos) != 0)
    //{
    //    perror("Error al crear el hilo");
    //    return -1; // Error al crear el hilo
    //}

    //limpiarBufferTeclado();
    while (continuar)
    {
        tiempo_actual = time(NULL);
        //limpiarBufferTeclado();

        if (difftime(tiempo_actual,tiempo_inicio) >= tiempo_turno)
        {
            printf("\nTiempo agotado. El programa ha finalizado.\n");
            break;
        }

        if (_kbhit())
        {
            // Windows: revisar si hay una tecla presionada

            letra_resp = _getch(); // Leer la tecla presionada
            letra_resp = toupper(letra_resp);


            if (letra_resp == 'Z')
            {
                ponerAlFinal(l, &letra_resp, sizeof(char));
                continuar = 0;
                break;
            }
            else if (isalpha(letra_resp) && (letra_resp == 'A' || letra_resp == 'V' || letra_resp == 'R' || letra_resp == 'N'))
            {
                printf("%c",letra_resp);
                cant_caracteres_resp++;
                ponerAlFinal(l, &letra_resp, sizeof(char));
            }
        }

        /// Si el cronómetro llegó a 0, continuar cambiara su estado a 0
        // if(continuar)
        // {
        //   letra_resp = toupper(letra_resp);
        // if(letra_resp == 'Z')
        //{
        //  ponerAlFinal(l, &letra_resp, sizeof(char));
        //continuar = 0;
        //}
        //else if (isalpha(letra_resp) && (letra_resp == 'A' || letra_resp == 'V' || letra_resp == 'R' || letra_resp == 'N'))
        //{
        //  cant_caracteres_resp++;
//                ponerAlFinal(l, &letra_resp, sizeof(char));
        //          }
        //    }
    }
    // Esperar a que el hilo del cronometro termine
    // pthread_join(hiloCronometro, NULL);

    return cant_caracteres_resp;
}

void* cronometro(void* args)
{
    Datos* datos = (Datos*)args;
    unsigned int tiempo_restante = *datos->tiempo_turno;

    /**
        -Si tiempo_restante es mayor a 0 y continuar vale 1, entonces el tiempo se decrementa.
        -Tambien puede ocurrir que el usuario ingrese 'Z' (un carácter especial).
        Si eso sucede antes de que el tiempo se acabe, continuar valdrá 0, lo que hará que el ciclo while termine.
    */
    while (tiempo_restante > 0 && *datos->continuar)
    {
        sleep(1); // Espera un segundo
        tiempo_restante--;
    }

    if (tiempo_restante == 0)
    {
        // Cambia continuar a 0 cuando se acaba el tiempo.
        // Esto provocara que en la funcion donde se invoco el hilo el valor de continuar cambie a 0.
        *datos->continuar = 0;

        limpiarPantalla();
        printf("EL TIEMPO SE ACABO, PRESIONE ENTER PARA VER EL RESULTADO...");
    }

    return NULL;
}

int cuantasVidasUsar(int min, int max)
{
    int vidas;

    printf("Solo puede usar un maximo de %d vidas....Cuantas quiere usar ? : ", max);
    do
    {
        limpiarBufferTeclado();
        scanf("%d",&vidas);
        if(vidas < min || vidas > max)
            puts("Ingrese una cantidad valida");
    }
    while((vidas < min || vidas > max));

    limpiarPantalla();
    return vidas;
}

void contarCantidad(void* e, void* contexto)
{
    *((int*)contexto) += 1;

    return;
}

void mostrarCaracter(void* e)
{
    printf("%c ", *((char*)e) );
}

void limpiarPantalla()
{
#ifdef _WIN32
    /// Si es Windows
    system("cls");  /// Limpia la pantalla en Windows
#else
    /// Para Linux y otros sistemas POSIX
    system("clear"); /// Limpia la pantalla en Linux
#endif
}

void pausa()
{
#ifdef _WIN32
    /// Si es Windows
    system("pause"); /// Pausa en Windows
#else
    /// Para Linux y otros sistemas POSIX
    printf("Presione Enter para continuar...");
    getchar();  /// Espera a que el usuario presione Enter
#endif
}

//Solo para crear el lote de pruebas...luego borrar
int generarSecuenciaParaPruebas(tLista* lista)
{
    char letra = 'N';
    ponerAlFinal(lista, &letra, sizeof(char));

    letra = 'A';
    ponerAlFinal(lista, &letra, sizeof(char));

    letra = 'A';
    ponerAlFinal(lista, &letra, sizeof(char));

    letra = 'V';
    ponerAlFinal(lista, &letra, sizeof(char));

    letra = 'R';
    ponerAlFinal(lista, &letra, sizeof(char));

    letra = 'N';
    ponerAlFinal(lista, &letra, sizeof(char));

    letra = 'A';
    ponerAlFinal(lista, &letra, sizeof(char));

    letra = 'R';
    ponerAlFinal(lista, &letra, sizeof(char));

    letra = 'N';
    ponerAlFinal(lista, &letra, sizeof(char));

    return 1;
}