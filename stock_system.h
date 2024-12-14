/* stock_system.h */
#ifndef STOCK_SYSTEM_H
#define STOCK_SYSTEM_H

struct Stock {
    char code[10];
    char name[50];
    char sector[30];
    int current_price;
    float daily_change;
};

void loadStocks(void);
void showStockList(void);
void searchStock(void);
struct Stock* getStock(const char* stockName);
void updateStockPrices(void);

#endif