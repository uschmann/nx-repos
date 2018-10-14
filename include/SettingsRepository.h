#pragma once

#include <switch.h>
#include "cJson.h"

class SettingsRepository
{
    public:
        SetRegion getRegion();
        ColorSetId getSystemeTheme();
        void setSystemeTheme(ColorSetId theme);
        void getSystemLanguage(char* lang);
        void getSerialNumber(char* serial);

        cJSON* getInfo();
};  