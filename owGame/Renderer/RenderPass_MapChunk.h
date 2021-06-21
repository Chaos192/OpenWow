#pragma once

class ZN_API CRenderPass_MapChunk 
	: public Base3DPass
{
public:
	CRenderPass_MapChunk(IScene& Scene);
	virtual ~CRenderPass_MapChunk();

	// IRenderPassPipelined
	std::shared_ptr<IRenderPassPipelined> ConfigurePipeline(std::shared_ptr<IRenderTarget> RenderTarget) override final;

    // IVisitor
    EVisitResult Visit(const std::shared_ptr<ISceneNode>& node) override final;

private:
	std::shared_ptr<IPropertyT<float>> m_MapChunkRenderDistance;
};