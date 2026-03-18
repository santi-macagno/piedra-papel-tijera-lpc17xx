# 📑 ÍNDICE GENERAL - Proyecto Piedra, Papel o Tijera LPC1769

## 🎯 INICIO RÁPIDO

### Para Empezar Inmediatamente:
1. Leer: **[RESUMEN_RAPIDO.md](RESUMEN_RAPIDO.md)** - 2 minutos
2. Cargar código en MCUXpresso
3. Seguir: **[INSTRUCCIONES_MCUXPRESSO.md](INSTRUCCIONES_MCUXPRESSO.md)** - 5 minutos
4. ¡Jugar!

---

## 📚 DOCUMENTACIÓN DISPONIBLE

### 🟢 NIVEL 1: Descripción General
- **[README.md](README.md)**
  - Descripción general del proyecto
  - Características principales
  - Requisitos de hardware
  - Diagrama de flujo
  - Características implementadas
  - **Tiempo de lectura:** 10 minutos

- **[RESUMEN_RAPIDO.md](RESUMEN_RAPIDO.md)**
  - Referencia rápida de todo
  - Tablas y matrices
  - Checklists
  - Troubleshooting básico
  - **Tiempo de lectura:** 5 minutos

### 🟡 NIVEL 2: Documentación Técnica
- **[DOCUMENTACION.md](DOCUMENTACION.md)**
  - Descripción detallada del programa
  - Funciones implementadas
  - Estructuras de datos
  - Compilación y requisitos
  - **Tiempo de lectura:** 15 minutos

- **[NOTAS_TECNICAS.md](NOTAS_TECNICAS.md)**
  - Detalles técnicos profundos
  - Manipulación de registros GPIO
  - Algoritmos detallados
  - Operaciones de bit
  - Ejemplos de código
  - **Tiempo de lectura:** 20 minutos

### 🔴 NIVEL 3: Pruebas e Implementación
- **[PLAN_PRUEBAS.md](PLAN_PRUEBAS.md)**
  - 12 pruebas detalladas
  - Procedimientos paso a paso
  - Resultados esperados
  - Matriz de pruebas
  - Checklist de aceptación
  - **Tiempo de lectura:** 25 minutos

- **[INSTRUCCIONES_MCUXPRESSO.md](INSTRUCCIONES_MCUXPRESSO.md)**
  - Cómo usar en MCUXpresso IDE
  - Compilación y depuración
  - Atajos de teclado
  - Solución de problemas
  - **Tiempo de lectura:** 15 minutos

- **[INDEX.md](INDEX.md)** (Este archivo)
  - Guía de navegación
  - Mapa del proyecto
  - Referencias cruzadas

### 📄 CÓDIGO FUENTE
- **[src/piedra-papel-tijera-lpc17xx.c](src/piedra-papel-tijera-lpc17xx.c)**
  - Implementación completa
  - 177 líneas comentadas
  - 8 funciones
  - Lista para compilar
  - Compatible con MCUXpresso

---

## 🗂️ ESTRUCTURA DEL PROYECTO

```
piedra-papel-tijera-lpc17xx/
├── 📄 Archivos de Documentación
│   ├── README.md                      [Inicio]
│   ├── RESUMEN_RAPIDO.md             [Referencia rápida]
│   ├── DOCUMENTACION.md              [Guía técnica]
│   ├── NOTAS_TECNICAS.md             [Detalles técnicos]
│   ├── PLAN_PRUEBAS.md               [Pruebas]
│   ├── INSTRUCCIONES_MCUXPRESSO.md  [Cómo usar IDE]
│   └── INDEX.md                      [Este archivo]
│
├── 📁 src/
│   └── piedra-papel-tijera-lpc17xx.c [Código principal ⭐]
│
├── 📁 CMSISv2p00_LPC17xx/            [Librerías CMSIS]
│   ├── inc/                          [Headers]
│   ├── Drivers/                      [Drivers GPIO]
│   └── ...
│
├── 📁 cmake-build-debug/             [Compilado]
│   └── piedra-papel-tijera-lpc17xx   [Ejecutable]
│
└── 📄 CMakeLists.txt                 [Configuración CMake]
```

---

## 🎓 GUÍA DE LECTURA POR OBJETIVO

### 👨‍💼 "Quiero usar el código en 5 minutos"
1. [RESUMEN_RAPIDO.md](RESUMEN_RAPIDO.md) - Configuración rápida
2. [INSTRUCCIONES_MCUXPRESSO.md](INSTRUCCIONES_MCUXPRESSO.md) - Cómo cargar
3. ¡Listo!

### 🔧 "Quiero entender cómo funciona"
1. [README.md](README.md) - Visión general
2. [DOCUMENTACION.md](DOCUMENTACION.md) - Funciones
3. [src/piedra-papel-tijera-lpc17xx.c](src/piedra-papel-tijera-lpc17xx.c) - Código
4. [NOTAS_TECNICAS.md](NOTAS_TECNICAS.md) - Detalles

### 🧪 "Quiero probar todo"
1. [PLAN_PRUEBAS.md](PLAN_PRUEBAS.md) - Procedimientos
2. [INSTRUCCIONES_MCUXPRESSO.md](INSTRUCCIONES_MCUXPRESSO.md) - Ejecución
3. Llenar checklist en PLAN_PRUEBAS.md

### 🐛 "Tengo un problema"
1. [RESUMEN_RAPIDO.md](RESUMEN_RAPIDO.md#troubleshooting) - Troubleshooting básico
2. [INSTRUCCIONES_MCUXPRESSO.md](INSTRUCCIONES_MCUXPRESSO.md#solución-de-problemas) - Problemas IDE
3. [PLAN_PRUEBAS.md](PLAN_PRUEBAS.md) - Diagnóstico

### 📚 "Quiero una documentación completa"
- Leer en orden: README.md → DOCUMENTACION.md → NOTAS_TECNICAS.md → PLAN_PRUEBAS.md

---

## 🔍 BÚSQUEDA RÁPIDA DE TÓPICOS

### Configuración de Hardware
- [README.md - Diagrama de Hardware](README.md#diagrama-de-flujo)
- [DOCUMENTACION.md - Hardware](DOCUMENTACION.md#hardware-utilizado)

### Estructuras de Datos
- [DOCUMENTACION.md - Arrays y Matrices](DOCUMENTACION.md#matriz-de-resultados)
- [NOTAS_TECNICAS.md - Estructuras](NOTAS_TECNICAS.md#estructuras-de-datos)

### Compilación
- [README.md - Compilación Manual](README.md#manualmente-con-gcc-arm)
- [INSTRUCCIONES_MCUXPRESSO.md - Compilación](INSTRUCCIONES_MCUXPRESSO.md#compilación)

### Depuración
- [INSTRUCCIONES_MCUXPRESSO.md - Depuración](INSTRUCCIONES_MCUXPRESSO.md#depuración-y-ejecución)
- [INSTRUCCIONES_MCUXPRESSO.md - Consola](INSTRUCCIONES_MCUXPRESSO.md#consola-de-semihosting)

### Pruebas
- [PLAN_PRUEBAS.md - Todas las pruebas](PLAN_PRUEBAS.md)
- [PLAN_PRUEBAS.md - Matriz de pruebas](PLAN_PRUEBAS.md#matriz-de-pruebas)

### Problemas y Soluciones
- [INSTRUCCIONES_MCUXPRESSO.md - Troubleshooting](INSTRUCCIONES_MCUXPRESSO.md#solución-de-problemas)
- [RESUMEN_RAPIDO.md - Troubleshooting](RESUMEN_RAPIDO.md#troubleshooting)

---

## ✨ CARACTERÍSTICAS PRINCIPALES

### 🎮 Funcionalidad
- ✓ Lectura de 3 botones
- ✓ Generación aleatoria
- ✓ Matriz de resultados
- ✓ Array de mapeo
- ✓ Control de 3 LEDs
- ✓ Semihosting (consola)
- ✓ Debounce integrado

### 🔧 Técnico
- ✓ 177 líneas de código
- ✓ 8 funciones
- ✓ 3 estructuras de datos
- ✓ Compilable
- ✓ Compatible MCUXpresso
- ✓ GPIO P0.0-P0.2 (entrada)
- ✓ GPIO P0.4-P0.6 (salida)

---

## 📊 ESTADÍSTICAS

| Aspecto | Valor |
|---------|-------|
| **Código** | 177 líneas |
| **Funciones** | 8 |
| **Documentación** | 6 archivos |
| **Líneas docs** | ~2000 |
| **Pruebas** | 12 casos |
| **Compilación** | ✓ Exitosa |
| **Tiempo lectura total** | ~60-90 min |
| **Tiempo implementación** | ~15 min |

---

## 🚀 FLUJO RECOMENDADO

```
┌─────────────────────────────┐
│ 1. Leer RESUMEN_RAPIDO.md   │ (5 min)
└────────────┬────────────────┘
             │
┌────────────▼────────────────┐
│ 2. Leer README.md           │ (10 min)
└────────────┬────────────────┘
             │
┌────────────▼────────────────┐
│ 3. Abrir en MCUXpresso      │ (5 min)
└────────────┬────────────────┘
             │
┌────────────▼──────────────────────┐
│ 4. Compilar (Ctrl+B)               │ (2 min)
│    Ver INSTRUCCIONES_MCUXPRESSO.md │
└────────────┬──────────────────────┘
             │
┌────────────▼────────────────┐
│ 5. Cargar firmware (F11)     │ (3 min)
└────────────┬────────────────┘
             │
┌────────────▼────────────────┐
│ 6. Probar en hardware        │ (10 min)
│    Ver PLAN_PRUEBAS.md       │
└────────────┬────────────────┘
             │
        ✓ ¡LISTO!
```

---

## 📞 REFERENCIAS CRUZADAS

### Buscar Tema: GPIO
- ✓ [DOCUMENTACION.md](DOCUMENTACION.md#manipulación-de-puertos-gpio)
- ✓ [NOTAS_TECNICAS.md](NOTAS_TECNICAS.md#operaciones-de-registro-gpio)
- ✓ [PLAN_PRUEBAS.md](PLAN_PRUEBAS.md#7-prueba-de-validación-de-entrada)

### Buscar Tema: Entradas/Salidas
- ✓ [README.md](README.md#hardware-utilizado)
- ✓ [RESUMEN_RAPIDO.md](RESUMEN_RAPIDO.md#-funcionalidad)
- ✓ [NOTAS_TECNICAS.md](NOTAS_TECNICAS.md#mapeo-de-hardware)

### Buscar Tema: Compilación
- ✓ [README.md](README.md#compilación)
- ✓ [INSTRUCCIONES_MCUXPRESSO.md](INSTRUCCIONES_MCUXPRESSO.md#compilación)
- ✓ [RESUMEN_RAPIDO.md](RESUMEN_RAPIDO.md#-compilación-rápida)

### Buscar Tema: Pruebas
- ✓ [PLAN_PRUEBAS.md](PLAN_PRUEBAS.md)
- ✓ [INSTRUCCIONES_MCUXPRESSO.md](INSTRUCCIONES_MCUXPRESSO.md#pruebas-en-hardware)
- ✓ [RESUMEN_RAPIDO.md](RESUMEN_RAPIDO.md#-notas-de-implementación)

---

## 🎯 CHECKLIST DE COMPLETITUD

- ✓ Código escrito y compilable
- ✓ Documentación general (README.md)
- ✓ Referencia rápida (RESUMEN_RAPIDO.md)
- ✓ Documentación técnica (DOCUMENTACION.md)
- ✓ Notas técnicas detalladas (NOTAS_TECNICAS.md)
- ✓ Plan de pruebas (PLAN_PRUEBAS.md)
- ✓ Instrucciones MCUXpresso (INSTRUCCIONES_MCUXPRESSO.md)
- ✓ Índice de navegación (INDEX.md - este archivo)

---

## 📝 INFORMACIÓN DEL DOCUMENTO

- **Versión:** 1.0
- **Fecha:** Marzo 2025
- **Microcontrolador:** LPC1769
- **Lenguaje:** C (C11)
- **IDE:** MCUXpresso
- **Estado:** ✅ Completado y listo para usar

---

## 🎓 ÚLTIMA ACTUALIZACIÓN

Todos los archivos están **sincronizados y actualizados**:
- Código fuente: ✓ Compilable
- Documentación: ✓ Completa
- Pruebas: ✓ Definidas
- Ejemplos: ✓ Incluidos

---

**¡Bienvenido! Comienza por [RESUMEN_RAPIDO.md](RESUMEN_RAPIDO.md) o [README.md](README.md)**


