#pragma once

#include <vector>
#include <unordered_map>

#include "Shader.h"
#include "Model.h"
#include <mutex> 
#include <queue>

// SINGLE THREAD AND OPENGL CONTEXT
class SceneManager
{
	// SceneName :: Model[]
	std::unordered_map<std::string, std::vector<Model*>> sceneTable;
	std::string activeScene;
	
	void LoadObj(const std::string& scenename, const std::string& filepath);

	std::queue<std::pair<std::string, std::string>> downloadedQueue;
	
	bool isRenderAll = false;



public:
	static SceneManager* instance;
	
	SceneManager();
	~SceneManager();
	

	void QueueDownloadedFile(const std::string& scenename, const std::string& filepath);
	void NotifyFinishLoading();



	void Update();

	void SwitchActiveScene(const std::string& sceneName);
	void RenderActiveScene(Shader& shader);
	
	void ToggleRenderAll(bool renderAll);
};