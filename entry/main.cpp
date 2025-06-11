#include "main.h"
#include <thread>
#include <iostream>
#include <Windows.h>

driver::c_driver* ctx = new driver::c_driver();


auto init() -> bool
{
	if (!ctx->setup())
	return std::getchar();

	if (!ctx->attach(L"r5apex_dx12.exe"))
	{
		cout << "<!> failed to find process" << endl;
		return false;
	}

	std::cout << "PID: " << ctx->m_process_id << std::endl;

	std::cout << "BASE ADDR: " << ctx->m_base_address << std::endl;



	setupoverlay();

	std::thread player_thread(player_reading_work);
	std::thread glow_thread(glow_loop);
	render_loop();

	player_thread.join();
	glow_thread.join();

}

auto main() -> void
{
	SetConsoleTitleA("gurt: sybau Private. apex external, @vrailn");

	cout << "gurt: sybau private " << endl;

	if (!init())
	{

		cout << "<!> failed to gurt: sybau" << endl;
		Sleep(3000);
		exit(0);
	}

}