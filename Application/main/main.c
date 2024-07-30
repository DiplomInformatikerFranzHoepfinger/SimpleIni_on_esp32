#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>






#include "settingsIni.h"




void file_server_main1(void);
void file_server_main2(void);





void app_main(void)
{









    file_server_main1();

	initSettings("/data/settings.ini");
	setX64("test-Sec", "test-key", 0xFFFFFFFFFFFFFFFFU);
	saveSettings();




	uint64_t u64testVal = getX64("test-Sec2", "test-key2", 0xFAFAFAFAFAFAFAFAU);
	
	printf("test-key2: %" PRIx64 "  \n", u64testVal);

    file_server_main2();
}
