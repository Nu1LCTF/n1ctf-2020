#ifndef _COMMON_H
#define _COMMON_H

#include "ntdll.h"

#define HALLOC(x) ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, x)
#define HFREE(x) ::HeapFree(::GetProcessHeap(), 0, x)

#endif 