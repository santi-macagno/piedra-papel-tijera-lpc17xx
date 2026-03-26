# RESUMEN RÁPIDO - Piedra, Papel o Tijera LPC1769

## 📋 Archivos Principales

### Código Fuente
- **`src/piedra-papel-tijera-lpc17xx.c`** (178 líneas)
  - Implementación completa del juego
  - Compilado correctamente (archivo .o generado)

### Documentación
- **`README.md`** - Guía general y características
- **`DOCUMENTACION.md`** - Documentación detallada
- **`NOTAS_TECNICAS.md`** - Detalles técnicos y implementación
- **`PLAN_PRUEBAS.md`** - Plan completo de pruebas
- **`RESUMEN_RAPIDO.md`** - Este archivo

## 🎮 Funcionalidad

### Entradas (GPIO0)
| Bit | Pin | Función |
|:---:|:---:|---------|
| 0 | P0.0 | Botón Piedra |
| 1 | P0.1 | Botón Papel |
| 2 | P0.2 | Botón Tijera |

### Salidas (GPIO0)
| Bit | Pin | LED |
|:---:|:---:|-----|
| 4 | P0.4 | Empate |
| 5 | P0.5 | Gana Jugador |
| 6 | P0.6 | Gana CPU |

## 🔧 Compilación Rápida

```bash
arm-none-eabi-gcc -c src/piedra-papel-tijera-lpc17xx.c \
  -I CMSISv2p00_LPC17xx/inc \
  -I CMSISv2p00_LPC17xx/Drivers/inc \
  -D__USE_CMSIS=CMSISv2p00_LPC17xx \
  -D__LPC17XX__ -D__CODE_RED -D__REDLIB__ -DCORE_M3 \
  -mcpu=cortex-m3 -mthumb
```

## 📊 Matriz de Resultados

| Usuario \ CPU | Piedra | Papel | Tijera |
|:---:|:---:|:---:|:---:|
| **Piedra** | 0 (Empate) | -1 (CPU) | 1 (Usuario) |
| **Papel** | 1 (Usuario) | 0 (Empate) | -1 (CPU) |
| **Tijera** | -1 (CPU) | 1 (Usuario) | 0 (Empate) |

## 🔑 Array de Mapeo

```c
int mapa[8] = {-1, 0, 1, -1, 2, -1, -1, -1};
```

| Entrada (GPIO) | Binario | Mapa | Significado |
|:---:|:---:|:---:|---------|
| 0 | 000 | -1 | Inválido |
| 1 | 001 | 0 | Piedra ✓ |
| 2 | 010 | 1 | Papel ✓ |
| 3 | 011 | -1 | Inválido |
| 4 | 100 | 2 | Tijera ✓ |
| 5-7 | 1xx | -1 | Inválido |

## 🎯 Flujo de Ejecución

```
1. Inicializar GPIO
2. Apagar todos LEDs
3. BUCLE INFINITO:
   a. Leer entrada
   b. ¿Entrada válida? (1, 2, 4)
   c. SI → Procesar:
      - Mapear a jugada
      - Generar CPU aleatoria
      - Consultar matriz
      - Encender LED
      - Imprimir consola
   d. Debounce y esperar suelta
   e. Volver a paso 3a
```

## 💾 Estructuras de Datos

### Array de Mapeo
```c
int mapa[8] = {-1, PIEDRA, PAPEL, -1, TIJERA, -1, -1, -1};
```

### Matriz de Resultados
```c
int resultado[3][3] = {
    { 0, -1, 1},   // Piedra
    { 1,  0, -1},  // Papel
    {-1,  1,  0}   // Tijera
};
```

### Nombres para Consola
```c
const char* nombres_jugada[3] = {"Piedra", "Papel", "Tijera"};
```

## 🔌 Registros GPIO Utilizados

```c
LPC_GPIO0->FIODIR     // Dirección (entrada/salida)
LPC_GPIO0->FIOPIN     // Leer entrada
LPC_GPIO0->FIOSET     // Encender salida
LPC_GPIO0->FIOCLR     // Apagar salida
```

## 📝 Máscaras de Bits

```c
#define ENTRADA_MASK    0x07    // Bits 0-2
#define SALIDA_MASK     0x70    // Bits 4-6
```

## ⏱️ Timing

- **Debounce**: 50ms
- **Espera suelta botón**: variable (10ms checks)
- **Espera siguiente entrada**: 100ms
- **Loop principal**: 10ms delay

## 🎮 Ejemplo de Ejecución

```
Console Output:
=== JUEGO PIEDRA, PAPEL O TIJERA ===
Presione uno de los botones:
Botón 0 (P0.0) = Piedra
Botón 1 (P0.1) = Papel
Botón 2 (P0.2) = Tijera

[Usuario presiona P0.1]

=== NUEVA JUGADA ===
Jugada del usuario: Papel
Jugada del CPU: Piedra
Resultado: GANA EL JUGADOR

LED: P0.5 se enciende (Gana Jugador)

[Esperando siguiente entrada...]
```

## ✅ Checklist de Implementación

- ✓ Lectura de botones con validación
- ✓ Detección de cambios de entrada
- ✓ Debounce implementado
- ✓ Generación de aleatoriedad
- ✓ Array de mapeo
- ✓ Matriz de resultados
- ✓ Control de LEDs
- ✓ Semihosting (printf)
- ✓ Bucle principal continuo
- ✓ Compilación sin errores

## 🧪 Pruebas Esenciales

1. **Compilación**: Genera .o sin errores
2. **Botones**: Cada uno genera jugada correcta
3. **LEDs**: Se encienden según resultado
4. **Consola**: Muestra información correcta
5. **Debounce**: No hay múltiples activaciones
6. **Validación**: Rechaza entradas inválidas
7. **Lógica**: Matriz de resultados correcta
8. **Estabilidad**: Funciona múltiples rondas

## 📚 Referencias Rápidas

### Definiciones de Constantes
```c
#define PIEDRA 0
#define PAPEL  1
#define TIJERA 2
```

### Resultados
```c
1   = Gana Jugador
0   = Empate
-1  = Gana CPU
```

### Valores Válidos de Entrada
```
1 = 0x01 = 0b001 = Piedra
2 = 0x02 = 0b010 = Papel
4 = 0x04 = 0b100 = Tijera
```

## 🚀 Cómo Cargar en MCUXpresso

1. Abrir MCUXpresso
2. File → Open Existing Project
3. Seleccionar carpeta del proyecto
4. Click derecho → Build Project
5. Debugger → Debug As → Embedded C/C++ Application
6. Abrir Console (semihosting)
7. Presionar Play (Resume)

## 🐛 Troubleshooting

| Problema | Solución |
|----------|----------|
| Compilación falla | Verificar flags: `-D__USE_CMSIS=CMSISv2p00_LPC17xx` |
| Botones no funcionan | Verificar conexión en P0.0, P0.1, P0.2 |
| LEDs no encienden | Verificar P0.4, P0.5, P0.6 y resistencias |
| Sin salida en consola | Habilitar semihosting en MCUXpresso |
| Rebotes de botón | Debounce automático (50ms) |

## 📞 Documentación Disponible

| Archivo | Contenido |
|---------|-----------|
| README.md | Descripción general |
| DOCUMENTACION.md | Guía completa |
| NOTAS_TECNICAS.md | Detalles técnicos |
| PLAN_PRUEBAS.md | Plan de pruebas |
| RESUMEN_RAPIDO.md | Este archivo |

---

**Estado**: ✅ Implementación Completa  
**Compilación**: ✅ Exitosa  
**Documentación**: ✅ Completa  
**Listo para**: Cargar en MCUXpresso y ejecutar


