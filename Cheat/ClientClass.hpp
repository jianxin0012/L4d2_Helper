#pragma once

class ClientClass;
class IClientNetworkable;

using FnCreateClientClass = IClientNetworkable * (__cdecl*)(std::uint32_t nEntityIndex, std::uint32_t nSerialNum);
using FnCreateEvent = IClientNetworkable * (__cdecl*)();

enum ClassID
{
	CWorld = 260,
	CTerrorPlayer = 231,
	SurvivorBot = 275,
	CCSTeam = 50,
	CTerrorPlayerResource = 232,
	CVoteController = 252,
	CTerrorGameRulesProxy = 228,
	CBeamSpotlight = 32,
	CSprite = 177,

	CWeaponAmmoSpawn = 256,  //�����ӵ��ĵط�
	CWeaponSpawn = 260, //�����ӵ��ĵط�

	CFuncPlayerInfectedClip = 86,
	CFuncSimpleLadder = 90,
	CRopeKeyframe = 156,
	C_BaseEntity = 15,
	CFogController = 75,
	CShadowControl = 160,
	CEnvTonemapController = 65,
	CEnvDetailController = 57,
	CWaterLODControl = 254,
	CTerrorViewModel = 233,
	CPhysicsProp = 127,
	CSteamJet = 180,
	CPistol = 131,
	CBasePropDoor = 21,
	CFuncAreaPortalWindow = 78,
	CPostProcessController = 138,
	CParticleSystem = 124,
	CShotgun_Chrome = 161,
	CColorCorrection = 45,
	CFuncOccluder = 84,
	CFirstAidKit = 73,
	CDynamicProp = 52,
	CSurvivorPosition = 184,
	CBaseUpgradeItem = 29,
	CSpotlightEnd = 176,
	CPropDoorRotatingCheckpoint = 143,
	CBeam = 31,
	CFireSmoke = 70,
	CBreakable = 35,
	CSceneEntity = 158,

	Boomer = 0,
	Charger = 99,
	Hunter = 263,
	Infected = 264,
	Jockey = 265,
	Smoker = 270,
	Spitter = 272,
	Witch = 277,
	Tank = 276,


	CSmokerClaw = 167,
	CTongue = 245,
	
	CHunterClaw = 100,
	CCSRagdoll = 49,
	
	CJockeyClaw = 112,
	CBoomerClaw = 34,
	
	CChargerClaw = 41,
	
	CSpitterClaw = 175,
	CSpitterProjectile = 175,
	CInsectSwarm = 104,
	
	CTankClaw = 186,
	
	CBaseCSGrenadeProjectile = 13,
	CMolotov = 118,
	CMolotovProjectile = 119,
	CInferno = 101,
	CEntityFlame = 55,
	CPipeBomb = 129,
	CPipeBombProjectile = 130,
	CItem_Adrenaline = 105,
	CAutoShotgun = 2,
	CTerrorMeleeWeapon = 230,
	CChainsaw = 39,
	CColaBottles = 44,
	CItemDefibrillator = 109,
	CFireworkCrate = 72,
	CGasCan = 94,
	CGnome = 95,
	CGrenadeLauncher = 96,
	CSniperRifle = 171,
	COxygenTank = 120,
	CPainPills = 121,
	CMagnumPistol = 116,
	CPropaneTank = 142,
	CPumpShotgun = 148,
	CFireCrackerBlast = 69,
	CAssaultRifle = 1,
	CRifle_AK47 = 152,
	CRifle_Desert = 153,
	CRifle_M60 = 154,
	CRifle_SG552 = 155,
	CShotgun_SPAS = 163,
	CSubMachinegun = 181,
	CSMG_MP5 = 164,
	CSMG_Silenced = 165,
	CSniper_AWP = 169,
	//CSniper_Military = 169,???
	CSniper_Scout = 170,
	CItemUpgradePackExplosive = 110,
	CItemUpgradePackIncendiary = 111,
	CItem_VomitJar = 106,

};

struct RecvProp;

struct RecvTable
{
	RecvProp* m_pProps;
	int m_nProps;
	void* m_pDecoder;
	char* m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

class ClientClass
{
public:
	FnCreateClientClass      m_pCreateFn;
	FnCreateEvent            m_pCreateEventFn;
	char*                    m_pNetworkName;
	RecvTable*				 m_pRecvTable;
	ClientClass*             m_pNext;
	ClassID                  m_ClassID;
};