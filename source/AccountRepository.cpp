
#include "AccountRepository.h"

AccountRepository::AccountRepository()
{

}

bool AccountRepository::init()
{
    Result rc=0;

    rc = accountInitialize();
    if(R_FAILED(rc)) {
          printf("accountInitialize() failed: 0x%x\n", rc);
          return false;
    }

    rc = accountGetUserCount(&mNumberOfUsers);
    if(R_FAILED(rc)) {
          printf("accountGetUserCount() failed: 0x%x\n", rc);
          return false;
    }

    size_t loadedUsers;
    rc = accountListAllUsers(mUserIds, ACC_USER_LIST_SIZE, &loadedUsers);
    if(R_FAILED(rc)) {
          printf("accountListAllUsers() failed: 0x%x\n", rc);
          return false;
    }
    printf("Number of loaded IDs: %d\n", loadedUsers);

    for(int i = 0; i < loadedUsers; i ++) {
        Account* account = new Account(mUserIds[i]); 
        printf("%s\n", account->getUsername());
    }

    return true;
}

void AccountRepository::exit()
{
    accountExit();
}

s32 AccountRepository::getNumberOfUsers()
{
    return mNumberOfUsers;
}