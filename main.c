/* main.c */
#include <stdio.h>
#include "stock_system.h"
#include "user_system.h"
#include "portfolio_system.h"

void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void showStartMenu(void) {
    printf("===========================\n");
    printf("     주식 시뮬레이션 구현기~~    \n");
    printf("===========================\n");
    printf("1. 회원가입\n");
    printf("2. 로그인\n");
    printf("3. 나가기\n");
    printf("===========================\n");
    printf("선택: ");
}

void showMainMenu(void) {
    printf("===========================\n");
    printf("           메인 메뉴         \n");
    printf("===========================\n");
    printf("1. 주식 목록\n");
    printf("2. 주식 검색\n");
    printf("3. 나의 포트폴리오\n");
    printf("4. 로그아웃\n");
    printf("===========================\n");
    printf("선택: ");
}

int main(void) {
    int choice;
    
    while (1) {
        showStartMenu();
        scanf("%d", &choice);
        clearScreen();
        
        switch (choice) {
            case 1:
                if (makeNewAccount()) {
                    printf("회원가입을 완료하였습니다!\n");
                } else {
                    printf("회원가입에 실패하였습니다.\n");
                }
                break;
                
            case 2:
                if (login()) {
                    printf("로그인 성공!\n");
                    // TODO: Implement main menu handling
                } else {
                    printf("로그인 실패.\n");
                }
                break;
                
            case 3:
                printf("프로그램을 종료합니다.\n");
                return 0;
                
            default:
                printf("올바른 숫자를 입력하세요!\n");
                break;
        }
    }
    
    return 0;
}
