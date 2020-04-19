#include <Windows.h>

#define define_dll_read_memory(T) \
T dll_read_memory_##T(LPVOID address) { \
        return *((T*)address); \
}

#define define_dll_write_memory(T) \
void dll_write_memory_##T(LPVOID address, T val) { \
        *((T*)address) = val; \
}

#define define_dll_read_memory_pointer(T) \
T* dll_read_memory_pointer_##T(LPVOID address) { \
        return ((T*)address); \
}

#define dll_read_memory(T) dll_read_memory_##T
#define dll_write_memory(T) dll_write_memory_##T
#define dll_read_memory_pointer(T) dll_read_memory_pointer_##T

define_dll_read_memory(DWORD)
define_dll_write_memory(DWORD)
define_dll_read_memory_pointer(DWORD)

// EXAMPLES
// DWORD val = dll_read_memory(DWORD)(adr);
// dll_write_memory(DWORD)(adr, val);

// Pointer ex
// DWORD* val_pointer = dll_read_memory_pointer(DWORD)(address); 
// DWORD value = *val_pointer;  // 'read'
// (*val_pointer)++;Windows// 'write'
