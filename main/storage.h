//
// Created by mordesku on 10/31/2021.
//

#ifndef POOR_KVM_STORAGE_H
#define POOR_KVM_STORAGE_H
#include "stddef.h"

int storage_init(char *storageName);
int storage_close();
int storage_store_str(char *key, char *val);
int storage_get_str(char *key, char *out_val, size_t *length);
#endif //POOR_KVM_STORAGE_H
