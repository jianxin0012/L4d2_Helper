#pragma once

namespace Offsets
{
	struct SOffsets
	{
		std::uintptr_t m_iHealth = 0xEC;
		std::uintptr_t m_nTeamNum = 0xE4;
		std::uintptr_t m_vecOrigin = 0x94;
		std::uintptr_t m_lifeState = 0x147;
		std::uintptr_t m_fFlags = 0xF0;
		std::uintptr_t m_vecViewOffset = 0xF4;
		std::uintptr_t m_nSequence = 0x8A4;
		std::uintptr_t m_hActiveWeapon = 0x1084;
		//std::uintptr_t m_weaponID = 0x958;
		std::uintptr_t m_fMaxSpread = 0xD0C;
		std::uintptr_t m_hOwnerEntity = 0x138;
		std::uintptr_t m_nTickbase = 0x14EC;
		std::uintptr_t m_iWeaponID = 0x2C;
		std::uintptr_t m_vecPunch = 0x1224;
		std::uintptr_t clientMode = findByPattern("client.dll", "8904B5????E8") + 0x3;
		std::uintptr_t uSharedRandomFloat = findByPattern("client.dll", "558BEC83EC08A1????5356578B7D148D4D1451897DF88945FCE8????6A048D55FC528D451450E8????6A048D4DF8518D551452E8????8B750856E8????508D45145650E8????8D4D1451E8????8B15????8B5D1483C430837A30007426");
		std::uintptr_t PredictionRandomSeed = uSharedRandomFloat + 0x7;
		std::uintptr_t UpdateMaxSpread = findByPattern("client.dll", "538BDC83EC0883E4F083C404558B6B04896C24048BEC83EC2856578BF9E8????8BCF8945F0E8????8BF085F6751B");
		std::uintptr_t moveHelper = findByPattern("client.dll", "8B0D????8B118B5234") + 0x2;
		std::uintptr_t GlobalVars = findByPattern("client.dll", "A1????D9400C51D91C2457") + 0x1;
		std::uintptr_t WeaponIDToAlias = findByPattern("client.dll", "558BEC8B450883F837");		
		std::uintptr_t InfAmmo = findByPattern("server.dll", "8B86141400008D78FFC645FF003BC774") + 0xF;		

		// 函数将一个1字节的十六进制字符串转换为1字节的十六进制值
		unsigned char hexStringToByte(const char* hexStr) {
			//取出两个字符
			char str[3] = { hexStr[0],hexStr[1],'\0' };
			// 使用strtoul函数将十六进制字符串转换为整数值
			char* endPtr;
			unsigned long intValue = strtol(str, &endPtr, 16);

			// 确保整数值在一个字节的范围内（0到255）
			intValue &= 0xFF;

			// 将整数值转换为1字节的十六进制表示
			unsigned char byteValue = static_cast<unsigned char>(intValue);
			return byteValue;
		}

		std::uintptr_t findByPattern(const char* moduleName, const char* pattern)
		{
			if (!moduleName || !pattern)
			{
				return 0;
			}

			HMODULE hModule = GetModuleHandleA(moduleName);
			if (hModule == 0x0)
			{
				return 0x0;
			}
			char* baseAddress = reinterpret_cast<char*>(hModule);
			printf("client基址：%d", reinterpret_cast<DWORD>(baseAddress));
			PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)baseAddress;
			PIMAGE_NT_HEADERS ntHeaders = (PIMAGE_NT_HEADERS)(baseAddress + dosHeader->e_lfanew);
			if (ntHeaders == 0x0)
			{
				return 0x0;
			}
			char* startAddress = baseAddress + ntHeaders->OptionalHeader.BaseOfCode;
			char* endAddress = startAddress + ntHeaders->OptionalHeader.SizeOfCode;
			std::uintptr_t ret = 0;
			const char* pat = pattern;

			for (; startAddress <= endAddress; startAddress++)
			{
				const unsigned char byte = *startAddress;
				const unsigned char patChar = *pat;
				if (patChar == '\?' || byte == hexStringToByte(pat))
				{
					printf("%d\n", byte);
					if (ret == 0)
					{
						ret = reinterpret_cast<std::uintptr_t>(startAddress);
					}
					if (!pat[2]) //如果当前指针向后三位是空字符（当前匹配的2位再加上字符串结尾默认的空字符），代表匹配完成，直接返回结果。
					{
						return ret;
					}
					pat += (patChar == '\?') ? 1 : 2; //问号移动一位，别的移动两位

				}
				else
				{
					pat = pattern;
					ret = 0;
				}
			}
			return 0;
		}
	};

}

extern Offsets::SOffsets g_Offsets;