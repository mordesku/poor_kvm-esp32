/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "storage.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp32/rom/uart.h"

void app_main()
{
    if (!storage_init("storage")) {
        printf("Can't init NVS storage.\n");
        return;
    }
    char * name;
    size_t nameSize;
    esp_err_t err = storage_get_str("name", NULL, &nameSize);
    if (err == ESP_OK) {
        name = malloc(nameSize);
        storage_get_str("name", name, &nameSize);
        printf("Last logged user: %s\n", name);
    }
    char *input = malloc(128 * sizeof(char));
    printf("Enter your name: ");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    fgets(input, 128, stdin);
    storage_store_str("name", input);
    storage_close();
    printf("Good job %s\n", input);

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    free(input);
    fflush(stdout);
    esp_restart();
}
