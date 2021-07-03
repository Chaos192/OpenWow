#include "stdafx.h"

// Include
#include "M2.h"

// General
#include "M2_Part_Camera.h"

CM2_Part_Camera::CM2_Part_Camera(const CM2& M2Object, const std::shared_ptr<IByteBuffer>& ByteBuffer, const SM2_Camera& M2Camera)
	: m_M2Object(M2Object)
{
	nearclip = M2Camera.near_clip;
	farclip = M2Camera.far_clip;

	m_PositionBase = Fix_XZmY(M2Camera.position_base);
	m_TargetBase = Fix_XZmY(M2Camera.target_position_base);

	tPos.Initialize(M2Camera.positions, ByteBuffer, M2Object.getSkeleton().GetAnimFiles(), Fix_XZmY);
	tTarget.Initialize(M2Camera.target_position, ByteBuffer, M2Object.getSkeleton().GetAnimFiles(), Fix_XZmY);

	tRoll.Initialize(M2Camera.roll, ByteBuffer, M2Object.getSkeleton().GetAnimFiles());
	//fov = M2Camera.fov / sqrtf(1.0f + powf(m_VideoSettings->aspectRatio, 2.0f));;
}

CM2_Part_Camera::~CM2_Part_Camera()
{
}

void CM2_Part_Camera::calc(uint32 time, uint32 globalTime)
{
	if (tPos.IsUsesBySequence(0))
	{
		pResult = tPos.GetValue(0, time, m_M2Object.getSkeleton().getGlobalLoops(), globalTime);
	}

	if (tTarget.IsUsesBySequence(0))
	{
		tResult = tTarget.GetValue(0, time, m_M2Object.getSkeleton().getGlobalLoops(), globalTime);
	}

	if (tRoll.IsUsesBySequence(0))
	{
		rollResult = tRoll.GetValue(0, time, m_M2Object.getSkeleton().getGlobalLoops(), globalTime) / (glm::pi<float>() * 180.0f);
	}
}

void CM2_Part_Camera::setup(const glm::vec3& _startPoint, float rotate)
{
	glm::vec3 u(0, 1, 0);

	glm::vec3 pp = m_PositionBase + pResult;
	glm::vec3 tt = m_TargetBase + tResult;

	// TODO
	//_Render->getCamera()->setupViewParams(fov, m_VideoSettings.aspectRatio, nearclip, farclip);
	//_Render->getCamera()->Position = pp;
	//_Render->getCamera()->setViewMatrix(glm::lookAt(pp, tt, u));
}

void CM2_Part_Camera::getParams(glm::vec3* _position, glm::vec3* _target, float* _fov, float* _nearPlane, float* _farPlane)
{
	*_position = m_PositionBase + pResult;
	*_target = m_TargetBase + tResult;
	*_fov = fov;
	*_nearPlane = nearclip;
	*_farPlane = farclip;
}
