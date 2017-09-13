#pragma once

class WoWSettings
{
	CLASS_INSTANCE_API(WoWSettings, OW_SHARED_DLL_API);

public:
	OW_SHARED_DLL_API WoWSettings();

public:
	inline void CalculateSquareDistances()
	{
		highresdistance2 = highresdistance * highresdistance;
		mapdrawdistance2 = mapdrawdistance * mapdrawdistance;
		modeldrawdistance2 = modeldrawdistance * modeldrawdistance;
		doodaddrawdistance2 = doodaddrawdistance * doodaddrawdistance;
		culldistance2 = culldistance * culldistance;
	}

public:
	// Distances
	float mapdrawdistance, modeldrawdistance, doodaddrawdistance, highresdistance, culldistance;
	float mapdrawdistance2, modeldrawdistance2, doodaddrawdistance2, highresdistance2, culldistance2;
	float fogdistance;

	// Drawing
	bool lighting;
	bool drawmodels;
	bool drawdoodads;
	bool drawterrain;
	bool drawwmo;
	bool loading;
	bool drawhighres;
	bool drawfog;
	bool drawColors;

	// Quality
	bool uselowlod;
	bool useshaders;
};

#define _WowSettings WoWSettings::instance()