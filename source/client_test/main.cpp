
#include "Log.hpp"
#include "Client.hpp"

using namespace net;

Client client("127.0.0.1");

int main() {
    
    client.request("userAuth", [](Response response) {
        Info(response.to_string());
    });
    
    return 0;
}
