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

using namespace cu;
using namespace net;

Client::Client(const cu::Path& base_url) : base_url(base_url) {
    
}

void Client::request(const cu::Path& path, Completion completion) {
    request(path, Method::GET, completion);
}

void Client::request(const cu::Path& p, Method method, Completion completion) {
    URI uri(base_url + "/" + p);
    HTTPClientSession session(uri.getHost(), uri.getPort());
    
    // prepare path
    std::string path(uri.getPathAndQuery());
    if (path.empty())
        path = "/";
    
    // send request
    HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
    session.sendRequest(req);
    
    // get response
    HTTPResponse res;
    cout << res.getStatus() << " " << res.getReason() << endl;
    
    // print response
    istream &is = session.receiveResponse(res);
    
    std::string content{ std::istreambuf_iterator<char>(is),
        std::istreambuf_iterator<char>() };
    
    Info(content);
}
