#include "stdafx.h"

// General
#include "RenderPass_MapChunk.h"

// Additional
#include "Map/MapChunk.h"

CRenderPass_MapChunk::CRenderPass_MapChunk(IScene& Scene)
	: Base3DPass(Scene)
{
	SetPassName("MapChunk");

	m_MapChunkRenderDistance = GetBaseManager().GetManager<ISettings>()->GetGroup("WoWSettings")->GetPropertyT<float>("MapChunkRenderDistance");
}

CRenderPass_MapChunk::~CRenderPass_MapChunk()
{}



//
// IRenderPassPipelined
//
std::shared_ptr<IRenderPassPipelined> CRenderPass_MapChunk::ConfigurePipeline(std::shared_ptr<IRenderTarget> RenderTarget)
{
	__super::ConfigurePipeline(RenderTarget);

	std::shared_ptr<IShader> vertexShader;
	std::shared_ptr<IShader> pixelShader;

	if (GetRenderDevice().GetDeviceType() == RenderDeviceType::RenderDeviceType_DirectX11)
	{
		vertexShader = GetRenderDevice().GetObjectsFactory().LoadShader(EShaderType::VertexShader, "shaders_D3D/MapChunk.hlsl", "VS_main");
		pixelShader = GetRenderDevice().GetObjectsFactory().LoadShader(EShaderType::PixelShader, "shaders_D3D/MapChunk.hlsl", "PS_main");
	}
	else if (GetRenderDevice().GetDeviceType() == RenderDeviceType::RenderDeviceType_OpenGL)
	{
		vertexShader = GetRenderDevice().GetObjectsFactory().LoadShader(EShaderType::VertexShader, "shaders_OGL/MapChunk.vs", "");
		pixelShader = GetRenderDevice().GetObjectsFactory().LoadShader(EShaderType::PixelShader, "shaders_OGL/MapChunk.ps", "");
	}
	vertexShader->LoadInputLayoutFromReflector();

	// PIPELINES
	GetPipeline().GetBlendState()->SetBlendMode(disableBlending);
	GetPipeline().GetDepthStencilState()->SetDepthMode(enableDepthWrites);
	GetPipeline().GetRasterizerState()->SetCullMode(IRasterizerState::CullMode::Back);
	GetPipeline().GetRasterizerState()->SetFillMode(IRasterizerState::FillMode::Solid, IRasterizerState::FillMode::Solid);
	GetPipeline().SetRenderTarget(RenderTarget);
	GetPipeline().SetShader(vertexShader);
	GetPipeline().SetShader(pixelShader);

	return shared_from_this();
}



//
// IVisitor
//
EVisitResult CRenderPass_MapChunk::Visit(const std::shared_ptr<ISceneNode>& SceneNode3D)
{
	if (const auto adtMCNKInstance = std::dynamic_pointer_cast<CMapChunk>(SceneNode3D))
	{
		if (auto colliderComponent = SceneNode3D->GetComponentT<IColliderComponent>())
			if (colliderComponent->IsCulled(GetRenderEventArgs().Camera))
				return EVisitResult::Block;

		return __super::Visit(SceneNode3D);
	}

	return EVisitResult::AllowVisitChilds;
}