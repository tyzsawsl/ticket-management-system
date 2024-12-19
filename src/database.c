#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERS_FILE "data/users.txt"
#define SCHEDULES_FILE "data/schedules.txt"

void read_users() {
    FILE *file = fopen(USERS_FILE, "r");
    if (file == NULL) {
        perror("�޷����û��ļ�");
        return;
    }
    fclose(file);
}

void write_user(const char *user_info) {
    FILE *file = fopen(USERS_FILE, "a");
    if (file == NULL) {
        perror("�޷����û��ļ�");
        return;
    }
    fprintf(file, "%s\n", user_info);
    fclose(file);
}

void read_schedules() {
    FILE *file = fopen(SCHEDULES_FILE, "r");
    if (file == NULL) {
        perror("�޷��򿪰���ļ�");
        return;
    }
    fclose(file);
}

void write_schedule(const char *schedule_info) {
    FILE *file = fopen(SCHEDULES_FILE, "a");
    if (file == NULL) {
        perror("�޷��򿪰���ļ�");
        return;
    }
    fprintf(file, "%s\n", schedule_info);
    fclose(file);
}