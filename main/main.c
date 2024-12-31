#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "protocol_examples_common.h"

#include "mqtt_client.h"

#define BROKER_URI "mqtt://192.168.0.191"
#define FEED "/topic/led0"

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{

    esp_mqtt_event_handle_t e = event_data;

    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:
            printf("[MQTT_EVENT_CONNECTED]\n");

            // Publish
            esp_mqtt_client_publish(e->client, FEED, "from ESP32!", 0, 0, 0);

            // Subscribe
            esp_mqtt_client_subscribe(e->client, FEED, 0);

            break;

        case MQTT_EVENT_DISCONNECTED:
            printf("[MQTT_EVENT_DISCONNECTED]\n");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            printf("[MQTT_EVENT_SUBSCRIBED]\n");
            break;

        case MQTT_EVENT_UNSUBSCRIBED:
            printf("[MQTT_EVENT_UNSUBSCRIBED]\n");
            break;

        case MQTT_EVENT_DATA:
            printf("[MQTT_EVENT_DATA]\n");
            printf("TOPIC=%.*s\r\n", e->topic_len, e->topic);
            printf("DATA=%.*s\r\n", e->data_len, e->data);
            break;

        default:
        printf("MQTT event %ld\n", event_id);
            break;
    }
}

// MQTT開始
void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = BROKER_URI,
    };

    printf("MQTT client initialized\n");
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);

    printf("MQTT client register\n");
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);

    printf("MQTT client start\n");
    esp_mqtt_client_start(client);
}

void app_main(void) {

    // NVS をぶち消す
    nvs_flash_init();
    printf("NVS flash initialized\n");

    // Network Interface を初期化
    esp_netif_init();
    printf("Network Interface initialized\n");

    // Event Loop を作成
    esp_event_loop_create_default();
    printf("Event loop created\n");

    // Wi-Fi に接続（サンプル）
    example_connect();
    printf("Connected to Wi-Fi\n");

    // MQTT開始
    mqtt_app_start();

    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

