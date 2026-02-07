/*
 * ESP32 Blink 範例 (PlatformIO)
 * 讓板子上的 LED 每秒閃爍一次
 *
 * 多數 ESP32 開發板的內建 LED 接在 GPIO 2
 * 若你的板子不同，請修改 BLINK_GPIO 的數字
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "blink";

// 內建 LED 的 GPIO（大部分 ESP32 開發板是 GPIO 2）
#define BLINK_GPIO  2

void app_main(void)
{
    // 將 GPIO 設為輸出
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    int led_state = 0;

    while (1) {
        // 設定 LED 亮(1) 或 滅(0)
        gpio_set_level(BLINK_GPIO, led_state);
        ESP_LOGI(TAG, "LED %s", led_state ? "ON" : "OFF");

        // 切換狀態
        led_state = !led_state;

        // 延遲 500ms（500 / portTICK_PERIOD_MS 個 tick，tick 通常 1ms）
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
