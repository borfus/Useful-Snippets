void LoadDll(HANDLE process, const wchar_t* dllPath)
{
    // write the dll name to memory
    int namelen = wcslen(dllPath) + 1;
    LPVOID remoteString = VirtualAllocEx(process, NULL, namelen * 2, MEM_COMMIT, PAGE_EXECUTE);
    WriteProcessMemory(process, remoteString, dllPath, namelen * 2, NULL);

    // get the address of LoadLibraryW()
    HMODULE k32 = GetModuleHandleA("kernel32.dll");
    LPVOID funcAdr = GetProcAddress(k32, "LoadLibraryW");

    // create the thread
    HANDLE thread = CreateRemoteThread(process, NULL, NULL, (LPTHREAD_START_ROUTINE)funcAdr, remoteString, NULL, NULL);
        
    // let the thread finish and clean up
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);    
    // Maybe use VirtualFreeEx(process, remoteString, namelen*2, MEM_RELEASE) when closing hack? 
}
