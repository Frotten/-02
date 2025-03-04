#pragma once
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#define MAX_Error 3
typedef struct movie {//储存电影的“仓库”,同样应该是一个链表
	struct movie* prev;
	char Name[30];//电影票的名字
	int month;
	int day;
	int starthour;
	int endhour;
	int startminut;
	int endminut;
	int location[10][10];//该电影的座位信息
	char decription[200];//影片信息
	struct movie* next;
}Movies;
typedef struct Ticket {
	int month;
	int day;
	int starthour;
	int startminut;
	char name[30];
	int line;
	int row;
}Vote;
typedef struct user {//User结构体应当是一个链表
	struct user* prev;
	int Permission;//权限
	long long Account;//账号
	char Cipher[20];//密码
	Vote Wallet[20];//票夹
	struct user* next;
}User;
void flush();
void loginmap();
void ownermap();
void usermap();
void Lack_Movie();
void locationprint(Movies* temp);
void registration_Permission();
void registration_owner();
void registration_user();
void Vote_Found(User* Now, Movies* HACH);
void afterLogin(User* New, Movies* HACH,User* head);
void DeleteMovie(char* Moviename, Movies* HACH, User* head);
void Movie_Found(Movies* temp);
void Movies_Search_for_information(char* Moviename, Movies* HACH);
void subscription(char* Moviename, Movies* HACH, User* Now,User* head);
void Subcrip_change(char* Moviename, Movies* HACH, User* Now,User* head);
void InitializeUser(User** head, User** early);
void SaveUser(const User* head);
void InitializeMovie(Movies** head, Movies** early);
void SaveMovies(const Movies* head);
int compareVotes(const void* a, const void* b);
int minl(int a, int b, int c);
int levenshtein_distance(const char* s1, const char* s2);
int fuzzy_search_levenshtein(const char* str, const char* pattern, int max_errors);
User* AddUser(User* head);
User* searchforuser(long long id, char* cip, User* head);
Movies* AddMovie();
Movies* SearchforMovie(char* Moviename, Movies* HACH);
