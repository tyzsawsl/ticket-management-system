#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "common.h"

int login_user(const char *username, const char *password) {
    FILE *file = fopen("data/users.txt", "r");
    if (file == NULL) {
        return -1;
    }

    char stored_username[50];
    char stored_password[50];
    char user_type[10];

    while (fscanf(file, "%[^,], %[^,], %s\n", stored_username, stored_password, user_type) == 3) {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
            fclose(file);
            return strcmp(user_type, "admin") == 0 ? ADMIN : USER;
        }
    }

    fclose(file);
    return -1;
}