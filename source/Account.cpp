#include "Account.h"
#include <cstring>
#include <cstdlib>

Account::Account(u128 userId)
{
    mUserId = userId;
    
    load();
}

void Account::load()
{
    Result rc = 0;
    
    rc = accountGetProfile(&mProfile, mUserId);
    if(R_FAILED(rc)) {
        printf("accountGetProfile failed: 0x%x\n", rc);
    }

    rc = accountProfileGet(&mProfile, &mUserData, &mProfileBase);
    if(R_FAILED(rc)) {
        printf("accountProfileGet failed: 0x%x\n", rc);
    }

    memset(mUsername, 0, sizeof(mUsername));
    strncpy(mUsername, mProfileBase.username, sizeof(mUsername)-1);

    rc = accountProfileGetImageSize(&mProfile, &mImageSize);
    if(R_FAILED(rc)) {
        printf("accountProfileGetImageSize failed: 0x%x\n", rc);
    }

    mImage = (u8*)malloc(mImageSize);
    accountProfileLoadImage(&mProfile, &mImage, 1, &mImageSize);

    accountProfileClose(&mProfile);
}

u128 Account::getUserId()
{
    return mUserId;
}

char * Account::getUsername() 
{
    return mUsername;
}