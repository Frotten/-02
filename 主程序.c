#include "标头.h"
int main() {
	User* head = (User*)malloc(sizeof(User));
	User* early = head;
	head->next = NULL;
	head->prev = NULL;
	Movies* HACH = (Movies*)malloc(sizeof(Movies));
	strcpy(HACH->Name, "0");
	HACH->next = NULL;
	HACH->prev = NULL;
	Movies* ZAO = HACH;
	InitializeUser(&head, &early);
	InitializeMovie(&HACH, &ZAO);
	long long Nickname = 0;
	system("color 0e");
	while (1) {
		loginmap();
		Nickname = 0;
		if (scanf("%lld", &Nickname) == 1) {
			if (Nickname == -10086) {
				User* New = AddUser(head);
				if (New == NULL) {//创建失败，应该返回登录界面
					continue;
				}
				else {
					early->next = New;
					New->prev = early;
					early = New;
					SaveUser(head);
				}
			}
			else {
				char cip[20] = { 0 };
				printf("|:");
				flush();
				fgets(cip,sizeof(cip),stdin);
				User* New = searchforuser(Nickname, cip, head);
				if (New == NULL) {
					continue;
				}
				else {//登陆成功，进入用户界面
					afterLogin(New,HACH,head);
					flush();
				}
			}
		}
		else {
			printf("退出程序\n");
			break;
		}
	}
}
