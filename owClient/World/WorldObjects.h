#pragma once

#include "../Objects/Base/WoWObject.h"
#include "../Objects/Items/WoWItem.h"
#include "../Objects/Items/WoWContainer.h"
#include "../Objects/Units/WoWUnit.h"
#include "../Objects/GameObjects/WoWGameObject.h"

#include "../Objects/WoWPlayer.h"
#include "../Objects/WoWDynamicObject.h"
#include "../Objects/WoWCorpse.h"

#include "../Renderer/RenderPass_Path.h"

// FORWARD BEGIN
class CWoWWorld;
// FORWARD END

class CWorldObjects
{
public:
	CWorldObjects(CWoWWorld& WoWWorld, IScene& Scene);
	virtual ~CWorldObjects();

	void Update(const UpdateEventArgs& e);
	void Accept(IWoWVisitor * WoWVisitor);

	std::shared_ptr<WoWObject> CreateWoWObject(CWoWGuid ObjectGUID, EWoWObjectTypeID TypeID);
	std::shared_ptr<WoWObject> GetWoWObject(CWoWGuid ObjectGUID);
	bool IsWoWObjectExists(CWoWGuid ObjectGUID);
	void EraseWoWObject(const std::shared_ptr<WoWObject>& WoWObject);



private:
	CWoWWorld& m_WoWWorld;
	IScene& m_Scene;
	//std::map<CWoWGuid, std::shared_ptr<WoWObject>>         m_WoWObjects;

	std::map<CWoWGuid, std::shared_ptr<WoWItem>>           m_WoWItems;

	std::map<CWoWGuid, std::shared_ptr<WoWUnit>>           m_WoWUnits;
	std::map<CWoWGuid, std::shared_ptr<WoWUnit>>           m_WoWUnitsPet;
	std::map<CWoWGuid, std::shared_ptr<WoWUnit>>           m_WoWUnitsVehicle;

	std::map<CWoWGuid, std::shared_ptr<WoWPlayer>>         m_WoWPlayers;

	std::map<CWoWGuid, std::shared_ptr<WoWGameObject>>     m_WoWGameObjects;
	std::map<CWoWGuid, std::shared_ptr<WoWGameObject>>     m_WoWGameObjectsTransport;
	std::map<CWoWGuid, std::shared_ptr<WoWGameObjectMOTransport>> m_WoWGameObjectsMOTransport;

	std::map<CWoWGuid, std::shared_ptr<WoWDynamicObject>>  m_WoWDynamicObjects;

	std::map<CWoWGuid, std::shared_ptr<WoWCorpse>>         m_WoWCorpses;
};