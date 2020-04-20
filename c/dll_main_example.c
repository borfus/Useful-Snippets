#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DWORD WINAPI run(LPVOID hModule) {
    // run your bot
    int new_base = (int)GetModuleHandle(NULL); // running with game codebase
    char new_base_string[16];
    _itoa(new_base, new_base_string, 16);
    char message_box_string[126] = "DLL Attached!\nNew Base: ";
    strcat(message_box_string, new_base_string);

    while (true) {
        if (GetAsyncKeyState(VK_END) & 1) {
            break;
        }

        if (GetAsyncKeyState(VK_BACK) & 1) {
            MessageBoxA(NULL, message_box_string, "Game Hacking", MB_OK | MB_TOPMOST);
        }
    }
    
    FreeLibraryAndExitThread((HMODULE)hModule, 0);
    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  reason,
                      LPVOID lpReserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            CloseHandle(CreateThread(NULL, 0, &run, hModule, 0, NULL));
            break;
        case DLL_PROCESS_DETACH: 
            printf("DLL detached!\n");
            break;
    }
    return TRUE;
}
