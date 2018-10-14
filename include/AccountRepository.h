#pragma once

#include <switch.h>
#include <stdio.h>
#include <string.h>
#include "account.h"
#include <vector> 


class AccountRepository
{
    public:
        AccountRepository();

        s32 getNumberOfUsers();
        Account getAccountByIndex(int index);
        Account* getAccountById(u128 id);
    protected:
        s32 mNumberOfUsers;
        std::vector<Account> mAccounts;
        
        bool init();
};