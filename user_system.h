/* user_system.h */
#ifndef USER_SYSTEM_H
#define USER_SYSTEM_H

#include <stdio.h>
#include <string.h>

// User account structure
struct User {
    char id[20];         
    char password[20];   
    int money;          
};

int login(void);
int makeNewAccount(void);

#endif