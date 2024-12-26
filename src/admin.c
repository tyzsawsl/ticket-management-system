#include "admin.h"
#include "common.h"
#include <stdio.h>
#include <string.h>

void add_schedule() { //添加班次
    Schedule newSchedule; //声明一个Schedule结构体变量用于储存新班次信息
    printf("\n添加新班次\n");
    printf("请输入车次名称: ");
    scanf("%s", newSchedule.busName);
    printf("请输入目的地: ");
    scanf("%s", newSchedule.destination);
    printf("请输入日期 (YYYY-MM-DD): ");
    scanf("%s", newSchedule.date);
    printf("请输入时间 (HH:MM): ");
    scanf("%s", newSchedule.time);
    printf("请输入座位数: ");
    scanf("%d", &newSchedule.availableSeats);

    FILE *file = fopen("data/schedules.txt", "a"); //以追加模式打开文件
    if (file != NULL) {
        fprintf(file, "%s\t%s\t%s\t%s\t%d\n", 
            newSchedule.busName, 
            newSchedule.destination,
            newSchedule.date,
            newSchedule.time,
            newSchedule.availableSeats);
        fclose(file);
        printf("班次添加成功！\n");
    } else {
        printf("无法打开文件！\n");
    }
}

void modify_schedule() { //修改班次
    char target_bus[BUS_NAME_LENGTH]; //定位目标车次
    FILE *file = fopen("data/schedules.txt", "r"); //打开文件
    FILE *temp = fopen("data/schedules.temp", "w"); //创建临时文件
    
    if (file == NULL || temp == NULL) {
        printf("无法打开文件！\n");
        return;
    }

    printf("请输入要修改的车次名称: ");
    scanf("%s", target_bus);

    char bus[BUS_NAME_LENGTH], dest[DESTINATION_LENGTH], date[DATE_LENGTH], time[TIME_LENGTH];
    int seats;
    int found = 0;

    while (fscanf(file, "%s\t%s\t%s\t%s\t%d\n", bus, dest, date, time, &seats) == 5) { //读取文件中的信息
        if (strcmp(bus, target_bus) == 0) {
            found = 1;
            Schedule modified;
            strcpy(modified.busName, bus);

            printf("\n当前班次信息：\n");
            printf("目的地: %s\n日期: %s\n时间: %s\n座位数: %d\n", dest, date, time, seats);
            
            printf("\n请输入新的信息：\n");
            printf("新的目的地: ");
            scanf("%s", modified.destination);
            printf("新的日期 (YYYY-MM-DD): ");
            scanf("%s", modified.date);
            printf("新的时间 (HH:MM): ");
            scanf("%s", modified.time);
            printf("新的座位数: ");
            scanf("%d", &modified.availableSeats);

            fprintf(temp, "%s\t%s\t%s\t%s\t%d\n", 
                modified.busName,
                modified.destination,
                modified.date,
                modified.time,
                modified.availableSeats); //将修改后的信息写入临时文件
        } else {
            fprintf(temp, "%s\t%s\t%s\t%s\t%d\n", bus, dest, date, time, seats);
        }
    }

    fclose(file);
    fclose(temp); //关闭文件

    if (!found) {
        printf("未找到指定的车次！\n");
        remove("data/schedules.temp");
    } else {
        remove("data/schedules.txt");
        rename("data/schedules.temp", "data/schedules.txt");
        printf("修改成功！\n");
    }
}

void view_schedules() { //查看班次
    FILE *file = fopen("data/schedules.txt", "r"); //打开文件
    if (file == NULL) {
        printf("暂无班次信息！\n");
        return;
    }

    char line[256];
    printf("\n当前所有班次信息：\n");
    printf("车次名称\t目的地\t日期\t时间\t座位数\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

void adminMenu() { //管理员菜单
    int choice;
    do {
        printf("\n管理员菜单\n");
        printf("1. 添加班次\n");
        printf("2. 修改班次\n");
        printf("3. 查看班次\n");
        printf("0. 退出\n");
        printf("请选择: ");
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
                printf("退出系统\n");
                break;
            default:
                printf("无效选择\n");
        }
    } while(choice != 0);
}