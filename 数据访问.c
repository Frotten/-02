#include "标头.h"
User* AddUser(User* head) {
	registration_Permission();
	int temp = -1;
	if (scanf("%d", &temp)==1) {
		if (temp == 1 || temp == 0) {
			if(temp == 1) registration_owner();
			if(temp == 0) registration_user();
			long long username;
			char cip[20];
			if (scanf("%lld", &username) == 1) {
				User* tal = head->next;
				while (1) {
					if (tal == NULL) {
						break;
					}
					if (tal->Account == username) {
						printf("该id已有人使用，请重新尝试\n");
						return;
					}
					else {
						tal = tal->next;
					}
				}
				flush();
				fgets(cip, sizeof(cip), stdin);
				User* New = (User*)malloc(sizeof(User));
				New->Permission = temp;
				New->Account = username;
				strcpy(New->Cipher, cip);
				for (int i = 0; i < 20; i++) {
					New->Wallet[i].line = 0;
					New->Wallet[i].row = 0;
					strcpy(New->Wallet[i].name, "0");
					New->Wallet[i].day = -1;
					New->Wallet[i].month = -1;
					New->Wallet[i].starthour = -1;
					New->Wallet[i].startminut = -1;
				}
				New->prev = NULL;
				New->next = NULL;
				return New;
			}
		}
		else {
			printf("输入不合法");
			return NULL;
		}
	}
	else {
		printf("输入不合法");
		return NULL;
	}
}
User* searchforuser(long long id, char *cip, User* head) {
	User* now = head->next;
	if (now == NULL) {
		printf("\nError: User does not exist.\n");
		Sleep(520);
		return NULL;
	}
	while (now != NULL) {
		if (now->Account == id) {
			if (!strcmp(cip, now->Cipher)) {
				printf("\nLogin Completely\n");
				Sleep(520);//为了让人能看到这几个提示的英文，我写了这句话
				return now;
			}
			else {
				printf("\nError: Wrong Cipher\n");
				Sleep(520);
				return NULL;
			}
		}
		else {
			now = now->next;
		}
	}
	printf("\nError: Aim does not exist.\n");
	Sleep(520);
	return NULL;
}
Movies* AddMovie() {
	registration_Movie();
	printf("请输入电影名称：（输入Quit以退出\n");
	Movies* New = (Movies*)malloc(sizeof(Movies));
	New->next = NULL;
	New->prev = NULL;
	char name[30] = { 0 };
	flush();
	fgets(name,sizeof(name),stdin);
	if (!strcmp(name, "Quit\n")) {
		free(New);
		return NULL;
	}
	else {
		strcpy(New->Name, name);
	}
	int yue, ri;
	while (1) {
		printf("请输入电影上线的日期（月，日）：（输入-1，-1以退出）\n");
		scanf("%d %d", &yue, &ri);
		if (yue == -1 && ri == -1) {
			free(New);
			return NULL;
		}
		if (yue <= 0 || yue > 12 || ri <= 0 || ri > 31) {
			printf("\nError:Invalid Input\n");
			Sleep(520);
			continue;
		}
		New->month = yue;
		New->day = ri;
		break;
	}
	yue = 0, ri = 0;
	while (1) {
		printf("请输入电影的起始时间（时，分）：（输入-1，-1以退出）\n");
		scanf("%d %d", &yue, &ri);
		if (yue == -1 && ri == -1) {
			free(New);
			return NULL;
		}
		if (yue < 0 || yue >= 24 || ri < 0 || ri >= 60) {
			printf("\nError:Invalid Input\n");
			Sleep(520);
			continue;
		}
		New->starthour = yue;
		New->startminut = ri;
		break;
	}
	yue = 0, ri = 0;
	while (1) {
		printf("请输入电影的终止时间（时，分）：（输入-1，-1以退出）\n");
		scanf("%d %d", &yue, &ri);
		if (yue == -1 && ri == -1) {
			free(New);
			return NULL;
		}
		if (yue < 0 || yue >= 24 || ri < 0 || ri >= 60) {
			printf("\nError:Invalid Input\n");
			Sleep(520);
			continue;
		}
		New->endhour = yue;
		New->endminut = ri;
		break;
	}
	char descript[200];
	printf("请输入对该电影的描述：（输入Quit以退出\n");
	flush();
	fgets(descript,sizeof(descript),stdin);
	if (!strcmp(descript, "Quit")) {
		free(New);
		return NULL;
	}
	else {
		strcpy(New->decription, descript);
	}
	memset(New->location, 0, sizeof(New->location));
	return New;
}
Movies* SearchforMovie(char* Moviename, Movies* HACH) {
	if (HACH->next == NULL) {
		Lack_Movie();
		Sleep(520);
		return NULL;
	}
	Movies* now = HACH->next;
	Movies* early = HACH;
	while (1) {
		if (now == NULL) {//这里可以改成精准搜索失败后转入模糊搜索
			Movies* ARR[200];
			int count = 1;
			now = HACH->next;
			early = HACH;
			while (1) {
				if (now == NULL) {
					break;
				}
				if (strcmp(now->Name,"0") && levenshtein_distance(Moviename, now->Name) <= MAX_Error) {
					ARR[count++] = now;
				}
				early = now;
				now = now->next;
			}
			if (count == 1) {//没有在误差范围内找到相关的结果
				Lack_Movie();
				Sleep(520);
				return NULL;
			}
			else {//找到了相似结果
				system("cls");
				printf("请输入对应数字以跳转至对应结果：\n");
				for (int i = 1; i < count; i++) {
					printf("%d：%s", i, ARR[i]->Name);
				}
				int temp;
				while (1) {
					scanf("%d", &temp);
					if (temp < count && temp > 0) {
						return ARR[temp];
					}
					else {
						printf("Error Input\n");
						continue;
					}
				}
			}
		}
		if (!strcmp(now->Name, Moviename)) {
			return now;
		}
		else {
			early = now;
			now = now->next;
		}
	}
}
void DeleteMovie(char* Moviename, Movies* HACH, User* head) {
	Movies* temp = SearchforMovie(Moviename, HACH);
	if (temp != NULL) {
		if (temp->next != NULL) {
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
		}
		else {
			temp->prev->next = NULL;
		}
		User* temp = head->next;
		while (temp != NULL) {
			for (int i = 0; i < 20; i++) {
				if (!strcmp(temp->Wallet[i].name, Moviename)) {
					strcpy(temp->Wallet[i].name, "0");
					temp->Wallet[i].day = -1;
					temp->Wallet[i].month = -1;
					temp->Wallet[i].starthour = -1;
					temp->Wallet[i].startminut = -1;
					temp->Wallet[i].row = 0;
					temp->Wallet[i].line = 0;
					qsort(temp->Wallet, 20, sizeof(Vote), compareVotes);
				}
			}
			temp = temp->next;
		}
		free(temp);
		printf("\nDelete Completely\n");
		Sleep(520);
		return;
	}
	else {
		printf("\nError:Aim does not exist\n");
		Sleep(520);
		return;
	}
}
void Movies_Search_for_information(char* Moviename, Movies* HACH) {
	Movies* Temp;
	if (!strcmp(Moviename, "WRYYYYYYYYYY")) {
		Temp = HACH->next;
		while (1) {
			if (!strcmp(Temp->Name, "0") && Temp->next != NULL) {
				Temp = Temp->next;
			}
			else {
				break;
			}
		}
	}
	else {
		Temp = SearchforMovie(Moviename, HACH);
	}
	if (Temp == NULL) return;
	while (1) {//这里可以用来加一个左右查找的功能，向左或者向右查看电影|<-已完成
		if (Temp != NULL) {
			Movie_Found(Temp);
			printf("输入'a'以查看上一部电影，输入'd'以查看下一部电影,输入'q'以退出\n");
			char temp;
			temp = getchar();
			if (temp == 'a') {
				if (Temp->prev != NULL && strcmp(Temp->prev->Name, "0")) {
					Temp = Temp->prev;
				}
				else {
					printf("\n已经到最前的电影了\n");
					Sleep(520);
				}
			}
			else if (temp == 'd') {
				if (Temp->next != NULL) {
					Temp = Temp->next;
				}
				else{
					printf("\n已经到最后的电影了\n");
					Sleep(520);
				}
			}
			else if (temp == 'q') {
				return;
			}
			else {
				printf("\nInvalid input\n");
			}
		}
	}
}
void Movie_change(char* Moviename, Movies* HACH) {
	Movies* temp = SearchforMovie(Moviename, HACH);
	if (temp == NULL) return;
	while (1) {
		Movie_Found(temp);
		printf("请输入代号以修改电影的对应描述，输入Quit以退出\n");
		printf("1->名称，2->时间，3->描述\n");
		char TAG[10];
		fgets(TAG, sizeof(TAG), stdin);
		if (!strcmp(TAG, "Quit\n")) {
			break;
		}
		if (!strcmp(TAG, "1\n")) {
			char name[20];
			printf("请输入修改后的名字：");
			fgets(name, sizeof(name), stdin);
			strcpy(temp->Name, name);
		}
		if (!strcmp(TAG, "2\n")) {
			int mon, day;
			printf("请输入修改后的月，日：");
			scanf("%d %d", &mon, &day);
			temp->month = mon;
			temp->day = day;
			printf("请输入修改后的电影起始时间（时，分）：");
			scanf("%d %d", &mon, &day);
			temp->starthour = mon;
			temp->startminut = day;
			printf("请输入修改后的电影终止时间（时，分）：");
			scanf("%d %d", &mon, &day);
			temp->endhour = mon;
			temp->endminut = day;
		}
		if (!strcmp(TAG, "3\n")) {
			char descri[50];
			printf("请输入修改后的电影描述：");
			fgets(descri, sizeof(descri), stdin);
			strcpy(temp->decription, descri);
		}
	}
}
int compareVotes(const void* a, const void* b) {
	const Vote* voteA = (const Vote*)a;
	const Vote* voteB = (const Vote*)b;
	if (voteA->month == -1 && voteB->month == -1) {
		return 0;
	}
	else if (voteA->month == -1) {
		return 1;
	}
	else if (voteB->month == -1) {
		return -1;
	}
	if (voteA->month != voteB->month) {
		return voteA->month - voteB->month;
	}
	if (voteA->day != voteB->day) {
		return voteA->day - voteB->day;
	}
	if (voteA->starthour != voteB->starthour) {
		return voteA->starthour - voteB->starthour;
	}
	return voteA->startminut - voteB->startminut;
}
void subscription(char* Moviename, Movies* HACH, User* Now,User* head) {//5
	Movies* temp = SearchforMovie(Moviename, HACH);
	if (temp == NULL) return;
	locationprint(temp);
	printf("%s|:(%d月%d日)%02d:%02d--%02d:%02d\n", temp->Name, temp->month, temp->day, temp->starthour, temp->startminut, temp->endhour, temp->endminut);
	printf("请输入想要预定的位置（行，列）\n（输入0 0以退出）\n");
	int row, line;
	while (1) {
		scanf("%d %d", &row, &line);
		if (row == 0 && line == 0) return;
		if (row > 0 && row < 10 && line > 0 && line < 10 && temp->location[row][line] == 0) {
			int count = 0;
			for (count = 0; count < 20; count++) {
				if (!strcmp(Now->Wallet[count].name, Moviename)) {
					printf("该电影已订阅，请勿重复买票\n");
					return;
				}
				if (!strcmp(Now->Wallet[count].name, "0")) {
					break;
				}
			}
			if (count >= 20) {
				printf("票夹已满，请清理后再进行订阅\n");
				return;
			}
			temp->location[row][line]++;
			Now->Wallet[count].line = line;
			Now->Wallet[count].row = row;
			Now->Wallet[count].month = temp->month;
			Now->Wallet[count].day = temp->day;
			Now->Wallet[count].starthour = temp->starthour;
			Now->Wallet[count].startminut = temp->startminut;
			strcpy(Now->Wallet[count].name, temp->Name);
			printf("Subscript Completely\n");
			Sleep(520);
			qsort(Now->Wallet, 20, sizeof(Vote), compareVotes);
			SaveUser(head);
			SaveMovies(HACH);
			break;
		}
		else {
			printf("Error Input\n");
			flush();
		}
	}
}
void Subcrip_change(char* Moviename, Movies* HACH, User* Now, User* head) {//4
	Movies* temp = SearchforMovie(Moviename, HACH);
	if (temp == NULL) return;
	int count = 0,flag = 0;
	for (count = 0; count < 20; count++) {
		if (!strcmp(Now->Wallet[count].name, Moviename)) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		printf("未在票夹中找到对应电影\n");
		return;
	}
	locationprint(temp);
	printf("我的位置：%d %d\n", Now->Wallet[count].row, Now->Wallet[count].line);
	while (1) {
		printf("输入0以退出，输入1以删除订阅，输入2以修改位置\n");
		int choice;
		scanf("%d", &choice);
		switch (choice) {
		case 0: {
			return;
		}
		case 1: {
			temp->location[Now->Wallet[count].row][Now->Wallet[count].line] = 0;
			Now->Wallet[count].row = 0;
			Now->Wallet[count].line = 0;
			Now->Wallet[count].month = -1;
			Now->Wallet[count].day = -1;
			Now->Wallet[count].starthour = -1;
			Now->Wallet[count].startminut = -1;
			strcpy(Now->Wallet[count].name, "0");
			qsort(Now->Wallet, 20, sizeof(Vote), compareVotes);
			SaveUser(head);
			SaveMovies(HACH);
			printf("Delete Completely\n");
			Sleep(520);
			return;
		}
		case 2: {
			printf("请输入修改后的位置：");
			int newrow, newline;
			scanf("%d %d", &newrow, &newline);
			temp->location[Now->Wallet[count].row][Now->Wallet[count].line] = 0;
			temp->location[newrow][newline] = 1;
			Now->Wallet[count].row = newrow;
			Now->Wallet[count].line = newline;
			printf("Move Completely\n");
			qsort(Now->Wallet, 20, sizeof(Vote), compareVotes);
			SaveUser(head);
			SaveMovies(HACH);
			Sleep(520);
			return;
		}
		default:
			printf("Error Input");
			break;
		}
	}
}
void InitializeUser(User** head, User** early) {
	FILE* P = fopen("User.txt", "rb");
	if (P == NULL) {
		return;
	}
	while (1) {
		User Newly;
		if (fread(&Newly, sizeof(User), 1, P) != 1) {
			if (feof(P)) {
				printf("Initialize Complete\n");
			}
			else {
				perror("Initialize Error");
			}
			break;
		}
		User* New = (User*)malloc(sizeof(User));
		memcpy(New, &Newly, sizeof(User));
		New->prev = (*early);
		New->next = NULL;
		(*early)->next = New;
		(*early) = New;
	}
	fclose(P);
}
void SaveUser(const User* head){
	if (head == NULL)
	{
		FILE* P = fopen("User.txt", "wb");
		fclose(P);
		P = NULL;
		printf("No any User should be saved\n");
		return;
	}
	FILE* P = fopen("User.txt", "wb");
	if (P == NULL)
	{
		perror("Save");
	}
	User* Temp = head;
	while (1)
	{
		if (Temp == NULL)
		{
			break;
		}
		else
		{
			fwrite(Temp, sizeof(User), 1, P);
			Temp = Temp->next;
		}
	}
	fclose(P);
	P = NULL;
	return;
}
void InitializeMovie(Movies** head, Movies** early) {
	FILE* P = fopen("Movies.txt", "rb");
	if (P == NULL) {
		return;
	}
	while (1) {
		Movies Newly;
		if (fread(&Newly, sizeof(Movies), 1, P) != 1) {
			if (feof(P)) {
				printf("Initialize Complete\n");
			}
			else {
				perror("Initialize Error");
			}
			break;
		}
		Movies* New = (Movies*)malloc(sizeof(Movies));
		memcpy(New, &Newly, sizeof(Movies));
		New->prev = (*early);
		New->next = NULL;
		(*early)->next = New;
		(*early) = New;
	}
	fclose(P);
}
void SaveMovies(const Movies* head) {
	if (head == NULL)
	{
		FILE* P = fopen("Movies.txt", "wb");
		fclose(P);
		P = NULL;
		printf("No any Movies should be saved\n");
		return;
	}
	FILE* P = fopen("Movies.txt", "wb");
	if (P == NULL)
	{
		perror("Save");
	}
	Movies* Temp = head;
	while (1)
	{
		if (Temp == NULL)
		{
			break;
		}
		else
		{
			fwrite(Temp, sizeof(Movies), 1, P);
			Temp = Temp->next;
		}
	}
	fclose(P);
	P = NULL;
	return;
}
