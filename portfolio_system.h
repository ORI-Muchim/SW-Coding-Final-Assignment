/* portfolio_system.h */
#ifndef PORTFOLIO_SYSTEM_H
#define PORTFOLIO_SYSTEM_H

#include <stdio.h>

// Portfolio stock structure
struct MyStock {
    char name[50];   
    int count;      
    int buyPrice;   
};

void showMyStocks(void);
void calculateProfit(void);

#endif