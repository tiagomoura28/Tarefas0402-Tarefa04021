#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13

int current_led = 0; // Variável para controlar qual LED está aceso

// Função de callback que será chamada repetidamente pelo temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    printf("3 segundo passaram\n");

    // Desliga todos os LEDs
    gpio_put(LED_PIN_GREEN, false);
    gpio_put(LED_PIN_BLUE, false);
    gpio_put(LED_PIN_RED, false);

    // Lógica para acionar o LED atual
    if (current_led == 0) {
        gpio_put(LED_PIN_RED, true);  // Aciona o LED verde
        current_led = 1;  // Pronto para o próximo LED
    } else if (current_led == 1) {
        gpio_put(LED_PIN_BLUE, true);  // Aciona o LED azul
        current_led = 2;  // Pronto para o próximo LED
    } else if (current_led == 2) {
        gpio_put(LED_PIN_GREEN, true);   // Aciona o LED vermelho
        current_led = 0;  // Volta ao LED verde
    }

    return true; // Retorna true para continuar o temporizador
}

int main() {
    stdio_init_all();

    // Inicializa os três pinos de LED como saída
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);

    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    uint32_t interval = 1000;
    struct repeating_timer timer;
    
    
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);
    absolute_time_t next_wake_time = delayed_by_us(get_absolute_time(), interval * 1000);
    while (true) {
      if (time_reached(next_wake_time)){
       // sleep_ms(5000); // Pausa para reduzir o uso da CPU
        printf("rotina de repetição principal 1 segundo passou\n");
        next_wake_time = delayed_by_us(next_wake_time, interval * 1000);
      }
    }

    return 0;
}
