#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "nvs_flash.h"


void app_main(void) {

    // NVS をぶち消す
    nvs_flash_init();

    printf("Hello world!\n");

    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

