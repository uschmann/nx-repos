#pragma once

#include <switch.h>
#include <stdio.h>

class Account
{
    public:
        Account(u128 userId);

        u128 getUserId();
        char * getUsername();
    protected:
        u128 mUserId;
        AccountProfile mProfile;
        AccountUserData mUserData;
        AccountProfileBase mProfileBase;
        size_t mImageSize;
        u8 * mImage;

        char mUsername[0x21];

        void load();
};
