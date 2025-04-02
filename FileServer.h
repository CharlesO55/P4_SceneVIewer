#pragma once
#include <cstdint>
#include "Proto/SceneViewer.pb.h"
#include "Proto/SceneViewer.grpc.pb.h"
#include "IETThread.h"

class FileServer final : public SceneStreamer::Service, public IETThread {
public:

	// Functions created in SceneViewer.grpc.pb.cc
	grpc::Status SendSceneRequest(grpc::ServerContext* context, const SceneRequest* request, grpc::ServerWriter< ::FileChunkReply>* writer) override;
	static void RunServer(uint16_t port);



	void run() override;
};