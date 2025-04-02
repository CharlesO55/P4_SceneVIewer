#pragma once
#include <cstdint>
#include "Proto/SceneViewer.pb.h"
#include "Proto/SceneViewer.grpc.pb.h"
#include "IETThread.h"

class FileServer final : public SceneStreamerService::Service, public IETThread {
public:

	// Functions created in SceneViewer.grpc.pb.cc
	grpc::Status SendSceneRequest(grpc::ServerContext* context, const SceneRequest* request, grpc::ServerWriter< ::FileChunkReply>* writer) override;
	//grpc::Status RequestSceneFilePaths(grpc::ServerContext* context, const EmptyMsg* request, const SceneFilepathsReply* response) override;
	grpc::Status RequestSceneFilePaths(grpc::ServerContext* context, const EmptyMsg* request, SceneFilepathsReply* response) override;

	static void RunServer(uint16_t port);


private:
	const std::string SERVER_FOLDER = "ServerFiles";
	void run() override;
};