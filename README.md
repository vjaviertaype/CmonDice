# CmonDice

**CmonDice** es una versión del clásico "Simón dice" que desafía la memoria de los jugadores, quienes deben recordar y repetir una secuencia de colores para avanzar de nivel y ganar puntos. El jugador que acumule más puntos en su turno, ¡gana!

## 📜 Instrucciones de Juego

### 1. Inicio del Juego
Al iniciar, se presenta un menú interactivo con música de fondo para ambientar la partida. Las opciones disponibles son:

- **Instrucciones**: Una guía rápida sobre cómo jugar.
- **Jugar**: Permite iniciar una partida. Se pedirá seleccionar la dificultad y luego el ingreso de los nombres de los jugadores.
- **Ver Dificultades**: Muestra los niveles de dificultad disponibles y cómo afectan los tiempos de respuesta y visualización de secuencias, así como las vidas.
- **Desarrolladores**: Información sobre los creadores del juego.
- **Salir**: Termina el juego.

### 2. Configuración del Juego
Antes de empezar a jugar, deberá elegir una dificultad: **fácil**, **medio** o **difícil**.

Después, se ingresan los nombres de los jugadores; para finalizar, ingresa el número "0" y oprime `< Enter >`.

### 3. Desarrollo del Juego
Se ingresarán los nombres de los jugadores y el sistema sorteará el orden de los turnos.

- El jugador activo observará una secuencia de letras (R, V, A, N) en la pantalla, cada una con su color correspondiente, mostrada de una en una. Luego se le da un tiempo para memorizarla.
- Una vez retirada la secuencia, el jugador tiene un tiempo limitado para ingresarla, letra por letra.
- Cada jugador puede borrar una letra ingresada al presionar "Z", lo cual consume una vida. El número de intentos depende de las vidas disponibles.
- Si no se completa la secuencia a tiempo, se indicará que el tiempo ha finalizado. Si el jugador tiene vidas restantes, se usará una para intentar de nuevo.

### 4. Validación de la Secuencia
Después de ingresar la secuencia, el sistema valida la respuesta:

- **Correcta**: El jugador avanza al siguiente nivel.
- **Incorrecta**: Se informará la cantidad de vidas restantes y se podrá deshacer movimientos según las vidas disponibles.

### 5. Puntuación
La puntuación se calcula de la siguiente forma:

- **+3 puntos** por cada secuencia correctamente ingresada sin usar vidas.
- **+1 punto** por cada secuencia ingresada correctamente usando vidas.

Al finalizar todos los turnos, el jugador con mayor puntaje será declarado ganador.

### 6. Informe Final
Al terminar el juego, se generará un informe que detalla las secuencias de cada ronda, respuestas de los jugadores, vidas usadas y puntaje final.

## ⚙️ Configuraciones

### Archivo de Configuración

Para editar el archivo de configuración, se debe tener en cuenta el siguiente formato:

> **NOTA:** Solo deben ser tres configuraciones, edítelas respetando límites de abajo y no cambie las dificultades de orden.


```
NIVEL|TIEMPO_MUESTRA|TIEMPO_RESPUESTA|CANT_VIDAS
```

- **NIVEL**: Es un único carácter que lo identifica *(F = fácil, M = medio y D = difícil)*.
- **TIEMPO_MUESTRA**: Es el tiempo que se mostrará la secuencia en pantalla *(se guarda en segundos, con un mínimo de 0 y un máximo de 20 segundos)*.
- **TIEMPO_RESPUESTA**: Es el tiempo que se esperará la respuesta del jugador *(se guarda en segundos, con un mínimo de 0 y un máximo de 20 segundos)*.
- **CANT_VIDAS**: Es la cantidad de vidas por ronda de cada jugador *(con un mínimo de 0 y un máximo de 5)*.

### Configuración de `libcurl` y `winmm` en Code::Blocks

#### Paso 1: Descargar `libcurl`

1. **Descargar el Archivo Precompilado**:
   - Visita la página oficial de [curl](https://curl.se/download.html).
   - Busca la sección que ofrece las descargas para Windows y elige una versión precompilada para Win32 o Win64.

2. **Descomprimir el Archivo**:
   - Una vez descargado, descomprime el archivo ZIP en una ubicación de tu elección. Recuerda la ruta, ya que necesitarás acceder a ella más adelante.

#### Paso 2: Estructura de Archivos

Asegúrate de que los siguientes archivos estén disponibles en la carpeta descomprimida:

- **Librerías**: Archivos `.dll`, `.a` o `.lib` (por ejemplo, `libcurl.dll`, `libcurl.dll.a` y `libcurl.a`).
- **Archivos de Cabecera**: Carpeta `include` que contenga `curl/curl.h`.

#### Paso 3: Configuración en Code::Blocks

1. **Agregar Archivos de Cabecera**:
   - Ve a **Project > Build options**.
   - En la pestaña **Search directories**, selecciona **Compiler**.
   - Agrega la ruta a la carpeta `include` que contiene `curl/curl.h`.

2. **Agregar las Librerías para Enlace**:
   - En la misma ventana de **Build options**, ve a la pestaña **Linker settings**.
   - Haz clic en **Add** y agrega `libcurl.dll.a` o `libcurl.a` (la que hayas descargado).
   - Agrega también la librería `winmm`:
     - Haz clic en **Add** y escribe `winmm`.

3. **Configurar Opciones de Enlace Adicionales**:
   - Asegúrate de que la carpeta que contiene `libcurl.dll` esté en la misma carpeta que tu archivo ejecutable o en el **PATH** de tu sistema.

Al finalizar la configuración, deberías poder compilar y ejecutar el programa.
