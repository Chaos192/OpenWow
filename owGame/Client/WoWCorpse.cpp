#include "stdafx.h"

#ifdef ENABLE_WOW_CLIENT

// General
#include "WoWCorpse.h"

WoWCorpse::WoWCorpse(ObjectGuid Guid)
	: WoWObject(Guid)
{
	m_ObjectType |= TYPEMASK_CORPSE;
	m_ObjectTypeId = TYPEID_CORPSE;
	m_valuesCount = CORPSE_END;
}

WoWCorpse::~WoWCorpse()
{
}

std::shared_ptr<WoWCorpse> WoWCorpse::Create(IScene& Scene, ObjectGuid Guid)
{
	std::shared_ptr<WoWCorpse> thisObj = std::make_shared<WoWCorpse>(Guid);
	return thisObj;
}

#endif