#pragma once
#include "DriverAPI.h"
#include <stdio.h>

class CsgoProcess {

	static CsgoProcess* instance;

	CsgoProcess() {
		while (!Pid) {
			Pid = Memory::get_process_id_by_name("csgo.exe");
			Sleep(1000);
		}
		printf("csgo pid: %d\n", Pid);
		while (!client_base) {
			client_base = DriverAPI::get_client_base(Pid);
			Sleep(1000);
		}
		printf("found client.dll: 0x%x\n", client_base);
		while (!engine_base) {
			engine_base = DriverAPI::get_engine_base(Pid);
			Sleep(1000);
		}
		printf("found engine.dll: 0x%x\n", engine_base);
	}

public:

	static CsgoProcess* getInstance() {
		if (!instance)
			instance = new CsgoProcess;
		return instance;
	}

	int Pid = 0;
	ULONG client_base = 0;
	ULONG engine_base = 0;


	template<typename t>
	t RPM(ULONG address) {
		return DriverAPI::read_memory<t>(Pid, address);
	}

	template<typename t>
	void WPM(int address, t buffer) {
		return DriverAPI::write_memory(Pid, address, buffer);
	}

};
