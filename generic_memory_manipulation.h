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

#define read_memory(T) read_memory_##T
#define write_memory(T) write_memory_##T

define_read_memory(DWORD)
define_write_memory(DWORD)

// example usage after defines
// DWORD val = read_memory(DWORD)(proc, adr)
// write_memory(DWORD)(proc, adr, val)