//
//  NetworkingTypes.cpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "NetworkingTypes.hpp"

using namespace net;

const std::unordered_map<Method, std::string> method_to_string = {
    { Method::GET,  "GET"  },
    { Method::POST, "POST" }
};

std::unordered_map<std::string, Method> string_to_method = {
    { "GET",  Method::GET  },
    { "POST", Method::POST }
};
