# CmonDice
Es una variante del juego "Simón dice", donde los jugadores deberan utilizar su memoria para recordar la secuencia de colores mostrada por pantalla y al cabo de un breve tiempo, reproducir la misma de forma exacta con el fin de alcanzar el siguiente round y sumar un determinado puntaje. El juego, sera ganado por el jugador que haya logrado conseguir la mayor cantidad de puntos durante su turno.

##Como jugar?
El juego consiste en varias partes:

1. **Inicio del Juego**:
   - Al iniciar, se presenta un menú con varias opciones junto a una pequeña musica que acompañar a los jugadores durante su partida. El menu contendra: 
     - Instrucciones
     - Jugar
     - Ver Dificultades
     - Desarrolladores
     - Salir
       
   - Si seleccionas "Jugar", se te pedirá que ingreses los nombres de los jugadores. Puedes ingresar tantos nombres como desees. Para dejar de ingresar jugadores, bastara con           ingresar el numero "0"
   - Si seleccionas "Instrucciones", se te mostrara por pantalla una breve explicacion acerca de como podras jugar.
   - En el apartado de "Dificultades", podras ver todas las disponibles y el impacto que estas tendran con los tiempos tanto de respuesta como al mostrar la secuencia asi como en       las vidas disponibles.
   - "Desarrolladores", mostrara un poco los creditos del juego creado indicando las personas involucradas en el mismo.
   - Por ultimo, la opcion "Salir" permitira al usuario terminar el juego.

2. **Configuración del Juego**:
   - Después de ingresar los nombres, debes elegir el nivel de dificultad del juego: fácil, medio o difícil.
   - El sistema sorteará el orden en que jugarán los participantes y mostrará las configuraciones del juego, que incluyen:
     - Cantidad de vidas para cada jugador.
     - Tiempo que tendrán para ver la secuencia.
     - Tiempo que tendrán para ingresar la secuencia.

3. **Desarrollo del Juego**:
   - El primer jugador en el orden sorteado verá una secuencia de letras (R, V, A, N) mostrada una a una durante un tiempo determinado junto a su correspondiente color asignado.
   - Después de que se elimine la secuencia de la pantalla, el jugador tiene un tiempo limitado para ingresar la secuencia letra por letra.
   - El jugador puede borrar una letra ingresada pulsando la tecla "Z", lo que consumira una vida. Esto, podrá ser realizado segun cuantas vidas tenga el jugador.
   - Si el jugador no ingresa la secuencia a tiempo, se indicará que el tiempo ha finalizado. Si tiene vidas disponibles, puede usar una vida para intentar nuevamente.

4. **Validación de la Secuencia**:
   - Al finalizar el ingreso, el programa valida si la secuencia ingresada es correcta.
   - Si es correcta, el jugador avanza a la siguiente secuencia.
   - Si es incorrecta, se le informará al jugador cuántas vidas tiene y podrá deshacer un número de movimientos según la cantidad de vidas que le queden.

5. **Puntuación**:
   - Los puntos se suman de la siguiente manera:
     - +3 puntos por cada secuencia bien ingresada sin usar vidas.
     - +1 punto por cada secuencia bien ingresada usando vidas.
   - Al final de todos los turnos, el jugador con la mayor cantidad de puntos es declarado ganador.

6. **Informe Final**:
   - Al finalizar el juego, se generará un informe que incluirá detalles sobre las secuencias de cada ronda, las respuestas de los jugadores, las vidas utilizadas y el puntaje         total.

  
**Cambios en las configuraciones**

En el caso de asi desearlo, el usuario tendra la posibilidad de cambiar las reglas del juego a si antojo, permitiendo la modificacion de las dificultades y sus componentes. Esto, podra ser llevado a cabo mediante la alteracion del archivo "config.txt" el cual se encuentra adjunto al programa.

