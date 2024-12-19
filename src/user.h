#ifndef USER_H
#define USER_H

#include "common.h"

void query_schedule();
void registerUser(User user);
void viewBookedTickets(const char* username);
void bookTicket(const char* username, const char* scheduleId);
void userMenu(const char* username);

#endif