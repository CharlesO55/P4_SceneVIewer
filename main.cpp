//#include "GreeterServer.h"
//#include "GreeterClient.h"


#include "FileServer.h"
#include "FileClient.h"

#include <thread>

int main()
{
    // Async run
    FileServer fServer;
    fServer.start();
    

    //Wait for server to startup
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    FileClient::runClient();
    
    /*for (int i = 0; i < users.size(); i++) {
        std::thread([username = users[i].name, repeat = users[i].repetitions, message=users[i].message]() {

            GreeterClient::runClientLooped(username, repeat, message);
                }).detach();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }*/

    std::this_thread::sleep_for(std::chrono::seconds(10));
}