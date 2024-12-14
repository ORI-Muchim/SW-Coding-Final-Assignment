/* transaction_system.c */
#include "stock_system.c"
#include "portfolio_system.c"
#include "user_system.c"
#include <time.h>

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
