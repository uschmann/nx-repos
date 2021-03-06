#include "SaveData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SaveData::SaveData(int index, u128 userId, u64 titleId, char* name, char* author, size_t iconSize)
{
    mIndex = index;
    mUserId = userId;
    mTitleId = titleId;
    mIconSize = iconSize;

    sprintf(mName, "%s", name);
    sprintf(mAuthor, "%s", author);
}

char* SaveData::getName()
{
    return mName;
}

char* SaveData::getAuthor()
{
    return mAuthor;
}

int SaveData::getIndex()
{
    return mIndex;
}

NsApplicationControlData* SaveData::getApplicationControlData()
{
    Result rc = 0;
    size_t outsize=0;
    NsApplicationControlData *buf = NULL;
    buf = (NsApplicationControlData*)malloc(sizeof(NsApplicationControlData));
    if(buf == NULL) {
        printf("Failed to mallic NsApplicationControlData\n");
        return NULL;
    }
    memset(buf, 0, sizeof(NsApplicationControlData));

    rc = nsGetApplicationControlData(1, mTitleId, buf, sizeof(NsApplicationControlData), &outsize);
    return buf;
}

size_t SaveData::getImageSize()
{
    return mIconSize;
}

cJSON* SaveData::toJson()
{
    cJSON* json = cJSON_CreateObject();
    cJSON_AddItemToObject(json, "index", cJSON_CreateNumber(mIndex));
    cJSON_AddItemToObject(json, "name", cJSON_CreateString(mName));
    cJSON_AddItemToObject(json, "author", cJSON_CreateString(mAuthor));
    return json;
}