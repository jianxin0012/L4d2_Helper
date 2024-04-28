#pragma once

namespace Config
{
	enum AIMBOT_MODE
	{
		AIMBOT_OFF = 0,
		AIMBOT_NONSILENT,
		AIMBOT_SILENT
	};

	struct SConfig
	{
		std::int32_t m_nAimMode = AIMBOT_MODE::AIMBOT_OFF;
		std::int32_t m_nAimkey = 1;
		bool m_bChams = false;
		bool m_bESP = false;
		bool m_bInfAmmo = false;
	};
}

extern Config::SConfig g_Config;