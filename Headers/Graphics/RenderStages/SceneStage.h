#pragma once

#include "Graphics/RenderStage.h"

class Scene;

class SceneStage : public RenderStage
{
public:
	SceneStage();

	void RecordStage(ComPtr<ID3D12GraphicsCommandList4> commandList) override;

	void SetScene(Scene* scene);

private:
	void InitializePipeline();

private:
	Scene* scene;
};