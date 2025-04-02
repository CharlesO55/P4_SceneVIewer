#include "FileClient.h"
#include <grpcpp/create_channel.h>

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
    stub_->SendSceneRequest(&context, request);


    /*if (status.ok()) {
        return reply.message();
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
        return "RPC failed";
    }*/
}

void FileClient::runClient()
{
    FileClient client(grpc::CreateChannel("localhost:" + std::to_string(PORT_NUMBER), grpc::InsecureChannelCredentials()));
    client.RequestScene("RANDOM SCENE JUmbo");
}