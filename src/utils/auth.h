#ifndef AUTH_H
#define AUTH_H

#include "../include/common.h"

int login_user(const char* username, const char* password);
int register_user(const char* username, const char* password);

#endif