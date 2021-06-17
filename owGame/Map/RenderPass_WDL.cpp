#include "stdafx.h"

// General
#include "RenderPass_WDL.h"

// Additional
#include "WDL_LowResTile.h"
#include "Map.h"

CRenderPass_WDL::CRenderPass_WDL(IScene& Scene)
	: Base3DPass(Scene)
{
	m_WoWSettings = GetBaseManager().GetManager<ISettings>()->GetGroup("WoWSettings");
}

CRenderPass_WDL::~CRenderPass_WDL()
{}



//
// IRenderPassPipelined
//
std::shared_ptr<IRenderPassPipelined> CRenderPass_WDL::ConfigurePipeline(std::shared_ptr<IRenderTarget> RenderTarget)
{
	__super::ConfigurePipeline(RenderTarget);

	// CreateShaders
	std::shared_ptr<IShader> vertexShader = GetRenderDevice().GetObjectsFactory().LoadShader(EShaderType::VertexShader, "shaders_D3D/MapWDL.hlsl", "VS_main");
	vertexShader->LoadInputLayoutFromReflector();

	std::shared_ptr<IShader> pixelShader = GetRenderDevice().GetObjectsFactory().LoadShader(EShaderType::PixelShader, "shaders_D3D/MapWDL.hlsl", "PS_main");

	// PIPELINES
	std::shared_ptr<IPipelineState> pipeline = GetRenderDevice().GetObjectsFactory().CreatePipelineState();
	pipeline->GetBlendState()->SetBlendMode(disableBlending);
	pipeline->GetDepthStencilState()->SetDepthMode(disableDepthWrites);
	pipeline->GetRasterizerState()->SetCullMode(IRasterizerState::CullMode::Back);
	pipeline->GetRasterizerState()->SetFillMode(IRasterizerState::FillMode::Wireframe, IRasterizerState::FillMode::Wireframe);
	pipeline->SetRenderTarget(RenderTarget);
	pipeline->SetShader(vertexShader);
	pipeline->SetShader(pixelShader);

	return shared_from_this();
}



//
// IVisitor
//
EVisitResult CRenderPass_WDL::Visit(const std::shared_ptr<ISceneNode>& SceneNode)
{
	if (const auto map = std::dynamic_pointer_cast<CMap>(SceneNode))
		return __super::Visit(SceneNode);

	return EVisitResult::AllowVisitChilds;
}

EVisitResult CRenderPass_WDL::Visit(const std::shared_ptr<IModel>& Model)
{
	const auto wdlMesh = std::dynamic_pointer_cast<CWDL_LowResTile>(Model);
	if (wdlMesh == nullptr)
        return EVisitResult::Block;

	if (false == wdlMesh->IsNeedRender())
		return EVisitResult::Block;

	return __super::Visit(wdlMesh);
}
