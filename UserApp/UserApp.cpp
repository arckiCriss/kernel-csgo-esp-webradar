#include <iostream>
#include "CsgoProcess.h"
#include "Overlay.h"
#include <thread>
#include "Esp.h"

int main()
{
	LoadLibraryA("user32.dll");
	LoadLibraryA("win32u.dll");
	GetModuleHandleA("win32u.dll");


    CsgoProcess* csgo_process = csgo_process->getInstance();
	FOverlay* overlay = { 0 };

	if (!overlay->window_init())
		return 0;

	if (!overlay->init_d2d())
		return 0;

	std::thread t1(ESP::Run, overlay);

	t1.join();

	overlay->d2d_shutdown();

}
