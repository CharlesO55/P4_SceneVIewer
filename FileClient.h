#pragma once
#include <string>
#include "Proto/SceneViewer.grpc.pb.h"

#include <condition_variable>

class FileClient
{
public:
	FileClient();
	void PrepFolders();
	//static void runClient();

	void Run();

	std::condition_variable cv_LOAD;
	std::mutex mtx_LOAD;
	std::mutex mtx_STREAMING;

	void BeginStream();


private:
	bool isStreaming = false;


	static void UnloadFolders(std::filesystem::path dir);



	const std::string CLIENT_FOLDER = "ClientFiles";
	
	void RequestScene(const std::string filename); // Relative path. Exclude folder parent

	
	void PrintStatus(const grpc::Status& status, const std::string& success_msg);

	std::unique_ptr<SceneStreamerService::Stub> stub;
	std::unordered_map<std::string, std::vector<std::string>> sceneFilesTable;
};