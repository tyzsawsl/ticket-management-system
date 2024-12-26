#include <stdio.h>
#include "common.h"
#include "admin.h"
#include "user.h"
#include "database.h"
#include "utils/auth.h"

int main() { //程序入口
    printf("欢迎使用车票管理系统\n");
    printf("请输入用户名和密码:\n");
    
    char username[50], password[50]; //输入用户名和密码
    printf("用户名: ");
    scanf("%s", username);
    printf("密码: ");
    scanf("%s", password);

    int userType = login_user(username, password); //判断用户类型

	if (userType == ADMIN) {
    	adminMenu();//管理员菜单
	} else if (userType == USER) {
    	userMenu(username);//用户菜单
	} else {
    	printf("登录失败，请重试。\n");
	}

    return 0;
}