/* portfolio_system.c */
#include "portfolio_system.h"
#include "stock_system.h"
#include "user_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PORTFOLIO 20
#define PORTFOLIO_FILE "./trading_data/portfolio.txt"
#define TRANSACTIONS_FILE "./trading_data/transactions.txt"

static struct MyStock portfolio[MAX_PORTFOLIO];
static int portfolioCount = 0;

void loadPortfolio(void) {
    FILE *fp = fopen(PORTFOLIO_FILE, "r");
    if (fp == NULL) return;
    
    char userId[20];
    portfolioCount = 0;
    
    while (fscanf(fp, "%s %s %d %d", 
                 userId, 
                 portfolio[portfolioCount].name,
                 &portfolio[portfolioCount].count,
                 &portfolio[portfolioCount].buyPrice) != EOF) {
        if (strcmp(userId, getCurrentUser()->id) == 0) {
            portfolioCount++;
        }
    }
    
    fclose(fp);
}

void savePortfolio(void) {
    FILE *fp = fopen(PORTFOLIO_FILE, "w");
    if (fp == NULL) return;
    
    for (int i = 0; i < portfolioCount; i++) {
        if (portfolio[i].count > 0) {
            fprintf(fp, "%s %s %d %d\n",
                    getCurrentUser()->id,
                    portfolio[i].name,
                    portfolio[i].count,
                    portfolio[i].buyPrice);
        }
    }
    
    fclose(fp);
}

void recordTransaction(const char* stockCode, char type, 
                      int quantity, int price) {
    FILE *fp;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[20];
    
    sprintf(date, "%04d-%02d-%02d", 
            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
    
    fp = fopen(TRANSACTIONS_FILE, "a");
    if (fp == NULL) return;
    
    fprintf(fp, "%s %s %c %d %d %s\n",
            getCurrentUser()->id, stockCode, type, quantity, price, date);
    fclose(fp);
}

void addToPortfolio(const char* stockName, int count, int price) {
    for (int i = 0; i < portfolioCount; i++) {
        if (strcmp(portfolio[i].name, stockName) == 0) {
            int totalValue = portfolio[i].count * portfolio[i].buyPrice;
            totalValue += count * price;
            portfolio[i].count += count;
            portfolio[i].buyPrice = totalValue / portfolio[i].count;
            savePortfolio();
            return;
        }
    }
    
    if (portfolioCount < MAX_PORTFOLIO) {
        strcpy(portfolio[portfolioCount].name, stockName);
        portfolio[portfolioCount].count = count;
        portfolio[portfolioCount].buyPrice = price;
        portfolioCount++;
        savePortfolio();
    }
}

int removeFromPortfolio(const char* stockName, int count) {
    for (int i = 0; i < portfolioCount; i++) {
        if (strcmp(portfolio[i].name, stockName) == 0) {
            if (portfolio[i].count >= count) {
                portfolio[i].count -= count;
                if (portfolio[i].count == 0) {
                    // Remove this stock from portfolio
                    for (int j = i; j < portfolioCount - 1; j++) {
                        portfolio[j] = portfolio[j + 1];
                    }
                    portfolioCount--;
                }
                savePortfolio();
                return 1;
            } else {
                printf("보유 수량이 부족합니다.\n");
                return 0;
            }
        }
    }
    
    printf("해당 주식을 보유하고 있지 않습니다.\n");
    return 0;
}

void showMyStocks(void) {
    struct User* user = getCurrentUser();
    double totalValue = 0;
    
    printf("\n=== 주식 포트폴리오 ===\n");
    printf("[보유 현금] %d원\n\n", user->money);
    printf("[보유 종목]\n");
    
    for (int i = 0; i < portfolioCount; i++) {
        struct Stock* currentStock = getStock(portfolio[i].name);
        if (currentStock == NULL) continue;
        
        int currentValue = currentStock->current_price * portfolio[i].count;
        float profitRate = ((float)currentStock->current_price / portfolio[i].buyPrice - 1) * 100;
        
        printf("%d. %s\n", i + 1, portfolio[i].name);
        printf("   - %d주 보유 (평단가: %d원)\n", 
               portfolio[i].count, portfolio[i].buyPrice);
        printf("   - 현재가: %d원\n", currentStock->current_price);
        printf("   - 수익률: %+.2f%%\n", profitRate);
        
        totalValue += currentValue;
    }
    
    printf("\n[총 자산] %.0f원\n", totalValue + user->money);
    printf("===========================\n\n");
}

int buyStock(const char* stockName, int quantity) {
    struct Stock* stock = getStock(stockName);
    struct User* user = getCurrentUser();
    
    if (stock == NULL) {
        printf("존재하지 않는 주식입니다.\n");
        return 0;
    }
    
    int totalCost = stock->current_price * quantity;
    if (totalCost > user->money) {
        printf("잔액이 부족합니다.\n");
        return 0;
    }
    
    updateUserBalance(-totalCost);
    addToPortfolio(stock->name, quantity, stock->current_price);
    recordTransaction(stock->code, 'B', quantity, stock->current_price);
    
    printf("%s %d주를 %d원에 매수했습니다.\n", 
           stockName, quantity, stock->current_price);
    return 1;
}

int sellStock(const char* stockName, int quantity) {
    struct Stock* stock = getStock(stockName);
    if (stock == NULL) {
        printf("존재하지 않는 주식입니다.\n");
        return 0;
    }
    
    if (removeFromPortfolio(stockName, quantity)) {
        int totalEarning = stock->current_price * quantity;
        updateUserBalance(totalEarning);
        recordTransaction(stock->code, 'S', quantity, stock->current_price);
        
        printf("%s %d주를 %d원에 매도했습니다.\n", 
               stockName, quantity, stock->current_price);
        return 1;
    }
    
    return 0;
}

void processTrading(void) {
    char stockName[50];
    int choice, quantity;
    
    printf("=== 매도/매수 ===\n");
    printf("원하는 기업이름 입력 (뒤로가기: 1): ");
    scanf("%s", stockName);
    
    if (strcmp(stockName, "1") == 0) {
        return;
    }
    
    printf("1. 매수\n");
    printf("2. 매도\n");
    printf("3. 뒤로가기\n");
    printf("선택: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1: // 매수
            printf("매수할 수량: ");
            scanf("%d", &quantity);
            buyStock(stockName, quantity);
            break;
            
        case 2: // 매도
            printf("매도할 수량: ");
            scanf("%d", &quantity);
            sellStock(stockName, quantity);
            break;
            
        case 3: // 뒤로가기
            return;
            
        default:
            printf("올바른 선택지를 입력하세요.\n");
    }
}
