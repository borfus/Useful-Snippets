#include <Windows.h>

#define define_read_memory(T) \
T read_memory_##T(HANDLE process, LPVOID address) { \
	T val; \
	ReadProcessMemory(process, address, &val, sizeof(T), NULL); \
	return val; \
}

#define define_write_memory(T) \
void write_memory_##T(HANDLE process, LPVOID address, T val) { \
	WriteProcessMemory(process, address, &val, sizeof(T), NULL); \
}

#define define_protect_memory(T) \
DWORD protect_memory_##T(HANDLE process, LPVOID address, DWORD prot) { \
    DWORD old_prot; \
    VirtualProtectEx(process, address, sizeof(T), prot, &old_prot); \
    return old_prot; \
}

#define read_memory(T) read_memory_##T
#define write_memory(T) write_memory_##T
#define protect_memory(T) protect_memory_##T

define_read_memory(DWORD)
define_write_memory(DWORD)
define_protect_memory(DWORD)

// example usage after defines
// DWORD val = read_memory(DWORD)(proc, adr);
// write_memory(DWORD)(proc, adr, val);

// DWORD old_prot = protect_memory(DWORD)(proc, adr, PAGE_READWRITE);    // Might want PAGE_EXECUTE_READWRITE to prevent some game crashing
// write_memory(DWORD)(proc, adr, new_val);
// protect_memory(DWORD)(proc, adr, old_prot);
