#pragma once

#include <vector>
#include <unordered_map>

#include "Shader.h"
#include "Model.h"
#include <mutex> 
#include <queue>
#include <condition_variable>


// SINGLE THREAD AND OPENGL CONTEXT
class SceneManager
{
	// SceneName :: Model[]
	std::unordered_map<std::string, std::vector<Model*>> sceneTable;
	std::string activeScene;
	
	void LoadObj(const std::string& scenename, const std::string& filepath);

	std::queue<std::pair<std::string, std::string>> downloadedQueue;
	
	bool isRenderAll = false;

	std::condition_variable cv;
	std::mutex TABLE_LOCK;

public:
	static SceneManager* instance;
	
	SceneManager();
	~SceneManager();
	

	static void QueueDownloadedFile(const std::string& scenename, const std::string& filepath);



	void Update();

	void SwitchActiveScene(const std::string& sceneName);
	void RenderActiveScene(Shader& shader);
	
	void UnloadActiveScene();
	void UnloadAll();

	void ToggleRenderAll(bool renderAll);
};