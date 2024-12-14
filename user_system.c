/* user_system.c */
#include "user_system.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_USERS 100
#define USERS_FILE "./trading_data/users.txt"

static struct User currentUser;
static int isLoggedIn = 0;

struct User* getCurrentUser(void) {
    return &currentUser;
}

int makeNewAccount(void) {
    struct User newUser;
    FILE *fp;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    
    printf("=== 회원가입 ===\n");
    printf("아이디 (20자 이내): ");
    scanf("%s", newUser.id);
    printf("비밀번호 (20자 이내): ");
    scanf("%s", newUser.password);
    
    // 초기 자금 설정
    newUser.money = 10000000; // 1000만원
    sprintf(newUser.join_date, "%04d-%02d-%02d", 
            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
    
    // 파일에 사용자 정보 저장
    fp = fopen(USERS_FILE, "a");
    if (fp == NULL) {
        printf("파일 열기 실패!\n");
        return 0;
    }
    
    fprintf(fp, "%s %s %d %s\n", 
            newUser.id, newUser.password, newUser.money, newUser.join_date);
    fclose(fp);
    
    return 1;
}

int login(void) {
    char inputId[20], inputPw[20];
    FILE *fp;
    
    printf("=== 로그인 ===\n");
    printf("아이디: ");
    scanf("%s", inputId);
    printf("비밀번호: ");
    scanf("%s", inputPw);
    
    fp = fopen(USERS_FILE, "r");
    if (fp == NULL) {
        printf("파일 열기 실패!\n");
        return 0;
    }
    
    while (fscanf(fp, "%s %s %d %s", 
                 currentUser.id, currentUser.password, 
                 &currentUser.money, currentUser.join_date) != EOF) {
        if (strcmp(inputId, currentUser.id) == 0 && 
            strcmp(inputPw, currentUser.password) == 0) {
            isLoggedIn = 1;
            fclose(fp);
            return 1;
        }
    }
    
    fclose(fp);
    return 0;
}

void updateUserBalance(int amount) {
    FILE *fp, *temp;
    struct User user;
    
    currentUser.money += amount;
    
    fp = fopen(USERS_FILE, "r");
    temp = fopen("./trading_data/temp.txt", "w");
    
    while (fscanf(fp, "%s %s %d %s", 
                 user.id, user.password, &user.money, user.join_date) != EOF) {
        if (strcmp(user.id, currentUser.id) == 0) {
            fprintf(temp, "%s %s %d %s\n", 
                    currentUser.id, currentUser.password, 
                    currentUser.money, currentUser.join_date);
        } else {
            fprintf(temp, "%s %s %d %s\n", 
                    user.id, user.password, user.money, user.join_date);
        }
    }
    
    fclose(fp);
    fclose(temp);
    remove(USERS_FILE);
    rename("./trading_data/temp.txt", USERS_FILE);
}
