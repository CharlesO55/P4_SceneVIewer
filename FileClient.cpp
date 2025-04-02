#include "FileClient.h"
#include <grpcpp/create_channel.h>
#include <fstream>

#include "Settings.h"


FileClient::FileClient(std::shared_ptr<grpc::ChannelInterface> channel)
{
	this->stub_ = SceneStreamer::NewStub(channel);
}

void FileClient::RequestScene(const std::string sceneName)
{
    SceneRequest request;
    request.set_scenename(sceneName);

    grpc::ClientContext context;
    std::chrono::time_point deadline = std::chrono::system_clock::now() +
        std::chrono::milliseconds(2000);
    context.set_deadline(deadline);

    //grpc::Status status = 
    //stub_->SendSceneRequest(&context, request);

    std::unique_ptr<grpc::ClientReader<FileChunkReply>> reader(stub_->SendSceneRequest(&context, request));


    // Open output file
    std::ofstream output_file("ClientFiles/received_file.jpg", std::ios::binary);

    FileChunkReply reply;
    while (reader->Read(&reply)) {

        std::cout << reply.chunk1024().size() << std::endl;
        output_file.write(reply.chunk1024().data(), reply.chunk1024().size());
    }

    grpc::Status status = reader->Finish();
    if (!status.ok()) {
        std::cerr << COLOR::R << "[CLIENT] ERROR: " << status.error_message() << COLOR::W << std::endl;
    }
    else {
        std::cout << COLOR::G << "File received successfully." << COLOR::W << std::endl;
    }

    output_file.close();
}

void FileClient::runClient()
{
    FileClient client(grpc::CreateChannel("localhost:" + std::to_string(PORT_NUMBER), grpc::InsecureChannelCredentials()));
    client.RequestScene("ServerFiles/test.jpg");
}