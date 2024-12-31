#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_log.h"

void app_main(void) {

    printf("Hello world!\n");

    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

