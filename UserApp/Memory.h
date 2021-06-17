#pragma once

#include "Hook.h"
#include <TlHelp32.h>

namespace Memory
{
	int get_process_id_by_name(const char* process_name);
}