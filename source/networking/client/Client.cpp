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

    Dispatch::Task finish;

    try {
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

        auto finish = [=] {
            completion(Response(status,
                                code,
                                content,
                                request_info));
        };

    }
    catch (Poco::Exception ex) {

        Logvar(ex.message());
     //   Logvar(ex.displayText());
        Logvar(ex.className());


        if (async) {
            Dispatch::on_main([=] { completion(Response(request_info, what())); });
        }
        else {
            completion(Response(request_info, what()));
        }
    }

    if (async) {
        Dispatch::on_main(finish);
    }
    else {
        finish();
    }

}
