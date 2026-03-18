# Notas Técnicas - Implementación Piedra, Papel, Tijera LPC1769

## Estructura de la Solución

### 1. Definiciones de Constantes

#### Valores de Jugada
```c
#define PIEDRA    0
#define PAPEL     1
#define TIJERA    2
```

#### Configuración GPIO
```c
#define GPIO_PORT LPC_GPIO0                 // Puerto GPIO utilizado
#define ENTRADA_MASK    0x07                // Máscara para bits 0-2
#define SALIDA_MASK     0x70                // Máscara para bits 4-6
#define LED_EMPATE      (1 << 4)            // Bit 4
#define LED_GANA_USER   (1 << 5)            // Bit 5
#define LED_GANA_CPU    (1 << 6)            // Bit 6
```

### 2. Estructuras de Datos

#### Array de Mapeo
Índice = valor leído de GPIO (0-7)
Valor = jugada válida o -1 si es inválida

```
Entrada GPIO | Valor Binario | mapa[] | Significado
     0       |     000       |   -1   | Inválido (ningún botón)
     1       |     001       |    0   | Piedra ✓
     2       |     010       |    1   | Papel ✓
     3       |     011       |   -1   | Inválido (múltiples botones)
     4       |     100       |    2   | Tijera ✓
     5       |     101       |   -1   | Inválido
     6       |     110       |   -1   | Inválido
     7       |     111       |   -1   | Inválido
```

#### Matriz de Resultados
`resultado[jugador_usuario][jugada_cpu]`

```
Usuario \ CPU |  Piedra  | Papel | Tijera
   Piedra     |    0     |  -1   |   1
   Papel      |    1     |   0   |  -1
   Tijera     |   -1     |   1   |   0
```

### 3. Operaciones de Registro GPIO

#### Lectura
```c
entrada = LPC_GPIO0->FIOPIN & 0x07;  // Leer bits 0-2 del puerto
```

#### Escritura
```c
LPC_GPIO0->FIOSET = (1 << 4);       // Encender LED en bit 4
LPC_GPIO0->FIOCLR = 0x70;           // Apagar LEDs en bits 4-6
```

#### Configuración Dirección
```c
LPC_GPIO0->FIODIR = 0x70;           // Bits 4-6 como salida (1)
                                    // Bits 0-2 como entrada (0)
```

### 4. Algoritmo Principal

```
INICIO
  ├─ Inicializar GPIO
  ├─ Apagar LEDs
  ├─ Mostrar mensaje de bienvenida
  │
  └─ BUCLE INFINITO
      ├─ Leer entrada actual
      │
      ├─ SI (entrada cambió Y entrada es válida)
      │  ├─ Guardar entrada actual
      │  ├─ Debounce (50ms)
      │  ├─ Esperar a suelta de botón
      │  ├─ Apagar LEDs anteriores
      │  │
      │  ├─ Mapear entrada a jugada usuario
      │  ├─ Generar jugada aleatoria CPU
      │  ├─ Consultar matriz resultado[usuario][cpu]
      │  │
      │  ├─ SEGÚN resultado:
      │  │  ├─ 0 → Encender LED_EMPATE
      │  │  ├─ 1 → Encender LED_GANA_USER
      │  │  └─ -1 → Encender LED_GANA_CPU
      │  │
      │  ├─ Imprimir en consola
      │  ├─ Esperar 100ms antes de siguiente entrada
      │  └─ Reset de entrada anterior
      │
      └─ Delay 10ms (anti-busy-wait)
```

### 5. Manejo de Debounce

```c
// 1. Detectar cambio de entrada
if (entrada_actual != entrada_anterior) {
    
    // 2. Verificar que sea válida
    if (entrada_actual != 0 && mapa[entrada_actual] != -1) {
        
        // 3. Debounce: esperar 50ms
        delay_ms(50);
        
        // 4. Esperar suelta del botón
        while (Leer_Entrada() != 0) {
            delay_ms(10);
        }
        
        // 5. Esperar 100ms antes de siguiente
        delay_ms(100);
    }
}
```

### 6. Detección de Números Aleatorios

Para garantizar aleatoriedad:
```c
srand((unsigned int)time(NULL));  // Inicializar con tiempo
int cpu = rand() % 3;             // Generar 0, 1, 2
```

### 7. Función Delay por Software

Aproximada a 1ms por iteración para MCU a 60MHz:
```c
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 123; j++) {  // Constante empírica
            __asm("nop");
        }
}
```

**Nota**: La constante 123 puede ajustarse según la frecuencia real del MCU.

### 8. Flujo de una Jugada

```
[Usuario presiona botón]
         ↓
[Leer GPIO, mapear a jugada]
         ↓
[Generar jugada CPU aleatoria]
         ↓
[Consultar matriz resultado]
         ↓
[Encender LED correspondiente]
         ↓
[Imprimir en consola]
         ↓
[Esperar suelta de botón + debounce]
         ↓
[Listo para siguiente jugada]
```

### 9. Salida en Consola (Semihosting)

El programa utiliza `printf()` para mostrar:

```
=== JUEGO PIEDRA, PAPEL O TIJERA ===
Presione uno de los botones:
Botón 0 (P0.0) = Piedra
Botón 1 (P0.1) = Papel
Botón 2 (P0.2) = Tijera

=== NUEVA JUGADA ===
Jugada del usuario: Papel
Jugada del CPU: Piedra
Resultado: GANA EL JUGADOR
```

### 10. Requisitos de Compilación

#### Definiciones Requeridas
```bash
-D__USE_CMSIS=CMSISv2p00_LPC17xx
-D__LPC17XX__
-D__CODE_RED
-D__REDLIB__
-DCORE_M3
```

#### Flags de Arquitectura
```bash
-mcpu=cortex-m3
-mthumb
```

#### Directorios Include
```
-I CMSISv2p00_LPC17xx/inc
-I CMSISv2p00_LPC17xx/Drivers/inc
```

### 11. Ejemplo de Compilación Manual

```bash
arm-none-eabi-gcc \
  -c src/piedra-papel-tijera-lpc17xx.c \
  -I CMSISv2p00_LPC17xx/inc \
  -I CMSISv2p00_LPC17xx/Drivers/inc \
  -D__USE_CMSIS=CMSISv2p00_LPC17xx \
  -D__LPC17XX__ \
  -D__CODE_RED \
  -D__REDLIB__ \
  -DCORE_M3 \
  -mcpu=cortex-m3 \
  -mthumb \
  -o piedra-papel-tijera-lpc17xx.o
```

## Mapeo de Hardware

### Diagrama de Conexiones

```
    LPC1769 GPIO0
    ┌─────────────────┐
    │                 │
    │ Entrada:        │ Salida:
    │ P0.0 ───[PB]─ Piedra        P0.4 ───[LED]─ Empate
    │ P0.1 ───[PB]─ Papel         P0.5 ───[LED]─ Gana Jugador
    │ P0.2 ───[PB]─ Tijera        P0.6 ───[LED]─ Gana CPU
    │                 │
    └─────────────────┘
```

### Especificación de Pines
- **P0.0 - P0.2**: Entrada digital (botones)
- **P0.4 - P0.6**: Salida digital (LEDs)
- **Voltaje**: 3.3V (lógica CMOS)
- **Corriente**: Limitada por resistencias de pull-up/pull-down

## Optimizaciones Posibles

1. **Usar Timer para delays**: Reemplazar delay_ms con TIMER0
2. **Usar Interrupciones GPIO**: En lugar de polling continuo
3. **Utilizar RNG hardware**: Si el MCU lo tiene disponible
4. **Optimizar debounce**: Usar máquina de estados
5. **Agregar timeout**: Para evitar esperas infinitas

## Pruebas Sugeridas

1. Verificar que cada botón genera la jugada correcta
2. Verificar que los LEDs se encienden según resultado
3. Verificar mensajes en consola semihosting
4. Verificar debounce con pulsaciones rápidas
5. Verificar que programa se recupera de entradas inválidas
6. Medir tiempo de respuesta entre entrada y salida


