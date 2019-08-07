
#include "Log.hpp"
#include "Client.hpp"

using namespace net;

Client client("http://localhost/");

int main() {
    
    client.request("userAuth", [](Response response) {
        Info(response.to_string());
    });
    
    return 0;
}
