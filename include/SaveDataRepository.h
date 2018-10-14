#pragma once
#include <switch.h>
#include <unordered_map>
#include <vector>
#include "SaveData.h"

class SaveDataRepository
{
    public:
        SaveDataRepository();
        std::vector<SaveData>* getSavesByUserId(u128 userId);
        size_t getNumberOfSavesByUserId(u128 userId);
        SaveData* getSaveData(u128 userId, int index);
    protected:
        void init();
        std::unordered_map<u128, std::vector<SaveData>> mSavesData;
};