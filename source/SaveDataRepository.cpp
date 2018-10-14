
#include "SaveDataRepository.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SaveData.h"

SaveDataRepository::SaveDataRepository()
{
    init();
}

void SaveDataRepository::init()
{
    FsSaveDataIterator iterator;
    FsSaveDataInfo info;
    size_t total_entries = 0;
    size_t outsize = 0;

    NacpLanguageEntry* nle = NULL;
    NsApplicationControlData* nsacd = (NsApplicationControlData*)malloc(sizeof(NsApplicationControlData));
    if (nsacd == NULL)
    {
        printf("Could not alloc NsApplicationControlData\n");
        return;
    }
    memset(nsacd, 0, sizeof(NsApplicationControlData));

    Result res = fsOpenSaveDataIterator(&iterator, FsSaveDataSpaceId_NandUser);
    if (R_FAILED(res))
    {
        printf("fsOpenSaveDataIterator failed\n");
        free(nsacd);
        return;
    }

    int index = 0;
    while(1) {
        index ++;
        res = fsSaveDataIteratorRead(&iterator, &info, 1, &total_entries);

        if (R_FAILED(res) || total_entries == 0)
        {
            break;
        }

        if (info.SaveDataType == FsSaveDataType_SaveData)
        {
            u64 tid = info.titleID;
            u128 uid = info.userID;

            res = nsGetApplicationControlData(1, tid, nsacd, sizeof(NsApplicationControlData), &outsize);
            if(R_FAILED(res)) {
                printf("accountListAllUsers() failed: 0x%x\n", res);
            }
            if (R_SUCCEEDED(res) && !(outsize < sizeof(nsacd->nacp)))
            {
                res = nacpGetLanguageEntry(&nsacd->nacp, &nle);
                if (R_SUCCEEDED(res) && nle != NULL)
                {
                    SaveData saveData(index, uid, tid, nle->name, nle->author, outsize - sizeof(nsacd->nacp));
                    
                    if(mSavesData.find(uid) != mSavesData.end()) {
                        mSavesData.find(uid)->second.push_back(saveData);
                    }
                    else {
                        std::vector<SaveData> vec;
                        vec.push_back(saveData);
                        mSavesData.insert({ uid, vec });
                    }
                }
            }
            else {
                printf("nsGetApplicationControlData failed?\n");
            }
        }
    }

    free(nsacd);
    fsSaveDataIteratorClose(&iterator);
}

std::vector<SaveData>* SaveDataRepository::getSavesByUserId(u128 userId) 
{
    if(mSavesData.find(userId) != mSavesData.end()) {
        return &mSavesData.find(userId)->second;
    }
    return NULL;
}

size_t SaveDataRepository::getNumberOfSavesByUserId(u128 userId)
{
    if(mSavesData.find(userId) != mSavesData.end()) {
        return mSavesData.find(userId)->second.size(); 
    }
    return 0;
}

SaveData* SaveDataRepository::getSaveData(u128 userId, int index)
{
    if(mSavesData.find(userId) != mSavesData.end()) {
        std::vector<SaveData> saves = mSavesData.find(userId)->second; 
        for(int i = 0; i < saves.size(); i++) {
            if(saves.at(i).getIndex() == index) {
                return &saves.at(i);
            }
        }
    }
    return NULL;
}