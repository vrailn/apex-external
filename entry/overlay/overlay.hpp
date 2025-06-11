#include "../main.h"
#include "includes.h"
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include "../imgui/imgui_impl_dx11.h"

#pragma comment(lib, "d3d11.lib")

using Microsoft::WRL::ComPtr;

namespace LootTexture
{
	namespace MedTexture {
		inline ComPtr<ID3D11ShaderResourceView> SmallMedTexture;
		inline ComPtr<ID3D11ShaderResourceView> LargeMedTexture;
		inline ComPtr<ID3D11ShaderResourceView> SmallShieldTexture;
		inline ComPtr<ID3D11ShaderResourceView> LargeShieldTexture;
		inline ComPtr<ID3D11ShaderResourceView> PhynioxTexture;
		inline ComPtr<ID3D11ShaderResourceView> EvoCacheTexture;
	}
	namespace AmmoTexture {
		inline ComPtr<ID3D11ShaderResourceView> SniperAmmoTexture;
		inline ComPtr<ID3D11ShaderResourceView> ShotGunAmmoTexture;
		inline ComPtr<ID3D11ShaderResourceView> LightAmmoTexture;
		inline ComPtr<ID3D11ShaderResourceView> HeavyAmmoTexture;
		inline ComPtr<ID3D11ShaderResourceView> EnergyAmmoTexture;
	}
	namespace Armor {
		inline ComPtr<ID3D11ShaderResourceView> ShieldTexture;
		inline ComPtr<ID3D11ShaderResourceView> HelmetTexture;
	}
}
inline std::vector<std::pair<int, std::string>> MedList = {
	{213, "Sringe"},
	{212, "Med-Kit"},
	{353, "Evo-Cache"},
	{215, "Shield-Cell"},
	{214, "Shield-Battery"},
	{211, "Phoenix-Kit"}
};


inline std::vector<std::pair<int, std::string>> SniperGunList = {
	{70, "Longbow DMR"},
	{75, "Charge Rifle"},
	{118, "Wingman"},
	{139, "Sentinel"},
	{146, "Bocek Compound Bow"},
};

inline std::vector<std::pair<int, std::string>> LightGunList = {
	{124, "P2020"},
	{133, "RE-45"},
	{48, "Alternator"},
	{53, "R-99"},
	{85, "R-301"},
	{80, "M600 Spit-fire"},
	{43, "G7 Scout"}
};

inline std::vector<std::pair<int, std::string>> LegendaryList = {
	{97, "PeaceKeeper"},
	{246, "Throwing Knife"},
	{1, "Kraber .50-Cal Sniper"},
	{27, "Triple Take"},

};

inline std::vector<std::pair<int, std::string>> EnergyList = {
	{14, "Havoc"},
	{20, "Devotion LMG"},
	{8, "L-Star EMG"},
	{65, "Volt SMG"},
	{157, "Nemesis Burst AR"},

};

inline std::vector<std::pair<int, std::string>> HeavyList = {
	{173, "C.A.R SMG"},
	{168, "Rampage LMG"},
	{152, "30-30 Repeater"},
	{59, "Prowler Burst PDW"},
	{37, "Hemlok Burst AR"},
	{32, "VK-47 Flatline"},

};

inline std::vector<std::pair<int, std::string>> ShotGunlist = {
	{102, "mozambique"},
	{90, "EVA"},
	{2, "Mastiff"}
};


inline std::vector<std::pair<int, std::string>> ShieldList = {
	{233, "Shield Level 1"},
	{234, "Shield Level 2"},
	{235, "Shield Level 3"},
	{223, "Shield Level 4"}
};


inline std::vector<std::pair<int, std::string>> BackList = {
	{242, "BackPack Level 1"},
	{243, "BackPack Level 2"},
	{244, "BackPack Level 3"},
	{245, "BackPack Level 4"}
};

inline std::vector<std::pair<int, std::string>> knockedShield = {
	{238, "Knocked Shield Level 1"},
	{239, "Knocked Shield Level 2"},
	{240, "Knocked Shield Level  3"},
};
inline std::vector<std::pair<int, std::string>> HelmetList = {
	  {205, "Helmet Level 1"},
	{206, "Helmet Level 2"},
	{220, "Helmet Level 3"},
	{221, "Helmet Level 4"}
};

namespace WeaponIcon
{
	namespace PistolICON
	{
		inline ComPtr<ID3D11ShaderResourceView> P2020Texture;
		inline ComPtr<ID3D11ShaderResourceView> AlternatorTexture;
		inline ComPtr<ID3D11ShaderResourceView> Re45Texture;
		inline ComPtr<ID3D11ShaderResourceView> WingmenTexture;
	}
	namespace ShotgunICON {
		inline ComPtr<ID3D11ShaderResourceView> EVA8Texture;
		inline ComPtr<ID3D11ShaderResourceView> MastiffTexture;
		inline ComPtr<ID3D11ShaderResourceView> MozambiqueTexture;
		inline ComPtr<ID3D11ShaderResourceView> peacekeeperTexture;
	}
	namespace Rifle {
		inline ComPtr<ID3D11ShaderResourceView> CarTexture;
		inline ComPtr<ID3D11ShaderResourceView> CarbineTexture;
		inline ComPtr<ID3D11ShaderResourceView> FlatlineTexture;
		inline ComPtr<ID3D11ShaderResourceView> HemlockTexture;
		inline ComPtr<ID3D11ShaderResourceView> ProwlerTexture;
		inline ComPtr<ID3D11ShaderResourceView> RampageTexture;
		inline ComPtr<ID3D11ShaderResourceView> RepeaterTexture;
		inline ComPtr<ID3D11ShaderResourceView> ScoutTexture;
		inline ComPtr<ID3D11ShaderResourceView> SpitFireTexture;
	}
	namespace Special {
		inline ComPtr<ID3D11ShaderResourceView> BowTexture;
		inline ComPtr<ID3D11ShaderResourceView> DevotionTexture;
		inline ComPtr<ID3D11ShaderResourceView> KnifeTexture;
		inline ComPtr<ID3D11ShaderResourceView> KraberTexture;
		inline ComPtr<ID3D11ShaderResourceView> R99Texture;
	}
	namespace Sniper {
		inline ComPtr<ID3D11ShaderResourceView> ChargedRifleTexture;
		inline ComPtr<ID3D11ShaderResourceView> DMRTexture;
		inline ComPtr<ID3D11ShaderResourceView> SentinelTexture;

	}
	namespace Energy {
		inline ComPtr<ID3D11ShaderResourceView> NemesisTexture;
		inline ComPtr<ID3D11ShaderResourceView> VoltTexture;
		inline ComPtr<ID3D11ShaderResourceView> TripleTexture;
		inline ComPtr<ID3D11ShaderResourceView> EMGTexture;
		inline ComPtr<ID3D11ShaderResourceView> HAVOCTexture;

	}
}

inline ComPtr<ID3D11Device> g_pd3dDevice;
inline ComPtr<ID3D11DeviceContext> g_pd3dDeviceContext;
inline ComPtr<IDXGISwapChain> g_pSwapChain;
inline ComPtr<ID3D11RenderTargetView> g_mainRenderTargetView;

inline void CreateRenderTarget()
{
	ComPtr<ID3D11Texture2D> pBackBuffer;
	g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	g_pd3dDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &g_mainRenderTargetView);
}

inline void CleanupRenderTarget()
{
	g_mainRenderTargetView.Reset();
}

inline bool createwindow()
{
	Overlay.Hwnd = FindWindowA(
		"Chrome_WidgetWin_1",
		"Discord Overlay"
	);

	if (!Overlay.Hwnd)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		MessageBoxA(0, ("didnt parse overlay."), ("Overlay"), MB_OK);
		Sleep(5000);
		exit(1);
		return false;
	}

	SetLayeredWindowAttributes(Overlay.Hwnd, RGB(0, 0, 0), BYTE(255), LWA_ALPHA);
	UpdateWindow(Overlay.Hwnd);
	HWND(overlaywindow);
	return true;
}

inline bool dx11()
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferCount = 2;
	sd.BufferDesc.Width = Width;
	sd.BufferDesc.Height = Height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = Overlay.Hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[1] = { D3D_FEATURE_LEVEL_11_0 };

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 1,
		D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext)))
	{
		return false;
	}

	CreateRenderTarget();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\ebrima.ttf", 16.0f);


	ImGui_ImplWin32_Init(Overlay.Hwnd);
	ImGui_ImplDX11_Init(g_pd3dDevice.Get(), g_pd3dDeviceContext.Get());
	return true;
}

inline bool setupoverlay() {
	if (!createwindow())
	{
		cout << "<!> Overlay Failed" << endl;
		return false;
	}
	if (!dx11())
	{
		cout << "<!> DirectX 11 Failed" << endl;
		return false;
	}
	return true;
}