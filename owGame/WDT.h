#pragma once

#include "ADT_WMO_Instance.h"

struct WDT_MPHD_Flags
{
	uint32 Flag_GlobalWMO : 1;  // Use global map object definition.
	uint32 Flag_UseMCCV : 1;    // Use vertex shading (ADT.MCNK.MCCV)
	uint32 Flag_8bitMCAL : 1;   // Decides whether to use _env terrain shaders or not: funky and if MCAL has 4096 instead of 2048(?)
	uint32 Flag_Unk0 : 1;       // Disables something. No idea what. Another rendering thing. Someone may check all them in wild life..
	uint32 Flag_HasMCLV : 1;    // vertexBufferFormat = PNC2. (adds second color: ADT.MCNK.MCLV)
	uint32 Flag_FlipGround : 1; // Flips the ground display upside down to create a ceiling (Cataclysm)
	uint32 : 26;
};

struct WDT_MAIN
{
	struct Flags
	{
		uint32 Flag_HasADT : 1;
		uint32 Flag_IsLoaded : 1;
		uint32 : 30;
	}			flags;
	uint32_t	asyncId;
};

// FORWARD BEGIN
class MapController;
// FORWARD END

class WDT
{
	friend MapController;
public:
	WDT();

	void CreateInsances(SceneNode* _parent);

	void Load(cstring _name);

	//--

	bool MapHasTiles() { return m_IsTileBased; }
	bool MapHasGlobalWMO() { return !m_GlobalWMOName.empty(); }

	ADT_WMO_Instance* GetGlobalWMOInstance() { return m_GlobalWMO; }
	ADT_MODF& GetGlobalWMOPlacementInfo() { return m_GlobalWMOPlacementInfo; }

private:
	WDT_MPHD_Flags		m_Flag;
	bool				m_IsTileBased;
	WDT_MAIN			m_TileFlag[C_TilesInMap][C_TilesInMap];

private:
	string						m_GlobalWMOName;
	ADT_MODF					m_GlobalWMOPlacementInfo;
	SmartPtr<ADT_WMO_Instance>	m_GlobalWMO;
};