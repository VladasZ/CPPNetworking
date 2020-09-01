//
//  Client.cpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include <thread>

#include <Poco/URI.h>
#include <Poco/Path.h>
#include <Poco/Exception.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPClientSession.h>

#include "Log.hpp"
#include "Client.hpp"
#include "Dispatch.hpp"
#include "ExceptionCatch.hpp"

using namespace cu;
using namespace net;
using namespace std;
using namespace Poco;
using namespace Poco::Net;


Client::Client(const cu::Path& base_url, bool async) : _base_url(base_url), async(async) {

}

void Client::request(const cu::Path& path, CoreCompletion completion) const {
    _dispatch(path, Method::GET, completion);
}

void Client::request(const URL& path, Method method, CoreCompletion completion) const {
    _dispatch(path, method, completion);
}


void Client::_dispatch(const URL& path, Method method, CoreCompletion completion) const {
    if (async) {
        Dispatch::async([=] {
            _request(path, method, completion);
        });
    }
    else {
        _request(path, method, completion);
    }
}

void Client::_request(const URL& path, Method method, CoreCompletion completion) const {

    URL url = _base_url / path;
    Request request_info(url, method);

    try {

        URI uri(url);

        HTTPClientSession session(uri.getHost(), uri.getPort());

        HTTPRequest request(method_to_string[method],
                            uri.getPathAndQuery(),
                            HTTPMessage::HTTP_1_1);

        session.sendRequest(request);

        HTTPResponse http_response;

        istream &stream = session.receiveResponse(http_response);

        string content { istreambuf_iterator<char>(stream),
                         istreambuf_iterator<char>()       };

        auto status = http_response.getReason();
        auto code   = http_response.getStatus();

        auto response = Response(status,
                                 code,
                                 content,
                                 request_info);

        auto finish = bind(completion, response);

        if (async) {
            Dispatch::on_main(finish);
        }
        else {
            finish();
        }

    }
    catch (...) {
        auto finish = bind(completion, Response(request_info, what()));

        if (async) {
            Dispatch::on_main(finish);
        }
        else {
            finish();
        }
    }

}
