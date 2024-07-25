#include "Graphics/RenderStages/SceneStage.h"

#include "Graphics/DXCommon.h"
#include "Graphics/DXCommonSystems.h"
#include "Graphics/Model.h"
#include "Graphics/Mesh.h"
#include "Graphics/Camera.h"
#include "Framework/Scene.h"
#include "Framework/GameObject.h"

#include <imgui_impl_dx12.h>

SceneStage::SceneStage()
{
	InitializePipeline();
}

void SceneStage::RecordStage(ComPtr<ID3D12GraphicsCommandList4> commandList)
{
	if(!scene)
	{
		LOG(Log::MessageType::Error, "Scene has not been set for the 'Scene' rendering stage.");
		return;
	}

	// 0. Grab all relevant variables //
	ComPtr<ID3D12Resource> renderTargetBuffer = window->GetCurrentScreenBuffer();
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle = window->GetCurrentScreenRTV();
	CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle = window->GetDepthDSV();

	// 1. Prepare resource state for render target, then clear & bind Render Target and Deph Buffer //
	TransitionResource(renderTargetBuffer.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	BindAndClearRenderTarget(window, &rtvHandle, &dsvHandle);

	// 2. Bind pipeline & root // 
	commandList->SetGraphicsRootSignature(rootSignature->GetAddress());
	commandList->SetPipelineState(pipeline->GetAddress());

	// 3. Render Model(s) //
	const std::vector<GameObject*>& gameObjects = scene->GetGameObjects();
	for(GameObject* gameObject : gameObjects)
	{
		glm::mat4 modelMatrix = gameObject->Transform.GetModelMatrix();
		glm::mat4 mvp = scene->GetCamera()->GetViewProjectionMatrix() * modelMatrix;

		// Bind Model & MVP Matrix //
		commandList->SetGraphicsRoot32BitConstants(0, 16, &modelMatrix, 0);
		commandList->SetGraphicsRoot32BitConstants(0, 16, &mvp, 16);

		// Material //
		commandList->SetGraphicsRoot32BitConstants(1, 3, &gameObject->Material, 0);

		const std::vector<Mesh*>& meshes = gameObject->GetModel()->GetMeshes();
		for(Mesh* mesh : meshes)
		{
			commandList->IASetVertexBuffers(0, 1, &mesh->GetVertexBufferView());
			commandList->IASetIndexBuffer(&mesh->GetIndexBufferView());
			commandList->DrawIndexedInstanced(mesh->GetIndicesCount(), 1, 0, 0, 0);
		}
	}
	
	//  4. Draw UI & Transition the render target for presentation //
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList.Get());
	TransitionResource(renderTargetBuffer.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
}

void SceneStage::SetScene(Scene* scene)
{
	this->scene = scene;
}

void SceneStage::InitializePipeline()
{
	CD3DX12_ROOT_PARAMETER1 rootParameters[2];
	rootParameters[0].InitAsConstants(32, 0, 0, D3D12_SHADER_VISIBILITY_VERTEX);
	rootParameters[1].InitAsConstants(3, 0, 0, D3D12_SHADER_VISIBILITY_PIXEL);

	rootSignature = new DXRootSignature(rootParameters, _countof(rootParameters), D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	DXPipelineDescription description;
	description.VertexPath = "Source/Shaders/screen.vertex.hlsl";
	description.PixelPath = "Source/Shaders/screen.pixel.hlsl";
	description.RootSignature = rootSignature;

	pipeline = new DXPipeline(description);
}