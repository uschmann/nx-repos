
#include "AccountRepository.h"
#include <stdio.h>
#include <stdlib.h>

AccountRepository::AccountRepository()
{
    init();
}

bool AccountRepository::init()
{
    Result rc=0;

    rc = accountGetUserCount(&mNumberOfUsers);
    if(R_FAILED(rc)) {
          printf("accountGetUserCount() failed: 0x%x\n", rc);
          return false;
    }

    size_t loadedUsers;
    u128 userIds[ACC_USER_LIST_SIZE];
    rc = accountListAllUsers(userIds, ACC_USER_LIST_SIZE, &loadedUsers);
    if(R_FAILED(rc)) {
          printf("accountListAllUsers() failed: 0x%x\n", rc);
          return false;
    }

    for(int i = 0; i < loadedUsers; i ++) {
        Account account(userIds[i], i);
        mAccounts.push_back(account);
    }

    return true;
}

s32 AccountRepository::getNumberOfUsers()
{
    return mNumberOfUsers;
}

Account AccountRepository::getAccountByIndex(int index) {
    return mAccounts.at(index);
}

Account* AccountRepository::getAccountById(u128 id) 
{
    for(int i = 0; i < getNumberOfUsers(); i++) {
        if(mAccounts.at(i).getUserId() == id) {
            return &mAccounts.at(i);
        }
    }
    return NULL;
}