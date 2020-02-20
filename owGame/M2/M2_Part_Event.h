#pragma once

#include "M2_Types.h"
#include "M2_Part_Bone.h"

// FORWARD BEGIN
class M2;
// FORWARD END

class CM2_Part_Event
{
public:
	CM2_Part_Event(const M2& M2Model, std::shared_ptr<IFile> f, const SM2_Event& _proto, cGlobalLoopSeq global);

private:
	char					m_ID[4];
	uint32					m_Data;
	std::weak_ptr<const CM2_Part_Bone>	m_Bone;
	vec3					m_Position;

	M2_Animated<bool>		m_IsEnabled;
};