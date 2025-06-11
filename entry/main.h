#pragma once
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <Psapi.h>
#include <dwmapi.h>
#include <d3d9.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_internal.h"
#include "kernel/driver.h"
#pragma comment(lib, "dwmapi.lib")

using namespace std;
namespace fs = std::filesystem;

int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);


IDirect3DTexture9* sillycar = nullptr;

struct CurrentProcess {
	DWORD ID;
	HANDLE Handle;
	HWND Hwnd;
	WNDPROC WndProc;
	int WindowWidth;
	int WindowHeight;
	int WindowLeft;
	int WindowRight;
	int WindowTop;
	int WindowBottom;
	LPCSTR Title;
	LPCSTR ClassName;
	LPCSTR Path;
}Process;

struct OverlayWindow {
	WNDCLASSEX WindowClass;
	HWND Hwnd;
	LPCSTR Name;
}Overlay;

struct DirectX9Interface {
	IDirect3D9Ex* IDirect3D9 = NULL;
	IDirect3DDevice9Ex* pDevice = NULL;
	D3DPRESENT_PARAMETERS pParameters = { NULL };
	MARGINS Margin = { -1 };
	MSG Message = { NULL };
}DirectX9;

extern driver::c_driver* ctx;

template<typename ret_t, typename addr_t>
ret_t read(addr_t address) {
	ret_t data{};
	if (!ctx->read_memory(
		(uintptr_t)address,
		&data,
		sizeof(ret_t)
	)) return ret_t{};
	return data;
}

template<typename data_t, typename addr_t>
bool write(addr_t address, data_t data) {
	return ctx->write_memory(
		(uintptr_t)address,
		&data,
		sizeof(data_t)
	);
}

inline std::string readstring(uintptr_t address) {
	char buffer[256];
	if (ctx->read_memory(address, buffer, sizeof(buffer) - 1)) {
		buffer[sizeof(buffer) - 1] = '\0';
		return std::string(buffer);
	}
	return "";
}

#include "overlay/overlay.hpp"
#include "engine/cheat/loop.hpp"