#include <stddef.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define GPIO_LED 17
#define GPIO_LED_PIN_SEL (1ULL << GPIO_LED)
//#define ESP_INTR_FLAG_DEFAULT 0

//static void button_handler(void *arg);

static void init_hw(void)
{
    gpio_config_t io_conf;

    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);


}

static TickType_t next = 0;
static bool led_state = false;

void app_main() {
    init_hw();

    while (1)
    {
        TickType_t now = xTaskGetTickCountFromISR();
        if(now > next)
        {
            led_state = !led_state;
            gpio_set_level(GPIO_LED, led_state);
            next = now + 500 / portTICK_PERIOD_MS;
        }
        
    }
    
}