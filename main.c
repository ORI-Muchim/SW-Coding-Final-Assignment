/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "user_system.h"
#include "stock_system.h"
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
    printf("1. 로그인\n");
    printf("2. 회원가입\n");
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
    time_t lastUpdate = 0;
    
    // 필요한 디렉토리 생성
    #ifdef _WIN32
        system("if not exist \"trading_data\" mkdir trading_data");
    #else
        system("mkdir -p ./trading_data");  // 상대 경로로 수정
    #endif
    
    // 초기 데이터 로드
    loadStocks();
    
    while (1) {
        // 매 5분마다 주가 업데이트
        if (time(NULL) - lastUpdate > 300) {
            updateStockPrices();
            lastUpdate = time(NULL);
        }
        
        showStartMenu();
        scanf("%d", &choice);
        clearScreen();
        
        switch (choice) {
            case 1: // 로그인
                if (login()) {
                    printf("로그인 성공!\n");
                    loadPortfolio(); // 포트폴리오 로드
                    
                    while (1) {
                        showMainMenu();
                        scanf("%d", &choice);
                        clearScreen();
                        
                        switch (choice) {
                            case 1: // 주식 목록
                                showStockList();
                                processTrading();
                                break;
                                
                            case 2: // 주식 검색
                                searchStock();
                                break;
                                
                            case 3: // 나의 포트폴리오
                                showMyStocks();
                                break;
                                
                            case 4: // 로그아웃
                                printf("로그아웃 되었습니다.\n");
                                goto logout;
                                
                            default:
                                printf("올바른 숫자를 입력하세요!\n");
                        }
                    }
                    logout:
                        continue;
                } else {
                    printf("로그인 실패.\n");
                }
                break;
                
            case 2: // 회원가입
                if (makeNewAccount()) {
                    printf("회원가입을 완료하였습니다!\n");
                } else {
                    printf("회원가입에 실패하였습니다.\n");
                }
                break;
                
            case 3: // 종료
                printf("프로그램을 종료합니다.\n");
                return 0;
                
            default:
                printf("올바른 숫자를 입력하세요!\n");
        }
    }
    
    return 0;
}
