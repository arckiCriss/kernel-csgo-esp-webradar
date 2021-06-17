#include "Hook.h"

void Hook::call_hook(void* info_struct)
{
	void* hooked_fn = GetProcAddress(GetModuleHandleA("win32u.dll"), "NtGdiDdDDINetDispGetNextChunkInfo");

	auto fn = static_cast<void(_stdcall*)(void*)>(hooked_fn);

	fn(info_struct);
}
