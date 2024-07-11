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
	rootSignature = new DXRootSignature(nullptr, 0, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	DXPipelineDescription description;
	description.VertexPath = "Source/Shaders/screen.vertex.hlsl";
	description.PixelPath = "Source/Shaders/screen.pixel.hlsl";
	description.RootSignature = rootSignature;

	pipeline = new DXPipeline(description);

	testModel = new Model("Assets/Models/Sphere/sphere.gltf");
}