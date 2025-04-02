#pragma once
#include <string>
#include "Proto/SceneViewer.grpc.pb.h"


class FileClient
{
public:
	FileClient(std::shared_ptr<grpc::ChannelInterface> channel);
	
	void RequestScene(const std::string sceneName);

	static void runClient();

private:
	std::unique_ptr<SceneStreamer::Stub> stub_;
};