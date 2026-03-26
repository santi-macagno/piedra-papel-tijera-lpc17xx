# Piedra, Papel o Tijera - LPC1769

## Resumen del Proyecto

Este proyecto implementa el juego clásico "Piedra, Papel o Tijera" para el microcontrolador LPC1769 de NXP. El programa utiliza GPIO para lectura de botones y control de LEDs, generando jugadas aleatorias y determinando el ganador de cada ronda.

## Estructura del Proyecto

```
piedra-papel-tijera-lpc17xx/
├── src/
│   └── piedra-papel-tijera-lpc17xx.c    # Código principal del juego
├── CMSISv2p00_LPC17xx/                  # Librerías CMSIS para LPC1769
│   ├── inc/                             # Headers de CMSIS
│   └── Drivers/                         # Drivers de periféricos
├── CMakeLists.txt                       # Configuración CMake
├── DOCUMENTACION.md                     # Documentación completa
├── NOTAS_TECNICAS.md                    # Detalles técnicos
└── README.md                            # Este archivo
```

## Características

### ✓ Entradas (GPIO0, bits 0-2)
- **Botón 0 (P0.0)**: Jugada "Piedra"
- **Botón 1 (P0.1)**: Jugada "Papel"
- **Botón 2 (P0.2)**: Jugada "Tijera"

### ✓ Salidas (GPIO0, bits 4-6)
- **LED Bit 4 (P0.4)**: Empate
- **LED Bit 5 (P0.5)**: Gana el Jugador
- **LED Bit 6 (P0.6)**: Gana el Microcontrolador

### ✓ Funcionalidades
- Lectura confiable de botones con debounce
- Generación de jugadas aleatorias para el CPU
- Matriz de resultados para determinar ganador
- Array de mapeo para validar entradas
- Salida de información por semihosting (consola)
- Bucle principal que se ejecuta continuamente

## Compilación

### Con MCUXpresso IDE
El proyecto está configurado para compilarse dentro de MCUXpresso. Simplemente:
1. Abrir el proyecto en MCUXpresso
2. Click derecho → Build Project
3. La salida será `/cmake-build-debug/piedra-papel-tijera-lpc17xx`

### Manualmente con GCC ARM
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
  -o piedra-papel-tijera.o
```

## Ejecución

1. **Cargar el firmware** en el LPC1769 usando MCUXpresso Debugger
2. **Ejecutar el programa** (Play o depuración)
3. **Abrir consola de semihosting** en MCUXpresso
4. **Presionar botones** para jugar

## Ejemplo de Uso

### Entrada del Usuario
```
Usuario presiona botón en P0.1 (Papel)
```

### Procesamiento
```
1. Leer entrada: 0x02 (binario 010)
2. Mapear a jugada: mapa[2] = PAPEL (1)
3. Generar jugada CPU: rand() % 3 = 0 (PIEDRA)
4. Consultar matriz: resultado[1][0] = 1 (Gana jugador)
5. Encender LED_GANA_USER (P0.5)
```

### Salida en Consola
```
=== NUEVA JUGADA ===
Jugada del usuario: Papel
Jugada del CPU: Piedra
Resultado: GANA EL JUGADOR
```

## Conceptos de Programación Utilizados

### Estructuras de Datos
- **Arrays**: `mapa[8]` para mapeo de entradas
- **Matrices**: `resultado[3][3]` para lógica del juego

### Manipulación de Bits
- Máscaras: `0x07`, `0x70`
- Operadores: `&` (AND), `<<` (shift)

### Acceso a Hardware
- Registros GPIO: `FIODIR`, `FIOPIN`, `FIOSET`, `FIOCLR`
- Operaciones atómicas en hardware

### Control de Flujo
- Bucles: `while(1)` para ejecución continua
- Condicionales: `if/else` para lógica de juego
- Comparaciones: validación de entradas

### Función de Tiempo
- `delay_ms()`: delays por software
- `time(NULL)`: inicialización de aleatoriedad

## Validación de Entrada

El programa valida automáticamente:
- Solo acepta valores 1, 2, 4 (botones individuales)
- Rechaza 0 (sin botones)
- Rechaza 3, 5, 6, 7 (múltiples botones)

```c
if (entrada_actual != 0 && mapa[entrada_actual] != -1) {
    // Entrada válida - procesar
}
```

## Debounce Implementado

```c
delay_ms(50);              // Esperar 50ms
while (Leer_Entrada() != 0) {   // Esperar suelta de botón
    delay_ms(10);
}
delay_ms(100);             // Esperar antes de siguiente entrada
```

## Matriz de Resultados Explicada

| Usuario \ CPU | Piedra | Papel | Tijera |
|:---:|:---:|:---:|:---:|
| **Piedra** | Empate (0) | Pierde (-1) | Gana (1) |
| **Papel** | Gana (1) | Empate (0) | Pierde (-1) |
| **Tijera** | Pierde (-1) | Gana (1) | Empate (0) |

## Requisitos de Hardware

- **Microcontrolador**: LPC1769
- **Puerto GPIO**: 0
- **Botones**: 3 (conectados a P0.0, P0.1, P0.2)
- **LEDs**: 3 (conectados a P0.4, P0.5, P0.6)
- **Pull-ups/Pull-downs**: Según configuración (típicamente pull-down para botones)
- **Resistencias limitadoras**: Para los LEDs (~330Ω típico)
- **Fuente de alimentación**: 3.3V

## Diagrama de Flujo

```
┌─────────────────┐
│     INICIO      │
└────────┬────────┘
         │
    ┌────▼─────────────────┐
    │  Inicializar GPIO    │
    │  Apagar todos LEDs   │
    │  Iniciar generador   │
    │  aleatorio           │
    └────┬────────────────┘
         │
    ┌────▼──────────────────────────┐
    │   BUCLE PRINCIPAL (while 1)   │
    │                               │
    │  Leer estado de GPIO (bits 0-2)
    │  ¿Cambio de entrada?          │
    │      │                        │
    │      ├─ NO ──────────────┐   │
    │      │                   │   │
    │      └─ SI ──► ¿Válida?  │   │
    │             │  │         │   │
    │             ├─ NO ┐      │   │
    │             │     │      │   │
    │             └─ SI ┐      │   │
    │                   │      │   │
    │        ┌──────────▼──────┘   │
    │        │  Procesar Jugada    │
    │        │  - Mapear entrada   │
    │        │  - Gen. aleatorio   │
    │        │  - Consultar matriz │
    │        │  - Encender LED     │
    │        │  - Print consola    │
    │        │  - Debounce         │
    │        └──────┬─────────────┘
    │               │                │
    │        Delay 10ms              │
    └────────┬──────────────────────┘
             │
         Repetir
```

## Pruebas Sugeridas

1. **Prueba funcional básica**
   - Presionar cada botón y verificar LED correcto
   - Verificar mensajes en consola

2. **Prueba de aleatoriedad**
   - Jugar varias rondas, verificar resultados diversos

3. **Prueba de debounce**
   - Presionar botones rápidamente
   - Verificar que no haya múltiples activaciones

4. **Prueba de validación**
   - Intentar presionar múltiples botones (debe rechazar)

5. **Prueba de recuperación**
   - Verificar que programa se reinicia correctamente para nuevas jugadas

## Limitaciones Conocidas

- No hay almacenamiento de puntajes entre sesiones
- Delay por software (no ideal, se puede mejorar con timer)
- Sin protección contra condiciones de carrera (puede mejorarse con interrupciones)

## Mejoras Futuras

- Implementar delays con Timer0
- Usar interrupciones para GPIO
- Agregar pantalla LCD/OLED para mostrar resultados
- Almacenar puntaje en EEPROM
- Agregar sonido (buzzer)
- Implementar dificultad variable

## Contacto y Soporte

Para preguntas sobre la implementación, revisar:
- `DOCUMENTACION.md` - Descripción general
- `NOTAS_TECNICAS.md` - Detalles técnicos
- Código comentado en `piedra-papel-tijera-lpc17xx.c`

## Licencia

Este proyecto utiliza las librerías CMSIS de NXP bajo los términos de la licencia NXP.

---

**Versión**: 1.0  
**Microcontrolador**: LPC1769  
**Lenguaje**: C (C11)  
**IDE**: MCUXpresso  
**Última actualización**: Marzo 2025

