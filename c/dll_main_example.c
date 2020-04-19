#include <Windows.h>

DWORD WINAPI runBot(LPVOID lpParam) {
    // run your bot
    DWORD new_base = (DWORD)GetModuleHandle(NULL); // running with game codebase
    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            MessageBoxA(NULL, "DLL Attached!\n", "Game Hacking", MB_OK | MB_TOPMOST);
            HANDLE thread = CreateThread(NULL, 0, &runBot, NULL, 0, NULL);
            CloseHandle(thread);
            break;
        case DLL_PROCESS_DETACH:
            printf("DLL detached!\n");
            break;
    }
    return TRUE;
}
