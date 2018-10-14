#pragma once

#include <switch.h>
#include <stdio.h>
#include "cJson.h"

class Account
{
    public:
        Account(u128 userId, int index);
        ~Account();

        u128 getUserId();
        char * getUsername();
        u8* loadImage();

        size_t getImageSize();
        cJSON* toJson();
    protected:
        u128 mUserId;
        int mIndex;
        size_t mImageSize;
        char mUsername[0x21];
};
