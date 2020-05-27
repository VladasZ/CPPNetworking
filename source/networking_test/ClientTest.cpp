
#include "Log.hpp"
#include "Client.hpp"

using namespace net;

Client client("http://ip.jsontest.com");

void client_test() {

    client.request("userAuth", [](Response response) {
        Log(response.to_string());
    });

}
