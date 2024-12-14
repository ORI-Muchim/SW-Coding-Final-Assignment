/* stock_system.c */
#include "stock_system.h"
#include "user_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STOCKS_FILE "./trading_data/stocks.txt"
#define MAX_STOCKS 10

static struct Stock stockList[MAX_STOCKS];
static int stockCount = 0;

void loadStocks(void) {
    FILE *fp = fopen(STOCKS_FILE, "r");
    if (fp == NULL) {
        printf("주식 정보 파일을 찾을 수 없습니다.\n");
        return;
    }
    
    while (fscanf(fp, "%s %s %s %d %f", 
                 stockList[stockCount].code,
                 stockList[stockCount].name,
                 stockList[stockCount].sector,
                 &stockList[stockCount].current_price,
                 &stockList[stockCount].daily_change) != EOF 
           && stockCount < MAX_STOCKS) {
        stockCount++;
    }
    
    fclose(fp);
}

void showStockList(void) {
    printf("\n=== 오늘의 핫한 종목을 확인! ===\n");
    for (int i = 0; i < stockCount; i++) {
        printf("%d. %s(%s) : %d원 (%+.1f%%)\n", 
               i + 1, 
               stockList[i].name, 
               stockList[i].sector,
               stockList[i].current_price, 
               stockList[i].daily_change);
    }
    printf("===============================\n\n");
}

void searchStock(void) {
    char searchName[50];
    int found = 0;
    
    printf("검색할 주식 이름: ");
    scanf("%s", searchName);
    
    for (int i = 0; i < stockCount; i++) {
        if (strstr(stockList[i].name, searchName) != NULL) {
            printf("%s(%s): %d원 (%+.1f%%)\n", 
                   stockList[i].name,
                   stockList[i].sector, 
                   stockList[i].current_price, 
                   stockList[i].daily_change);
            found = 1;
        }
    }
    
    if (!found) {
        printf("검색 결과가 없습니다.\n");
    }
}

struct Stock* getStock(const char* stockName) {
    for (int i = 0; i < stockCount; i++) {
        if (strcmp(stockList[i].name, stockName) == 0) {
            return &stockList[i];
        }
    }
    return NULL;
}

void updateStockPrices(void) {
    srand(time(NULL));
    for (int i = 0; i < stockCount; i++) {
        float change = (float)(rand() % 11 - 5) / 100.0f; // -5% to +5%
        stockList[i].daily_change = change * 100;
        stockList[i].current_price *= (1 + change);
    }
    
    // 파일 업데이트
    FILE *fp = fopen(STOCKS_FILE, "w");
    if (fp == NULL) return;
    
    for (int i = 0; i < stockCount; i++) {
        fprintf(fp, "%s %s %s %d %.2f\n",
                stockList[i].code,
                stockList[i].name,
                stockList[i].sector,
                stockList[i].current_price,
                stockList[i].daily_change);
    }
    fclose(fp);
}
