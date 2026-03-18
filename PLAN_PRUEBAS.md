# Plan de Pruebas - Piedra, Papel o Tijera LPC1769

## 1. Prueba de Compilación

### Objetivo
Verificar que el código se compila sin errores o advertencias críticas.

### Pasos
```bash
cd /home/tanti/Documents/MCUXpresso_25.6.136/workspace/piedra-papel-tijera-lpc17xx
arm-none-eabi-gcc -c src/piedra-papel-tijera-lpc17xx.c \
  -I CMSISv2p00_LPC17xx/inc \
  -I CMSISv2p00_LPC17xx/Drivers/inc \
  -D__USE_CMSIS=CMSISv2p00_LPC17xx \
  -D__LPC17XX__ -D__CODE_RED -D__REDLIB__ -DCORE_M3 \
  -mcpu=cortex-m3 -mthumb -o piedra-papel-tijera.o
```

### Resultado Esperado
- Archivo `.o` se crea sin errores
- Sin warnings de `undefined reference` para símbolos principales

---

## 2. Prueba de Inicialización GPIO

### Objetivo
Verificar que GPIO se inicializa correctamente.

### Procedimiento
1. Cargar firmware en el LPC1769
2. Conectar analizador lógico o multímetro a P0.0-P0.6
3. Ejecutar el programa

### Resultado Esperado
- P0.4, P0.5, P0.6 comienzan en estado LOW (0V)
- P0.0, P0.1, P0.2 aceptan entrada
- Mensaje de bienvenida aparece en consola

---

## 3. Prueba Individual de Botones

### Objetivo
Verificar que cada botón es reconocido correctamente.

### Prueba 3.1: Botón Piedra (P0.0)
**Pasos:**
1. Presionar botón en P0.0
2. Mantener presionado 1 segundo
3. Soltar botón

**Resultado Esperado:**
```
=== NUEVA JUGADA ===
Jugada del usuario: Piedra
Jugada del CPU: [Piedra|Papel|Tijera]
Resultado: [EMPATE|GANA EL JUGADOR|GANA EL CPU]
```
- LED correspondiente se enciende
- Consola muestra jugada

### Prueba 3.2: Botón Papel (P0.1)
**Pasos:**
1. Presionar botón en P0.1
2. Mantener presionado 1 segundo
3. Soltar botón

**Resultado Esperado:**
- Igual a 3.1, pero "Jugada del usuario: Papel"

### Prueba 3.3: Botón Tijera (P0.2)
**Pasos:**
1. Presionar botón en P0.2
2. Mantener presionado 1 segundo
3. Soltar botón

**Resultado Esperado:**
- Igual a 3.1, pero "Jugada del usuario: Tijera"

---

## 4. Prueba de LEDs

### Objetivo
Verificar que cada LED se enciende cuando corresponde.

### Prueba 4.1: LED Empate (P0.4)
**Pasos:**
1. Presionar Piedra → CPU juega Piedra (esperar a que ocurra)
2. O presionar Papel → CPU juega Papel (esperar a que ocurra)
3. O presionar Tijera → CPU juega Tijera (esperar a que ocurra)

**Verificación:**
- LED en P0.4 se enciende cuando hay empate
- Consola muestra "EMPATE"

### Prueba 4.2: LED Gana Jugador (P0.5)
**Pasos:**
1. Presionar Papel → CPU juega Piedra (esperar a que ocurra)
2. O presionar Piedra → CPU juega Tijera (esperar a que ocurra)
3. O presionar Tijera → CPU juega Papel (esperar a que ocurra)

**Verificación:**
- LED en P0.5 se enciende cuando gana jugador
- Consola muestra "GANA EL JUGADOR"

### Prueba 4.3: LED Gana CPU (P0.6)
**Pasos:**
1. Presionar Tijera → CPU juega Piedra (esperar a que ocurra)
2. O presionar Piedra → CPU juega Papel (esperar a que ocurra)
3. O presionar Papel → CPU juega Tijera (esperar a que ocurra)

**Verificación:**
- LED en P0.6 se enciende cuando gana CPU
- Consola muestra "GANA EL CPU"

---

## 5. Prueba de Aleatoriedad

### Objetivo
Verificar que el programa genera jugadas variadas, no siempre la misma.

### Procedimiento
1. Jugar 20 rondas (presionar el mismo botón 20 veces)
2. Anotar todas las jugadas del CPU
3. Verificar variedad en los resultados

### Resultado Esperado
```
Ronda 1: CPU juega Papel    → Resultado: GANA EL CPU
Ronda 2: CPU juega Piedra   → Resultado: EMPATE
Ronda 3: CPU juega Tijera   → Resultado: GANA EL JUGADOR
...
```
- Los resultados varían (no siempre gana o pierde)
- Todos los tres resultados posibles ocurren

---

## 6. Prueba de Debounce

### Objetivo
Verificar que el programa rechaza rebotes de botones.

### Procedimiento
1. Presionar rápidamente el botón varias veces (tap rápidos)
2. Observar consola
3. Contar el número de jugadas registradas

### Resultado Esperado
- Solo **una** jugada por pulsación de botón
- No hay múltiples jugadas de un solo tap
- Ejemplo: presionar 5 veces rápido = 5 jugadas (no 10+)

---

## 7. Prueba de Validación de Entrada

### Objetivo
Verificar que el programa rechaza entradas inválidas.

### Prueba 7.1: Múltiples Botones Simultáneamente
**Procedimiento:**
1. Presionar simultáneamente P0.0 y P0.1 (Piedra + Papel)
2. Presionar simultáneamente P0.0 y P0.2 (Piedra + Tijera)
3. Presionar simultáneamente P0.1 y P0.2 (Papel + Tijera)
4. Presionar los tres botones juntos

**Resultado Esperado:**
- No se registra jugada
- No se enciende LED
- No hay salida en consola
- El programa espera a que se suelte todo

### Prueba 7.2: Sin Botones Presionados
**Procedimiento:**
1. Ejecutar programa sin presionar nada
2. Esperar 10 segundos

**Resultado Esperado:**
- No se registra jugada
- No se enciende LED
- No hay salida en consola (excepto mensaje inicial)

---

## 8. Prueba de Recuperación

### Objetivo
Verificar que el programa puede jugar múltiples rondas sin problemas.

### Procedimiento
1. Jugar 50 rondas consecutivas
2. Observar comportamiento entre rondas
3. Presionar botones a velocidades variadas

### Resultado Esperado
- Cada jugada se procesa correctamente
- No hay cuelgues del programa
- LEDs se encienden y apagan correctamente en cada ronda
- Consola muestra todos los resultados

---

## 9. Prueba de Consola Semihosting

### Objetivo
Verificar que semihosting funciona correctamente.

### Procedimiento
1. Abrir consola de semihosting en MCUXpresso
2. Ejecutar programa
3. Presionar botones y observar salida

### Resultado Esperado
```
=== JUEGO PIEDRA, PAPEL O TIJERA ===
Presione uno de los botones:
Botón 0 (P0.0) = Piedra
Botón 1 (P0.1) = Papel
Botón 2 (P0.2) = Tijera

=== NUEVA JUGADA ===
Jugada del usuario: [Jugada]
Jugada del CPU: [Jugada]
Resultado: [Resultado]
```
- Texto se muestra clara y correctamente
- No hay caracteres basura
- Codificación correcta

---

## 10. Prueba de Matrices

### Objetivo
Verificar que la lógica del juego es correcta.

### Matriz de Verdad Esperada

| Usuario | CPU | Esperado |
|:---:|:---:|:---:|
| Piedra | Piedra | EMPATE |
| Piedra | Papel | GANA EL CPU |
| Piedra | Tijera | GANA EL JUGADOR |
| Papel | Piedra | GANA EL JUGADOR |
| Papel | Papel | EMPATE |
| Papel | Tijera | GANA EL CPU |
| Tijera | Piedra | GANA EL CPU |
| Tijera | Papel | GANA EL JUGADOR |
| Tijera | Tijera | EMPATE |

### Procedimiento
1. Para cada combinación, jugar hasta obtenerla
2. Verificar que el resultado mostrado es correcto

**Nota**: Puede requerir muchas rondas por la aleatoriedad de CPU

---

## 11. Prueba de Estrés

### Objetivo
Verificar que el programa es estable bajo condiciones extremas.

### Procedimiento
1. Presionar botones continuamente durante 1 minuto
2. Alternar entre los tres botones
3. Presionar rápidamente y lentamente
4. Observar comportamiento

### Resultado Esperado
- Programa no se cuelga
- No hay pérdida de datos
- LEDs funcionan correctamente
- Consola muestra todos los eventos

---

## 12. Prueba de Timing

### Objetivo
Verificar que los delays funcionan correctamente.

### Procedimiento
1. Usar osciloscopio o analizador lógico en P0.4-P0.6
2. Medir duración del LED encendido
3. Medir tiempo entre apagado de un LED y encendido del siguiente

### Resultado Esperado
- LED permanece encendido durante toda la duración de espera
- Tiempo de respuesta < 500ms desde presión hasta LED

---

## Matriz de Pruebas

| # | Tipo | Descripción | Estado |
|---|------|-------------|--------|
| 1 | Compilación | Compila sin errores | [ ] |
| 2 | Inicialización | GPIO se inicializa correctamente | [ ] |
| 3.1 | Entrada | Botón Piedra funciona | [ ] |
| 3.2 | Entrada | Botón Papel funciona | [ ] |
| 3.3 | Entrada | Botón Tijera funciona | [ ] |
| 4.1 | Salida | LED Empate funciona | [ ] |
| 4.2 | Salida | LED Gana Jugador funciona | [ ] |
| 4.3 | Salida | LED Gana CPU funciona | [ ] |
| 5 | Aleatoriedad | Resultados variados | [ ] |
| 6 | Debounce | Rebotes rechazados | [ ] |
| 7.1 | Validación | Múltiples botones rechazados | [ ] |
| 7.2 | Validación | Sin entrada maneja correctamente | [ ] |
| 8 | Recuperación | Múltiples rondas OK | [ ] |
| 9 | Consola | Semihosting funciona | [ ] |
| 10 | Lógica | Matriz de resultados correcta | [ ] |
| 11 | Estrés | Programa estable bajo carga | [ ] |
| 12 | Timing | Delays correctos | [ ] |

---

## Registro de Resultados

### Fecha de Prueba: _______________
### Probador: _______________
### Versión del Firmware: _______________

### Resultados:
```
Total de pruebas: 17
Pasadas: ____
Fallidas: ____
Inconclusivas: ____
```

### Problemas Encontrados:
1. _________________________________
2. _________________________________
3. _________________________________

### Notas Adicionales:
_____________________________________
_____________________________________
_____________________________________

---

## Criterio de Aceptación

El programa se considera **APROBADO** si:
- ✓ Compila sin errores
- ✓ Todos los botones son reconocidos
- ✓ Todos los LEDs funcionan
- ✓ Lógica del juego es correcta (matriz)
- ✓ No hay entradas inválidas
- ✓ Debounce funciona
- ✓ Semihosting muestra información
- ✓ Programa no se cuelga
- ✓ Puede jugar múltiples rondas


