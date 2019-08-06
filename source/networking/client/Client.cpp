//
//  Client.cpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Exception.h>
#include <Poco/Path.h>
#include <Poco/URI.h>

#include <iostream>

using namespace Poco::Net;
using namespace Poco;
using namespace std;

#include "Log.hpp"
#include "Client.hpp"

using namespace net;

Client::Client(const cu::Path& base_url) : _base_url(base_url) {
    
}

void Client::request(const cu::Path& path, CoreCompletion completion) {
    request(path, Method::GET, completion);
}

void Client::request(const URL& path, Method method, CoreCompletion completion) {
    
    URL url = _base_url / path;
    URI uri(url);
    
    HTTPClientSession session(uri.getHost(), uri.getPort());
    
    HTTPRequest request(method_to_string[method],
                        uri.getPathAndQuery(),
                        HTTPMessage::HTTP_1_1);
    
    session.sendRequest(request);
    
    HTTPResponse response;

    istream &stream = session.receiveResponse(response);
    
    string content { istreambuf_iterator<char>(stream),
                     istreambuf_iterator<char>()       };
    
    auto status = response.getReason();
    auto code   = response.getStatus();
    
    cout << "rglica" << endl;
    cout << code << " " << status << endl;
    cout << "rglica2" << endl;

    
    completion(Response("",
                        status,
                        code,
                        content,
                        Request(url, method)));
}
