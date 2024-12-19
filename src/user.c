#include "user.h"
#include <stdio.h>
#include <string.h>

void query_schedule() {
    FILE *file = fopen("data/schedules.txt", "r");
    if (file == NULL) {
        printf("暂无班次信息！\n");
        return;
    }

    char line[256];
    printf("\n当前可用班次：\n");
    printf("车次\t目的地\t日期\t时间\t剩余座位\n");
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
        printf("无法访问班次信息！\n");
        return;
    }

    printf("请输入要预订的车次名称：");
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
                    printf("预订成功！剩余座位数：%d\n", seats);
                    
                    fprintf(temp, "%s\t%s\t%s\t%s\t%d\n", 
                        bus, dest, date, time, seats);
                }
            } else {
                printf("对不起，该班次已无余票！\n");
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
        printf("未找到指定的车次！\n");
        remove("data/schedules.temp");
    } else {
        if (remove("data/schedules.txt") == 0) {
            if (rename("data/schedules.temp", "data/schedules.txt") != 0) {
                printf("更新班次信息失败！\n");
            }
        }
    }
}

void viewBookedTickets(const char* username) {
    FILE *file = fopen("data/bookings.txt", "r");
    if (file == NULL) {
        printf("暂无订票记录！\n");
        return;
    }

    char user[USERNAME_LENGTH], bus[BUS_NAME_LENGTH], dest[DESTINATION_LENGTH];
    char date[DATE_LENGTH], time[TIME_LENGTH];
    int tickets;
    int found = 0;

    printf("\n您的订票记录：\n");
    printf("车次\t目的地\t日期\t时间\t票数\n");
    
    while (fscanf(file, "%s\t%s\t%s\t%s\t%s\t%d\n", 
           user, bus, dest, date, time, &tickets) == 6) {
        if (strcmp(user, username) == 0) {
            printf("%s\t%s\t%s\t%s\t%d\n", bus, dest, date, time, tickets);
            found = 1;
        }
    }

    if (!found) {
        printf("暂无订票记录！\n");
    }

    fclose(file);
}

void userMenu(const char* username) {
    int choice;
    do {
        printf("\n用户菜单\n");
        printf("1. 查询班车信息\n");
        printf("2. 预订车票\n");
        printf("3. 查看已订车票\n");
        printf("0. 退出\n");
        printf("请选择: ");
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
                printf("退出系统\n");
                break;
            default:
                printf("无效选择\n");
        }
    } while(choice != 0);
}