#include <switch.h>
#include <stdio.h>

#include "AccountRepository.h"
#include "SaveDataRepository.h"
#include "cJson.h"
#include <vector>

int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(NULL);

	accountInitialize();
	fsInitialize();
	nsInitialize();

	AccountRepository* accountRepository = new AccountRepository(); 
	SaveDataRepository* saveDataRepository = new SaveDataRepository();

	printf("Users: %d\n", accountRepository->getNumberOfUsers());

	Account account = accountRepository->getAccountByIndex(0);
	printf("%s\n", account.getUsername());

	for(int i = 0; i < saveDataRepository->getNumberOfSavesByUserId(account.getUserId()); i++) {
		std::vector<SaveData>* savData = saveDataRepository->getSavesByUserId(account.getUserId());
		printf("\t%s - %s\n", savData->at(i).getName(), savData->at(i).getAuthor());


		NsApplicationControlData* data = savData->at(i).getApplicationControlData();
		char filename[500];
		sprintf(filename, "%s.jpg", savData->at(i).getName());
		FILE* f = fopen(filename, "wb");
		fwrite(data->icon, savData->at(i).getImageSize(), 1, f);
		fclose(f);
	}

	
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

	accountExit();
	fsExit();
	nsExit();
	gfxExit();
	return 0;
}