/* stock_system.h */
#ifndef STOCK_SYSTEM_H
#define STOCK_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stock information structure
struct Stock {
    char name[50];    
    int price;        
    int change;       
};

void showStockList(void);
void searchStock(void);

#endif