#include "标头.h"
int minl(int a, int b, int c) {//三项比较取小
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}
int levenshtein_distance(const char* s1, const char* s2) {//通过动态分配查找目标串与输入串的区别个数
    int len1 = strlen(s1), len2 = strlen(s2);
    int* dp = malloc((len1 + 1) * sizeof(int));
    for (int i = 0; i <= len1; i++) dp[i] = i;
    for (int j = 1; j <= len2; j++) {
        int prev = dp[0];
        dp[0] = j;
        for (int i = 1; i <= len1; i++) {
            int temp = dp[i];
            dp[i] = minl(dp[i] + 1,        // 删除
                dp[i - 1] + 1,    // 插入
                prev + (tolower(s1[i - 1]) != tolower(s2[j - 1]))); // 替换
            prev = temp;
        }
    }
    int result = dp[len1];
    free(dp);
    return result;
}
int fuzzy_search_levenshtein(const char* str, const char* pattern, int max_errors) {//模糊输入，max_errors指最大错误个数，查询成功就返回1，否则返回0
    return levenshtein_distance(str, pattern) <= max_errors;
}
void flush() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void afterLogin(User* New, Movies* HACH,User* head) {
    Movies* ZAO = HACH;
    while (ZAO->next != NULL) {
        ZAO = ZAO->next;//ZAO放在链表末位
    }
    while (1) {
        if (New->Permission == 1) {
            ownermap();
            int temp;
            if (scanf("%d", &temp) == 1) {
                if (temp >= 1 && temp <= 8) {
                    switch (temp) {
                    case 1: {
                        Movies* LIN = AddMovie();
                        if (LIN != NULL) {
                            LIN->prev = ZAO;
                            ZAO->next = LIN;
                            ZAO = LIN;
                            SaveMovies(HACH);
                        }
                        break;
                    }
                    case 2: {
                        char name[20];
                        printf("请输入要删除的电影名称：");
                        flush();
                        fgets(name,sizeof(name),stdin);
                        DeleteMovie(name, HACH, head);
                        SaveMovies(HACH);
                        break;
                    }
                    case 3: {
                        char name[20];
                        printf("请输入要查找的电影名称：");
                        flush();
                        fgets(name, sizeof(name), stdin);
                        Movies_Search_for_information(name, HACH);
                        break;
                    }
                    case 4: {
                        char name[20];
                        printf("请输入要修改的电影名称：");
                        flush();
                        fgets(name, sizeof(name), stdin);
                        Movie_change(name, HACH);
                        break;
                    }
                    case 5: {
                        char name[20];
                        printf("请输入要订阅的电影名称：");
                        flush();
                        fgets(name, sizeof(name), stdin);
                        Subcrip_change(name, HACH, New,head);
                        break;
                    }
                    case 6: {
                        char name[20];
                        printf("请输入要订阅的电影名称：");
                        flush();
                        fgets(name, sizeof(name), stdin);
                        subscription(name, HACH, New,head);
                        break;
                    }
                    case 7:
                        Vote_Found(New,HACH);
                        break;
                    case 8: {
                        Movies_Search_for_information("WRYYYYYYYYYY",HACH);
                        break;
                    }
                    default:
                        printf("Error Input\n");
                        Sleep(520);
                        break;
                    }
                }
                else {
                    printf("\nWrong Input\n");
                    Sleep(520);
                    continue;
                }
            }
            else {
                printf("\n退出登录\n");
                Sleep(520);
                break;
            }
        }
        else {
            usermap();
            int temp;
            if (scanf("%d", &temp) == 1) {
                if (temp >= 1 && temp <= 5) {
                    switch (temp) {
                    case 1: {
                        char name[20];
                        printf("请输入要查找的电影名称：");
                        flush();
                        fgets(name, sizeof(name), stdin);
                        Movies_Search_for_information(name, HACH);
                        break;
                    }
                    case 2: {
                        char name[20];
                        printf("请输入要订阅的电影名称：");
                        flush();
                        fgets(name, sizeof(name), stdin);
                        Subcrip_change(name, HACH, New, head);
                        break;
                    }
                    case 3:{
                        char name[20];
                        printf("请输入要订阅的电影名称：");
                        flush();
                        fgets(name, sizeof(name), stdin);
                        subscription(name, HACH, New, head);
                        break;
                    }
                    case 4:
                        Vote_Found(New, HACH);
                        break;
                    case 5: {
                        Movie_Found(HACH->next);
                        break;
                    }
                    default:
                        printf("Error Input\n");
                        Sleep(520);
                        break;
                    }
                }
                else {
                    printf("\nWrong Input\n");
                    Sleep(520);
                    continue;
                }
            }
            else {
                printf("\n退出登录\n");
                Sleep(520);
                break;
            }
        }
    }
}
