#include "SettingsRepository.h"
#include <stdio.h>
#include <string.h>

ColorSetId SettingsRepository::getSystemeTheme() 
{
    ColorSetId theme;
    Result rc = setsysGetColorSetId(&theme);
	if(R_FAILED(rc)) {
		printf("Failed to get color\n");
	}

    return theme;
}

void SettingsRepository::setSystemeTheme(ColorSetId theme)
{
    setsysSetColorSetId(theme);
}   

SetRegion SettingsRepository::getRegion()
{
    SetRegion region;
    setGetRegionCode(&region);
    return region; 
}

void SettingsRepository::getSystemLanguage(char* lang)
{
    setGetSystemLanguage((u64*)lang);
}

void SettingsRepository::getSerialNumber(char* serial)
{
    setsysGetSerialNumber(serial);
}

cJSON* SettingsRepository::getInfo()
{
    char buffer[1024];
    cJSON* json = cJSON_CreateObject();
    getSystemLanguage(buffer);
    cJSON_AddItemToObject(json, "language", cJSON_CreateString(buffer));

    getSerialNumber(buffer);
    cJSON_AddItemToObject(json, "serial", cJSON_CreateString(buffer));

    switch(getSystemeTheme()) {
        case ColorSetId::ColorSetId_Light:
            cJSON_AddItemToObject(json, "theme", cJSON_CreateString("light"));
            break;
        case ColorSetId::ColorSetId_Dark:
            cJSON_AddItemToObject(json, "theme", cJSON_CreateString("dark"));
            break;
    }

    switch(getRegion()) {
        case SetRegion::SetRegion_AUS:
            cJSON_AddItemToObject(json, "region", cJSON_CreateString("aus"));
            break;
        case SetRegion::SetRegion_EUR:
            cJSON_AddItemToObject(json, "region", cJSON_CreateString("eur"));
            break;
        case SetRegion::SetRegion_JPN:
            cJSON_AddItemToObject(json, "region", cJSON_CreateString("jpn"));
            break;
        case SetRegion::SetRegion_USA:
            cJSON_AddItemToObject(json, "region", cJSON_CreateString("usa"));
            break;
        default:
            cJSON_AddItemToObject(json, "region", cJSON_CreateString("unknown"));
            break;
    }

    return json;
}

