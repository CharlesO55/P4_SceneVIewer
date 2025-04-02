#include "FileServer.h"

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "Settings.h"


grpc::Status FileServer::SendSceneRequest(grpc::ServerContext* context, const SceneRequest* request, grpc::ServerWriter<::FileChunkReply>* writer)
{
	std::cout << COLOR::Y << "[SERVER] Received request for: " << request->scenename() << COLOR::W << std::endl;
    return grpc::Status::OK;
}


void FileServer::RunServer(uint16_t port)
{
	std::string serverAddress = absl::StrFormat("localhost:%d", port);
	
	FileServer service;

	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();
	grpc::ServerBuilder builder;
	
	// Service synchornously running so detach this is detached.
	builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	
	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	
	std::cout << COLOR::G << "Server listening on " << serverAddress << COLOR::W << std::endl;
	
	// [Implement] server->ShutDown() to exit
	
	try {
		// If you see a vs break here, most likely the port number is being used.
		// Find a different one, bcuz this try catch don't work ;)
		server->Wait();
	}
	catch (...){
		std::cerr << COLOR::R << "[ERROR] : Server failed to start on " << serverAddress << COLOR::W << std::endl;
	}

	std::cout << COLOR::Y << "Exited Server Thread on Port" << serverAddress << COLOR::W << std::endl;
}



void FileServer::run()
{
	RunServer(PORT_NUMBER);
}