#include "FileClient.h"
#include <grpcpp/create_channel.h>
#include <fstream>

#include "Settings.h"

#include "src/SceneManager.h"

#include <thread>

FileClient* FileClient::instance = nullptr;

FileClient::FileClient()
{
}


void FileClient::RequestScene(const std::string filePath)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    SceneRequest request;
    request.set_scenename(filePath);

    grpc::ClientContext context;
    std::chrono::time_point deadline = std::chrono::system_clock::now() +
        std::chrono::seconds(5);
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


    size_t scenename = filePath.find('/');

    if (filePath.substr(filePath.length() - 4) == ".obj"){
        SceneManager::instance->QueueDownloadedFile(filePath.substr(0, scenename), CLIENT_FOLDER + "/" + filePath);
    }
}




void FileClient::PrepFolders()
{
    isStreaming = true;

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


        
    }
    
    PrintStatus(status, "[CLIENT] Read all files.");

    isStreaming = false;
}


void FileClient::LoadBySceneName()
{
    isStreaming = true;

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


        if (scene == sceneToLoad)
            RequestScene(scene + "/" + file);
    }

    PrintStatus(status, "[CLIENT] Read all files.");

    this->sceneToLoad.clear();
    isStreaming = false;
}

void FileClient::Run()
{
    instance = this;
    this->stub = SceneStreamerService::NewStub(grpc::CreateChannel("localhost:" + std::to_string(PORT_NUMBER), grpc::InsecureChannelCredentials()));

    std::unique_lock<std::mutex> lck(mtx_LOAD);
    while (true) {
        this->cv_LOAD.wait(lck);

        if(!isStreaming)
            if (sceneToLoad.empty()) {
                PrepFolders();
            }
            else {
                LoadBySceneName();
            }
        else
            std::cout << COLOR::Y << "ALREADY STREAMING. Submit another request later." << COLOR::W << COLOR::W;
    }
}


void FileClient::BeginStream()
{
    this->cv_LOAD.notify_one();
}

void FileClient::BeginStream(std::string sceneName)
{
    this->sceneToLoad = sceneName;
    this->cv_LOAD.notify_one();
}



void FileClient::UnloadFolders(std::filesystem::path dir)
{
    try {
        // Iterate over the directory
        for (const auto& entry : std::filesystem::directory_iterator(dir)) {
            // Check if it's a directory
            if (std::filesystem::is_directory(entry.status())) {
                // Recursively delete contents and the directory
                UnloadFolders(entry.path());
                std::filesystem::remove_all(entry.path());  // Delete the folder and its contents
                std::cout << "Deleted folder: " << entry.path() << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error while deleting folders: " << e.what() << std::endl;
    }
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
