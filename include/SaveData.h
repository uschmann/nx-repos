#pragma once

#include <switch.h>
#include "cJson.h"

class SaveData
{
    public:
        SaveData(int index, u128 userId, u64 titleId, char* name, char* author, size_t iconSize);
        char* getName();
        char* getAuthor();
        size_t getImageSize();
        int getIndex();
        NsApplicationControlData* getApplicationControlData();
        cJSON* toJson();
    protected:    
        int mIndex;
        u64 mTitleId;
        u128 mUserId;
        char mName[0x200];
        char mAuthor[0x100];
        size_t mIconSize;
};