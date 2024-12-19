#include "user.h"
#include <stdio.h>
#include <string.h>

void query_schedule() {
    FILE *file = fopen("data/schedules.txt", "r");
    if (file == NULL) {
        printf("���ް����Ϣ��\n");
        return;
    }

    char line[256];
    printf("\n��ǰ���ð�Σ�\n");
    printf("����\tĿ�ĵ�\t����\tʱ��\tʣ����λ\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

void bookTicket(const char* username, const char* scheduleId) {
    (void)scheduleId;
    FILE *schedule_file = fopen("data/schedules.txt", "r");
    FILE *temp = fopen("data/schedules.temp", "w");
    
    if (schedule_file == NULL || temp == NULL) {
        printf("�޷����ʰ����Ϣ��\n");
        return;
    }

    printf("������ҪԤ���ĳ������ƣ�");
    char target_bus[BUS_NAME_LENGTH];
    scanf("%s", target_bus);

    char bus[BUS_NAME_LENGTH], dest[DESTINATION_LENGTH];
    char date[DATE_LENGTH], time[TIME_LENGTH];
    int seats;
    int found = 0;

    while (fscanf(schedule_file, "%s\t%s\t%s\t%s\t%d\n", 
           bus, dest, date, time, &seats) == 5) {
        if (strcmp(bus, target_bus) == 0) {
            found = 1;
            if (seats > 0) {
                seats--;
                FILE *booking_file = fopen("data/bookings.txt", "a");
                if (booking_file != NULL) {
                    fprintf(booking_file, "%s\t%s\t%s\t%s\t%s\t%d\n", 
                        username, bus, dest, date, time, 1);
                    fclose(booking_file);
                    printf("Ԥ���ɹ���ʣ����λ����%d\n", seats);
                    
                    fprintf(temp, "%s\t%s\t%s\t%s\t%d\n", 
                        bus, dest, date, time, seats);
                }
            } else {
                printf("�Բ��𣬸ð��������Ʊ��\n");
                fprintf(temp, "%s\t%s\t%s\t%s\t%d\n", 
                    bus, dest, date, time, seats);
            }
        } else {
            fprintf(temp, "%s\t%s\t%s\t%s\t%d\n", 
                bus, dest, date, time, seats);
        }
    }

    fclose(schedule_file);
    fclose(temp);

    if (!found) {
        printf("δ�ҵ�ָ���ĳ��Σ�\n");
        remove("data/schedules.temp");
    } else {
        if (remove("data/schedules.txt") == 0) {
            if (rename("data/schedules.temp", "data/schedules.txt") != 0) {
                printf("���°����Ϣʧ�ܣ�\n");
            }
        }
    }
}

void viewBookedTickets(const char* username) {
    FILE *file = fopen("data/bookings.txt", "r");
    if (file == NULL) {
        printf("���޶�Ʊ��¼��\n");
        return;
    }

    char user[USERNAME_LENGTH], bus[BUS_NAME_LENGTH], dest[DESTINATION_LENGTH];
    char date[DATE_LENGTH], time[TIME_LENGTH];
    int tickets;
    int found = 0;

    printf("\n���Ķ�Ʊ��¼��\n");
    printf("����\tĿ�ĵ�\t����\tʱ��\tƱ��\n");
    
    while (fscanf(file, "%s\t%s\t%s\t%s\t%s\t%d\n", 
           user, bus, dest, date, time, &tickets) == 6) {
        if (strcmp(user, username) == 0) {
            printf("%s\t%s\t%s\t%s\t%d\n", bus, dest, date, time, tickets);
            found = 1;
        }
    }

    if (!found) {
        printf("���޶�Ʊ��¼��\n");
    }

    fclose(file);
}

void userMenu(const char* username) {
    int choice;
    do {
        printf("\n�û��˵�\n");
        printf("1. ��ѯ�೵��Ϣ\n");
        printf("2. Ԥ����Ʊ\n");
        printf("3. �鿴�Ѷ���Ʊ\n");
        printf("0. �˳�\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                query_schedule();
                break;
            case 2:
                bookTicket(username, "schedule_id");
                break;
            case 3:
                viewBookedTickets(username);
                break;
            case 0:
                printf("�˳�ϵͳ\n");
                break;
            default:
                printf("��Чѡ��\n");
        }
    } while(choice != 0);
}