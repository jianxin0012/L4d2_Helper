#include "stdafx.h"

MiscFeatures::CMiscFeatures::CMiscFeatures() {}

MiscFeatures::CMiscFeatures::~CMiscFeatures() {}

void MiscFeatures::CMiscFeatures::Execute( CUserCmd* cmd )
{
	Bunnyhop( cmd );
	InfiniteAmmo();
}

void MiscFeatures::CMiscFeatures::Bunnyhop( CUserCmd * cmd )
{
	auto pLocal = g_Interfaces->EntityList->GetClientEntity( g_Interfaces->EngineClient->GetLocalPlayer() );
	if (!pLocal || pLocal->LifeState())
		return;

	auto nFlags = pLocal->Flags();

	if (cmd->buttons & IN_JUMP && GetAsyncKeyState( VK_SPACE ))
	{
		if (!(nFlags & FL_ONGROUND))
			cmd->buttons &= ~IN_JUMP;
	}
}

void modifyMemoryByte(char* byte,char value) {
	DWORD oldProtect;
	if (!VirtualProtect(byte, 0x1, PAGE_EXECUTE_READWRITE, &oldProtect)) {
		return;
	}
	*byte = value;

	DWORD dummy;
	VirtualProtect(byte, 0x1, oldProtect, &dummy);
}

void MiscFeatures::CMiscFeatures::InfiniteAmmo()
{
	static char* byte = reinterpret_cast<char*>(g_Offsets.InfAmmo);

	if (g_Config.m_bInfAmmo && *byte == 0x74)
	{
		modifyMemoryByte(byte,0x75);
	}
	if (!g_Config.m_bInfAmmo && *byte == 0x75)
	{
		modifyMemoryByte(byte, 0x74);
	}
}
