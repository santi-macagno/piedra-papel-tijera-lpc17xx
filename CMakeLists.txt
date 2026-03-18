cmake_minimum_required(VERSION 3.20)

# Evita que CMake falle al probar el compilador de ARM
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(piedra-papel-tijera-lpc17xx C ASM)

set(CMAKE_C_STANDARD 11)

# 1. Definimos la ruta de la librería según tu estructura
set(CMSIS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMSISv2p00_LPC17xx")

# 2. Recolectamos todos los archivos .c (src del proyecto y de la lib)
file(GLOB_RECURSE SOURCES
        "src/*.c"
        "${CMSIS_DIR}/src/*.c"
        "${CMSIS_DIR}/Drivers/src/*.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

# 3. DIRECTORIOS DE INCLUSIÓN (Donde están tus .h)
target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMSIS_DIR}/inc"          # Aquí están LPC17xx.h y core_cm3.h
        "${CMSIS_DIR}/Drivers/inc"  # Aquí están los drivers (gpio, uart, etc.)
        "inc"                       # Por si creaste la carpeta inc raíz
)

# 4. Definiciones necesarias (Actualizadas según tu log de MCUXpresso)
target_compile_definitions(${PROJECT_NAME} PRIVATE
        DEBUG
        __CODE_RED
        __REDLIB__
        CORE_M3
        __LPC17XX__
        __USE_CMSIS=CMSISv2p00_LPC17xx
)

# 5. Flags de arquitectura ARM
set(MCU_FLAGS -mcpu=cortex-m3 -mthumb -mfloat-abi=soft)
target_compile_options(${PROJECT_NAME} PRIVATE ${MCU_FLAGS} -Wall -g)

# 6. Opciones del Linker (Usando tus archivos .ld copiados a la raíz)
target_link_options(${PROJECT_NAME} PRIVATE
        ${MCU_FLAGS}
        --specs=nosys.specs
        -L "${CMAKE_CURRENT_SOURCE_DIR}"
        -T "${CMAKE_CURRENT_SOURCE_DIR}/linker_script.ld"
        -Wl,-Map="${PROJECT_NAME}.map"
        -Wl,--gc-sections
)