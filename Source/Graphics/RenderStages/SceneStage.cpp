#include "Graphics/RenderStages/SceneStage.h"

#include "Graphics/DXPipeline.h"
#include "Graphics/DXRootSignature.h"
#include "Graphics/DXDescriptorHeap.h"
#include "Graphics/DXUtilities.h"
#include "Graphics/Model.h"
#include "Graphics/Mesh.h"
#include "Graphics/Window.h"

#include <imgui_impl_dx12.h>

SceneStage::SceneStage()
{
	InitializePipeline();
}

void SceneStage::RecordStage(ComPtr<ID3D12GraphicsCommandList4> commandList)
{
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

	// 3. Bind root parameters //
	glm::mat4 modelMatrix = testModel->Transform.GetModelMatrix();
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0, 1.0, 0.0));

	float aspectRatio = float(DXAccess::GetWindow()->GetWindowWidth()) / float(DXAccess::GetWindow()->GetWindowHeight());
	glm::mat4 projection = glm::perspective(glm::radians(80.0f), aspectRatio, 0.01f, 1000.0f);
	glm::mat4 mvp = (projection * view) * modelMatrix;

	commandList->SetGraphicsRoot32BitConstants(0, 16, &mvp, 0);

	// 3. Render model // 
	Mesh* testMesh = testModel->GetMesh(0);

	commandList->IASetVertexBuffers(0, 1, &testMesh->GetVertexBufferView());
	commandList->IASetIndexBuffer(&testMesh->GetIndexBufferView());
	commandList->DrawIndexedInstanced(testMesh->GetIndicesCount(), 1, 0, 0, 0);

	//  4. Draw UI & Transition the render target for presentation //
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList.Get());
	TransitionResource(renderTargetBuffer.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
}

void SceneStage::InitializePipeline()
{
	CD3DX12_ROOT_PARAMETER1 rootParameters[1];
	rootParameters[0].InitAsConstants(16, 0, 0, D3D12_SHADER_VISIBILITY_VERTEX);

	rootSignature = new DXRootSignature(rootParameters, _countof(rootParameters), D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	DXPipelineDescription description;
	description.VertexPath = "Source/Shaders/screen.vertex.hlsl";
	description.PixelPath = "Source/Shaders/screen.pixel.hlsl";
	description.RootSignature = rootSignature;

	pipeline = new DXPipeline(description);

	testModel = new Model("Assets/Models/Sphere/sphere.gltf");
}