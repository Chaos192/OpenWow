#include "stdafx.h"

#ifdef USE_M2_MODELS

// Include
#include "Character.h"

// General
#include "Character_SectionWrapper.h"

/*
			0 -	Base Skin		1 - Face			2 - Facial Hair		3 - Hair			4 - Underwear
Type		-					FaceType			FacialHairType		HairStyle			-
Texture1	SkinTexture			FaceLowerTexture	FacialLowerTexture	HairTexture			PelvisTexture
Texture2	ExtraSkinTexture	FaceUpperTexture	FacialUpperTexture	ScalpLowerTexture	TorsoTexture
Texture3	-					-					-					ScalpUpperTexture	-
*/

Character_SectionWrapper::Character_SectionWrapper(const IBaseManager& BaseManager)
	: m_BaseManager(BaseManager)
{
	m_DBCs = m_BaseManager.GetManager<CDBCStorage>();
}

Character_SectionWrapper::~Character_SectionWrapper()
{
}

std::shared_ptr<IImage> Character_SectionWrapper::getSkinTexture(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharSections())
	{
		if (i->Get_GeneralType() == DBC_CharSections_GeneralType::Skin &&
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Color() == (uint32)CharacterTemlate.skin)
		{
			std::string textureName = i->Get_Texture1();
			if (textureName.empty())
				break;

			return m_BaseManager.GetManager<IImagesFactory>()->CreateImage(textureName);
		}
	}

	return nullptr;
}

std::shared_ptr<IImage> Character_SectionWrapper::getSkinExtraTexture(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharSections())
	{
		if (i->Get_GeneralType() == DBC_CharSections_GeneralType::Skin &&
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Color() == CharacterTemlate.skin)
		{
			std::string textureName = i->Get_Texture2();
			if (textureName.empty())
				break;

			return m_BaseManager.GetManager<IImagesFactory>()->CreateImage(textureName);
		}
	}

	return nullptr;
}

//------------------------------------------------------------
//-- Face
//------------------------------------------------------------

std::shared_ptr<IImage> Character_SectionWrapper::getFaceLowerTexture(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharSections())
	{
		if (
			i->Get_GeneralType() == DBC_CharSections_GeneralType::Face &&
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Type() == CharacterTemlate.face &&
			i->Get_Color() == CharacterTemlate.skin
			)
		{
			std::string textureName = i->Get_Texture1();
			if (textureName.empty())
				break;

			return m_BaseManager.GetManager<IImagesFactory>()->CreateImage(textureName);
		}
	}
	return nullptr;
}

std::shared_ptr<IImage> Character_SectionWrapper::getFaceUpperTexture(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharSections())
	{
		if (
			i->Get_GeneralType() == DBC_CharSections_GeneralType::Face &&
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Type() == CharacterTemlate.face &&
			i->Get_Color() == CharacterTemlate.skin
			)
		{
			std::string textureName = i->Get_Texture2();
			if (textureName.empty())
				break;

			return m_BaseManager.GetManager<IImagesFactory>()->CreateImage(textureName);
		}
	}
	return nullptr;
}

//------------------------------------------------------------
//-- FaņialHair
//------------------------------------------------------------

std::shared_ptr<IImage> Character_SectionWrapper::getFacialHairLowerTexture(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharSections())
	{
		if (
			i->Get_GeneralType() == DBC_CharSections_GeneralType::FacialHair &&
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Type() == CharacterTemlate.facialStyle
			)
		{
			std::string textureName = i->Get_Texture1();
			if (textureName.empty())
				break;

			return m_BaseManager.GetManager<IImagesFactory>()->CreateImage(textureName);
		}
	}

	return nullptr;
}

std::shared_ptr<IImage> Character_SectionWrapper::getFacialHairUpperTexture(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharSections())
	{
		if (
			i->Get_GeneralType() == DBC_CharSections_GeneralType::FacialHair &&
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Type() == CharacterTemlate.facialStyle
			)
		{
			std::string textureName = i->Get_Texture2();
			if (textureName.empty())
				break;
			return m_BaseManager.GetManager<IImagesFactory>()->CreateImage(textureName);
		}
	}

	return nullptr;
}

uint32 Character_SectionWrapper::getFacial01Geoset(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharacterFacialHairStyles())
	{
		if (
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Variation() == CharacterTemlate.facialStyle
			)
		{
			return i->Get_Group_01xx();
		}
	}

	return UINT32_MAX;
	//throw CException("Character_SectionWrapper::getFacial01Geoset: Geoset for Race '%d', Gender '%d', FacialStyle '%d'.", (uint32)CharacterTemlate.Race, (uint32)CharacterTemlate.Gender, CharacterTemlate.facialStyle);
}

uint32 Character_SectionWrapper::getFacial02Geoset(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharacterFacialHairStyles())
	{
		if (
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Variation() == CharacterTemlate.facialStyle
			)
		{
			return i->Get_Group_02xx();
		}
	}

	return UINT32_MAX;
	//throw CException("Character_SectionWrapper::getFacial02Geoset: Geoset for Race '%d', Gender '%d', FacialStyle '%d'.", (uint32)CharacterTemlate.Race, (uint32)CharacterTemlate.Gender, CharacterTemlate.facialStyle);
}

uint32 Character_SectionWrapper::getFacial03Geoset(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharacterFacialHairStyles())
	{
		if (
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Variation() == CharacterTemlate.facialStyle
			)
		{
			return i->Get_Group_03xx();
		}
	}

	return UINT32_MAX;
	//throw CException("Character_SectionWrapper::getFacial03Geoset: Geoset for Race '%d', Gender '%d', FacialStyle '%d'.", (uint32)CharacterTemlate.Race, (uint32)CharacterTemlate.Gender, CharacterTemlate.facialStyle);
}

uint32 Character_SectionWrapper::getFacial16Geoset(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharacterFacialHairStyles())
	{
		if (
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Variation() == CharacterTemlate.facialStyle
			)
		{
			return i->Get_Group_16xx();
		}
	}

	return UINT32_MAX;
	//throw CException("Character_SectionWrapper::getFacial16Geoset: Geoset for Race '%d', Gender '%d', FacialStyle '%d'.", (uint32)CharacterTemlate.Race, (uint32)CharacterTemlate.Gender, CharacterTemlate.facialStyle);
}

uint32 Character_SectionWrapper::getFacial17Geoset(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharacterFacialHairStyles())
	{
		if (
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Variation() == CharacterTemlate.facialStyle
			)
		{
			return i->Get_Group_17xx();
		}
	}

	return UINT32_MAX;
	//throw CException("Character_SectionWrapper::getFacial17Geoset: Geoset for Race '%d', Gender '%d', FacialStyle '%d'.", (uint32)CharacterTemlate.Race, (uint32)CharacterTemlate.Gender, CharacterTemlate.facialStyle);
}



//------------------------------------------------------------
//-- Hair
//------------------------------------------------------------

uint32 Character_SectionWrapper::getHairGeoset(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharHairGeosets())
	{
		if (
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_HairType() == CharacterTemlate.hairStyle
			)
		{
			return i->Get_Geoset();
		}
	}

	_ASSERT(false);
	return UINT32_MAX;
}

uint32 Character_SectionWrapper::getHairShowScalp(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharHairGeosets())
	{
		if (
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_HairType() == CharacterTemlate.hairStyle
			)
		{
			return i->Get_Bald();
		}
	}

	return UINT32_MAX;
}

std::shared_ptr<IImage> Character_SectionWrapper::getHairTexture(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharSections())
	{
		if (
			i->Get_GeneralType() == DBC_CharSections_GeneralType::Hair &&
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Type() == CharacterTemlate.hairStyle &&
			i->Get_Color() == CharacterTemlate.hairColor
			)
		{
			std::string textureName = i->Get_Texture1();
			if (textureName.empty())
				break;

			return m_BaseManager.GetManager<IImagesFactory>()->CreateImage(textureName);
		}
	}

	return nullptr;
}

std::shared_ptr<IImage> Character_SectionWrapper::getHairScalpLowerTexture(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharSections())
	{
		if (
			i->Get_GeneralType() == DBC_CharSections_GeneralType::Hair &&
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Type() == CharacterTemlate.hairStyle &&
			i->Get_Color() == CharacterTemlate.hairColor
			)
		{
			std::string textureName = i->Get_Texture2();
			if (textureName.empty())
				break;

			return m_BaseManager.GetManager<IImagesFactory>()->CreateImage(textureName);
		}
	}

	return nullptr;
}

std::shared_ptr<IImage> Character_SectionWrapper::getHairScalpUpperTexture(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharSections())
	{
		if (
			i->Get_GeneralType() == DBC_CharSections_GeneralType::Hair &&
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Type() == CharacterTemlate.hairStyle &&
			i->Get_Color() == CharacterTemlate.hairColor
			)
		{
			std::string textureName = i->Get_Texture3();
			if (textureName.empty())
				break;

			return m_BaseManager.GetManager<IImagesFactory>()->CreateImage(textureName);
		}
	}

	return nullptr;
}

//------------------------------------------------------------
//-- NAKED
//------------------------------------------------------------

std::string Character_SectionWrapper::getNakedPelvisTexture(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharSections())
	{
		if (
			i->Get_GeneralType() == DBC_CharSections_GeneralType::Underwear &&
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Color() == CharacterTemlate.skin
			)
		{
			return i->Get_Texture1();
		}
	}

	_ASSERT(false); 
	return "";
}

std::string Character_SectionWrapper::getNakedTorsoTexture(const SCharacterTemplate& CharacterTemlate) const
{
	for (const auto& i : m_DBCs->DBC_CharSections())
	{
		if (
			i->Get_GeneralType() == DBC_CharSections_GeneralType::Underwear &&
			i->Get_Race() == (uint32)CharacterTemlate.Race &&
			i->Get_Gender() == (uint32)CharacterTemlate.Gender &&
			i->Get_Color() == CharacterTemlate.skin
			)
		{
			return i->Get_Texture2();
		}
	}

	_ASSERT(false);
	return "";
}

#endif
