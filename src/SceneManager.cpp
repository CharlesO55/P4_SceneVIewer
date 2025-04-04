#include "SceneManager.h"
#include <semaphore>

SceneManager* SceneManager::instance = nullptr;

std::mutex TABLE_LOCK;
std::counting_semaphore QUEUE_PERMITS(2);


#include "../Settings.h"

SceneManager::SceneManager()
{
	std::cout << "[SCENE MANAGER] Create" << std::endl;
	instance = this;
}

SceneManager::~SceneManager()
{
	for (auto& pair : sceneTable) {
		// Iterate over each Class pointer in the vector
		for (Model* ptr : pair.second) {
			delete ptr;  // Free the dynamically allocated Class objects
		}
		pair.second.clear();  // Clear the vector
	}
	sceneTable.clear();  // Clear the map
}


void SceneManager::QueueDownloadedFile(const std::string& scenename, const std::string& filepath)
{
	// CONSIDER ADDING A SEMAPHORE TO PAUSE THE NUMBER OF LOADING
	//QUEUE_PERMITS.acquire();

	downloadedQueue.push(std::make_pair(scenename, filepath));
}

void SceneManager::NotifyFinishLoading()
{
	//std::cout << "Reeeeee";
	//QUEUE_PERMITS.release();
}


void SceneManager::LoadObj(const std::string& scenename, const std::string& filepath)
{
	TABLE_LOCK.lock();
	Model* model = new Model(filepath, glm::vec3(instance->sceneTable[scenename].size() * 5, 0, -20));
	instance->sceneTable[scenename].push_back(model);
	TABLE_LOCK.unlock();
}



void SceneManager::Update()
{
	if (!downloadedQueue.empty()) {
		std::pair<std::string, std::string> toLoad = downloadedQueue.front();
		downloadedQueue.pop();

		std::cout << toLoad.first << std::endl;
		std::cout << toLoad.second << std::endl;

		LoadObj(toLoad.first, toLoad.second);
	}
}


void SceneManager::SwitchActiveScene(const std::string& sceneName)
{
	this->activeScene = sceneName;
}

void SceneManager::RenderActiveScene(Shader& shader)
{
	TABLE_LOCK.lock();
	for (Model* m : sceneTable[activeScene]) {
		m->Draw(shader);
	}
	TABLE_LOCK.unlock();
}

void SceneManager::ToggleRenderAll(bool renderAll)
{
	this->isRenderAll = renderAll;
}
