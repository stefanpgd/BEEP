#pragma once
#include <string>
#include <vector>
#include <d3d12.h>
#include <wrl.h>
using namespace Microsoft::WRL;

class Scene;
class SceneStage;

class Renderer
{
public:
	Renderer(const std::wstring& applicationName, unsigned int windowWidth, unsigned int windowHeight);
	
	void Render();
	void Resize();

	void SetScene(Scene* scene);

private:
	void InitializeImGui();

private:
	Scene* scene;
	SceneStage* sceneStage;
};