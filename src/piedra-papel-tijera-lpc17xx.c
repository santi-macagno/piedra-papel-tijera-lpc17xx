/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definiciones de jugadas
#define PIEDRA    0
#define PAPEL     1
#define TIJERA    2

// Puerto GPIO utilizado (Puerto 0)
#define GPIO_PORT LPC_GPIO0

// Máscaras de bits
#define ENTRADA_MASK    0x07    // Bits 0, 1, 2 para entrada
#define SALIDA_MASK     0x70    // Bits 4, 5, 6 para salida

// Bits de salida
#define LED_EMPATE      (1 << 4)     // Bit 4
#define LED_GANA_USER   (1 << 5)     // Bit 5
#define LED_GANA_CPU    (1 << 6)     // Bit 6

// Array de mapeo para convertir entrada a jugada
// Índice: valor de los 3 bits de entrada (0-7)
// Valor: -1 (entrada inválida), 0 (Piedra), 1 (Papel), 2 (Tijera)
int mapa[8] = {-1, PIEDRA, PAPEL, -1, TIJERA, -1, -1, -1};

// Matriz de resultados: resultado[jugador][cpu]
// 1 = gana jugador, 0 = empate, -1 = gana CPU
int resultado[3][3] = {
    { 0, -1, 1},   // Jugador juega Piedra
    { 1,  0, -1},  // Jugador juega Papel
    {-1,  1,  0}   // Jugador juega Tijera
};

// Nombres de las jugadas
const char* nombres_jugada[3] = {"Piedra", "Papel", "Tijera"};

// Función para inicializar GPIO
void GPIO_Init(void) {
    // Configurar bits 0, 1, 2 como entrada (FIODIR = 0)
    // Configurar bits 4, 5, 6 como salida (FIODIR = 1)
    // Los demás bits quedan como entrada por defecto
    GPIO_PORT->FIODIR = SALIDA_MASK;  // Solo bits 4, 5, 6 como salida
}

// Función para leer la entrada de GPIO
int Leer_Entrada(void) {
    return (GPIO_PORT->FIOPIN & ENTRADA_MASK);
}

// Función para apagar todos los LEDs
void Apagar_LEDs(void) {
    GPIO_PORT->FIOCLR = SALIDA_MASK;
}

// Función para encender un LED
void Encender_LED(int led) {
    GPIO_PORT->FIOSET = led;
}

// Función para generar una jugada aleatoria del CPU
int Generar_Jugada_CPU(void) {
    return rand() % 3;  // 0, 1 o 2
}

// Función para hacer una pausa (delay por software)
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 123; j++) {  // Aproximado para 1ms @ 60MHz
            __asm("nop");
        }
}

// Función para procesar una jugada válida
void Procesar_Jugada(int entrada_user) {
    // Mapear entrada a jugada del usuario
    int jugada_user = mapa[entrada_user];

    // Generar jugada del CPU
    int jugada_cpu = Generar_Jugada_CPU();

    // Determinar resultado
    int res = resultado[jugada_user][jugada_cpu];

    // Apagar LEDs anteriores
    Apagar_LEDs();

    // Encender LED según resultado
    if (res == 0) {
        Encender_LED(LED_EMPATE);
    } else if (res == 1) {
        Encender_LED(LED_GANA_USER);
    } else {
        Encender_LED(LED_GANA_CPU);
    }

    // Imprimir información por semihosting
    printf("=== NUEVA JUGADA ===\n");
    printf("Jugada del usuario: %s\n", nombres_jugada[jugada_user]);
    printf("Jugada del CPU: %s\n", nombres_jugada[jugada_cpu]);

    if (res == 0) {
        printf("Resultado: EMPATE\n");
    } else if (res == 1) {
        printf("Resultado: GANA EL JUGADOR\n");
    } else {
        printf("Resultado: GANA EL CPU\n");
    }
    printf("\n");
}

int main(void) {
    // Inicializar el generador de números aleatorios
    srand((unsigned int)time(NULL));

    // Inicializar GPIO
    GPIO_Init();

    // Apagar todos los LEDs al inicio
    Apagar_LEDs();

    printf("=== JUEGO PIEDRA, PAPEL O TIJERA ===\n");
    printf("Presione uno de los botones:\n");
    printf("Botón 0 (P0.0) = Piedra\n");
    printf("Botón 1 (P0.1) = Papel\n");
    printf("Botón 2 (P0.2) = Tijera\n\n");

    // Variable para almacenar la entrada anterior
    int entrada_anterior = 0;

    // Bucle principal
    while(1) {
        // Leer entrada actual
        int entrada_actual = Leer_Entrada();

        // Verificar si hay un cambio en la entrada
        // y que sea una entrada válida (1, 2 o 4)
        if (entrada_actual != entrada_anterior) {
            if (entrada_actual != 0 && mapa[entrada_actual] != -1) {
                // Entrada válida detectada
                Procesar_Jugada(entrada_actual);

                // Esperar a que se suelte el botón
                entrada_anterior = entrada_actual;
                delay_ms(50);  // Debounce

                while (Leer_Entrada() != 0) {
                    delay_ms(10);
                }

                delay_ms(100);  // Esperar antes de aceptar siguiente entrada
                entrada_anterior = 0;
            }
        }

        delay_ms(10);
    }

    return 0;
}
