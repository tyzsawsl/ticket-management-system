#include <stdio.h>
#include "common.h"
#include "admin.h"
#include "user.h"
#include "database.h"
#include "utils/auth.h"

int main() { //�������
    printf("��ӭʹ�ó�Ʊ����ϵͳ\n");
    printf("�������û���������:\n");
    
    char username[50], password[50]; //�����û���������
    printf("�û���: ");
    scanf("%s", username);
    printf("����: ");
    scanf("%s", password);

    int userType = login_user(username, password); //�ж��û�����

	if (userType == ADMIN) {
    	adminMenu();//����Ա�˵�
	} else if (userType == USER) {
    	userMenu(username);//�û��˵�
	} else {
    	printf("��¼ʧ�ܣ������ԡ�\n");
	}

    return 0;
}