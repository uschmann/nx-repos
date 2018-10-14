#include <switch.h>
#include <stdio.h>

#include "AccountRepository.h"
#include "SaveDataRepository.h"
#include "SettingsRepository.h"
#include "cJson.h"
#include <vector>

int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(NULL);

	// Account
	accountInitialize();
	// SaveData
	fsInitialize();
	nsInitialize();
	// Settings
	setInitialize();
	setsysInitialize();

	AccountRepository* accountRepository = new AccountRepository(); 
	SaveDataRepository* saveDataRepository = new SaveDataRepository();
	SettingsRepository* settingsRepository = new SettingsRepository();

	Account account = accountRepository->getAccountByIndex(0);
	SaveData* save = saveDataRepository->getSaveData(account.getUserId(), 1);

	// Main loop
	while(appletMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		// Your code goes here

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_PLUS) break; // break in order to return to hbmenu

		gfxFlushBuffers();
		gfxSwapBuffers();
		gfxWaitForVsync();
	}

	delete accountRepository;
	delete saveDataRepository;
	delete settingsRepository;

	accountExit();
	fsExit();
	nsExit();
	setExit();
	setsysExit();
	gfxExit();
	return 0;
}