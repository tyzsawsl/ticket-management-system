#ifndef COMMON_H
#define COMMON_H

#define MAX_USERS 100
#define MAX_SCHEDULES 50
#define USERNAME_LENGTH 30
#define PASSWORD_LENGTH 30
#define BUS_NAME_LENGTH 50
#define DESTINATION_LENGTH 50
#define DATE_LENGTH 11
#define TIME_LENGTH 6

#define ADMIN 1
#define USER 0

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    int isAdmin;
} User;

typedef struct {
    char busName[BUS_NAME_LENGTH];
    char destination[DESTINATION_LENGTH];
    char date[DATE_LENGTH];
    char time[TIME_LENGTH];
    int availableSeats;
} Schedule;

int authenticateUser();
void adminMenu();
void userMenu();

#endif