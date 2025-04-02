#pragma once
#include <string>
#include "Proto/SceneViewer.grpc.pb.h"


class FileClient
{
public:
	FileClient(std::shared_ptr<grpc::ChannelInterface> channel);
	void PrepFolders();
	static void runClient();

private:
	const std::string CLIENT_FOLDER = "ClientFiles";
	
	void RequestScene(const std::string filename); // Relative path. Exclude folder parent




	void PrintStatus(const grpc::Status& status, const std::string& success_msg);

	std::unique_ptr<SceneStreamerService::Stub> stub;
	std::unordered_map<std::string, std::vector<std::string>> sceneFilesTable;
};