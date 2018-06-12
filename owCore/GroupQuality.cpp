#include "stdafx.h"

// General
#include "GroupQuality.h"

enum R_SamplerState2 // DELETE ME!!!
{
	SS_FILTER_BILINEAR = 0x0000,
	SS_FILTER_TRILINEAR = 0x0001,
	SS_FILTER_POINT = 0x0002,

	SS_ANISO1 = 0x0000,
	SS_ANISO2 = 0x0004,
	SS_ANISO4 = 0x0008,
	SS_ANISO8 = 0x0010,
	SS_ANISO16 = 0x0020,

	SS_ADDRU_CLAMP = 0x0000,
	SS_ADDRU_WRAP = 0x0040,
	SS_ADDRU_CLAMPCOL = 0x0080,

	SS_ADDRV_CLAMP = 0x0000,
	SS_ADDRV_WRAP = 0x0100,
	SS_ADDRV_CLAMPCOL = 0x0200,

	SS_ADDRW_CLAMP = 0x0000,
	SS_ADDRW_WRAP = 0x0400,
	SS_ADDRW_CLAMPCOL = 0x0800,

	SS_ADDR_CLAMP = SS_ADDRU_CLAMP | SS_ADDRV_CLAMP | SS_ADDRW_CLAMP,
	SS_ADDR_WRAP = SS_ADDRU_WRAP | SS_ADDRV_WRAP | SS_ADDRW_WRAP,
	SS_ADDR_CLAMPCOL = SS_ADDRU_CLAMPCOL | SS_ADDRV_CLAMPCOL | SS_ADDRW_CLAMPCOL,

	SS_COMP_LEQUAL = 0x1000
};

CGroupQuality::CGroupQuality()
{
	_Bindings->RegisterInputListener(this);
}

CGroupQuality::~CGroupQuality()
{
	_Bindings->UnregisterInputListener(this);
}

void CGroupQuality::InitDefault()
{
	Terrain_LowDetail = false;
	Texture_Sampler = R_SamplerState2::SS_ANISO16;

	WMO_MOCV = true;
	WMO_AmbColor = false;

	draw_map_chunk = true;
	draw_map_wmo = true;
	draw_map_wmo_doodads = true;
	draw_map_mdx = true;
	draw_water = true;

	drawfog = false;
	timeEnable = false;
}

bool CGroupQuality::OnKeyboardPressed(int _key, int _scancode, int _mods)
{
	if (_key == OW_KEY_KP_1)
	{
		SwitchBool(draw_map_chunk);
		return true;
	}
	if (_key == OW_KEY_KP_2)
	{
		SwitchBool(draw_map_wmo);
		return true;
	}
	if (_key == OW_KEY_KP_3)
	{
		SwitchBool(draw_map_wmo_doodads);
		return true;
	}

	if (_key == OW_KEY_KP_4)
	{
		SwitchBool(draw_map_mdx);
		return true;
	}

	if (_key == OW_KEY_F1)
	{
		Texture_Sampler = R_SamplerState2::SS_FILTER_POINT;
		return true;
	}

	if (_key == OW_KEY_F2)
	{
		Texture_Sampler = R_SamplerState2::SS_FILTER_BILINEAR;
		return true;
	}

	if (_key == OW_KEY_F3)
	{
		Texture_Sampler = R_SamplerState2::SS_FILTER_TRILINEAR;
		return true;
	}

	if (_key == OW_KEY_F6)
	{
		Texture_Sampler = R_SamplerState2::SS_ANISO1;
		return true;
	}

	if (_key == OW_KEY_F7)
	{
		Texture_Sampler = R_SamplerState2::SS_ANISO2;
		return true;
	}

	if (_key == OW_KEY_F8)
	{
		Texture_Sampler = R_SamplerState2::SS_ANISO4;
		return true;
	}

	if (_key == OW_KEY_F9)
	{
		Texture_Sampler = R_SamplerState2::SS_ANISO8;
		return true;
	}

	if (_key == OW_KEY_F10)
	{
		Texture_Sampler = R_SamplerState2::SS_ANISO16;
		return true;
	}

	if (_key == OW_KEY_C)
	{
		SwitchBool(WMO_MOCV);
		return true;
	}

	if (_key == OW_KEY_V)
	{
		SwitchBool(WMO_AmbColor);
		return true;
	}

	if (_key == OW_KEY_F)
	{
		SwitchBool(drawfog);
		return true;
	}

	if (_key == OW_KEY_T)
	{
		SwitchBool(timeEnable);
		return true;
	}

	return false;
}