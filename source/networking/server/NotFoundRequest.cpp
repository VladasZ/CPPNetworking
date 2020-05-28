
#include "NotFoundRequest.hpp"

using namespace std;
using namespace Poco::Net;

void NotFoundRequest::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
    response.setStatus(HTTPResponse::HTTP_NOT_FOUND);
    response.setReason("NOT FOUND");
    response.send() << "NOT FOUND";
}
