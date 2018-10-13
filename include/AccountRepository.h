#pragma once

#include <switch.h>
#include <stdio.h>
#include <string.h>
#include "account.h"


class AccountRepository
{
    public:
        AccountRepository();
        bool init();
        void exit();

        s32 getNumberOfUsers();
    protected:
        s32 mNumberOfUsers;
        u128* mUserIds;



};