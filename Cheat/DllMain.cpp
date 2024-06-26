#include "stdafx.h"

HMODULE g_hModule = nullptr;

DWORD __stdcall OnDllAttach( LPVOID lpParams )
{
#if(L4D2_DEBUG == 1)
	AllocConsole();
	freopen( "conin$", "r", stdin );
	freopen( "conout$", "w", stdout );
	freopen( "conout$", "w", stderr );
#endif

	g_Interfaces = std::make_unique<Interfaces::CInterfaces>();
	Hooks::Initialize();

	for (;;)
	{
		std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );

		if (GetAsyncKeyState( VK_DELETE ))
		{
			printf("unhook");
			Hooks::Unhook();
			std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
			FreeLibraryAndExitThread( g_hModule, 0 );
		}
	}
}

int __stdcall DllMain( HMODULE hModule, int nReason, PVOID lpReserved )
{
	if (nReason == DLL_PROCESS_ATTACH)
	{
		g_hModule = hModule;
		CreateThread( nullptr, 0, OnDllAttach, nullptr, 0, nullptr );
		
		return TRUE;
	}

	return TRUE;
}