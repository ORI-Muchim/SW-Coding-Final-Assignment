/* portfolio_system.h */
#ifndef PORTFOLIO_SYSTEM_H
#define PORTFOLIO_SYSTEM_H

struct MyStock {
    char name[50];
    int count;
    int buyPrice;
};

void loadPortfolio(void);
void savePortfolio(void);
void addToPortfolio(const char* stockName, int count, int price);
int removeFromPortfolio(const char* stockName, int count);
void showMyStocks(void);
void recordTransaction(const char* stockCode, char type, int quantity, int price);
int buyStock(const char* stockName, int quantity);
int sellStock(const char* stockName, int quantity);
void processTrading(void);

#endif
