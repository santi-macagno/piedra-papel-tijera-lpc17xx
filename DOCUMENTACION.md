# Juego Piedra, Papel o Tijera - LPC1769

## Descripción General
Implementación del juego Piedra, Papel o Tijera para el microcontrolador LPC1769 usando entradas y salidas digitales en el puerto GPIO0.

## Características Principales

### 1. Entrada de Datos (Botones)
- **Bit 0 (P0.0)**: Entrada para Piedra
- **Bit 1 (P0.1)**: Entrada para Papel
- **Bit 2 (P0.2)**: Entrada para Tijera
- Solo un botón puede estar presionado a la vez
- Valores válidos de entrada: 1, 2, 4 (en binario: 001, 010, 100)

### 2. Salida de Datos (LEDs)
- **Bit 4 (P0.4)**: LED de Empate
- **Bit 5 (P0.5)**: LED de Victoria del Jugador
- **Bit 6 (P0.6)**: LED de Victoria del CPU

### 3. Funcionalidad del Programa

#### Representación de Jugadas
```c
#define PIEDRA    0
#define PAPEL     1
#define TIJERA    2
```

#### Array de Mapeo
Convierte los valores de entrada GPIO (0-7) a valores de jugada válidos:
```c
int mapa[8] = {-1, PIEDRA, PAPEL, -1, TIJERA, -1, -1, -1};
//             0    1       2      3    4      5   6    7
```
- `-1` indica entrada inválida (no presionar botones o presionar múltiples botones)
- Los valores válidos son: 1 (Piedra), 2 (Papel), 4 (Tijera)

#### Matriz de Resultados
```c
int resultado[3][3] = {
    { 0, -1, 1},   // Jugador juega Piedra:  [Empate vs Piedra, Pierde vs Papel, Gana vs Tijera]
    { 1,  0, -1},  // Jugador juega Papel:   [Gana vs Piedra, Empate vs Papel, Pierde vs Tijera]
    {-1,  1,  0}   // Jugador juega Tijera:  [Pierde vs Piedra, Gana vs Papel, Empate vs Tijera]
};
```
Donde:
- `1` = Gana el jugador
- `0` = Empate
- `-1` = Gana el CPU

### 4. Flujo de Ejecución

1. **Inicialización**
   - Configurar GPIO (bits 0-2 como entrada, bits 4-6 como salida)
   - Apagar todos los LEDs
   - Inicializar generador de números aleatorios

2. **Bucle Principal**
   - Leer continuamente el estado del puerto GPIO
   - Esperar a que se presione un botón válido
   - Realizar debounce (50ms)
   - Procesar la jugada del jugador

3. **Procesamiento de Jugada**
   - Mapear entrada a jugada del usuario
   - Generar jugada aleatoria del CPU (0, 1, 2)
   - Consultar matriz de resultados
   - Encender LED correspondiente
   - Imprimir resultado por consola (semihosting)

### 5. Funciones Implementadas

```c
void GPIO_Init(void)           // Inicializar configuración de GPIO
int Leer_Entrada(void)         // Leer estado de bits 0-2
void Apagar_LEDs(void)         // Apagar todos los LEDs
void Encender_LED(int led)     // Encender un LED específico
int Generar_Jugada_CPU(void)   // Generar número aleatorio 0-2
void delay_ms(unsigned int ms) // Delay por software
void Procesar_Jugada(int entrada_user) // Procesar una jugada completa
int main(void)                 // Función principal
```

### 6. Salida por Consola (Semihosting)

Para cada jugada válida, el programa imprime:
```
=== NUEVA JUGADA ===
Jugada del usuario: [Piedra|Papel|Tijera]
Jugada del CPU: [Piedra|Papel|Tijera]
Resultado: [EMPATE|GANA EL JUGADOR|GANA EL CPU]
```

### 7. Detalles de Implementación

#### Manipulación de Registros GPIO
```c
LPC_GPIO0->FIODIR = SALIDA_MASK;   // Configurar dirección (entrada/salida)
LPC_GPIO0->FIOPIN & ENTRADA_MASK;  // Leer entrada
LPC_GPIO0->FIOSET = led;           // Encender LED
LPC_GPIO0->FIOCLR = SALIDA_MASK;   // Apagar LEDs
```

#### Uso de Máscaras de Bits
- `ENTRADA_MASK = 0x07` (bits 0-2)
- `SALIDA_MASK = 0x70` (bits 4-6)
- Permite aislar solo los bits de interés

#### Debounce
Se implementa con delays por software para evitar lecturas falsas de botones.

## Compilación

### Opciones de Compilador Requeridas
```bash
-D__USE_CMSIS=CMSISv2p00_LPC17xx
-D__LPC17XX__
-D__CODE_RED
-D__REDLIB__
-DCORE_M3
-mcpu=cortex-m3
-mthumb
```

### Directorios de Inclusión
```
-I CMSISv2p00_LPC17xx/inc
-I CMSISv2p00_LPC17xx/Drivers/inc
```

## Requisitos Cumplidos

✓ Escrito en lenguaje C
✓ Utiliza estructuras definidas en lpc17xx.h
✓ Lee entradas desde GPIO
✓ Se mantiene en espera mientras puerto = 0
✓ Valida jugadas (entrada = 1, 2, 4)
✓ Utiliza matriz de resultados
✓ Utiliza array de mapeo
✓ Muestra resultado mediante LEDs
✓ Implementa delays por software
✓ Utiliza semihosting para output
✓ No almacena puntajes ni historial
✓ Ejecuta continuamente en while(1)
✓ Genera jugada aleatoria para CPU
✓ Maneja debounce de botones
✓ Imprime información en consola

## Notas de Implementación

- La función `delay_ms()` utiliza un bucle con instrucción `nop` para generar delays aproximados a 1ms para frecuencia de 60MHz
- La aleatoridad se basa en `rand() % 3`, inicializado con `srand(time(NULL))`
- Se implementó detección de cambio de estado para evitar múltiples lecturas de una sola pulsación
- El sistema es tolerante con entradas inválidas (rechaza automáticamente)

## Testing Recomendado

1. Presionar cada botón individualmente y verificar que se reconoce
2. Verificar que los LEDs se encienden correctamente según el resultado
3. Verificar mensajes en la consola semihosting
4. Probar debounce presionando rápidamente los botones
5. Verificar que el programa se reinicia correctamente para nueva jugada

