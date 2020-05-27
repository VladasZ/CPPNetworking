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


Request::Request(const URL& url, Method method) : url(url), method(method) {
    
}

string Request::to_string() const {
    return string() +
    "URL: " + url.to_string() + "\n"
    "Method:" + method_to_string[method];
}
