#include "FileClient.h"
#include <grpcpp/create_channel.h>
#include <fstream>

#include "Settings.h"

#include "src/SceneManager.h"

#include <thread>

FileClient::FileClient(std::shared_ptr<grpc::ChannelInterface> channel)
{
	this->stub = SceneStreamerService::NewStub(channel);
}

void FileClient::RequestScene(const std::string filePath)
{
    SceneRequest request;
    request.set_scenename(filePath);

    grpc::ClientContext context;
    std::chrono::time_point deadline = std::chrono::system_clock::now() +
        std::chrono::milliseconds(2000);
    context.set_deadline(deadline);

    
    std::unique_ptr<grpc::ClientReader<FileChunkReply>> reader(stub->SendSceneRequest(&context, request));


    // Open output file
    std::ofstream output_file(CLIENT_FOLDER + "/" + filePath, std::ios::binary);

    FileChunkReply reply;
    while (reader->Read(&reply)) {
        output_file.write(reply.chunk1024().data(), reply.chunk1024().size());
    }

    output_file.close();
    PrintStatus(reader->Finish(), "[CLIENT] Downloaded." + filePath);

    std::cout << std::endl << std::endl << filePath << std::endl << std::endl;

    size_t scenename = filePath.find('/');



    if (filePath.substr(filePath.length() - 4) == ".obj"){
        SceneManager::instance->QueueDownloadedFile(filePath.substr(0, scenename), CLIENT_FOLDER + "/" + filePath);
    }

}

void FileClient::PrepFolders()
{
    SceneFilepathsReply reply;
    
    grpc::ClientContext context;
    std::chrono::time_point deadline = std::chrono::system_clock::now() +
        std::chrono::milliseconds(2000);
    context.set_deadline(deadline);

    EmptyMsg e;
    grpc::Status status = stub->RequestSceneFilePaths(&context, e, &reply);

    for (int i = 0; i < reply.paths().size(); i++) {
        std::string scene = reply.paths()[i];
        std::string file = reply.filenames()[i];

        sceneFilesTable[scene].push_back(file);

        std::filesystem::path dir = std::filesystem::path(CLIENT_FOLDER) / scene;

        if (!std::filesystem::exists(dir)) {
            if (std::filesystem::create_directories(dir)) {
                std::cout << "[CLIENT] Create: " << dir.string() << std::endl;
            }
        }



        //std::thread(&FileClient::RequestScene, this, scene + "/" + file).detach();
        
        // [TO DO] : This will be one of the time consuming parts in downloading. Detach
        RequestScene(scene + "/" + file);
    }

    
    PrintStatus(status, "[CLIENT] Read all files.");
}

void FileClient::runClient()
{
    FileClient client(grpc::CreateChannel("localhost:" + std::to_string(PORT_NUMBER), grpc::InsecureChannelCredentials()));
    
    client.PrepFolders();
    //client.RequestScene("ServerFiles/test.jpg");
}

void FileClient::PrintStatus(const grpc::Status& status, const std::string& success_msg)
{
    if (!status.ok()) {
        std::cerr << COLOR::R << "[CLIENT] ERROR: " << status.error_message() << COLOR::W << std::endl;
    }
    else {
        std::cout << COLOR::G << success_msg << COLOR::W << std::endl;
    }
}
