#include "Hook.h"

bool Hook::init(void* kernel_address)
{
	if (!kernel_address) { return false; }

	void** function = reinterpret_cast<void**>(Memory::get_system_module_export("\\SystemRoot\\System32\\drivers\\dxgkrnl.sys", "NtGdiDdDDINetDispGetNextChunkInfo"));
	if (!function) { return false; }
	if (!function)
		return false;

	BYTE orig[] = { 0xCF, 0xDF, 0xFF, 0xFD, 0xFC, 0xCD, 0xDC, 0xCC, 0xDD, 0xFE, 0xEF, 0xEE };

	BYTE shell_code[] = { 0x48, 0xB8 };
	BYTE shell_code_end[] = { 0xFF, 0xE0 }; 

	RtlSecureZeroMemory(&orig, sizeof(orig));
	memcpy((PVOID)((ULONG_PTR)orig), &shell_code, sizeof(shell_code));
	uintptr_t hook_address = reinterpret_cast<uintptr_t>(kernel_address);
	memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code)), &hook_address, sizeof(void*));
	memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code) + sizeof(void*)), &shell_code_end, sizeof(shell_code_end));

	Memory::wpm(function, &orig, sizeof(orig));

	return true;
}

void Hook::handler(void* info_struct)
{
	PINFO_STRUCT info = (PINFO_STRUCT)info_struct;

	if (info->code == CLIENT_MODULE_REQUEST)
	{
		PEPROCESS target_process = NULL;
		if (NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)info->process_id, &target_process)))
		{
			KAPC_STATE apc;
			KeStackAttachProcess(target_process, &apc);
			ULONG b = Memory::get_module_base(target_process, L"client.dll");
			KeUnstackDetachProcess(&apc);
			if (b) { info->client_base = b; }
		}
	}
	else if (info->code == CODE_READ_MEMORY)
	{
		PEPROCESS target_process = NULL;
		if (NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)info->process_id, &target_process)))
		{
			Memory::read_memory(target_process, (void*)info->address, &info->buffer, info->size);
		}
	}
	else if (info->code == CODE_WRITE_MEMORY)
	{
		PEPROCESS target_process = NULL;
		if (NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)info->process_id, &target_process)))
		{
			Memory::write_memory(target_process, &info->buffer, (void*)info->address, info->size);
		}
	}
	else if (info->code = ENGINE_MODULE_REQUEST) {
		PEPROCESS target_process = NULL;
		if (NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)info->process_id, &target_process)))
		{
			KAPC_STATE apc;
			KeStackAttachProcess(target_process, &apc);
			ULONG b = Memory::get_module_base(target_process, L"engine.dll");
			KeUnstackDetachProcess(&apc);
			if (b) { info->engine_base = b; }
		}
	}
}
