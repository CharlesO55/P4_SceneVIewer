#include "SceneManager.h"
#include <semaphore>

SceneManager* SceneManager::instance = nullptr;

#include "../Settings.h"

std::counting_semaphore<> LOADING_PERMITS(1);

std::mutex mtw_QUEUE;

SceneManager::SceneManager()
{
	std::cout << "[SCENE MANAGER] Create" << std::endl;
	instance = this;
}

SceneManager::~SceneManager()
{
	UnloadAll();
}


void SceneManager::QueueDownloadedFile(const std::string& scenename, const std::string& filepath)
{
	LOADING_PERMITS.acquire();

	std::lock_guard<std::mutex> lck(mtw_QUEUE);
	instance->downloadedQueue.push(std::make_pair(scenename, filepath));
}

void SceneManager::NotifyModelLoaded()
{
	LOADING_PERMITS.release();
}



void SceneManager::LoadObj(const std::string& scenename, const std::string& filepath)
{
	Model* model = new Model(filepath, glm::vec3(instance->sceneTable[scenename].size() * 5, 0, -20));
	
	std::unique_lock<std::mutex> lock(TABLE_LOCK);
	instance->sceneTable[scenename].push_back(model);
}



void SceneManager::Update(float delta)
{
	time += delta;
	if (time < 5)
		return;

	std::lock_guard<std::mutex> lck(mtw_QUEUE);
	if (!downloadedQueue.empty()) {
		std::pair<std::string, std::string> toLoad = downloadedQueue.front();
		downloadedQueue.pop();

		LoadObj(toLoad.first, toLoad.second);
	}
}


void SceneManager::SwitchActiveScene(const std::string& sceneName)
{
	this->activeScene = sceneName;
}

void SceneManager::RenderActiveScene(Shader& shader)
{

	std::unique_lock<std::mutex> lock(TABLE_LOCK);
	
	if (!isRenderAll) {
		for (Model* m : sceneTable[activeScene]) {
			m->Draw(shader);
		}
	}
	else {
		for (const auto& lists : sceneTable) {
			for (Model* m : lists.second) {
				m->Draw(shader);
			}
		}
	}
}

void SceneManager::UnloadActiveScene()
{
	std::unique_lock<std::mutex> lock(TABLE_LOCK);
	for (Model* ptr : sceneTable[activeScene]) {
		delete ptr;
	}
	sceneTable[activeScene].clear();
}

void SceneManager::UnloadAll()
{
	std::unique_lock<std::mutex> lock(TABLE_LOCK);
	for (auto& pair : sceneTable) {
		for (Model* ptr : pair.second) {
			delete ptr;  
		}
		pair.second.clear();  
	}
	sceneTable.clear(); 
}

void SceneManager::ToggleRenderAll(bool renderAll)
{
	this->isRenderAll = renderAll;
}
