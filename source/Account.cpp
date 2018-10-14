#include "Account.h"
#include <cstring>
#include <cstdlib>

Account::Account(u128 userId, int index)
{
    mUserId = userId;
    mIndex = index;

    AccountProfile profile;
    AccountUserData userData;
    AccountProfileBase profileBase;
    Result rc = 0;

    rc = accountGetProfile(&profile, mUserId);
    if(R_FAILED(rc)) {
        printf("accountGetProfile failed: 0x%x\n", rc);
    }

    rc = accountProfileGet(&profile, &userData, &profileBase);
    if(R_FAILED(rc)) {
        printf("accountProfileGet failed: 0x%x\n", rc);
    }

    memset(mUsername, 0, sizeof(mUsername));
    strncpy(mUsername, profileBase.username, sizeof(mUsername)-1);

    rc = accountProfileGetImageSize(&profile, &mImageSize);
    if(R_FAILED(rc)) {
        printf("accountProfileGetImageSize failed: 0x%x\n", rc);
    }

    accountProfileClose(&profile);
}

Account::~Account()
{

}

u8* Account::loadImage()
{
    AccountProfile profile;
    Result rc = 0;

    rc = accountGetProfile(&profile, mUserId);
    if(R_FAILED(rc)) {
        printf("accountGetProfile failed: 0x%x\n", rc);
    }

    u8 * image = new u8[mImageSize];
    size_t actualImageSize;
    rc = accountProfileLoadImage(&profile, image, mImageSize, &actualImageSize);
    if(R_FAILED(rc)) {
        printf("accountProfileLoadImage failed: 0x%x\n", rc);
    }

    accountProfileClose(&profile);

    return image;
}

u128 Account::getUserId()
{
    return mUserId;
}

char * Account::getUsername() 
{
    return mUsername;
}

size_t Account::getImageSize()
{
    return mImageSize;
}

cJSON* Account::toJson()
{
    cJSON* json = cJSON_CreateObject();
    cJSON_AddItemToObject(json, "index", cJSON_CreateNumber(mIndex));
    cJSON_AddItemToObject(json, "name", cJSON_CreateString(mUsername));

    return json;
}