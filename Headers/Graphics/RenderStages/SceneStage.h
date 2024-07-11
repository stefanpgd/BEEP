#pragma once

#include "Graphics/RenderStage.h"

class Model;

class SceneStage : public RenderStage
{
public:
	SceneStage();

	void RecordStage(ComPtr<ID3D12GraphicsCommandList4> commandList) override;

private:
	void InitializePipeline();

private:
	Model* testModel;
};