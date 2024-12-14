/* user_system.h */
#ifndef USER_SYSTEM_H
#define USER_SYSTEM_H

struct User {
    char id[20];
    char password[20];
    int money;
    char join_date[20];
};

struct User* getCurrentUser(void);
int makeNewAccount(void);
int login(void);
void updateUserBalance(int amount);

#endif