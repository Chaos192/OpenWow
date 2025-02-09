#include "stdafx.h"

// General
#include "RenderPass_M2CollisionDebug.h"

// Additional
#include "WMO/WMOHelper.h"

CRenderPass_M2CollisionDebug::CRenderPass_M2CollisionDebug(IScene& Scene)
	: Base3DPass(Scene)
{
	SetPassName("M2CollisionDebug");
}

CRenderPass_M2CollisionDebug::~CRenderPass_M2CollisionDebug()
{}



//
// IRenderPassPipelined
//
std::shared_ptr<IRenderPassPipelined> CRenderPass_M2CollisionDebug::ConfigurePipeline(std::shared_ptr<IRenderTarget> RenderTarget)
{
	__super::ConfigurePipeline(RenderTarget);

	m_MaterialDebug = MakeShared(MaterialDebug, GetRenderDevice());

	auto vertexShader = GetRenderDevice().GetObjectsFactory().LoadShader(EShaderType::VertexShader, "3D/Debug.hlsl", "VS_main");
	vertexShader->LoadInputLayoutFromReflector();

	auto pixelShader = GetRenderDevice().GetObjectsFactory().LoadShader(EShaderType::PixelShader, "3D/Debug.hlsl", "PS_main");
	
	// PIPELINES
	GetPipeline().GetBlendState()->SetBlendMode(alphaBlending);
	GetPipeline().GetDepthStencilState()->SetDepthMode(disableDepthWrites);
	//GetPipeline().GetRasterizerState()->SetCullMode(IRasterizerState::CullMode::None);
	//GetPipeline().GetRasterizerState()->SetFillMode(IRasterizerState::FillMode::Wireframe, IRasterizerState::FillMode::Wireframe);
	GetPipeline().SetRenderTarget(RenderTarget);
	GetPipeline().SetShader(vertexShader);
	GetPipeline().SetShader(pixelShader);

	return shared_from_this();
}



//
// IVisitor
//
EVisitResult CRenderPass_M2CollisionDebug::Visit(const std::shared_ptr<ISceneNode>& SceneNode)
{
	/*if (auto m2Instance = std::dynamic_pointer_cast<CM2_Base_Instance>(SceneNode))
	{
		if (auto collisionGeom = m2Instance->GetM2().GetCollisionGeometry())
		{
			BindPerObjectData(PerObject(SceneNode->GetWorldTransfom()));

			m_MaterialDebug->SetDiffuseColor(ColorRGBA(0.0f, 1.0f, 1.0f, 1.0f));
			m_MaterialDebug->Bind(GetPipeline().GetPixelShaderPtr());
			collisionGeom->Render(GetPipeline().GetVertexShaderPtr());
			m_MaterialDebug->Unbind(GetPipeline().GetPixelShaderPtr());
		}
	}
	else */
	/*if (auto wmoGroupInstance = std::dynamic_pointer_cast<CWMO_Group_Instance>(SceneNode))
	{
		BindPerObjectData(PerObject(SceneNode->GetWorldTransfom()));

		if (auto collisionGeom = wmoGroupInstance->GetWMOGroup().GetCollisionGeometry())
		{
			m_MaterialDebug->SetDiffuseColor(ColorRGBA(1.0f, 0.0f, 1.0f, 1.0f));
			m_MaterialDebug->Bind(GetPipeline().GetPixelShaderPtr());
			collisionGeom->Render(GetPipeline().GetVertexShaderPtr());
			m_MaterialDebug->Unbind(GetPipeline().GetPixelShaderPtr());
		}
	}*/
	/*if (auto wmoGroupInstance = std::dynamic_pointer_cast<CWMO_Group_Instance>(SceneNode))
	{
		BindPerObjectData(PerObject());
		//BindPerObjectData(PerObject(SceneNode->GetWorldTransfom()));

		for (const auto& collisionNode : wmoGroupInstance->GetWMOGroup().GetCollisionNodes())
		{
			if (auto collisionGeom = collisionNode->GetCollisionGeometry())
			{
				m_MaterialDebug->SetDiffuseColor(ColorRGBA(1.0f, 0.0f, 1.0f, 1.0f));
				m_MaterialDebug->Bind(GetPipeline().GetPixelShaderPtr());
				collisionGeom->Render(GetPipeline().GetVertexShaderPtr());
				m_MaterialDebug->Unbind(GetPipeline().GetPixelShaderPtr());
			}
		}
	}*/


	if (auto wmoGroupInstance = std::dynamic_pointer_cast<CWMO_Group_Instance>(SceneNode))
	{
		BindPerObjectData(PerObject(SceneNode->GetWorldTransfom()));

		glm::vec3 cameraPosition = GetRenderEventArgs().Camera->GetPosition();
		cameraPosition = glm::inverse(SceneNode->GetWorldTransfom()) * glm::vec4(cameraPosition, 1.0f);

		BoundingBox camBBox;
		camBBox.setMin(cameraPosition - glm::vec3(1.0f, 10.0f, 1.0f));
		camBBox.setMax(cameraPosition + glm::vec3(1.0f, 2.0f, 1.0f));

		//for (const auto& it : wmoGroupInstance->GetWMOGroup().GetCollisionNodes())
		//	it->TEMP_RenderDisable = true;

		TraverseBsp(
			wmoGroupInstance->GetWMOGroup().GetCollisionNodes(), 
			0, 
			Fix_From_XYZ_to_XZmY(camBBox), 
			Fix_From_XYZ_to_XZmY(wmoGroupInstance->GetWMOGroup().GetBoundingBox()), 
			std::bind(&CRenderPass_M2CollisionDebug::WMOGroupCollisionAction, this, std::placeholders::_1)
		);
	}


	return EVisitResult::AllowVisitChilds;
}

EVisitResult CRenderPass_M2CollisionDebug::Visit(const std::shared_ptr<IGeometry>& Geometry, const std::shared_ptr<IMaterial>& Material, SGeometryDrawArgs GeometryDrawArgs)
{
	return EVisitResult::Block;
}



//
// Protected
//
void CRenderPass_M2CollisionDebug::WMOGroupCollisionAction(std::shared_ptr<CWMOGroup_Part_CollisionNode> CollisionNode)
{
	if (auto collisionGeom = CollisionNode->GetCollisionGeometry())
	{
		GetMaterial()->SetDiffuseColor(ColorRGBA(1.0f, 0.0f, 1.0f, 0.3f));
		GetMaterial()->Bind(GetPipeline().GetPixelShaderPtr());
		collisionGeom->Render(GetPipeline().GetVertexShaderPtr());
		GetMaterial()->Unbind(GetPipeline().GetPixelShaderPtr());
	}
}
