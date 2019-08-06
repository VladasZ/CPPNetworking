
#include "Log.hpp"
#include "Client.hpp"

using namespace net;

Client client("http://staging.actorspocketguide.com/apg-api");

int main() {
    
    client.request("userAuth", [](Response response) {
        Info(response.to_string());
    });
    
    return 0;
}
