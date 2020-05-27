//
//  Request.cpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Request.hpp"

using namespace net;
using namespace std;


Request::Request(const URL& url, Method method) : _url(url), _method(method) {
    
}

const URL& Request::url() const {
    return _url;
}

Method Request::method() const {
    return _method;
}

string Request::to_string() const {
    return string() +
    "URL: " + std::string(_url) + "\n"
    "Method:" + method_to_string[_method];
}
