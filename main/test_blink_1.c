#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void) {
    printf("Hello world!\n");

    // Inicializando GPIO4 como entrada con pull-up.
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_NUM_4, GPIO_PULLUP_ONLY);

    // Inicializando GPIO5 como salida.
    gpio_set_direction(GPIO_NUM_5, GPIO_MODE_OUTPUT);

    int button4 = 0;
    int led_state = 0;  // Variable para guardar el estado del LED (0: apagado, 1: encendido)

    while (true) {
        button4 = gpio_get_level(GPIO_NUM_4);

        // Usamos la lógica invertida del pull-up *correctamente* aquí:
        if (button4 == 0) {  // Botón PRESIONADO (nivel bajo)
            if (led_state != 1) { // Si el LED no está YA encendido...
                gpio_set_level(GPIO_NUM_5, 1);  // Encender el LED
                led_state = 1;          // Actualizar el estado
                printf("LED ON! Estado del LED: %d\n", led_state);
            }
        } else {  // Botón NO PRESIONADO (nivel alto)
            if (led_state != 0) { // Si el LED no está YA apagado...
                gpio_set_level(GPIO_NUM_5, 0);  // Apagar el LED
                led_state = 0;          // Actualizar el estado
                printf("LED OFF! Estado del LED: %d\n", led_state);
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);  // Esperar 10ms
    }
}