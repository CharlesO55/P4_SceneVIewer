#include "FileServer.h"

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "Settings.h"

#include <fstream>
#include <filesystem>

grpc::Status FileServer::SendSceneRequest(grpc::ServerContext* context, const SceneRequest* request, grpc::ServerWriter<::FileChunkReply>* writer)
{
	std::cout << COLOR::Y << "[SERVER] Received request for: " << request->scenename() << COLOR::W << std::endl;
	std::string filePath = SERVER_FOLDER + "/" + request->scenename();
	
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open()) {
		std::cout << COLOR::R << "[SERVER] Fail: " << filePath << COLOR::W << std::endl;
		return grpc::Status(grpc::StatusCode::NOT_FOUND, "File not found: " + filePath);
	}

	const size_t buffer_size = 1024;
	char buffer[buffer_size];

	while (file.read(buffer, buffer_size)) {
		FileChunkReply chunk;
		chunk.set_chunk1024(buffer, buffer_size);
		if (!writer->Write(chunk)) {
			file.close();
			return grpc::Status(grpc::StatusCode::UNKNOWN, "Failed to send chunk");
		}
	}

	// Handle the remainder chunk bytes
	std::streamsize bytes_read = file.gcount();
	if (bytes_read > 0) {
		FileChunkReply chunk;
		chunk.set_chunk1024(buffer, bytes_read);
		if (!writer->Write(chunk)) {
			file.close();
			return grpc::Status(grpc::StatusCode::UNKNOWN, "Failed to send final chunk");
		}
	}

	file.close();
	std::cout << COLOR::G << "[SERVER] Sent: " << filePath << COLOR::W << std::endl;
	return grpc::Status::OK;
}

grpc::Status FileServer::RequestSceneFilePaths(grpc::ServerContext* context, const EmptyMsg* request, SceneFilepathsReply* response)
{
	for (const auto& dir : std::filesystem::recursive_directory_iterator(SERVER_FOLDER)) {
		if (std::filesystem::is_regular_file(dir)) {  
			response->add_paths(std::filesystem::relative(dir.path().parent_path(), SERVER_FOLDER).string());
			response->add_filenames(dir.path().filename().string());
		}
	}

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
	
	
	try {
		// If you see a VS null break here, most likely the port number is being used.
		// Find a different one, bcuz this try catch don't work ;)
		// Change `PORT_NUMBER` in Settings.h for consistency between Client and Server.
		server->Wait();
	
		// [Implement] server->ShutDown() to properly exit
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