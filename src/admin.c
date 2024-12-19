#include "admin.h"
#include "common.h"
#include <stdio.h>
#include <string.h>

void add_schedule() {
    Schedule newSchedule;
    printf("\n����°��\n");
    printf("�����복������: ");
    scanf("%s", newSchedule.busName);
    printf("������Ŀ�ĵ�: ");
    scanf("%s", newSchedule.destination);
    printf("���������� (YYYY-MM-DD): ");
    scanf("%s", newSchedule.date);
    printf("������ʱ�� (HH:MM): ");
    scanf("%s", newSchedule.time);
    printf("��������λ��: ");
    scanf("%d", &newSchedule.availableSeats);

    FILE *file = fopen("data/schedules.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s\t%s\t%s\t%s\t%d\n", 
            newSchedule.busName, 
            newSchedule.destination,
            newSchedule.date,
            newSchedule.time,
            newSchedule.availableSeats);
        fclose(file);
        printf("�����ӳɹ���\n");
    } else {
        printf("�޷����ļ���\n");
    }
}

void modify_schedule() {
    char target_bus[BUS_NAME_LENGTH];
    FILE *file = fopen("data/schedules.txt", "r");
    FILE *temp = fopen("data/schedules.temp", "w");
    
    if (file == NULL || temp == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    printf("������Ҫ�޸ĵĳ�������: ");
    scanf("%s", target_bus);

    char bus[BUS_NAME_LENGTH], dest[DESTINATION_LENGTH], date[DATE_LENGTH], time[TIME_LENGTH];
    int seats;
    int found = 0;

    while (fscanf(file, "%s\t%s\t%s\t%s\t%d\n", bus, dest, date, time, &seats) == 5) {
        if (strcmp(bus, target_bus) == 0) {
            found = 1;
            Schedule modified;
            strcpy(modified.busName, bus);

            printf("\n��ǰ�����Ϣ��\n");
            printf("Ŀ�ĵ�: %s\n����: %s\nʱ��: %s\n��λ��: %d\n", dest, date, time, seats);
            
            printf("\n�������µ���Ϣ��\n");
            printf("�µ�Ŀ�ĵ�: ");
            scanf("%s", modified.destination);
            printf("�µ����� (YYYY-MM-DD): ");
            scanf("%s", modified.date);
            printf("�µ�ʱ�� (HH:MM): ");
            scanf("%s", modified.time);
            printf("�µ���λ��: ");
            scanf("%d", &modified.availableSeats);

            fprintf(temp, "%s\t%s\t%s\t%s\t%d\n", 
                modified.busName,
                modified.destination,
                modified.date,
                modified.time,
                modified.availableSeats);
        } else {
            fprintf(temp, "%s\t%s\t%s\t%s\t%d\n", bus, dest, date, time, seats);
        }
    }

    fclose(file);
    fclose(temp);

    if (!found) {
        printf("δ�ҵ�ָ���ĳ��Σ�\n");
        remove("data/schedules.temp");
    } else {
        remove("data/schedules.txt");
        rename("data/schedules.temp", "data/schedules.txt");
        printf("�޸ĳɹ���\n");
    }
}

void view_schedules() {
    FILE *file = fopen("data/schedules.txt", "r");
    if (file == NULL) {
        printf("���ް����Ϣ��\n");
        return;
    }

    char line[256];
    printf("\n��ǰ���а����Ϣ��\n");
    printf("��������\tĿ�ĵ�\t����\tʱ��\t��λ��\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

void adminMenu() {
    int choice;
    do {
        printf("\n����Ա�˵�\n");
        printf("1. ��Ӱ��\n");
        printf("2. �޸İ��\n");
        printf("3. �鿴���\n");
        printf("0. �˳�\n");
        printf("��ѡ��: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                add_schedule();
                break;
            case 2:
                modify_schedule();
                break;
            case 3:
                view_schedules();
                break;
            case 0:
                printf("�˳�ϵͳ\n");
                break;
            default:
                printf("��Чѡ��\n");
        }
    } while(choice != 0);
}