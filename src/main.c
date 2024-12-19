#include <stdio.h>
#include "common.h"
#include "admin.h"
#include "user.h"
#include "database.h"
#include "utils/auth.h"

int main() {
    printf("欢迎使用车票管理系统\n");
    printf("请输入用户名和密码:\n");
    
    char username[50], password[50];
    printf("用户名: ");
    scanf("%s", username);
    printf("密码: ");
    scanf("%s", password);

    int userType = login_user(username, password);

	if (userType == ADMIN) {
    	adminMenu();
	} else if (userType == USER) {
    	userMenu(username);
	} else {
    	printf("登录失败，请重试。\n");
	}

    return 0;
}