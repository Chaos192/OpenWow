#include "stdafx.h"

// General
#include "WMO_Liquid_Instance.h"

CWMO_Liquid_Instance::CWMO_Liquid_Instance()
	: m_PortalVisibilityState(true)
{
}

CWMO_Liquid_Instance::~CWMO_Liquid_Instance()
{
}

BoundingBox CWMO_Liquid_Instance::GetBoundingBox() const
{
	return GetComponent<IColliderComponent3D>()->GetWorldBounds();
}



//
// SceneNode3D
//
void CWMO_Liquid_Instance::Accept(IVisitor* visitor)
{
	if (m_PortalVisibilityState)
	{
		Liquid_Instance::Accept(visitor);
	}
}
