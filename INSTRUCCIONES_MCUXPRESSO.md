# Instrucciones de Uso en MCUXpresso

## 📋 Tabla de Contenidos
1. [Apertura del Proyecto](#apertura-del-proyecto)
2. [Compilación](#compilación)
3. [Depuración y Ejecución](#depuración-y-ejecución)
4. [Pruebas en Hardware](#pruebas-en-hardware)
5. [Solución de Problemas](#solución-de-problemas)

---

## Apertura del Proyecto

### Opción 1: Importar Proyecto Existente

1. **Abrir MCUXpresso IDE**
2. **Ir a:** File → Open Projects from File System...
3. **Seleccionar carpeta:**
   ```
   /home/tanti/Documents/MCUXpresso_25.6.136/workspace/piedra-papel-tijera-lpc17xx
   ```
4. **Click:** "Open" (o "Finish")
5. El proyecto aparecerá en el Project Explorer

### Opción 2: Trabajar en Espacio Existente

Si el proyecto ya está en el workspace:

1. **Ir a:** Window → Show View → Project Explorer
2. El proyecto debe aparecer automáticamente
3. Expandir el árbol del proyecto

---

## Compilación

### Método 1: Compilación Automática

1. **Habilitar compilación automática:**
   - Ir a: Project → Build Automatically
   - Verificar que esté marcado

2. El proyecto se compilará automáticamente al guardar cambios

### Método 2: Compilación Manual

1. **Seleccionar el proyecto** en Project Explorer
2. **Ir a:** Project → Build Project
   - O presionar: **Ctrl+B** (Windows/Linux)
   - O presionar: **Cmd+B** (Mac)

3. **Verificar en Console:**
   - El output debe mostrar:
   ```
   Building target: piedra-papel-tijera-lpc17xx
   Linking C executable cmake-build-debug/piedra-papel-tijera-lpc17xx
   ```
   - Debe terminar con:
   ```
   [100%] Linking C executable ...
   [100%] Built target piedra-papel-tijera-lpc17xx
   ```

### Verificación de Errores

Si hay errores:

1. **Revisar la consola de errores:**
   - Window → Show View → Problems

2. **Errores comunes:**
   - ❌ "Undefined reference to 'LPC_GPIO0'"
     - Solución: Verificar flags de compilación en CMakeLists.txt
   - ❌ "Multiple definition of 'main'"
     - Solución: Verificar que no hay otros archivos main en el proyecto
   - ❌ "Compilation failed"
     - Solución: Limpiar proyecto (Project → Clean Project)

---

## Depuración y Ejecución

### Preparación del Hardware

1. **Conexiones:**
   - Conectar botones a: P0.0, P0.1, P0.2
   - Conectar LEDs a: P0.4, P0.5, P0.6
   - Conectar programador JTAG/SWD al LPC1769

2. **Alimentación:**
   - Verificar voltaje 3.3V
   - Conectar GND común

### Carga del Firmware

#### Opción 1: Depuración (Recomendado)

1. **Click en el botón de Depuración:**
   - Icono de "insecto" en la barra de herramientas
   - O: Debug → Debug As → Embedded C/C++ Application

2. **Primera vez:**
   - Se abrirá ventana de configuración de depuración
   - Seleccionar programador (JTAG/SWD)
   - Click "OK"

3. **MCUXpresso cargará el firmware automáticamente**

#### Opción 2: Ejecutar sin Depuración

1. **Click en botón "Run":**
   - Icono de "play" verde en la barra
   - O: Run → Run As → Embedded C/C++ Application

2. **El programa comenzará automáticamente**

### Consola de Semihosting

Para ver la salida del programa:

1. **Ir a:** Window → Show View → Console
2. **Seleccionar la consola correcta:**
   - Verificar que está seleccionada la consola de semihosting
   - Debe mostrar el mensaje de bienvenida

3. **Verás:**
   ```
   === JUEGO PIEDRA, PAPEL O TIJERA ===
   Presione uno de los botones:
   Botón 0 (P0.0) = Piedra
   Botón 1 (P0.1) = Papel
   Botón 2 (P0.2) = Tijera
   ```

---

## Pruebas en Hardware

### Prueba 1: Verificar Compilación

1. Compilar proyecto (Ctrl+B)
2. ✓ Debe completarse sin errores

### Prueba 2: Verificar Carga

1. Cargar firmware (F11 para depuración)
2. Verificar que no hay errores de conexión
3. ✓ Mensaje de bienvenida debe aparecer

### Prueba 3: Probar Botón Piedra

1. **Presionar botón en P0.0**
2. Mantener 1 segundo
3. Soltar botón

**Resultado esperado:**
```
=== NUEVA JUGADA ===
Jugada del usuario: Piedra
Jugada del CPU: [Piedra|Papel|Tijera]
Resultado: [EMPATE|GANA EL JUGADOR|GANA EL CPU]
```
- LED correspondiente se enciende
- No más de una jugada por pulsación

### Prueba 4: Probar Botón Papel

1. **Presionar botón en P0.1**
2. Mantener 1 segundo
3. Soltar botón

**Resultado esperado:**
```
=== NUEVA JUGADA ===
Jugada del usuario: Papel
Jugada del CPU: [Piedra|Papel|Tijera]
Resultado: [EMPATE|GANA EL JUGADOR|GANA EL CPU]
```

### Prueba 5: Probar Botón Tijera

1. **Presionar botón en P0.2**
2. Mantener 1 segundo
3. Soltar botón

**Resultado esperado:**
```
=== NUEVA JUGADA ===
Jugada del usuario: Tijera
Jugada del CPU: [Piedra|Papel|Tijera]
Resultado: [EMPATE|GANA EL JUGADOR|GANA EL CPU]
```

### Prueba 6: Verificar LEDs

**Para cada resultado posible:**

1. Piedra del usuario:
   - ✓ vs Piedra → LED P0.4 (Empate)
   - ✓ vs Papel → LED P0.6 (CPU gana)
   - ✓ vs Tijera → LED P0.5 (Usuario gana)

2. Papel del usuario:
   - ✓ vs Piedra → LED P0.5 (Usuario gana)
   - ✓ vs Papel → LED P0.4 (Empate)
   - ✓ vs Tijera → LED P0.6 (CPU gana)

3. Tijera del usuario:
   - ✓ vs Piedra → LED P0.6 (CPU gana)
   - ✓ vs Papel → LED P0.5 (Usuario gana)
   - ✓ vs Tijera → LED P0.4 (Empate)

### Prueba 7: Verificar Debounce

1. **Presionar rápidamente 10 veces el mismo botón**
2. Contar jugadas en consola
3. ✓ Debe haber exactamente 10 jugadas (no más)

### Prueba 8: Validación de Entrada

1. **Presionar dos botones simultáneamente**
2. ✓ No debe registrar jugada
3. ✓ No debe encender LED
4. ✓ No debe imprimir en consola

---

## Solución de Problemas

### Problema: "No se carga el firmware"

**Síntomas:**
- Error: "Connection failed" o similar

**Soluciones:**
1. Verificar conexión USB del programador
2. Verificar que el LPC1769 está alimentado (3.3V)
3. Ir a: Debug → Device Configuration
4. Verificar que el dispositivo es LPC1769
5. Intentar reset de hardware

### Problema: "No hay salida en consola"

**Síntomas:**
- Consola vacía, sin mensajes

**Soluciones:**
1. Verificar que semihosting está habilitado:
   - Debug → Device Configuration → Semihosting
   - ✓ Debe estar marcado
2. Verificar que el programa está corriendo:
   - Window → Show View → Debug → Verificar estado "Running"
3. Si está pausado, presionar Resume (F8)

### Problema: "Botones no funcionan"

**Síntomas:**
- Presionar botones, sin respuesta

**Soluciones:**
1. Verificar conexiones:
   - P0.0, P0.1, P0.2 a botones
   - GND común
2. Verificar voltaje con multímetro:
   - 3.3V cuando no presionado
   - 0V cuando presionado
3. Verificar con osciloscopio si hay ruido (debería haber debounce)
4. Verificar que no hay cortocircuito

### Problema: "LEDs no encienden"

**Síntomas:**
- LEDs no responden

**Soluciones:**
1. Verificar conexiones:
   - P0.4, P0.5, P0.6 a LEDs
   - Ánodo a GPIO (con resistencia ~330Ω)
   - Cátodo a GND
2. Verificar polaridad:
   - LED debe estar al revés para invertir
3. Verificar resistencia:
   - No debe estar quemada
4. Reemplazar LED si es necesario

### Problema: "Compilación falla"

**Síntomas:**
- Errores de compilación

**Soluciones:**
1. Limpiar proyecto:
   - Project → Clean Project
2. Reconstruir:
   - Project → Build Project
3. Verificar CMakeLists.txt:
   - Flags deben incluir: `-D__USE_CMSIS=CMSISv2p00_LPC17xx`
4. Verificar path de includes:
   - Deben apuntar a: `CMSISv2p00_LPC17xx/inc`

### Problema: "Juego funciona pero lento"

**Síntomas:**
- Retrasos en respuesta

**Soluciones:**
1. Verificar frecuencia del MCU:
   - Debe ser ~60MHz
2. Verificar que no hay otros procesos pesados
3. Revisar la función delay_ms:
   - Puede necesitar ajuste de la constante 123

### Problema: "Aleatoriedad no funciona"

**Síntomas:**
- Mismo resultado todo el tiempo

**Soluciones:**
1. Verificar que `time(NULL)` funciona:
   - Puede necesitar inicializador diferente
2. Reemplazar con:
   ```c
   srand((unsigned)&entrada_anterior);  // Usar dirección de variable
   ```
3. O usar RNG basado en timer del MCU

---

## Atajos Útiles en MCUXpresso

| Acción | Windows/Linux | Mac |
|--------|---------------|-----|
| Compilar | Ctrl+B | Cmd+B |
| Ejecutar depuración | F11 | Cmd+F11 |
| Pausar ejecución | F6 | Cmd+F6 |
| Continuar (Resume) | F8 | Cmd+F8 |
| Step Over | F6 | Cmd+F6 |
| Step Into | F5 | Cmd+F5 |
| Establecer breakpoint | Ctrl+Shift+B | Cmd+Shift+B |
| Limpiar proyecto | Ctrl+Shift+K | Cmd+Shift+K |
| Mostrar consola | N/A | View → Console |

---

## Información Útil

### Ubicación de Archivos Compilados

```
/home/tanti/Documents/MCUXpresso_25.6.136/workspace/
  piedra-papel-tijera-lpc17xx/
  ├── cmake-build-debug/
  │   └── piedra-papel-tijera-lpc17xx  ← Ejecutable
  └── src/
      └── piedra-papel-tijera-lpc17xx.c
```

### Logs y Diagnóstico

- **Log de compilación:** Project → Show Console Output
- **Debug information:** Debug → Display in Debugger
- **Trace:** Debug → Debug Trace

### Configuración Recomendada

En MCUXpresso Preferences:
- Window → Preferences → MCUXpresso → Build
- ✓ Enable all build outputs
- ✓ Show build times

---

## Verificación Final

Antes de dar por completado:

- [ ] Proyecto compila sin errores
- [ ] Firmware se carga correctamente
- [ ] Consola muestra mensaje de bienvenida
- [ ] Botón Piedra funciona
- [ ] Botón Papel funciona
- [ ] Botón Tijera funciona
- [ ] LED Empate funciona
- [ ] LED Gana Jugador funciona
- [ ] LED Gana CPU funciona
- [ ] Consola muestra información de cada jugada
- [ ] Debounce funciona correctamente
- [ ] Puede jugar múltiples rondas

---

**¡Felicidades! El proyecto está listo para usar.**

Para preguntas o problemas, revisar:
- PLAN_PRUEBAS.md
- NOTAS_TECNICAS.md
- Código comentado en piedra-papel-tijera-lpc17xx.c


