#ifndef DATABASE_H
#define DATABASE_H

#include "common.h"
#include <stdio.h>
#include <stdlib.h>

// º¯ÊýÉùÃ÷
void loadUsers(User **users, int *userCount);
void saveUsers(User *users, int userCount);
void loadSchedules(Schedule **schedules, int *scheduleCount);
void saveSchedules(Schedule *schedules, int scheduleCount);

#endif