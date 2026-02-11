// ...existing code...
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"
#include "soc/soc.h"

static const char *TAG = "blink";
#define BLINK_GPIO 2

void app_main(void){
    REG_WRITE(IO_MUX_GPIO2_REG, (REG_READ(IO_MUX_GPIO2_REG) & ~FUN_IE) | FUN_DRV);
    REG_WRITE(GPIO_ENABLE_W1TS_REG, (1 << BLINK_GPIO));
    int led_state = 0;
    while(1){
        if (led_state) {
            REG_WRITE(GPIO_OUT_W1TS_REG, (1 << BLINK_GPIO)); 
        } else {
            REG_WRITE(GPIO_OUT_W1TC_REG, (1 << BLINK_GPIO)); 
        }
        led_state = !led_state;
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
