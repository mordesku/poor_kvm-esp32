//
// Created by mordesku on 10/31/2021.
//

#include "storage.h"
#include "nvs_flash.h"
#include "nvs.h"

nvs_handle_t nvsHandle;

int storage_init(char *storageName) {
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    err = nvs_open(storageName, NVS_READWRITE, &nvsHandle);
    if (err != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    }
    return err == ESP_OK;
}

int storage_close() {
    if (nvsHandle) {
        esp_err_t err = nvs_commit(nvsHandle);
        if (err == ESP_OK) {
            nvs_close(nvsHandle);
        }
        return err;
    }
    return ESP_ERR_NVS_INVALID_HANDLE;
}

int storage_store_str(char *key, char *val) {
    if (nvsHandle) {
        nvs_set_str(nvsHandle, key, val);
    }
    return ESP_ERR_NVS_INVALID_HANDLE;
}

int storage_get_str(char *key, char *out_val, size_t *length) {
    if (nvsHandle) {
        return nvs_get_str(nvsHandle, key, out_val, length);
    }
    return ESP_ERR_NVS_INVALID_HANDLE;
}