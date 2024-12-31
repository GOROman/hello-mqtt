#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "protocol_examples_common.h"

void app_main(void) {

    // NVS をぶち消す
    nvs_flash_init();

    // Network Interface を初期化
    esp_netif_init();

    // Wi-Fi を開始
    esp_event_loop_create_default();

    example_connect();

    printf("Hello world!\n");

    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

